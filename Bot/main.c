#include "stdio.h"
#include "stdlib.h"
#include "sdl.h"
#include "SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    //window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor, side_left_sensor, side_right_sensor =0;
    clock_t start_time, end_time;
    int msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    /*insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);*/


    //MAZE 1
    /*insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+175, 100, 10);
insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2+100, 300, 10);
insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-100);
insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, 110);
insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2+50, 150, 10);
insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2, 250, 10);
insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-90, 10, 200);
insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+100, 100, 10);
insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2, 10, 110);
insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2, 100, 10);
insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2-50, 350, 10);
insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-150, 10, 105);
insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2+150, OVERALL_WINDOW_HEIGHT/2+150, 10, OVERALL_WINDOW_HEIGHT/2-75);
insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2-150, 200, 10);
insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-150, 10, 105);
insertAndSetFirstWall(&head, 16,  OVERALL_WINDOW_WIDTH/2+300, OVERALL_WINDOW_HEIGHT/2-225, 10, 600);
insertAndSetFirstWall(&head, 17,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-225, 550, 10);
insertAndSetFirstWall(&head, 18,  OVERALL_WINDOW_WIDTH/2-75, OVERALL_WINDOW_HEIGHT/2-225, 10, 125);
insertAndSetFirstWall(&head, 19,  OVERALL_WINDOW_WIDTH/2-125, OVERALL_WINDOW_HEIGHT/2-175, 10, 125);
insertAndSetFirstWall(&head, 20,  OVERALL_WINDOW_WIDTH/2-175, OVERALL_WINDOW_HEIGHT/2-225, 10, 125);
insertAndSetFirstWall(&head, 21,  OVERALL_WINDOW_WIDTH/2-225, OVERALL_WINDOW_HEIGHT/2-175, 10, 125);
insertAndSetFirstWall(&head, 22,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2-225, 10, 600);
insertAndSetFirstWall(&head, 23,  OVERALL_WINDOW_WIDTH/2+50, OVERALL_WINDOW_HEIGHT/2-50, 10, 250);
insertAndSetFirstWall(&head, 24,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2+235, 600, 10);*/

    //Maze 1 (Maze 8)

    //Bottom 8
    //Outer rectangle

    /*insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT-10, 300, 10);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2 + 300, OVERALL_WINDOW_HEIGHT-250, 10, 250);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2 + 50, OVERALL_WINDOW_HEIGHT-250, 250, 10);

    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT-10, 300, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT-250, 10, 250);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT-250, 250, 10);

    //Inner rectangle
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT-75, 150, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2 + 150, OVERALL_WINDOW_HEIGHT-175, 10, 110);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT-175, 150, 10);

    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2 - 150, OVERALL_WINDOW_HEIGHT-75, 150, 10);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2 - 150, OVERALL_WINDOW_HEIGHT-175, 10, 110);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2 - 150, OVERALL_WINDOW_HEIGHT-175, 150, 10);

    //Connector
    insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2 - 50, OVERALL_WINDOW_HEIGHT-290, 10, 50);
    insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2 + 50, OVERALL_WINDOW_HEIGHT-290, 10, 50);

    //Upper 8
    //Outer Rectangle
    insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2 + 50, OVERALL_WINDOW_HEIGHT-290, 175, 10);
    insertAndSetFirstWall(&head, 16,  OVERALL_WINDOW_WIDTH/2 + 225, OVERALL_WINDOW_HEIGHT-425, 10, 145);
    insertAndSetFirstWall(&head, 17,  OVERALL_WINDOW_WIDTH/2 + 80, OVERALL_WINDOW_HEIGHT-425, 145, 10);

    insertAndSetFirstWall(&head, 18,  OVERALL_WINDOW_WIDTH/2 - 225, OVERALL_WINDOW_HEIGHT-290, 175, 10);
    insertAndSetFirstWall(&head, 19,  OVERALL_WINDOW_WIDTH/2 - 225, OVERALL_WINDOW_HEIGHT-425, 10, 50);
    insertAndSetFirstWall(&head, 20,  OVERALL_WINDOW_WIDTH/2 - 225, OVERALL_WINDOW_HEIGHT-325, 10, 40);
    insertAndSetFirstWall(&head, 21,  OVERALL_WINDOW_WIDTH/2 - 225, OVERALL_WINDOW_HEIGHT-425, 310, 10);

    //Inner Rectangle
    insertAndSetFirstWall(&head, 22,  OVERALL_WINDOW_WIDTH/2 - 150, OVERALL_WINDOW_HEIGHT-375, 300, 50);

    //Exit
    insertAndSetFirstWall(&head, 23,  OVERALL_WINDOW_WIDTH/2 - 325, OVERALL_WINDOW_HEIGHT-325, 100, 10);
    insertAndSetFirstWall(&head, 24,  OVERALL_WINDOW_WIDTH/2 - 325, OVERALL_WINDOW_HEIGHT-375, 110, 10);*/

    //R18G2
    /*insertAndSetFirstWall(&head, 1,  0+10, 0, 10, OVERALL_WINDOW_HEIGHT+10);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH-50, 0, 10, OVERALL_WINDOW_HEIGHT+10);
    insertAndSetFirstWall(&head, 3,  10, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2+100, 10);
    insertAndSetFirstWall(&head, 4,  150, OVERALL_WINDOW_HEIGHT-250, OVERALL_WINDOW_WIDTH/2-150, 10);
    insertAndSetFirstWall(&head, 5,OVERALL_WINDOW_WIDTH-320,170, 10, OVERALL_WINDOW_HEIGHT-300);
    insertAndSetFirstWall(&head, 6, OVERALL_WINDOW_WIDTH-250,100, 10, OVERALL_WINDOW_HEIGHT-350);
    insertAndSetFirstWall(&head, 7,  320, OVERALL_WINDOW_HEIGHT/2-80, OVERALL_WINDOW_WIDTH/2-250, 10);
    insertAndSetFirstWall(&head, 8,  320, OVERALL_WINDOW_HEIGHT/2+40, OVERALL_WINDOW_WIDTH/2-250, 10);
    insertAndSetFirstWall(&head, 9,  350, OVERALL_WINDOW_HEIGHT/2-150, OVERALL_WINDOW_WIDTH/2-200, 10);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-240, 480, 10);
    insertAndSetFirstWall(&head, 11, OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2+230, 580, 10);
    insertAndSetFirstWall(&head, 12, OVERALL_WINDOW_WIDTH-400,0, 10, OVERALL_WINDOW_HEIGHT-320);
    insertAndSetFirstWall(&head, 13,  180, OVERALL_WINDOW_HEIGHT/2-80, OVERALL_WINDOW_WIDTH/2-250, 10);
    insertAndSetFirstWall(&head, 14, OVERALL_WINDOW_WIDTH-460,0, 10, OVERALL_WINDOW_HEIGHT-320);*/

    //assessable 1 and 2
    /*insertAndSetFirstWall(&head, 2,  220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  400, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  620, 340, 20, 10);

    insertAndSetFirstWall(&head, 1,  320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  520, 440, 120, 10);
    */

    //assessable 3 and 4
    insertAndSetFirstWall(&head, 2,  640-10-220, 400, 10, 80);
    insertAndSetFirstWall(&head, 2,  640-200-20, 400, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 50, 10, 350);
    insertAndSetFirstWall(&head, 2,  640-280-20, 50, 280, 10);
    insertAndSetFirstWall(&head, 2,  640-10-300, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-110-300, 150, 110, 10);
    insertAndSetFirstWall(&head, 2,  640-10-400, 50, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-400-220, 50, 220, 10);
    insertAndSetFirstWall(&head, 2,  640-10-620, 50, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-620-20, 340, 20, 10);


    insertAndSetFirstWall(&head, 1,  640-10-320, 300, 10, 180);
    insertAndSetFirstWall(&head, 2,  640-200-120, 300, 200, 10);
    insertAndSetFirstWall(&head, 2,  640-10-120, 150, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-80-120, 150, 80, 10);
    insertAndSetFirstWall(&head, 2,  640-10-200, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-310-200, 250, 310, 10);
    insertAndSetFirstWall(&head, 2,  640-10-500, 150, 10, 100);
    insertAndSetFirstWall(&head, 2,  640-20-500, 150, 20, 10);
    insertAndSetFirstWall(&head, 2,  640-10-520, 150, 10, 290);
    insertAndSetFirstWall(&head, 2,  640-120-520, 440, 120, 10);


    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, side_left_sensor, side_right_sensor);
        robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        //if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){ //default maze
        //if (checkRobotReachedEnd(&robot, 640, 340, 10, 100)){ //Maze 1
        //if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){ //Maze 2
        if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){ // Maze 3
        //if (checkRobotReachedEnd(&robot, 640-10-320, 480, 100, 10)){ //Maze 4
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }

        //alternate for maze
        /*if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH/2 - 325, OVERALL_WINDOW_HEIGHT-375, 10, 100)){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }*/

        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            //if (front_left_sensor>0)
                //printf("Getting close on the left. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            //if (front_right_sensor>0)
                //printf("Getting close on the right. Score = %d\n", front_right_sensor);

            side_left_sensor = checkRobotSensorSideLeftAllWalls(&robot, head);
            if(side_left_sensor>0)
                printf("Getting close side left. Score = %d\n", side_left_sensor);

            side_right_sensor = checkRobotSensorSideRightAllWalls(&robot, head);
            if(side_right_sensor>0)
                printf("Getting close side right. Score = %d\n", side_right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
