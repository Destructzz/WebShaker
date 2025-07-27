#pragma once
#include <map>
#include <string>
#include <functional>
#include <stdexcept>

class RuleManager {
protected:
    std::map<std::string, std::function<bool()>> storage;  // Хранение правил

    std::string main_key;  // Текущий ключ
    std::function<bool()> main_rule;  // Текущая функция правила
public:
    RuleManager() {}  // Конструктор

    void add_rule(const std::string& key, std::function<bool()> function);  // Добавление правила
    void apply_rule(const std::string& key);  // Применение правила по ключу
    std::string what_rule();  // Какое правило используется

    bool use();  // Использование текущего правила
};

