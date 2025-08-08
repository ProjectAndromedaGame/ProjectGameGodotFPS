#include "character.h"

Character::Character() {}
Character::~Character() {}

void Character::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("move", "direction"), &Character::move);
    ClassDB::bind_method(D_METHOD("rotate", "delta"), &Character::rotate);
    ClassDB::bind_method(D_METHOD("do_action", "action"), &Character::do_action);
    ClassDB::bind_method(D_METHOD("moving", "delta"), &Character::moving);
    ClassDB::bind_method(D_METHOD("looking", "delta"), &Character::looking);
}


void Character::move(Vector3 direction)
{
    this->direction = direction.normalized();
}

void Character::rotate(Vector2 delta)
{
    this->mouse_delta = delta;
}


void Character::do_action(ActionFlags action)
{
    current_actions |= action;
}

void Character::moving(double delta)
{
    double gravity = ProjectSettings::get_singleton()->get("physics/3d/default_gravity");
    Vector3 velocity = get_velocity();
    Vector3 aux_direction = direction * speed;
    velocity.x = aux_direction.x;
    velocity.z = aux_direction.z;
    if (!is_on_floor())
    {
        velocity.y -= gravity * delta;
    }
    else
    {
        velocity.y = 0;
    }
    if (current_actions & JUMP)
    {
        if (is_on_floor())
        {
            velocity.y = 5.0;
        }
        current_actions &= ~JUMP;
    }
    if (current_actions & CROUCH)
    {
        current_actions &= ~CROUCH;
    }
    if (current_actions & RUN)
    {
        current_actions &= ~RUN;
    }
    set_velocity(velocity);
    move_and_slide();
}

void Character::looking(double delta)
{
    double yaw = mouse_delta.x * delta * 0.1;
    rotate_y(yaw);

    if (current_actions & SHOOT)
    {
        godot::print_line("Shooting logic not implemented yet.");
        current_actions &= ~SHOOT;
    }
    if (current_actions & RELOAD)
    {
        godot::print_line("Reloading logic not implemented yet.");
        current_actions &= ~RELOAD;
    }
}

void Character::_physics_process(double delta)
{
    moving(delta);
}

void Character::_process(double delta)
{
    looking(delta);
}

void Character::_ready()
{
}