#ifndef ACTION_FLAGS_H
#define ACTION_FLAGS_H

#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

struct UserCmd
{
    int comand_number = 0;
    Vector2 view_angles;
    float forward_move = 0.0f;
    float right_move = 0.0f;
    float up_move = 0.0f;
    uint32_t buttons = 0;
    Vector2 mouse_delta;
};


enum ButtonFlags
{
    NONE = 0,
    IN_JUMP = 1 << 0,
    IN_CROUCH = 1 << 1,
    IN_RUN = 1 << 2,
    IN_ACTION = 1 << 3,
    IN_ACTION2 = 1 << 4,
    IN_SWAP_ITEM1 = 1 << 5,
    IN_RELOAD = 1 << 6,
    DEBUG_MODE = 1 << 7,
};

struct ControlBinding {
    String action;
    uint32_t flag;
}; // <-- semicolon added

static const ControlBinding control_bindings[] = {
    {"JUMP", IN_JUMP},
    {"CROUCH", IN_CROUCH},
    {"RUN", IN_RUN},
    {"ACTION", IN_ACTION},
    {"ACTION2", IN_ACTION2},
    {"SWAP_ITEM1", IN_SWAP_ITEM1},
    {"RELOAD", IN_RELOAD},
    {"DEBUG_MODE", DEBUG_MODE}
};

#endif