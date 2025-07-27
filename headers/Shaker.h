#pragma once
#include <mutex>
#include <Windows.h>

class Shaker {
protected:
    mutable std::mutex mtx;  // ������� ��� �������������

public:
    // ����������� ������� �� dx, dy
    void move_cursor(int dx, int dy) const;
    void sendMoveCommand(int dx, int dy);
};

