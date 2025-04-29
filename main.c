

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






int main() {

    srand(time(NULL));


    gamedifficulty();

       return 0;
}


