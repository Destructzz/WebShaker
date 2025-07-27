#pragma once
#include <map>
#include <string>
#include <functional>
#include <stdexcept>

class RuleManager {
protected:
    std::map<std::string, std::function<bool()>> storage;  // �������� ������

    std::string main_key;  // ������� ����
    std::function<bool()> main_rule;  // ������� ������� �������
public:
    RuleManager() {}  // �����������

    void add_rule(const std::string& key, std::function<bool()> function);  // ���������� �������
    void apply_rule(const std::string& key);  // ���������� ������� �� �����
    std::string what_rule();  // ����� ������� ������������

    bool use();  // ������������� �������� �������
};

