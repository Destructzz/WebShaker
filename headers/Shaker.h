#pragma once
#include <mutex>
#include <Windows.h>

class Shaker {
protected:
    mutable std::mutex mtx;  // Мьютекс для синхронизации

public:
    // Перемещение курсора на dx, dy
    void move_cursor(int dx, int dy) const;
    void sendMoveCommand(int dx, int dy);
};

