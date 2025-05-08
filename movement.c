//
// Created by tomma on 06/05/2025.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Spacegameheader.h"

//this function handle the player movement
//based on the chosen direction the function update the x and y coordinates of the player
//it checks if the desired movement would bring the player outside the map
//when a capital letter is pressed, it trigger one of the conditon that allow the user to hrsl himself
//if the other condition are not met the player will simply move in the chosen direction

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
    }else if (p->ycoordinates < 0) {
        p->ycoordinates = 0;
    }else if (p->xcoordinates >= grid_size) {
        p->xcoordinates = grid_size - 1;
    }else if (p->ycoordinates >= grid_size) {
        p->ycoordinates = grid_size - 1;
    }

    grid[p->xcoordinates][p->ycoordinates] = 'P';


}

//this function handle the movement of the asteroid
//the it reaches the bottom left of the map, meanining that its x coordinate is 17 and is y coordinate is zero
//it reset the asteroid position to his previous one

void moveasteroids(int grid_size, char grid[grid_size][grid_size], struct asteroids *a, int object_x_coordinate[], int object_y_coordinate[],int range) {


    int check=0;
    //a->xcoord, i'm accessing the xcoord member of the asteroid structure that is pointed by a
    //so with -> i'm deferecing the pointer a and accessing a member of the structure

    if (a->xcoord < grid_size && a->ycoord > 0) {
        for(int i = 0; i<range;i++){
            if(object_x_coordinate[i]==a->xcoord && object_y_coordinate[i]==a->ycoord){

                check = 1;
                // i add this command meanig that if it finds something is gonna go outside the loop
            }

        }

        //when check is equal to zero it means that the asteorid and a piece of junk have the same coordinates

        if (check == 1){
            grid[a->xcoord][a->ycoord] = 'a';//when this happen the current coordinates of the asteorid needs to be replaced with the junk

        }else{
            grid[a->xcoord][a->ycoord] = '.';//when there is no collision the current position is being replace by a dot
        }

        //i'm updating the coordinates of the asterod
        a->xcoord += 1;
        a->ycoord -= 1;

        //after i've update the coordinates i'm inserting the asterod in the newly defined position
        grid[a->xcoord][a->ycoord] = 'O';
    }else {
        //the current position of the asteroid, that is gonna be the bottom left corner needs to be replace with a dot
        grid[a->xcoord][a->ycoord] = '.';

        a->xcoord = 0; // top
        a->ycoord = grid_size -1; //right,(out of the bounderis wihtout -1)
        //beacuse the matrix goes from 0 to 17 meaning that i use 18 the asteroid will wbe outside)

        grid[a->xcoord][a->ycoord] = 'O';

    }



}
