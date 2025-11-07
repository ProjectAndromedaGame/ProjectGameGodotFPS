#ifndef USER_CMD_H
#define USER_CMD_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/string.hpp>

using namespace godot;

enum ButtonFlags : uint32_t
{
    NONE = 0,
    IN_JUMP = 1 << 0,
    IN_CROUCH = 1 << 1,
    IN_RUN = 1 << 2,
    IN_SHOOT = 1 << 3,
    IN_AIM = 1 << 4,
    IN_RELOAD = 1 << 5,
};

struct UserCmd
{
    int64_t seq = 0;
    int64_t tick = 0;
    double dt = 0.0;
    Vector2 view_angles = Vector2(0, 0);
    Vector2 view_delta = Vector2(0, 0);
    float forward_move = 0;
    float side_move = 0;
    float up_move = 0;
    uint32_t buttons = 0;
};

#endif
