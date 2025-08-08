#include "controller.h"

void Controller::_bind_methods() {
    ClassDB::bind_method(D_METHOD("possess", "character"), &Controller::possess);
    ClassDB::bind_method(D_METHOD("depossess"), &Controller::depossess);
}

Controller::Controller() {}
Controller::~Controller() {}

void Controller::possess(Character *character) {
    if (character == nullptr) {
        ERR_PRINT("Cannot possess a null character.");
        return;
    }
    this->character = character;
    input = Input::get_singleton();
}

Character *Controller::depossess() {
    if (character == nullptr) {
        ERR_PRINT("Cannot depose a null character.");
        return nullptr;
    }

    Character *temp_character = character;
    character = nullptr;
    input = nullptr;
    return temp_character;
}

void Controller::_process(double delta) {}

void Controller::_input(const Ref<InputEvent> &event) {

    input = Input::get_singleton();
    Ref<InputEventMouseMotion> motion_event = event;

    if (character != nullptr) {
        Vector3 direction; 
        if (input->is_action_just_pressed("debug_mode")) {
            if (input->get_mouse_mode() == Input::MOUSE_MODE_CAPTURED) {
                input->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
            } else {
                input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
            }
        }
        if (motion_event.is_valid() && input->get_mouse_mode() == Input::MOUSE_MODE_CAPTURED) {
            Vector2 mouse_delta = motion_event->get_relative();
            character->rotate(mouse_delta);
        }

        Vector2 input_vector = input->get_vector("action_left", "action_right", "action_forward", "action_backward");
        direction.x = input_vector.x;
        direction.z = input_vector.y;

        character->move(direction);
        if (input->is_action_just_pressed("action_jump")) character->do_action(JUMP);
        if (input->is_action_just_pressed("action_crouch")) character->do_action(CROUCH);
        if (input->is_action_just_pressed("action_run")) character->do_action(RUN);
        if (input->is_action_just_pressed("action_shoot")) character->do_action(SHOOT);
        if (input->is_action_just_pressed("action_reload")) character->do_action(RELOAD);
    } else {
        ERR_PRINT("Controller has no character to control.");
    }
}

void Controller::_ready()
{
    Character *aux_node = get_node<Character>("Character");
    if (aux_node != nullptr) {
        possess(aux_node);
    } else {
        ERR_PRINT("No Character node found to possess.");
    }
}