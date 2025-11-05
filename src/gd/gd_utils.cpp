#include "gd_utils.h"

GDUtils *GDUtils::instance = nullptr;

GDUtils::GDUtils()
{
    if (instance == nullptr)
    {
        instance = this;
    }
    else
    {
        // Handle error: instance already exists
    }
}

GDUtils::~GDUtils()
{
    if (instance == this)
    {
        instance = nullptr;
    }
}

GDUtils *GDUtils::get_singleton()
{
    return instance;
}

Node *GDUtils::get_autoload(const String &name)
{
    SceneTree *tree = Object::cast_to<SceneTree>(Engine::get_singleton()->get_main_loop());
    if (!tree)
        return nullptr;
    Window *root = tree->get_root();
    if (!root)
        return nullptr;
    const NodePath path(String("/root/") + String(name));
    return root->get_node<Node>(path);
}

void GDUtils::test_function()
{
    SceneTree *tree = Object::cast_to<SceneTree>(Engine::get_singleton()->get_main_loop());
    Window *root = tree->get_root();
}