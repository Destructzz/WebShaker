#pragma once
#include <thread>
#include <atomic>
#include <functional>
#include "../headers/RuleManager.h"

class ExecutionManager {
protected:
    std::thread t;  // Поток выполнения
    std::atomic<bool> is_running = false;  // Флаг для контроля выполнения

public:
    RuleManager tern_rule;  // Объект класса RuleManager
    std::function<void()> sh_rule;  // Функция, которая будет вызываться при срабатывании правила

    // Асинхронный запуск выполнения
    void async();

    // Остановка выполнения
    void stop();
};
