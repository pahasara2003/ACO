#include "objects.h"


int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Colony Optimization");
    SetTargetFPS(2); 
    srand(time(NULL));

    home.position.x = SCREEN_WIDTH/2;
    home.position.y = SCREEN_HEIGHT/5;
    Ant a[ANTS_COUNT];
    init();
    home.color = GREEN;

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(BLACK);
        update_pheromones();

        for(int i = 0; i< ANTS_COUNT;i++){
            a[i].update(i);
            a[i].draw();
        }
        for(int i = 0; i< FOOD_COUNT;i++){
            food[i].draw();
        }
        home.draw();
        


        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}
