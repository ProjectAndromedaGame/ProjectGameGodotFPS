#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include "user_cmd.h"

class InputHandler
{
private:
    
    /* data */
public:
    InputHandler(/* args */);
    ~InputHandler();
    int get_buttons_flags(Input *input);
    UserCmd create_usercmd(const Ref<InputEvent> &event);
};

#endif