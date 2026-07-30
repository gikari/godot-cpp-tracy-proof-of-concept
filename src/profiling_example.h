#ifndef PROFILING_EXAMPLE_H
#define PROFILING_EXAMPLE_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

class ProfilingExample : public Node {
    GDCLASS(ProfilingExample, Node);

private:
    // Helper functions not exposed to GDScript
    void cpp_sleep1(int p_usec);
    void cpp_sleep2(int p_usec);
    void cpp_sleep3(int p_usec);

protected:
    static void _bind_methods();

public:
    ProfilingExample();
    ~ProfilingExample();

    // Main driver exposed to GDScript
    void run_cpp_sleeps(int p_usec);
};

} // namespace godot

#endif // PROFILING_EXAMPLE_H
