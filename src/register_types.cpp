#include "register_types.h"

#include "character.h"
#include "controller.h"
#include "world_controller.h"
#include "gd_bridge.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static GDBridge* gdbridge_singleton = nullptr;

void initialize_example_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

    // GDREGISTER_CLASS(GDExample);
    GDREGISTER_CLASS(Character);
    GDREGISTER_CLASS(Controller);
    GDREGISTER_CLASS(WorldController);
    GDREGISTER_CLASS(GDBridge);
    gdbridge_singleton = memnew(GDBridge); // Ensure singleton is created
    Engine::get_singleton()->register_singleton("GDBridge", gdbridge_singleton);
}

void uninitialize_example_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

    if (gdbridge_singleton)
    {
        memdelete(gdbridge_singleton);
    }
}

extern "C"
{
    // Initialization.
    GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_example_module);
        init_obj.register_terminator(uninitialize_example_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}