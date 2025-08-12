#include "controller.h"

void Controller::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("possess", "character"), &Controller::possess);
    ClassDB::bind_method(D_METHOD("depossess"), &Controller::depossess);
}

Controller::Controller() {}
Controller::~Controller() {}

void Controller::possess(Character *character)
{
    if (character == nullptr)
    {
        ERR_PRINT("Cannot possess a null character.");
        return;
    }
    this->character = character;
    input = Input::get_singleton();
}

Character *Controller::depossess()
{
    if (character == nullptr)
    {
        ERR_PRINT("Cannot depose a null character.");
        return nullptr;
    }

    Character *temp_character = character;
    character = nullptr;
    input = nullptr;
    return temp_character;
}

void Controller::_process(double delta) {}

void Controller::_input(const Ref<InputEvent> &event)
{

    UserCmd cmd = InputHandler::create_usercmd(event);

    if (character != nullptr)
    {
        cmd = InputHandler::create_usercmd(event);
        character->move(Vector3(cmd.forward_move, cmd.up_move, cmd.right_move));
        character->rotate(cmd.mouse_delta);
        character->do_action(cmd.buttons);
    }
    else
    {
        ERR_PRINT("Controller has no character to control.");
    }
}

void Controller::_ready()
{
    Character *aux_node = get_node<Character>("Character");
    if (aux_node != nullptr)
    {
        possess(aux_node);
    }
    else
    {
        ERR_PRINT("No Character node found to possess.");
    }
}