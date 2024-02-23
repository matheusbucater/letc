#include "raylib.h"
#include <stdio.h>

#define MAX_SCREEN

void draw_frame(void);
void draw_grid(void);
void draw_pixels(void);

void add_pixel_to_grid(void);

static Color background_color = WHITE;
static int pixel_size = 40;
static bool grid_active = false;

static Color grid[80][80] = { WHITE };

int main(void) {
    
    const int screen_width = 800;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pixel Drawing Editor");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        draw_frame();
    }

    CloseWindow();
    return 0;
}

void draw_frame(void) {

    if (IsKeyPressed(KEY_G)) {
        grid_active = !grid_active;
    }

    if (IsKeyPressed(KEY_C)) ClearBackground(background_color);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) add_pixel_to_grid();

    if (pixel_size + GetMouseWheelMove()*8 > 10) {
        pixel_size = pixel_size + GetMouseWheelMove()*8;
    }

    printf("%d\n", pixel_size);

    BeginDrawing();
        ClearBackground(background_color);
        draw_pixels();
        if (grid_active) draw_grid();
    EndDrawing();
}

void draw_grid(void) {

    float screen_width, screen_height;
    Vector2 hline_start, hline_end, vline_start, vline_end;

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    for (int x = 0; x < screen_width; x++) {
        for (int y = 0; y < screen_height; y++) {

            hline_start = (Vector2){0, y * pixel_size};
            hline_end = (Vector2){screen_width, y * pixel_size};
            vline_start = (Vector2){x * pixel_size, 0};
            vline_end = (Vector2){x * pixel_size, screen_height};

            DrawLineV(hline_start, hline_end, LIGHTGRAY);
            DrawLineV(vline_start, vline_end, LIGHTGRAY);
        }
    }
}

void add_pixel_to_grid(void) {

    float screen_width, screen_height;
    Vector2 mouse_pos, pixel_pos;

    mouse_pos = GetMousePosition();
    pixel_pos = (Vector2){mouse_pos.x / pixel_size, mouse_pos.y / pixel_size};
    grid[(int)pixel_pos.x][(int)pixel_pos.y] = RED;
}

void draw_pixels(void) {
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 80; y++) {
            Color pixel_color = grid[x][y];
            if (ColorToInt(pixel_color) != ColorToInt(background_color)) {
                Vector2 pixel_position = (Vector2){x * pixel_size, y * pixel_size};
                DrawRectangleV(pixel_position, (Vector2){pixel_size, pixel_size}, pixel_color);
            }
        }
    }
}
