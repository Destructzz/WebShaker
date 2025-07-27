#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

class Controller {
public:
    bool initialize();  // ������������� �����������
    ~Controller();      // ����������

    bool isPressed(Uint8 button);  // �������� ������� ������
    SDL_GameController* GetController();  // ��������� �����������

protected:
    SDL_GameController* controller = nullptr;
};
