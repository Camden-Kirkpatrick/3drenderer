# 3D Software Renderer

This project is a simple 3D software renderer written in C. It uses [SDL2](https://www.libsdl.org/) to create a window, render basic 2D and 3D shapes, and display them on the screen.

### File Descriptions

- **array.c / array.h**  
  Provides a dynamic array implementation (e.g., `array_push`, `array_free`). This helps store the project’s growing list of vertices/faces without manually managing memory.

- **display.c / display.h**  
  Handles SDL2 window creation, rendering, and low-level drawing. Exposes functions to draw pixels, lines, triangles, rectangles, and manage the main color buffer.

- **main.c**  
  The entry point of the application. Initializes the window, loads meshes, performs the main update and render loops, and handles user input (including FPS adjustments and pause controls).

- **mesh.c / mesh.h**  
  Defines a `mesh_t` containing dynamic arrays of vertices and faces, plus rotation data. Includes functions to load mesh data from an OBJ file or from hardcoded cube data.

- **triangle.h**  
  Declares `triangle_t`, representing the projected 2D coordinates of a single 3D triangle face, and `face_t`, which tracks a triangle’s vertex indices.

- **vector.c / vector.h**  
  A small math library for 2D and 3D vector operations (addition, subtraction, length, dot product, cross product, rotation, normalization, etc.).

## Features

- **3D Model Loading**  
  Able to load and parse simple OBJ files with vertex (`v`) and face (`f`) data.
- **Basic 3D Transformations**  
  Rotate and translate 3D objects in real time.
- **Back-Face Culling**  
  Discards faces not visible to the camera, improving performance.
- **Software Rasterization**  
  Renders 3D meshes to a 2D color buffer, displayed via SDL2.
- **Dynamic Arrays**  
  Manages vertices/faces without manual memory allocations.

## Dependencies

- **SDL2** library and headers  
  Required for compiling and linking the project. Ensure you have SDL2 installed and your compiler can locate it (e.g., `-lSDL2` and relevant include paths).

## Building and Running

1. **Install SDL2**  
   Make sure SDL2 is installed on your system or is available to your compiler.

2. **Compile**  
   The simplest approach is to compile all `.c` files together, linking with SDL2. For example:
   ```bash
   gcc -o renderer main.c array.c display.c mesh.c vector.c -I. -lSDL2
   ```

Your command may differ depending on your environment. Make sure the -I. includes the current directory for headers, and -lSDL2 links the SDL2 library.

Run:
```bash
renderer.exe
```

An SDL window should appear, rendering any OBJ model (default is assets/f22.obj if present).

## Usage

### Controls
- **Esc**: Quit the program  
- **1**: Pause rendering  
- **2**: Resume rendering  
- **3**: Decrease FPS (minimum of 1)  
- **4**: Increase FPS (maximum of 200)

### Changing the Loaded Mesh
In `main.c` (within `setup()`), change the call to `load_obj_file_data("assets/f22.obj")` to any other OBJ file path. Ensure the OBJ file is valid and follows the expected format (`v`, `f` lines).

### Window Resizing
By default, the window is sized to your display’s resolution. Adjust in `initialize_window()` (in `display.c`).

## License

This project is provided as-is, without warranty or guarantee. You are free to modify or extend it for your needs.

**Enjoy using the 3drenderer!**




