

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Spacegameheader.h"

//this file contain the function that handle the score, the health of the player and the heal function

//this function handle the score of the game
//if the coordinates of the player and the coordinates of the piece of junk are collected it means that it has been collected
//it replace the junk with the player, increase the score and remove the coordinates of the collected piece of junk from the array
void SCORE(struct score *s, struct player *p,int object_x_coordinate[], int object_y_coordinate[],int *remaingjunk,int grid_size, char grid[grid_size][grid_size]){


    for(int i = 0; i<*remaingjunk; i++){

        if(object_x_coordinate[i] == p->xcoordinates && object_y_coordinate[i]==p->ycoordinates){

            grid[object_x_coordinate[i]][object_y_coordinate[i]] = 'P';

            s->score+=1;

            //https://www.procoding.org/c-program-delete-an-element-from-array
            //the -1 in the condition is used to avoid to go out of the array boundaries
            //E.g the remaingjunk is 10, array goes from 0 to 9, when j is 9 j+1 will be 10. that's why i added the -1
            for(int j = i; j < *remaingjunk-1; j++) {

                //on each iteration the code overwrite the values placed on j position with the values next to them
                object_x_coordinate[j] = object_x_coordinate[j + 1];
                object_y_coordinate[j] = object_y_coordinate[j + 1];


            }
            //i'm reducing the integer stored in the memory address pointed by remaingjunk
            (*remaingjunk)--;
        }
    }

}
//this function handle the health of the player
//if the player and the asteroid coordinates are the same replace the current position of the player with the asteroids
//change the player coordinates with is previous one,replace the player using the old coordinates and decrease the HEALTh by 5
void HEALTH(struct healthbar *h,struct asteroids *a, struct player *p,int grid_size, char grid[grid_size][grid_size]){


    //if the player get hit
    if(p->xcoordinates==a->xcoord && p->ycoordinates==a->ycoord){

        // -> is deferencing and accessing at the same time
        grid[p->xcoordinates][p->ycoordinates] = 'O';

        p->xcoordinates = p->oldxcoordinate;//go back to your previous location

        p->ycoordinates = p->oldycoordinate;

        grid[p->xcoordinates][p->ycoordinates] = 'P';//put the player in the previous position

        h->health= h->health -5;
    }
}
//this function handle the heal, action that can happen only if the player score is greater than zero and his health is less than 8
//it increase the health and decrease the score when the condition is met
//it then generate a new piece of junk
//to do that it generate that x and y coordinates and the check if there is a collision with the player or the current position of the player
void heal(struct healthbar *h, struct player *p, struct score *s, int *remaingjunk, int grid_size, char grid[grid_size][grid_size], int object_x_coordinate[], int object_y_coordinate[]){

    int newx;
    int newy;
    int right;
    bool check = false;
    bool check1 = false;


    if(s->score == 0){

        printf("YOU NEED TO COLLECT PIECE OF JUNK");
        return;//this return is used to exit the function immediately

    }else{

        h->health = h->health + 1;
        s->score = s ->score - 1;


        //this condition will allow the loop to continue until at least one of the two given condition is false
        //when both become true the loop will end
        while(check == false && check1 == false){

            right = 0;//no collision
            newx = rand() % grid_size;
            newy = rand() % grid_size;

            //check for collision with the existing junk

            for(int i = 0; i<*remaingjunk;i++){
                if(object_x_coordinate[i] == newx && object_y_coordinate[i] == newy){

                    right = 1;//collision happen
                    //https://www.ibm.com/docs/en/wdfrhcw/1.4.0?topic=commands-break-command-c-c
                    //it can run even without it, it simply making more efficent because if it find more than one collisin
                    //right will be always one
                    break;// this line is responsible to exit the loop when one collisin has to found
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

    //first i need to deference(get access to the value stored in remaingjunk address) and then i can increment
    (*remaingjunk)++;
}









int main() {

    // this is used to define the seed of the rand function. Now the rand function will use as seed the total time passed since
    //january 1 1970. In this way every time i run the code the the time passed will change
    srand(time(NULL));


    gamedifficulty();

       return 0;
}


