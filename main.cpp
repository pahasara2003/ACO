#include "objects.h"


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Colony Optimization");
    SetTargetFPS(30); 

    Ant a[500];

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0; i< 500;i++){
            a[i].update();
            a[i].draw();
        }
        


        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
