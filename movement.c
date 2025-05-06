//
// Created by tomma on 06/05/2025.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Spacegameheader.h"

void moveplayer(char direction,bool *stop,int grid_size,char grid[grid_size][grid_size],struct player *p,bool *wantoheal){

    // by calling the structure as pointer i can modify the original structure without creating a new one
    //the changes will persist after the function ends his operation. without pointers the function will just create
    //a copy of a structure that is then gonna be deleted after the function ends is job

    grid[p->xcoordinates][p->ycoordinates] = '.';

    p->oldxcoordinate = p->xcoordinates;
    p->oldycoordinate = p->ycoordinates;

    if (direction == 'w'){
        p->xcoordinates -=1;

    }else if(direction == 's'){
        p->xcoordinates +=1;

    }else if(direction == 'd'){
        p->ycoordinates +=1;


    }else if(direction == 'a') {
        p->ycoordinates-=1;
    }else if(direction == 'f') {
        *stop = true;
    }else if(direction == 'W'){


        p->xcoordinates -=1;
        *wantoheal = true;


    }else if(direction == 'S'){


        p->xcoordinates +=1;
        *wantoheal = true;


    }else if(direction == 'A'){


        p->ycoordinates-=1;
        *wantoheal = true;


    }else if(direction == 'D'){

        p->ycoordinates +=1;
        *wantoheal = true;


    }

    if (p->xcoordinates < 0) {
        p->xcoordinates = 0;
    }
    if (p->ycoordinates < 0) {
        p->ycoordinates = 0;
    }
    if (p->xcoordinates >= grid_size) {
        p->xcoordinates = grid_size - 1;
    }
    if (p->ycoordinates >= grid_size) {
        p->ycoordinates = grid_size - 1;
    }

    grid[p->xcoordinates][p->ycoordinates] = 'P';

    //add the bounderis for version 2
}

void moveasteroids(int grid_size, char grid[grid_size][grid_size], struct asteroids *a, int object_x_coordinate[], int object_y_coordinate[],int range) {


    int check=0;
    if (a->xcoord < grid_size && a->ycoord > 0) {
        for(int i = 0; i<range;i++){
            if(object_x_coordinate[i]==a->xcoord && object_y_coordinate[i]==a->ycoord){

                check = 1;
                break; // i add this command meanig that if it finds something is gonna go outside the loop
            }

        }

        if (check == 1){
            grid[a->xcoord][a->ycoord] = 'a';
        }else{
            grid[a->xcoord][a->ycoord] = '.';
        }

        a->xcoord += 1;
        a->ycoord -= 1;


        grid[a->xcoord][a->ycoord] = 'O';
    }else {

        grid[a->xcoord][a->ycoord] = '.';

        a->xcoord = 0; // top
        a->ycoord = grid_size -1; //right,(out of the bounderis wihtout -1)

        grid[a->xcoord][a->ycoord] = 'O';

    }



}
