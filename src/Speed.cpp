#include "../headers/Speed.h"

// Конструктор
Speed::Speed() {
    check = std::thread([this]() {
        while (true) {
            GetCursorPos(&cur_pos);  // Получаем текущее положение курсора
            speed = std::sqrt(std::pow(cur_pos.x - prev_pos.x, 2) + std::pow(cur_pos.y - prev_pos.y, 2));
            prev_pos = cur_pos;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Пауза в 1 миллисекунду
        }
        });

    check.detach();  // Отсоединяем поток
}

// Деструктор
Speed::~Speed() {
    if (check.joinable()) {
        check.join();
    }
}

// Метод для получения текущей скорости
double Speed::time() const {
    return speed;  // Возвращаем рассчитанную скорость
}
