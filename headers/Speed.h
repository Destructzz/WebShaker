#pragma once
#include <Windows.h>
#include <thread>
#include <cmath>
#include <chrono>

class Speed {
protected:
    POINT prev_pos = { 0, 0 };  // ���������� ��������� �������
    POINT cur_pos = { 0, 0 };   // ������� ��������� �������
    double speed = 0;           // �������� � ������/������������
    std::thread check;          // ����� ��� ����������� ��������

public:
    Speed();  // �����������
    ~Speed();  // ����������

    double time() const;  // ����� ��� ��������� ��������
};

