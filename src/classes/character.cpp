#include "character.h"

Character::Character() {}
Character::~Character() {}

void Character::move(float forward, float right, float up)
{
    /* input de movimiento
        Recibe tres valores: adelante, derecha, arriba y mueve el personaje en esa direccion
        adelante y derecha son valores entre -1 y 1, arriba es un valor que puede ser positivo o negativo */
    Vector3 direction = Vector3(right, up, forward);
    this->direction = direction.normalized();
}

void Character::rotate(Vector2 angles)
{
    yaw = Math::deg_to_rad(angles.x);
    pitch = Math::deg_to_rad(angles.y);
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
    float cos_yaw = Math::cos(yaw);
    float sin_yaw = Math::sin(yaw);

    Vector3 world_dir = Vector3(
        direction.z * sin_yaw + direction.x * cos_yaw,
        direction.y,
        direction.z * cos_yaw - direction.x * sin_yaw);

    Vector3 velocity = world_dir * speed;
    set_velocity(velocity);
    move_and_slide();
}

void Character::looking(double delta)
{

    Vector3 new_rotation = Vector3(0, yaw, 0);
    set_rotation(new_rotation);
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

void Character::take_damage(float damage, IEntity *source)
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

void Character::destroy()
{
    queue_free();
}

void Character::_physics_process(double delta)
{
    if (!WorldController::get_singleton()->can_play())
    {
        return;
    }
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