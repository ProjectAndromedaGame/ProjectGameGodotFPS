#ifndef GD_UTILS_H
#define GD_UTILS_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/variant/node_path.hpp>

using namespace godot;

class GDUtils
{
private:
    static GDUtils *instance;

public:
    GDUtils();
    ~GDUtils();
    static GDUtils *get_singleton();
    static Node *get_autoload(const String &name);
    void test_function();
};

#endif
