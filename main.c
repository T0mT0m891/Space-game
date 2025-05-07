

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Spacegameheader.h"


void SCORE(struct score *s, struct player *p,int object_x_coordinate[], int object_y_coordinate[],int *remaingjunk,int grid_size, char grid[grid_size][grid_size]){


    for(int i = 0; i<*remaingjunk; i++){

        if(object_x_coordinate[i] == p->xcoordinates && object_y_coordinate[i]==p->ycoordinates){

            grid[object_x_coordinate[i]][object_y_coordinate[i]] = 'P';

            s->score+=1;

            //https://www.procoding.org/c-program-delete-an-element-from-array
            for(int j = i; j < *remaingjunk-1; j++) {


                object_x_coordinate[j] = object_x_coordinate[j + 1];
                object_y_coordinate[j] = object_y_coordinate[j + 1];
                ;// I need this because i need to decrease the value store in the address pointed by the pointer remainng junk

            }
            (*remaingjunk)--;
        }
    }

}
void HEALTH(struct healthbar *h,struct asteroids *a, struct player *p,int grid_size, char grid[grid_size][grid_size]){


    //if the player get hit
    if(p->xcoordinates==a->xcoord && p->ycoordinates==a->ycoord){

        grid[p->xcoordinates][p->ycoordinates] = 'O';

        p->xcoordinates = p->oldxcoordinate;//go back to your previous location

        p->ycoordinates = p->oldycoordinate;

        grid[p->xcoordinates][p->ycoordinates] = 'P';//put the player in the previous position

        h->health= h->health -5;
    }
}
void heal(struct healthbar *h, struct player *p, struct score *s, int *remaingjunk, int grid_size, char grid[grid_size][grid_size], int object_x_coordinate[], int object_y_coordinate[]){

    int newx;
    int newy;
    int right;
    bool check = false;
    bool check1 = false;


    if(s->score == 0){

        printf("YOU NEED TO COLLECT PIECE OF JUNK");
        return;

    }else{

        h->health = h->health + 1;
        s->score = s ->score - 1;



        while(check == false && check1 == false){

            right = 0;//no collision
            newx = rand() % grid_size;
            newy = rand() % grid_size;

            //check for collosion with the existing junk

            for(int i = 0; i<*remaingjunk;i++){
                if(object_x_coordinate[i] == newx && object_y_coordinate[i] == newy){

                    right = 1; //collisin happen
                    break;
                }
            }

            if(right == 1){
                check = false;
            }else{
                check = true;
            }

            //check with collisin with player
            if(p->xcoordinates == newx && p->ycoordinates == newy){
                check1 = false;
            }else{
                check1 = true;
            }
        }



    }

    grid[newx][newy]= 'a';
    object_x_coordinate[*remaingjunk] = newx;
    object_y_coordinate[*remaingjunk] = newy;

    (*remaingjunk)++;
}









int main() {

    srand(time(NULL));


    gamedifficulty();

       return 0;
}


