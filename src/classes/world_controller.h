#ifndef WORLD_CONTROLLER_H
#define WORLD_CONTROLLER_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/templates/vector.hpp>
#include "Ientity.h"

class WorldController : public godot::Node3D
{

    GDCLASS(WorldController, Node3D);

private:
    static WorldController *instance;
    Vector<IEntity *> entities;
    int32_t next_entity_id = 1;
    bool is_playing = false;

public:
    WorldController(/* args */);
    ~WorldController();

    static WorldController *get_singleton();
    void register_entity(IEntity *entity);
    void unregister_entity(IEntity *entity);
    void cleanup_dead_entities();

    Vector<IEntity *> get_all_entities() const;
    Vector<IEntity *> get_entities_by_type(EntityType type) const;
    Vector<IEntity *> get_entities_by_team(int team) const;
    Vector<IEntity *> get_entities_in_radius(Vector3 center, float radius) const;

    IEntity *get_entity_by_id(int32_t id) const;
    int32_t generate_entity_id();

    bool can_play() const;

    void _physics_process(double delta) override;
    void _ready() override;

protected:
    static void _bind_methods();
};

#endif