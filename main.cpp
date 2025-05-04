#include "objects.h"

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Colony Optimization");

    SetTargetFPS(60); 

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);


        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
