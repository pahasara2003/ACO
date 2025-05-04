#include "objects.h"


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Colony Optimization");
    SetTargetFPS(30); 

    Ant a[1500];
    init();

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);
        update_pheromones();

        for(int i = 0; i< 1500;i++){
            a[i].update();
            a[i].draw();
        }
        


        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
