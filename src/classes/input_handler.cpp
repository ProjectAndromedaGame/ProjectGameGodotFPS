#include "input_handler.h"

int get_button_flags(Input *input){
    int buttons = 0;
    
    if (input->is_action_pressed("action_jump")){
        buttons |= IN_JUMP;
    }
    if (input->is_action_pressed("action_crouch")){
        buttons |= IN_CROUCH;
    }
    if (input->is_action_pressed("action_run")){
        buttons |= IN_RUN;
    }
    if (input->is_action_pressed("action_shoot")){
        buttons |= IN_ACTION;
    }
    if (input->is_action_pressed("action_aim")){
        buttons |= IN_ACTION2;
    }
    if (input->is_action_pressed("action_switch_weapon")){
        buttons |= IN_SWAPW;
    }
    if (input->is_action_pressed("action_reload")){
        buttons |= IN_RELOAD;
    }
    if (input->is_action_pressed("debug_mode")){
        buttons |= DEBUG_MODE;
    }
    return buttons;
}

UserCmd create_usercmd(const Ref<InputEvent> &event){
    static int cmd_id = 0;
    Input *input = Input::get_singleton();
    Ref<InputEventMouseMotion> motion_event = event;
    UserCmd cmd;
    Vector3 direction;


    Vector2 input_vector = input->get_vector("action_left", "action_right", "action_forward", "action_backward"); 

    direction.x = input_vector.x;
    direction.z = input_vector.y;

    cmd.comand_number = cmd_id++;
    cmd.view_angles = Vector2();
    cmd.buttons = get_button_flags(input);
    cmd.mouse_delta = motion_event->get_relative();
}

