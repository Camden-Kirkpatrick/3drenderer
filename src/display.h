//#ifndef DISPLAY_H
//#define DISPLAY_H
//
//#include <stdint.h>
//#include <stdbool.h>
//#include <SDL.h>
//
//extern int previous_frame_time;
//extern int delta_time;
//
//// Basic colors
//#define WHITE      0xFFFFFFFF
//#define BLACK      0xFF000000
//#define RED        0xFFFF0000
//#define GREEN      0xFF00FF00
//#define BLUE       0xFF0000FF
//#define YELLOW     0xFFFFFF00
//#define MAGENTA    0xFFFF00FF
//#define TEAL       0xFF00FFFF
//// Custom colors
//#define ORANGE     0xFFFFA500
//#define PINK       0xFFFF69B4
//#define PURPLE     0xFF600060
//#define BROWN      0xFF301010
//#define GRAY       0xFF808080
//#define LIGHT_GRAY 0xFFC0C0C0
//#define DARK_GRAY  0xFF303030
//
//extern SDL_Window* window;
//extern SDL_Renderer* renderer;
//extern uint32_t* color_buffer;
//extern SDL_Texture* color_buffer_texture;
//
//extern int window_width;
//extern int window_height;
//
//bool initialize_window(void);
//uint32_t generate_random_color_interval(float* ftt);
//uint32_t generate_random_color(void);
//void draw_grid(void);
//void draw_checker_board(int cell_width, int cell_height, int rows, int cols, uint32_t cell_color_1, uint32_t cell_color_2, uint32_t border_color);
//void animate_pixel(int* x, int* y, int inc_x, int inc_y, uint32_t color);
//void draw_pixel(int x, int y, uint32_t color);
//void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
//void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
//void animate_rect(int* x, int* y, int width, int height, int inc_x, int inc_y);
//void draw_rect_center(int center_x, int center_y, int width, int height, uint32_t color);
//void draw_rect_bottom_right(int top_left_x, int top_left_y, int width, int height, uint32_t color);
//void draw_rect(int top_left_x, int top_left_y, int width, int height, uint32_t color);
//void render_color_buffer(void);
//void clear_color_buffer(uint32_t color);
//void destroy_window(void);
//
//#endif




#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

extern int previous_frame_time;
extern int delta_time;

// Basic colors
#define WHITE      0xFFFFFFFF
#define BLACK      0xFF000000
#define RED        0xFFFF0000
#define GREEN      0xFF00FF00
#define BLUE       0xFF0000FF
#define YELLOW     0xFFFFFF00
#define MAGENTA    0xFFFF00FF
#define TEAL       0xFF00FFFF
// Custom colors
#define ORANGE     0xFFFFA500
#define PINK       0xFFFF69B4
#define PURPLE     0xFF600060
#define BROWN      0xFF301010
#define GRAY       0xFF808080
#define LIGHT_GRAY 0xFFC0C0C0
#define DARK_GRAY  0xFF303030

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

extern int window_width;
extern int window_height;

bool initialize_window(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_rect(int top_left_x, int top_left_y, int width, int height, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);

#endif
