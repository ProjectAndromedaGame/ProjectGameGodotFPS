#ifndef ICONTROLLABLE_H
#define ICONTROLLABLE_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "user_cmd.h"

using namespace godot;

class IControllable
{
public:
    virtual void move(float forward, float right, float up) = 0;
    virtual void rotate(Vector2 delta) = 0;

    virtual void do_action(int32_t action) = 0;

    virtual ~IControllable() {}

private:
    virtual void moving(double delta) = 0;
    virtual void looking(double delta) = 0;
};

#endif // ICONTROLLABLE_H