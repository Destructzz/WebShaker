#include "../headers/Controller.h"

// ����������
Controller::~Controller() {
    if (controller) {
        SDL_GameControllerClose(controller);
    }
    SDL_Quit();
}

// ����� �������������
bool Controller::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "SDL �� ������������������: " << SDL_GetError() << std::endl;
        return false;
    }
    if (SDL_NumJoysticks() < 1) {
        std::cerr << "���������� �� ������!" << std::endl;
        return false;
    }

    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            controller = SDL_GameControllerOpen(i);
            if (controller) {
                std::cout << "���������� ���������: " << SDL_GameControllerName(controller) << std::endl;
                break;
            }
        }
    }

    if (!controller) {
        std::cerr << "�� ������� ������� ����������!" << std::endl;
        return false;
    }

    return true;
}

// ����� �������� ������� ������
bool Controller::isPressed(Uint8 button) {
    SDL_GameControllerUpdate();

    if (button == SDL_CONTROLLER_AXIS_TRIGGERLEFT || button == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) {
        int value = SDL_GameControllerGetAxis(controller, static_cast<SDL_GameControllerAxis>(button));
        return value > 16000;  // ����� ����������������
    }
    else {
        return SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(button)) == 1;
    }
}

// ����� ��� ��������� �����������
SDL_GameController* Controller::GetController() {
    return controller;
}
