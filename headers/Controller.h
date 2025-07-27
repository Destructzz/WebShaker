#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

class Controller {
public:
    bool initialize();  // Инициализация контроллера
    ~Controller();      // Деструктор

    bool isPressed(Uint8 button);  // Проверка нажатия кнопки
    SDL_GameController* GetController();  // Получение контроллера

protected:
    SDL_GameController* controller = nullptr;
};
