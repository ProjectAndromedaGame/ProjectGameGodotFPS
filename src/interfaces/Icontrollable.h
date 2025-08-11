#ifndef ICONTROLLABLE_H
#define ICONTROLLABLE_H

#include <godot_cpp/variant/vector3.hpp> // Add this include for Vector3
#include "action_flags.h"

using namespace godot;


class IControllable {
public:
    virtual void move(Vector3 direction) = 0;
    virtual void rotate(Vector2 delta) = 0;

    virtual void do_action(ActionFlags action) = 0;

    virtual void moving(double delta) = 0;
    virtual void looking(double delta) = 0;

    virtual ~IControllable() {}
};

#endif // ICONTROLLABLE_H