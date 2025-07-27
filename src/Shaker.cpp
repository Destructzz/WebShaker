#define ASIO_STANDALONE
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WINSOCKAPI_  // предотвращает конфликт с winsock.h

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <asio.hpp>

#include <iostream>
#include <sstream>
#include <mutex>
#include "../headers/Shaker.h"

void Shaker::move_cursor(int dx, int dy) const {
    std::lock_guard<std::mutex> lock(mtx);
    mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
}

void Shaker::sendMoveCommand(int dx, int dy) {
    setlocale(LC_ALL, "Russian");

    try {
        std::ostringstream oss;
        oss << "MOVE " << dx << " " << dy << "\n";
        std::string command = oss.str();

        asio::io_context io;
        asio::serial_port port(io, "COM5");

        port.set_option(asio::serial_port_base::baud_rate(9600));
        port.set_option(asio::serial_port_base::character_size(8));
        port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
        port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
        port.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));

        asio::write(port, asio::buffer(command));
        std::cout << "Команда отправлена: " << command;

        port.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка отправки: " << e.what() << std::endl;
    }
}
