extends Node

var cpp_profiler: ProfilingExample
var frame_count := 0
var max_frames := 180 # At 60 fps, 180 frames is roughly 3 seconds of execution

func _ready() -> void:
    print("--- Starting Frame-by-Frame Profiling Loop ---")
    cpp_profiler = ProfilingExample.new()
    add_child(cpp_profiler)

func _process(_delta: float) -> void:
    frame_count += 1

    # Run the GDScript sleeps (3 ms target total)
    run_gd_sleeps(1000)

    # Run the C++ sleeps (3 ms target total)
    cpp_profiler.run_cpp_sleeps(1000)

    # Print progress every 30 frames to show it is running and alive
    if frame_count % 30 == 0:
        print("  Processed %d / %d frames..." % [frame_count, max_frames])

    if frame_count >= max_frames:
        print("--- Frame-by-Frame Profiling Loop Finished ---")
        get_tree().quit()

func gd_sleep1(usec: int) -> void:
    OS.delay_usec(usec)

func gd_sleep2(usec: int) -> void:
    OS.delay_usec(usec)

func gd_sleep3(usec: int) -> void:
    OS.delay_usec(usec)

func run_gd_sleeps(usec: int) -> void:
    gd_sleep1(usec)
    gd_sleep2(usec)
    gd_sleep3(usec)
