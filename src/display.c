#include "display.h"
#include <stdio.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width;
int window_height;

int previous_frame_time = 0;
int delta_time = 0;

bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// Set width and height of the SDL window with the max screen resolution
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create a SDL Window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}

	// Create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}

	return true;
}

void draw_pixel(int x, int y, uint32_t color)
{
	if (x >= 0 && x < window_width && y >= 0 && y < window_height)
	{
		color_buffer[(window_width * y) + x] = color;
	}

	else
		printf("Pixel out of bounds: (%d, %d)\n", x, y);
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color)
{
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;

	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	float x_inc = (float)delta_x / (float)longest_side_length;
	float y_inc = (float)delta_y / (float)longest_side_length;

	float current_x = (float)x0;
	float current_y = (float)y0;

	for (int i = 0; i <= longest_side_length; i++)
	{
		draw_pixel((int)round(current_x), (int)round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}

void draw_rect(int top_left_x, int top_left_y, int width, int height, uint32_t color)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int current_x = top_left_x + j;
			int current_y = top_left_y + i;
			draw_pixel(current_x, current_y, color);
		}
	}
}

void render_color_buffer(void)
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
