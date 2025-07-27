#pragma once
#include <atomic>
#include <functional>
#include <thread>

class ToggleManager {
protected:
	std::atomic<bool> is_pressed = false;
	std::atomic<bool> stop_thread = false;
	std::thread toggle_thread;

	std::function<bool()> rule;
public:
	int iteration_time;
	int delay_time;
	ToggleManager(std::function<bool()> rule, int iteration_time, int delay_time);

	~ToggleManager();

	bool get_state() const;
};
