#include "../headers/RuleManager.h"

// ���������� ������� � ���������
void RuleManager::add_rule(const std::string& key, std::function<bool()> function) {
    storage[key] = function;
    if (storage.size() == 1)
        apply_rule(key);
}

// ���������� ������� �� �����
void RuleManager::apply_rule(const std::string& key) {
    if (storage.find(key) != storage.end()) {
        main_rule = storage[key];
        main_key = key;
    }
    else {
        throw std::runtime_error("������� � ������ '" + key + "' �� �������.");
    }
}

// ����������� ����� �������� �������
std::string RuleManager::what_rule() {
    return main_key;
}

// ������������� �������� ������� (����������� �������� ������� �������)
bool RuleManager::use() {
    return main_rule();
}
