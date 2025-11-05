#include "character.h"

Character::Character() {}
Character::~Character() {}

void Character::move(float forward, float right, float up)
{
    /* input de movimiento
        Recibe tres valores: adelante, derecha, arriba y mueve el personaje en esa direccion
        adelante y derecha son valores entre -1 y 1, arriba es un valor que puede ser positivo o negativo
        por ejemplo, adelante = 1, derecha = 0, arriba = 0 mueve el personaje hacia adelante
        adelante = 0, derecha = 1, arriba = 0 mueve el personaje hacia la derecha
        adelante = 0, derecha = 0, arriba = 1 mueve el personaje hacia arriba
        void Character::move(float forward, float right, float up) */
    Vector3 direction = Vector3(right, up, forward);
    this->direction = direction.normalized();
}

void Character::rotate(Vector2 delta)
{
    /* input de rotacion
        recibe un Vector2 con el delta del mouse
        y rota el personaje en base a ese delta
    */
    this->mouse_delta = delta;
}

void Character::do_action(int32_t action)
{
    /* input de acciones
        recibe un entero que representa la accion a realizar
    */
    current_actions |= action;
}

void Character::moving(double delta)
{
    double gravity = ProjectSettings::get_singleton()->get("physics/3d/default_gravity");
    Vector3 velocity = get_velocity();
    Vector3 relative_direction = get_global_transform().basis.xform(direction);
    Vector3 aux_direction = relative_direction * speed;
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
    // Reset mouse delta after processing

    if (current_actions & IN_SHOOT)
    {
        godot::print_line("Shooting logic not implemented yet.");
        current_actions &= ~IN_SHOOT;
    }
    if (current_actions & IN_RELOAD)
    {
        godot::print_line("Reloading logic not implemented yet.");
        current_actions &= ~IN_RELOAD;
    }
}

EntityType Character::get_entity_type() const
{
    return EntityType::ENTITY_PLAYER;
}

int32_t Character::get_entity_id() const
{
    return 0; // ID del jugador, implementar segun sistema de IDs
}

int Character::get_team() const
{
    return 0; // Equipo del jugador, implementar segun sistema de equipos
}

Vector3 Character::get_world_position() const
{
    return get_global_transform().origin;
}

float Character::get_health() const
{
    return health;
}

bool Character::is_alive() const
{
    return health > 0;
}

void Character::take_damage(float damage, IEntity* source)
{
    health -= damage;
    if (health <= 0)
    {
        health = 0;
        on_death(source);
    }
    else
    {
        on_damaged(damage, source);
    }
}

void Character::destroy() {
    queue_free();
}


void Character::_physics_process(double delta)
{
    moving(delta);
    looking(delta);
}

void Character::_bind_methods()
{
    // metodos que se pueden llamar desde GDScript
    ClassDB::bind_method(D_METHOD("move", "direction"), &Character::move);
    ClassDB::bind_method(D_METHOD("rotate", "delta"), &Character::rotate);
    ClassDB::bind_method(D_METHOD("do_action", "action"), &Character::do_action);
    ClassDB::bind_method(D_METHOD("moving", "delta"), &Character::moving);
    ClassDB::bind_method(D_METHOD("looking", "delta"), &Character::looking);
}