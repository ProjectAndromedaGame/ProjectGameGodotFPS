#ifndef IENTITY_H
#define IENTITY_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/core/class_db.hpp>


using namespace godot;

enum class EntityType {
    UNKNOWN = 0,
    ENTITY_PLAYER = 1,
    ENTITY_VEHICLE = 2,
    ENTITY_GADGET = 3,
    ENTITY_STATIC = 4,
    ENTITY_PROJECTILE = 5 
};

class IEntity {

public:
    virtual EntityType get_entity_type() const = 0;
    virtual int32_t get_entity_id() const = 0;
    virtual int get_team() const = 0;  // 0=neutral, 1=team1, 2=team2

    virtual Vector3 get_world_position() const = 0;

    virtual float get_health() const = 0;
    virtual bool is_alive() const = 0;
    virtual void take_damage(float damage, IEntity* source = nullptr) = 0;

    virtual void destroy() = 0;  // Para remover del mundo

    virtual void on_spawned() {}
    virtual void on_damaged(float damage, IEntity* source) {}
    virtual void on_death(IEntity* killer) {}
    virtual void on_destroyed() {}
private:
    virtual void apply_physics(double delta) {}
};


#endif