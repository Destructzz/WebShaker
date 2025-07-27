#include "../headers/RuleManager.h"

// Добавление правила в хранилище
void RuleManager::add_rule(const std::string& key, std::function<bool()> function) {
    storage[key] = function;
    if (storage.size() == 1)
        apply_rule(key);
}

// Применение правила по ключу
void RuleManager::apply_rule(const std::string& key) {
    if (storage.find(key) != storage.end()) {
        main_rule = storage[key];
        main_key = key;
    }
    else {
        throw std::runtime_error("Правило с ключом '" + key + "' не найдено.");
    }
}

// Возвращение ключа текущего правила
std::string RuleManager::what_rule() {
    return main_key;
}

// Использование текущего правила (возвращение значения текущей функции)
bool RuleManager::use() {
    return main_rule();
}
