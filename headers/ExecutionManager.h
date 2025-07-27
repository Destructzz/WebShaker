#pragma once
#include <thread>
#include <atomic>
#include <functional>
#include "../headers/RuleManager.h"

class ExecutionManager {
protected:
    std::thread t;  // ����� ����������
    std::atomic<bool> is_running = false;  // ���� ��� �������� ����������

public:
    RuleManager tern_rule;  // ������ ������ RuleManager
    std::function<void()> sh_rule;  // �������, ������� ����� ���������� ��� ������������ �������

    // ����������� ������ ����������
    void async();

    // ��������� ����������
    void stop();
};
