#include "raylib.h"
#include "raymath.h"
#include <stdbool.h>

#define SCREEN_WIDTH 800.0
#define SCREEN_HEIGTH 800.0

#define BLOCK_SIZE 20.0

#define MAX_PIECES 100

#define DEFAULT_SPEED 20.0

#define COLOR_I SKYBLUE
#define COLOR_O YELLOW
#define COLOR_T PINK
#define COLOR_J DARKBLUE
#define COLOR_L ORANGE
#define COLOR_S GREEN
#define COLOR_Z RED

#define STARTX_I (SCREEN_WIDTH / 2) - (2 * BLOCK_SIZE)
#define STARTX_O (SCREEN_WIDTH / 2) - BLOCK_SIZE
#define STARTX_T (SCREEN_WIDTH / 2) - (1.5 * BLOCK_SIZE)
#define STARTX_J (SCREEN_WIDTH / 2) - (1.5 * BLOCK_SIZE)
#define STARTX_K (SCREEN_WIDTH / 2) - (1.5 * BLOCK_SIZE)
#define STARTX_S (SCREEN_WIDTH / 2) - (1.5 * BLOCK_SIZE)
#define STARTX_Z (SCREEN_WIDTH / 2) - (1.5 * BLOCK_SIZE)

#define STARTY_I BLOCK_SIZE
#define STARTY_O BLOCK_SIZE
#define STARTY_T BLOCK_SIZE
#define STARTY_J BLOCK_SIZE
#define STARTY_K BLOCK_SIZE
#define STARTY_S (2 * BLOCK_SIZE)
#define STARTY_Z BLOCK_SIZE

typedef enum PieceType {
    I,
    O,
    T,
    J,
    L,
    S,
    Z
} PieceType;

typedef enum Orientation {
    UP,
    LEFT,
    DOWN,
    RIGHT
} Orientation;


typedef struct Piece {
    
    bool active;
    PieceType type;
    Color color;
    Vector2 position;
    Vector2 velocity;
    Orientation orientation;
    
} Piece;

Piece create_piece(PieceType type, Color color, Vector2 position) {
 
    Vector2 default_speed;
    default_speed.x = DEFAULT_SPEED;
    default_speed.y = DEFAULT_SPEED;

    return (Piece) {
        .active = true,
            .type = type,
            .color = color,
            .position = position,
            .velocity = default_speed,
            .orientation = UP
    };
}

void update_piece(Piece *piece, float frametime) {
    
    if (!piece->active) {
        return;
    }

    piece->position = Vector2Add(piece->position, Vector2Scale(piece->velocity, frametime));
}

void add_piece(PieceType type, Color color, Vector2 position, Vector2 velocity) {

    Piece piece = create_piece(T, COLOR_T, (Vector2){ 1.5 * BLOCK_SIZE, BLOCK_SIZE });
}


void draw_frame(void);
void draw_piece(Piece piece);
void draw_I(Vector2 start_pos, Color color);
void draw_O(Vector2 start_pos, Color color);
void draw_T(Vector2 start_pos, Color color);
void draw_J(Vector2 start_pos, Color color);
void draw_L(Vector2 start_pos, Color color);
void draw_S(Vector2 start_pos, Color color);
void draw_Z(Vector2 start_pos, Color color);

Piece _pieces[MAX_PIECES] = {0};

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGTH, "Tetris");
    SetTargetFPS(60);

    Piece piece;
    piece.type = O;
    piece.color = COLOR_O;

    while (!WindowShouldClose()) {

        draw_frame();

    }


    CloseWindow();

    return 0;
}

void draw_frame(void) {

    float frametime = GetFrameTime();

    for (int i = 0; i < MAX_PIECES; i++) {
        update_piece(_pieces + i, frametime);
    }

    BeginDrawing();

        ClearBackground(BLACK);
        
        for (int i = 0; i < MAX_PIECES; i++) {
            draw_piece(_pieces[i]);
        }



    EndDrawing();
}

void draw_piece(Piece piece){
    
    Vector2 start_pos;
    start_pos.x = SCREEN_WIDTH / 2;
    start_pos.y = BLOCK_SIZE;

    switch (piece.type) {
        case I:
            draw_I(start_pos, piece.color);
            break;
        case O:
            draw_O(start_pos, piece.color);
            break;
        // case T:
        //     draw_T(start_pos, piece.color);
        //     break;
        // case J:
        //     draw_J(start_pos, piece.color);
        //     break;
        // case L:
        //     draw_L(start_pos, piece.color);
        //     break;
        // case S:
        //     draw_S (start_pos, piece.color);
        //     break;
        // case Z:
        //     draw_Z(start_pos, piece.color);
        //     break;
    }
}

void draw_I(Vector2 start_pos, Color color) {

   Vector2 p1, p2, p3, p4;

    p1.x = start_pos.x - (2 * BLOCK_SIZE);
    p1.y = start_pos.y;

    p2.x = p1.x + (4 * BLOCK_SIZE);
    p2.y = p1.y;

    p3.x = p2.x;
    p3.y = p2.y + BLOCK_SIZE;

    p4.x = p1.x;
    p4.y = p3.y;

    Vector2 points[5];

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p1;

    DrawLineStrip(points, 5, color);

}

void draw_O(Vector2 start_pos, Color color) {

   Vector2 p1, p2, p3, p4;

    p1.x = start_pos.x - BLOCK_SIZE;
    p1.y = start_pos.y;

    p2.x = p1.x + (2 * BLOCK_SIZE);
    p2.y = p1.y;

    p3.x = p2.x;
    p3.y = p2.y + (2 * BLOCK_SIZE);

    p4.x = p1.x;
    p4.y = p3.y;

    Vector2 points[5];

    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
    points[4] = p1;

    DrawLineStrip(points, 5, color);

}

