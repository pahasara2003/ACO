#ifndef OBJECTS_H
#define OBJECTS_H
#include "raylib.h"
#include <math.h>
#include <iostream>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

using namespace std;


class Ant {
    public:
        int x = SCREEN_WIDTH/2;
        int y = SCREEN_HEIGHT/2;
        int R = 5;
        float direction = 0;
     
        void update() {
            direction += (rand()%3 - 1)*PI/6;
    
            int x_new = (int)(x + R*cosf64(direction));
            int y_new = (int)(y + R*sinf64(direction));
        
            if (x_new <= R || x_new >= SCREEN_WIDTH - R) {
                direction = PI - direction;
              
            }
            
            if (y_new <= R || y_new >= SCREEN_HEIGHT - R) {
                direction = 2*PI - direction;
            }
        
            
            x = max(R, min(SCREEN_WIDTH - R, x_new));
            y = max(R, min(SCREEN_HEIGHT - R, y_new));
            
        }
        void draw() {
            DrawCircle(x, y, R/2, GREEN);
        }
    };


#endif 

