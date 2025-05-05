#ifndef OBJECTS_H
#define OBJECTS_H
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <iostream>
#include <cmath> 
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define ANTS_COUNT 100
#define FOOD_COUNT 2


using namespace std;

float to_food_pheromones[SCREEN_HEIGHT][SCREEN_WIDTH];
float to_home_pheromones[SCREEN_HEIGHT][SCREEN_WIDTH];

float rho = 0.01;
int R = 5;

enum antStatus{
    SEARCH,
    RETURN
};


void init(){

    for (int j = 0; j< SCREEN_HEIGHT;j++){
        for (int i = 0; i< SCREEN_WIDTH;i++){
            to_food_pheromones[j][i] = 0.000001;
            to_home_pheromones[j][i] = 0.000001;

          }
      }
}

void update_pheromones(){
    for (int j = 0; j< SCREEN_HEIGHT;j++){
        for (int i = 0; i< SCREEN_WIDTH;i++){
            if(to_food_pheromones[j][i]>0.0000000001){
                unsigned char trans =  (unsigned char) to_food_pheromones[j][i]*100;
                // DrawPixel(i,j,Color{ 0, 0,255, trans  });
                to_food_pheromones[j][i] *= (1 - rho);

            }
            if(to_home_pheromones[j][i]>0.0000000001){
                unsigned char trans =  (unsigned char) to_home_pheromones[j][i]*100;
                // DrawPixel(i,j,Color{ 0, 255,0, trans  });
                to_home_pheromones[j][i] *= (1 - rho);

            }

          }
      }
}



class Point {
    public:
        Color color = YELLOW;
        Vector2 position = {rand()%SCREEN_WIDTH,rand()%SCREEN_HEIGHT};
    

        void draw() {
            if (color.r == YELLOW.r && color.g == YELLOW.g && color.b == YELLOW.b) {
                // Food
                DrawCircle(position.x, position.y, 10, color);  // Center in the rectangle and make it a circle
            } else {
                // Home
                DrawCircle(position.x, position.y, 10, color);  // Center in the rectangle and make it a circle
            }
        }

};

Point food[FOOD_COUNT];
Point home;






class Ant {
    public:
        antStatus status = SEARCH;
        float max_steer_force = 1;
        float max_velocity = 2;
        float max_wonder_strength = 0.9;
        float wonder_strength = max_wonder_strength;
        Vector2 position = {home.position.x,home.position.y};
        Vector2 velocity = Vector2{1,0};
        Vector2 desired_direction = velocity;

        bool attract_to(Point target){
            Vector2 displacement = Vector2Subtract(target.position,position);
            float angle = Vector2Angle(velocity,displacement); 
            
            if(Vector2Length(displacement) < 200   && angle < PI/3 && angle > -PI/3 ){
                wonder_strength = 0.1;
                desired_direction = Vector2Normalize(displacement);
                if(Vector2Length(displacement) < 10) status = (status == SEARCH ? RETURN : SEARCH);
                return true;

            }
            return false;
        }

        Vector2 choose(){
            float step_angle = PI/6;
            float sensor_offset = 10;
            float sensor_width = 6;
        
            for(int i = -1; i <= 1; i++){
                float theta = step_angle*i + atan2f(velocity.y,velocity.x);
                int x0 = (int) round(position.x + cos(theta)*sensor_offset);
                int y0 = (int) round(position.y + sin(theta)*sensor_offset);
        
                int k = cos(theta) > 0 ? 1 : cos(theta) == 0 ? 0 : -1;
                int x1 = x0 + sensor_width*(k-1)/2;
                int x2 = x1 + sensor_width;
                int y1 = y0;
                
                for(int i = x1; i<=x2;i++){
                    DrawPixel(i,y0,WHITE);

                }
        
        
        
            }
        
        
            float random_angle = 2*PI*(rand()%1000)/1000.0;
            Vector2 random_velocity = Vector2Scale({cos(random_angle),sin(random_angle)},wonder_strength);
            return random_velocity;
        };
        

     
        void update(int index) {

            bool target = false;
          

            if(status == SEARCH)
                for(int i = 0; i < FOOD_COUNT; i++) {      
                    target = attract_to(food[i]);
                }
            else if (status == RETURN){
                target = attract_to(home);
            }
               
            if (!target)
                wonder_strength = max_wonder_strength;
            
            
            
            Vector2 choosen_direction = choose();
            desired_direction = Vector2Normalize(Vector2Add(desired_direction,choosen_direction));
            Vector2 desired_velocity = Vector2Scale(desired_direction,max_velocity);

            Vector2 desired_force = Vector2Scale(Vector2Subtract(desired_velocity,velocity),max_steer_force);
            Vector2 acceleration = Vector2ClampValue(desired_force,0,max_steer_force);
            velocity = Vector2Add(velocity,acceleration); 
            Vector2 new_position = Vector2Add(position,velocity);
        
            if (new_position.x <= R || new_position.y >= SCREEN_WIDTH - R) {
                velocity.x *=-1;
              
            }
            
            if (new_position.y <= R || new_position.y >= SCREEN_HEIGHT - R) {
                velocity.y *=-1;
            }

            position.x = max(R, min(SCREEN_WIDTH - R, (int) round(new_position.x)));
            position.y = max(R, min(SCREEN_HEIGHT - R,(int) round(new_position.y)));
            
            if (status == SEARCH) to_home_pheromones[(int)position.y][(int)position.x] += 20;
            else to_food_pheromones[(int) position.y][(int) position.x] += 20;

            
        }
        void draw() {
            DrawCircle((int) position.x , (int) position.y , R, status == SEARCH ? GREEN : BLUE);
        }
    };


#endif

