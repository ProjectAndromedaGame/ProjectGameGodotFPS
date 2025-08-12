#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include "flags/action_flags.h"

class InputHandler
{
private:
        /* data */
public:
    InputHandler(/* args */);
    ~InputHandler();
    static uint32_t get_buttons_flags(Input *input);
    static UserCmd create_usercmd(const Ref<InputEvent> &event);
};

#endif