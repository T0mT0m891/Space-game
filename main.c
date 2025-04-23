
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct player {
    int xcoordinates;
    int ycoordinates;
    int oldxcoordinate;
    int oldycoordinate;
};
struct asteroids{

    int xcoord;
    int ycoord;
};

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

    a->xcoord = 0; // bottom
    a->ycoord = grid_size -1; //right

    grid[a->xcoord][a->ycoord] = 'O';
}


void Drawgrid(int difficulty, int grid_size){

    struct player p;
    struct asteroids a;

    int object_x_coordinate[difficulty];
    int object_y_coordinate[difficulty];
    char grid[grid_size][grid_size];




    for(int i = 0; i < difficulty; i++ ){

        object_x_coordinate[i] = rand() % grid_size;
        object_y_coordinate[i]= rand() % grid_size;

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


        for(int i = 0; i < grid_size; i++ ){
            for(int j = 0; j < grid_size; j++){

             printf(" %c ", grid[i][j]);

            };

            printf("\n");
        };



};

void gamedifficulty(){

    int x;
    int gridsize, n_junk;

    printf("\n");
    printf("The difficulty change the amount of junk that needs to be collected and the size of the grid\n");
    printf(" Level 1 => 5 piece of junk\n Level 2 => 8 piece of junk\n Level 3 => 10 piece of junk\n");
    printf("PLease choose the difficulty of the game: ");
    scanf("%d",&x);
    printf("\n");

    if(x == 1 ){

        gridsize = 25;
        n_junk = 5;

    }else if (x == 2){

        gridsize = 21;
        n_junk = 8;

    }else{
        gridsize = 19;
        n_junk = 10;
    }

    Drawgrid(n_junk, gridsize);
};






int main() {

    srand(time(NULL));


    gamedifficulty();

       return 0;
}


