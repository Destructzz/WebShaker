#pragma once
#include <Windows.h>
#include <thread>
#include <cmath>
#include <chrono>

class Speed {
protected:
    POINT prev_pos = { 0, 0 };  // Предыдущее положение курсора
    POINT cur_pos = { 0, 0 };   // Текущее положение курсора
    double speed = 0;           // Скорость в точках/миллисекунду
    std::thread check;          // Поток для мониторинга скорости

public:
    Speed();  // Конструктор
    ~Speed();  // Деструктор

    double time() const;  // Метод для получения скорости
};

