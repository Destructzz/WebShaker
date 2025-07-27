#include "../headers/Speed.h"

// �����������
Speed::Speed() {
    check = std::thread([this]() {
        while (true) {
            GetCursorPos(&cur_pos);  // �������� ������� ��������� �������
            speed = std::sqrt(std::pow(cur_pos.x - prev_pos.x, 2) + std::pow(cur_pos.y - prev_pos.y, 2));
            prev_pos = cur_pos;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  // ����� � 1 ������������
        }
        });

    check.detach();  // ����������� �����
}

// ����������
Speed::~Speed() {
    if (check.joinable()) {
        check.join();
    }
}

// ����� ��� ��������� ������� ��������
double Speed::time() const {
    return speed;  // ���������� ������������ ��������
}
