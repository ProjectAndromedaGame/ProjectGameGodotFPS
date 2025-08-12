#include "input_handler.h"

uint32_t InputHandler::get_buttons_flags(Input *input){
    uint32_t buttons = 0;

    for (const auto& binding : control_bindings) {
        if (input->is_action_pressed(binding.action)) {
            buttons |= binding.flag;
        }
    }
    return buttons;
}
UserCmd InputHandler::create_usercmd(const Ref<InputEvent> &event){
    static int cmd_id = 0;
    Input *input = Input::get_singleton();
    Ref<InputEventMouseMotion> motion_event = event;
    UserCmd cmd;

    Vector2 input_vector = input->get_vector("action_left", "action_right", "action_forward", "action_backward");

    cmd.comand_number = cmd_id++;
    cmd.view_angles = Vector2();
    cmd.forward_move = input_vector.y;
    cmd.right_move = input_vector.x;
    cmd.up_move = 0.0f;
    cmd.buttons = get_buttons_flags(input);
    cmd.mouse_delta = Vector2();

    return cmd;
}

