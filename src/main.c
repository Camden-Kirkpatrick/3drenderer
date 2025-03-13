#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "windows.h"
#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t* triangles_to_render = NULL;

bool is_running = true;
bool pause_rendering = false;

int fps = 60;
float frame_target_time;

vec3_t camera_position = { 0, 0, 0 };
float fov_factor = 640;

int counter = 0;

void setup(void)
{
    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    load_obj_file_data("assets/f22.obj");
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        is_running = false;
        break;

    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        else if (event.key.keysym.sym == SDLK_1)
            pause_rendering = true;
        else if (event.key.keysym.sym == SDLK_2)
            pause_rendering = false;
        else if (event.key.keysym.sym == SDLK_3)
        {
            if (fps > 1) { // Limit minimum FPS
                fps--;
                frame_target_time = 1000.0f / fps;
                printf("FPS decreased to: %d\n", fps);
            }
        }
        else if (event.key.keysym.sym == SDLK_4)
        {
            if (fps < 200) { // Limit max FPS
                fps++;
                frame_target_time = 1000.0f / fps;
                printf("FPS increased to: %d\n", fps);
            }
        }
        break;
    }
}

// Perspective projection
vec2_t p_project(vec3_t point)
{
    vec2_t projected_point = {
        .x = round((fov_factor * point.x) / point.z),
        .y = round((fov_factor * point.y) / point.z)
    };
    return projected_point;
}

// Orthographic projection
vec2_t o_project(vec3_t point)
{
    vec2_t projected_point = {
        .x = round((fov_factor * point.x)),
        .y = round((fov_factor * point.y))
    };
    return projected_point;
}

void update(void)
{
    int current_frame_time = SDL_GetTicks();
    // This is the amount of time between the current frame and the previous frame
    delta_time = current_frame_time - previous_frame_time;

    int time_to_wait = frame_target_time - delta_time;
    if (time_to_wait > 0)
    {
        SDL_Delay(time_to_wait);
        delta_time += time_to_wait; // Adjust delta_time for the delay
    }

    previous_frame_time = SDL_GetTicks(); // Update for the next frame

    // Initialize the array of triangles to render
    triangles_to_render = NULL;

    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.00;

    // Loop all triangle faces of our mesh
    int num_faces = array_length(mesh.faces);
    for (int i = 0; i < num_faces; i++)
    {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        // Get the three vertices for each triangle face
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        // Store the transformed vertices for each face
        vec3_t transformed_vertices[3];

        // Loop all three vertices of this current face and apply transformations
        for (int j = 0; j < 3; j++)
        {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            // Translate the vertex away from the camera
            transformed_vertex.z += 5;

            // Save the transformed vertex to the array of transformed vertices
            transformed_vertices[j] = transformed_vertex;
        }

        // Back-face Culling
        {
            counter++;
            vec3_t vector_a = transformed_vertices[0]; /* B   */
            vec3_t vector_b = transformed_vertices[1]; /* | \  */
            vec3_t vector_c = transformed_vertices[2]; /* A--C */

            // Get the vector from A to B and A to B
            vec3_t vector_ab = vec3_sub(vector_b, vector_a);
            vec3_t vector_ac = vec3_sub(vector_c, vector_a);
            vec3_normalize(&vector_ab);
            vec3_normalize(&vector_ac);

            // Compute the face normal (using the cross product)
            vec3_t normal = vec3_cross(vector_ab, vector_ac);
            vec3_normalize(&normal);

            // Find the vector from a point on the triangle to he camera
            vec3_t camera_ray = vec3_sub(camera_position, vector_a);
            //vec3_normalize(&camera_ray);

            // Calculate how alligned the camera ray is with the face normal (using the dot product
            float dot_normal_camera = vec3_dot(normal, camera_ray);

            // Bypass the triangles that are looking away from the camera
            if (dot_normal_camera < 0)
            {
                continue;
            }
        }

        triangle_t projected_triangle;

        // Project the vertices onto the screen (move the points so that there visible)
        for (int j = 0; j < 3; j++)
        {
            // Project the current vertex
            vec2_t projected_point = p_project(transformed_vertices[j]);

            // Scale and translate the projected points to the middle of the screen
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }

        // Save the projected triangle in the array of triangles to render
        array_push(triangles_to_render, projected_triangle);
    }
}

void render(void)
{
    clear_color_buffer(BLACK);

    // Loop all projected triangles and render them
    int num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++)
    {
        triangle_t triangle = triangles_to_render[i];

        // Draw vertex points
        draw_rect(triangle.points[0].x, triangle.points[0].y, 4, 4, GREEN); // vertex A
        draw_rect(triangle.points[1].x, triangle.points[1].y, 4, 4, GREEN); // vertex B
        draw_rect(triangle.points[2].x, triangle.points[2].y, 4, 4, GREEN); // vertex C

        // Draw unfilled triangle
        draw_triangle(
            triangle.points[0].x, triangle.points[0].y, // vertex A
            triangle.points[1].x, triangle.points[1].y, // vertex B
            triangle.points[2].x, triangle.points[2].y, // vertex C
            GREEN
        );
    }

    // Clear the array of triangles to render every frame loop
    array_free(triangles_to_render);

    render_color_buffer();

    SDL_RenderPresent(renderer);
}

void free_resources(void)
{
    free(color_buffer);
    array_free(mesh.faces);
    array_free(mesh.vertices);
}


int main(void)
{
    frame_target_time = 1000.0f / fps;

    is_running = initialize_window();

    setup();

    srand(time(NULL));

    while (is_running)
    {
        process_input();

        if (!pause_rendering)
        {
            update();
            render();
        }
    }

    destroy_window();
    free_resources();

    return 0;
}