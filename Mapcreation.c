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

   //with this line i'm accessing the xcoordinates member of the player structure that is pointed by p

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
	//strcut player is the prototype of the structure and p is the variable that refered to it
  	struct player p;//i'm declarinng a variable p that will represent a single player, with all the charcteristic define in the player structure
    struct score s;// the variable s contain all the field define inside the structure score
    struct asteroids a;
    struct healthbar h;

    int object_x_coordinate[difficulty];
    int object_y_coordinate[difficulty];
    char grid[grid_size][grid_size];
    int decision;

   // i'm declaring a boolean variable, a type of variable that can be only true or false
    bool stopgame = false; // this variable is used to end the game if the user press f
    bool endgame = false;//this variable ends the game when the player has collected all the available junk
    bool dead = false;//this variable is used to end the game if the player health is less or equal to zero
    bool wantoheal = false;//this variable is used to trigger the heal function
    bool finishmove = false;//this variable is used to end the game if the user finishes all the moves

	//the first part is called initialization, and is used to declare and set the counter for the loop
    //the second part a condtion that is check each time, before each iteration
    //the third part is the increment and it runs, after the loop interation

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

            //in the first loop is not going to check anything since i is zero and j is zero, is just going to generate the first junk
            //in the second loop it check the if the coordinate in postion zero are the same of the one that are just being genereted
            //in the third loop it will compared the first two coordinate and the newly define coordinate
            for(int j = 0; j<i; j++){

                if(object_x_coordinate[j] == x_coordinate && object_y_coordinate[j] == y_coordinate){

                    equal = true; // if number are the same set eqaul to false, meaning that it needs to generete a new piece of jjunk
                    //for that index position
                    //a break can eventually be added here
                }
            }



        }

        //assing the newly create variable to the array of coordintes

        object_x_coordinate[i] = x_coordinate;
        object_y_coordinate[i] = y_coordinate;

    }


	 //with these for loop i'm inserting the . inside the grid
    for(int i = 0; i < grid_size; i++ ){
        for(int j = 0; j < grid_size; j++){

            grid[i][j] = '.';

        };

    };

	//i'm inserting in the junk inside the matrix, using the random coordintes that i've genereted
    for(int i = 0; i < difficulty; i++) {
        int x1 = object_x_coordinate[i];
        int y1 = object_y_coordinate[i];
        grid[x1][y1] = 'a';
    }


	 //I'm passing the variable p as a pointer to my structure player
    //This allow my function to have access to the structure, it allows it to make changes to it, that will persist and remain outside the function
    playercreation(object_x_coordinate,object_y_coordinate,grid_size,grid,&p);
    asteroidscreation(grid_size,grid,&a);

    s.score= 0;
    h.health = 10;
    int isjunkthere = difficulty;

	//This loop  will continue on working until one of this condtion is no longer false
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

          	//the following function allow the user to heal himself with the junk that he collect. if this happen the function generate a new piece of junk in the map
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

    //im declaring a pointer to a file variable called end, it will create a new file called finalresult.txt and
    //it will open in it write mode, meaning that the user can write on the following file and in case a file with a similar name already exist
    //the content of it will be overwritten
    //fopen will return a pointer to a file
    FILE *end= fopen("hello.txt", "w");

    //writing the desired text in the finalresult file, that is link by the end pointer, so
    //my string is being send to the text fiel thourght the pointe end
    //look the file pointed by end and write a string in it
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