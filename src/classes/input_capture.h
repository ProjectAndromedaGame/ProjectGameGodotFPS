#ifndef INPUT_CAPTURE_H
#define INPUT_CAPTURE_H

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include "user_cmd.h"

class InputCapture{
private:
    /* data */
public:
    InputCapture(/* args */);
    ~InputCapture();
    int get_buttons_flags(Input *input);
    UserCmd create_usercmd(const Ref<InputEvent> &event); 
};



#endif