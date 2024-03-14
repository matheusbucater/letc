#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LIGHT_BG_COLOR WHITE
#define DARK_BG_COLOR BLACK

#define LIGHT_PRIMARY_COLOR BLACK
#define DARK_PRIMARY_COLOR WHITE

int get_largest_string_index(const char *strings[], int length);
void screenshot(void);

void draw_frame(void);
void draw_grid(void);
void draw_pixels(void);

void add_pixel_to_grid(void);
void remove_pixel_from_grid(void);
void mouse_to_grid(Color color);
void clear_grid(void);
void change_grid_theme(void);

void draw_help_message(void);
void draw_help_menu(void);
void draw_screenshot_message(void);

static bool dark_mode = false;
static Color background_color = LIGHT_BG_COLOR;
static Color curr_color = LIGHT_PRIMARY_COLOR;
static int pixel_size = 40;
static bool grid_active = true;
static bool help_message_active = true;
static bool help_menu_active = false;
static bool screenshot_active = false;

static double screenshot_timer = 0;

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
    if (IsKeyPressed(KEY_H)) {
        help_menu_active = !help_menu_active;
    }

    if (IsKeyPressed(KEY_M)) {
        help_message_active = !help_message_active;
    }

    if (IsKeyPressed(KEY_Q)) {
        CloseWindow();
    }

    if (IsKeyPressed(KEY_S)) {
        screenshot_active = true;
        help_menu_active = false;
        help_message_active = false;
    }

    if (IsKeyPressed(KEY_SPACE)) {
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
    
    if (screenshot_active) {
        if (screenshot_timer == 0 && !help_menu_active && !help_message_active) {
            screenshot();
        }
        screenshot_timer += GetFrameTime();
        if (screenshot_timer > 3) {
            screenshot_active = false;
            help_message_active = true;
            screenshot_timer = 0;
        }
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
        if (help_message_active) draw_help_message();
        if (help_menu_active) draw_help_menu();
        if (screenshot_active) draw_screenshot_message();
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

void screenshot(void) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    const char *file_basename = "pixel_draw_";
    const char *file_extension = ".png";
    char screenshot_name[100];
    strcpy(screenshot_name, file_basename);
    strcat(screenshot_name, buffer);
    strcat(screenshot_name, file_extension);

    TakeScreenshot(screenshot_name);
}

void draw_screenshot_message(void) {
    char *screenshot_message = "screenshot taken";
    const int font_size = 20;
    const int x = 400 - MeasureText(screenshot_message, font_size) / 2;
    const int y = 400 - font_size / 2;
    const int rec_padding = 5;
    DrawRectangle(x - rec_padding, y - rec_padding, MeasureText(screenshot_message, font_size) + rec_padding * 2, font_size + rec_padding * 2, dark_mode ? DARK_BG_COLOR : LIGHT_BG_COLOR);
    DrawText(screenshot_message, x, y, font_size, dark_mode ? DARK_PRIMARY_COLOR : LIGHT_PRIMARY_COLOR);
}

void draw_help_message(void) {
    const char *help_message = "h for help";
    const int font_size = 20;
    const int x = 15;
    const int y = 770;
    const int rec_padding = 5;
    DrawRectangle(x - rec_padding, y - rec_padding, MeasureText(help_message, font_size) + rec_padding * 2, font_size + rec_padding * 2, dark_mode ? DARK_BG_COLOR : LIGHT_BG_COLOR);
    DrawText("h for help", x, y, font_size, dark_mode ? DARK_PRIMARY_COLOR : LIGHT_PRIMARY_COLOR);
}

void draw_help_menu(void) {
    const int menu_options = 14;
    const char *help_menu[14] = {"[left mouse] draw", "[right mouse] erase",
                                "[scroll wheel] zoom in/out",
                                "[r] red", "[g] green", "[b] blue", "[d] default (black/white)",
                                "[s] screenshot", "[c] clear", "[v] toggle grid", "[space] dark/light mode",
                                "[h] toggle menu", "[m] toggle help message",
                                "[q] quit"};

    const int index = get_largest_string_index(help_menu, menu_options);
    const char* largest_string = help_menu[index];
    const int font_size = 20;
    const int x = 15;
    const int y = 15;
    const int rec_padding = 5;

    DrawRectangle(x - rec_padding, y - rec_padding, MeasureText(largest_string, font_size) + rec_padding * 2, font_size * menu_options * 2 + rec_padding * 2, dark_mode ? DARK_BG_COLOR : LIGHT_BG_COLOR);

    for (int i = 0; i < menu_options; i++) {
        DrawText(help_menu[i], x, y + font_size * i * 2, font_size, dark_mode ? DARK_PRIMARY_COLOR : LIGHT_PRIMARY_COLOR);
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

int get_largest_string_index(const char *strings[], int length) {
    int largest_index = 0;
    int largest_length = 0;

    for (int i = 0; i < length; i++) {
        if (strlen(strings[i]) > largest_length) {
            largest_length = strlen(strings[i]);
            largest_index = i;
        }
    }

    return largest_index;
}
