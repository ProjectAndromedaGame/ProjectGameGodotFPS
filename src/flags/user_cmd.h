#ifndef USER_CMD_H
#define USER_CMD_H

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

struct UserCmd
{
    int comand_number = 0;
    Vector2 view_angles;
    Vector3 move_delta;
    int buttons = 0;
    Vector2 mouse_delta;
};

enum ButtonFlags {
    IN_JUMP = 1 << 0,
    IN_CROUCH = 1 << 1,
    IN_RUN = 1 << 2,
    IN_ACTION = 1 << 3,
    IN_ACTION2 = 1 << 4,
    IN_SWAPW = 1 << 5,
    IN_RELOAD = 1 << 6,
    DEBUG_MODE = 1 << 7,
};


#endif