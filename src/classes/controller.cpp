#include "controller.h"
#include <memory>

Controller::Controller() {}
Controller::~Controller() {}

void Controller::possess(Character *character)
{
    /* posesion
        recibe un puntero a un personaje y lo asigna al controlador
        si el personaje es nulo, imprime un error
        si el controlador ya tiene un personaje, no hace nada
    */
    if (character == nullptr)
    {
        ERR_PRINT("Cannot possess a null character.");
        return;
    }
    this->character = character;
}

Character *Controller::depossess()
{
    /* desposeer
        devuelve un puntero al personaje poseido y lo designa del controlador
        si el personaje es nulo imprime un error
    */
    if (character == nullptr)
    {
        ERR_PRINT("Cannot depose a null character.");
        return nullptr;
    }

    Character *temp_character = character;
    character = nullptr;
    return temp_character;
}

void Controller::_physics_process(double delta)
{
    if (!WorldController::get_singleton()->can_play())
    {
        return;
    }

    player_cmd = bridge->get_user_cmd();

    if (character)
    {
        character->move(-player_cmd.forward_move, player_cmd.side_move, player_cmd.up_move);
        character->rotate(player_cmd.view_angles);
        character->do_action(player_cmd.buttons);
    }
}

void Controller::_ready()
{
    // Remover try/catch - código directo
    bridge = GDBridge::get_singleton();

    if (!bridge)
    {
        ERR_PRINT("GDBridge singleton not found.");
        return;
    }

    character = get_node<Character>("Character");

    if (!character)
    {
        ERR_PRINT("Character node not found.");
        return;
    }

    print_line("Controller initialized successfully.");
}

void Controller::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("possess", "character"), &Controller::possess);
    ClassDB::bind_method(D_METHOD("depossess"), &Controller::depossess);
}
