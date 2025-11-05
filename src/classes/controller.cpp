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
    if(!WorldController::get_singleton()->can_play()) {
        return;
    }

    player_cmd = bridge->get_user_cmd();

    print_line("Buttons Pressed: " + String::num(player_cmd.buttons));
    print_line("Mouse Delta: " + String(player_cmd.view_delta));
    print_line("angle_view: " + String::num(player_cmd.view_angles[0]) + ", " + String::num(player_cmd.view_angles[1]));
    print_line("Forward Move: " + String::num(player_cmd.forward_move));
    
    /* proceso
        recibe un delta de tiempo y actualiza el personaje poseido
        si el personaje es nulo, no hace nada

        tambien se encarga de recibir los comandos del usuario
        y pasarlos al personaje poseido
    */
    // UserCmd cmd = get_current_user_cmd();

    // print_line("Buttons Pressed: " + String::num(cmd.buttons));
    // print_line("Mouse Delta: " + String(cmd.mouse_delta));
    // print_line("angle_view: " + String::num(cmd.view_angles[0]) + ", " + String::num(cmd.view_angles[1]));
    //  print_line("Forward Move: " + String::num(cmd.forward_move));
    
    // UserCmd cmd = input_handler->get_current_user_cmd();
    // character->move(cmd.forward_move, cmd.side_move, cmd.up_move);
    // character->rotate(cmd.mouse_delta);
    // character->do_action(cmd.buttons);
}

void Controller::_ready()
{
    /* listo
        se llama cuando el nodo esta listo
        inicializa el controlador y el obtiene el nodo hijo personaje asignado al character
    */
    // input_handler = InputHandler::get_singleton();
    Character *aux_node = get_node<Character>("Character");
    bridge = GDBridge::get_singleton();
    if (aux_node != nullptr)
    {
        possess(aux_node);
    }
    else
    {
        ERR_PRINT("No Character node found to possess.");
    }
}

void Controller::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("possess", "character"), &Controller::possess);
    ClassDB::bind_method(D_METHOD("depossess"), &Controller::depossess);
}
