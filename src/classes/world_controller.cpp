#include "world_controller.h"

WorldController *WorldController::instance = nullptr;

WorldController::WorldController()
{
    if (instance == nullptr)
    {
        instance = this;
        print_line("WorldController instance created.");
    }
    else
    {
        print_line("Warning: Multiple instances of WorldController detected!");
    }
}
// Destructor
WorldController::~WorldController()
{
    entities.clear();

    if (instance == this)
    {
        instance = nullptr;
    }
    // Limpiar entidades si es necesario
}

WorldController *WorldController::get_singleton()
{
    return instance;
}

void WorldController::register_entity(IEntity *entity)
{
    if (entity)
    {
        entities.push_back(entity);
    }
}

void WorldController::unregister_entity(IEntity *entity)
{
    if (entity)
    {
        entities.erase(entity);
    }
}

void WorldController::cleanup_dead_entities()
{
    for (int i = entities.size() - 1; i >= 0; i--)
    {
        if (!entities[i]->is_alive())
        {
            entities.remove_at(i);
        }
    }
}

bool WorldController::can_play() const
{
    return is_playing;
}

void WorldController::_ready()
{
    if (!Engine::get_singleton()->is_editor_hint())
    {
        is_playing = true;
        print_line("Game is running - is_playing set to true");
    }
    else
    {
        is_playing = false;
        print_line("Running in editor - is_playing set to false");
    }
}

void WorldController::_physics_process(double delta)
{
    // Aquí puedes agregar la lógica que deseas que se ejecute en cada frame de física
}

void WorldController::_bind_methods()
{
}