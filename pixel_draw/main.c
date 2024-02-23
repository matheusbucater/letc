#include "raylib.h"

#define LIGHT_BG_COLOR WHITE
#define DARK_BG_COLOR BLACK

#define LIGHT_PRIMARY_COLOR BLACK
#define DARK_PRIMARY_COLOR WHITE

void draw_frame(void);
void draw_grid(void);
void draw_pixels(void);

void add_pixel_to_grid(void);
void remove_pixel_from_grid(void);
void mouse_to_grid(Color color);
void clear_grid(void);
void change_grid_theme(void);

static bool dark_mode = false;
static Color background_color = LIGHT_BG_COLOR;
static Color curr_color = LIGHT_PRIMARY_COLOR;
static int pixel_size = 40;
static bool grid_active = true;

static Color grid[80][80] = { LIGHT_BG_COLOR };

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

    if (IsKeyPressed(KEY_I)) {
        dark_mode = !dark_mode;
        change_grid_theme();
    }

    if (dark_mode) {
       background_color = DARK_BG_COLOR;
       if (ColorToInt(curr_color) == ColorToInt(LIGHT_PRIMARY_COLOR)) curr_color = DARK_PRIMARY_COLOR;
    }

    if (!dark_mode) {
        background_color = LIGHT_BG_COLOR;
        if (ColorToInt(curr_color) == ColorToInt(DARK_PRIMARY_COLOR)) curr_color = LIGHT_PRIMARY_COLOR;
    }

    if (IsKeyPressed(KEY_R)) {
        curr_color = RED;
    }
    if (IsKeyPressed(KEY_G)) {
        curr_color = GREEN;
    }
    if (IsKeyPressed(KEY_B)) {
        curr_color = BLUE;
    }
    if (IsKeyPressed(KEY_D)) {
        curr_color = BLACK;
    }

    if (IsKeyPressed(KEY_V)) {
        grid_active = !grid_active;
    }

    if (IsKeyPressed(KEY_C)) clear_grid();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) add_pixel_to_grid();

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) remove_pixel_from_grid();

    if (pixel_size + GetMouseWheelMove()*8 > 10) {
        pixel_size = pixel_size + GetMouseWheelMove()*8;
    }

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

void mouse_to_grid(Color color) {
    Vector2 mouse_pos, pixel_pos;

    mouse_pos = GetMousePosition();
    pixel_pos = (Vector2){mouse_pos.x / pixel_size, mouse_pos.y / pixel_size};
    grid[(int)pixel_pos.x][(int)pixel_pos.y] = color;
    
}

void add_pixel_to_grid(void) {
    mouse_to_grid(curr_color);
}

void remove_pixel_from_grid(void) {
    mouse_to_grid(background_color);
}

void draw_pixels(void) {
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 80; y++) {
            Color pixel_color = grid[x][y];
            Vector2 pixel_position = (Vector2){x * pixel_size, y * pixel_size};
            DrawRectangleV(pixel_position, (Vector2){pixel_size, pixel_size}, pixel_color);
        }
    }
}

void clear_grid(void) {
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 80; y++) {
            grid[x][y] = background_color;
        }
    }
}

void change_grid_theme(void) {
    for (int x = 0; x < 80; x++) {
        for (int y = 0; y < 80; y ++) {
            Color pixel_color = grid[x][y];

            if (ColorToInt(pixel_color) == ColorToInt(LIGHT_PRIMARY_COLOR)) grid[x][y] = DARK_PRIMARY_COLOR;
            if (ColorToInt(pixel_color) == ColorToInt(DARK_PRIMARY_COLOR)) grid[x][y] = LIGHT_PRIMARY_COLOR;
            if (ColorToInt(pixel_color) == ColorToInt(LIGHT_BG_COLOR)) grid[x][y] = DARK_BG_COLOR;
            if (ColorToInt(pixel_color) == ColorToInt(DARK_BG_COLOR)) grid[x][y] = LIGHT_BG_COLOR;
        }
    }
}
