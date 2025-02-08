#include <iostream>
#include <raylib.h>
#include <vector>
using namespace std;

Color green = {173,204,96,255};
Color darkGreen = {43,51,24,255};
Color darkRed = {200,51,24,255};

int cellSize = 30;
int cellCount = 25;

class Food{
    public:
        Vector2 position = {5,6};

        Food(){
            position = GenerateRandomPos();
        }

        void Draw(){
            DrawRectangle(position.x*cellSize,position.y*cellSize,cellSize,cellSize,darkRed);
        }
        
        Vector2 GenerateRandomPos(){
            float x = GetRandomValue(0,cellCount-1);
            float y = GetRandomValue(0,cellCount-1);

            return Vector2({x,y});
        }

        Rectangle GetRect(){
            return {position.x*cellSize,position.y*cellSize,(float)cellSize,(float)cellSize};
        }

    private:

};

class Snake{
        public:
            vector<Vector2> body = {{0,0}};
            Vector2 head;

            enum Directions{LEFT,RIGHT,UP,DOWN};

            double time = 0, time_sla = 0.2;

            Directions direction=DOWN;

            Snake(){
                head = Vector2({0,0});
            }

            void Draw(){
                for(int i=0;i<body.size();i++){
                    body.front()=head;
                    DrawRectangle(body[i].x*cellSize,body[i].y*cellSize,cellSize,cellSize,darkGreen);
                }
                DrawRectangle(head.x*cellSize,head.y*cellSize,cellSize,cellSize,darkGreen);
            }

            void Move(){
                
                if(IsKeyPressed(KEY_S)){
                    direction = DOWN;
                }
                if(IsKeyPressed(KEY_W)){
                    direction = UP;
                }
                if(IsKeyPressed(KEY_A)){
                    direction = LEFT;
                }
                if(IsKeyPressed(KEY_D)){
                    direction = RIGHT;
                }
            }

            void Update(){
                Move();
                
                if(direction==UP && GetTime()-time>time_sla){
                    time=GetTime();
                    head.y-=1;
                    AddBody(false);
                }
                if(direction==DOWN && GetTime()-time>time_sla){
                    time=GetTime();
                    head.y+=1;
                    AddBody(false);
                }
                if(direction==LEFT && GetTime()-time>time_sla){
                    time=GetTime();
                    head.x-=1;
                    AddBody(false);
                }
                if(direction==RIGHT && GetTime()-time>time_sla){
                    time=GetTime();
                    head.x+=1;
                    AddBody(false);
                }
            }

            void AddBody(bool t){
                body.insert(body.begin(),body.front());
                if(t==false){
                    body.erase(body.end());
                }
            }

            Rectangle GetRect(){
                return {head.x*cellSize,head.y*cellSize,(float)cellSize,(float)cellSize};
            }
            
};

int main(){

    InitWindow(cellSize*cellCount ,cellSize*cellCount ,"Snake game");
    SetTargetFPS(60);

    Food food = Food();
    Snake player = Snake();

    while(WindowShouldClose() == false){

        player.Update();
        if(CheckCollisionRecs(player.GetRect(),food.GetRect())){
            food.position = food.GenerateRandomPos();
            player.AddBody(true);
            
        }

        BeginDrawing();
        ClearBackground(green);

        food.Draw();
        player.Draw();
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}