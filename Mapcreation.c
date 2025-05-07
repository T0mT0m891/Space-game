//
// Created by tomma on 07/05/2025.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Spacegameheader.h"

void playercreation(int object_x_coordinate[], int object_y_coordinate[], int grid_size, char grid[grid_size][grid_size], struct player *p){

    //this is the version 2.0 of the function
    p->xcoordinates = grid_size-2;
    p->ycoordinates = grid_size/ 2;

    for(int i = 0; i < grid_size; i++ ){


        if(object_x_coordinate[i] == p->xcoordinates && object_y_coordinate[i] == p->ycoordinates){

            p->xcoordinates = p->xcoordinates + +1;
            p->ycoordinates = p->ycoordinates + +1;
        }
    };

    grid[p->xcoordinates][p->ycoordinates] = 'P';



};
void asteroidscreation(int grid_size,char grid[grid_size][grid_size], struct asteroids *a){

    a->xcoord = 0; // top
    a->ycoord = grid_size-1; //right(out of the bounderis wihtout -1)

    grid[a->xcoord][a->ycoord] = 'O';
}

void Drawgrid(int difficulty, int grid_size,int moves){

  struct player p;
    struct score s;
    struct asteroids a;
    struct healthbar h;

    int object_x_coordinate[difficulty];
    int object_y_coordinate[difficulty];
    char grid[grid_size][grid_size];
    int decision;

    bool stopgame = false;
    bool endgame = false;
    bool dead = false;
    bool wantoheal = false;
    bool finishmove = false;


    for(int i = 0; i < difficulty; i++ ){

        //the rand functinn is used to generate random from 0 to the size-1 of the grid_size
        //if an upper bound in not given the function will use the predefined one
        int x_coordinate;
        int y_coordinate;
        bool equal = true; // declare a boolean variable used for the while loop

        while(equal == true){

            x_coordinate = rand() % grid_size;// generate the x coordinte of one piece of junk
            y_coordinate = rand() % grid_size; // generate the y coordinate of one piece of junk

            equal = false; // with line i'm assuming that the the are no eqaul coordinate

            //in the first loop is not going to check anything since i is zero and j is zero, is just going to generatethe first junk
            //in the second loop it check the if the coordinate in postion zero are the same of the one that are just being genereted
            //in the third loop it will compared the first two coordinate and the newly define coordinate
            for(int j = 0; j<i; j++){

                if(object_x_coordinate[j] == x_coordinate && object_y_coordinate[j] == y_coordinate){

                    equal = true; // if number are the same set eqaul to false, meaning that it needs to generete a new piece of jjunk
                    //for that index position
                }
            }



        }

        //assing the newly create variable to the array of coordintes

        object_x_coordinate[i] = x_coordinate;
        object_y_coordinate[i] = y_coordinate;

    }



    for(int i = 0; i < grid_size; i++ ){
        for(int j = 0; j < grid_size; j++){

            grid[i][j] = '.';

        };

    };


    for(int i = 0; i < difficulty; i++) {
        int x1 = object_x_coordinate[i];
        int y1 = object_y_coordinate[i];
        grid[x1][y1] = 'a';
    }



    playercreation(object_x_coordinate,object_y_coordinate,grid_size,grid,&p);
    asteroidscreation(grid_size,grid,&a);

    s.score= 0;
    h.health = 10;
    int isjunkthere = difficulty;


    while(stopgame == false && endgame == false && dead == false && finishmove == false){
        for(int i = 0; i < grid_size; i++ ){
            for(int j = 0; j < grid_size; j++){

             printf(" %c ", grid[i][j]);

            };

            printf("\n");
        };


         char direction;

         printf("\n           CURRENT SCORE: %d\n", s.score);

          printf("\n           HEALTH: %d\n",h.health);


        printf("\nRemaining moves: %d\n", moves);
         printf("\nInsert in which direction you want to move");
         printf("\nFoward => W \n Backward => S \n Right => D \n Left => A \n");
         printf("\nUse the capital letter if you want to move and heal yourself \n");
         printf("Press f in you want to end the game: ");
         scanf(" %c", &direction);
         printf("\n");

        moveplayer(direction,&stopgame,grid_size,grid,&p,&wantoheal);
        if (wantoheal == true && h.health <= 8 ){

            heal(&h,&p,&s,&isjunkthere,grid_size,grid,object_x_coordinate,object_y_coordinate);
            wantoheal = false;
        }
        SCORE(&s,&p,object_x_coordinate,object_y_coordinate,&isjunkthere,grid_size,grid);
        moveasteroids(grid_size,grid,&a,object_x_coordinate,object_y_coordinate,difficulty);
        HEALTH(&h,&a,&p,grid_size,grid);

        moves = moves -1;

        if(isjunkthere==0){//new version

            endgame = true; // use this function to stop the game if the user collects all the pieces of junk
        }

        if(h.health <= 0){
            dead = true;
        }
        if (moves == 0) {
            finishmove = true;
        }
    }

    //www.geeksforgeeks.org/fprintf-in-c/
    FILE *end= fopen("hello.txt", "w");

    fprintf(end,"The game has ended\n");
    if(s.score == difficulty){
        fprintf(end,"\nYOU WON!!\n");
    }else{
        fprintf(end,"\nYOU LOST\n");
    }
    fprintf(end,"Final score: %d\n", s.score);
    fprintf(end,"Remaining moves: %d\n", moves);
    if(h.health <= 0){

        fprintf(end,"Final health: %d", h.health*0);

    }else{
       fprintf(end,"Final health: %d", h.health);
    }

    fclose(end);


};
void gamedifficulty(){

    int x;
    int gridsize, n_junk,totalmoves;

    printf("\n");
    printf("The difficulty change the amount of junk that needs to be collected and the size of the grid\n");
    printf(" Level 1 => 5 piece of junk\n Level 2 => 8 piece of junk\n Level 3 => 10 piece of junk\n");
    printf("PLease choose the difficulty of the game: ");
    scanf("%d",&x);
    printf("\n");

    if(x == 1 ){

        gridsize = 25;
        n_junk = 5;
        totalmoves = 100;

    }else if (x == 2){

        gridsize = 21;
        n_junk = 8;
        totalmoves = 84;

    }else{
        gridsize = 19;
        n_junk = 10;
        totalmoves = 76;
    }

    Drawgrid(n_junk, gridsize,totalmoves);
};