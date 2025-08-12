#include "character.h"

Character::Character() {}
Character::~Character() {}

void Character::_bind_methods()
{
}


void Character::move(Vector3 direction)
{
    this->direction = direction.normalized();
}

void Character::rotate(Vector2 delta)
{
    this->mouse_delta = delta;
}


void Character::do_action(uint32_t action)
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
    if (current_actions & IN_JUMP)
    {
        if (is_on_floor())
        {
            velocity.y = 5.0;
        }
        current_actions &= ~IN_JUMP;
    }
    if (current_actions & IN_CROUCH)
    {
        current_actions &= ~IN_CROUCH;
    }
    if (current_actions & IN_RUN)
    {
        current_actions &= ~IN_RUN;
    }
    set_velocity(velocity);
    move_and_slide();
}

void Character::looking(double delta)
{
    double yaw = mouse_delta.x * delta * 0.1;
    rotate_y(yaw);

    if (current_actions & IN_ACTION)
    {
        godot::print_line("Shooting logic not implemented yet.");
        current_actions &= ~IN_ACTION;
    }
    if (current_actions & IN_RELOAD)
    {
        godot::print_line("Reloading logic not implemented yet.");
        current_actions &= ~IN_RELOAD;
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