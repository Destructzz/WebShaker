#include "../headers/ExecutionManager.h"

// ����������� ������ ����������
void ExecutionManager::async() {
	if (!is_running) {
		is_running = true;

		t = std::thread([this]() {
			while (is_running) {
				if (tern_rule.use()) {
					sh_rule();
				}
				else {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
			});
		t.detach();
	}
}

// ��������� ����������
void ExecutionManager::stop() {
	is_running = false;
	if (t.joinable()) {
		t.join();
	}
}
