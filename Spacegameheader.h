//
// Created by tomma on 29/04/2025.
//

#ifndef SPACEGAMEHEADER_H
#define SPACEGAMEHEADER_H

// Structures
struct player {
    int xcoordinates;
    int ycoordinates;
    int oldxcoordinate;
    int oldycoordinate;
};

struct score {
    int score;
};

struct asteroids {
    int xcoord;
    int ycoord;
};

struct healthbar {
    int health;
};

// Function declarations
void playercreation(int object_x_coordinate[], int object_y_coordinate[], int grid_size, char grid[grid_size][grid_size], struct player *p);
void asteroidscreation(int grid_size, char grid[grid_size][grid_size], struct asteroids *a);
void moveasteroids(int grid_size, char grid[grid_size][grid_size], struct asteroids *a, int object_x_coordinate[], int object_y_coordinate[], int range);
void SCORE(struct score *s, struct player *p, int object_x_coordinate[], int object_y_coordinate[], int *remaingjunk, int grid_size, char grid[grid_size][grid_size]);
void HEALTH(struct healthbar *h, struct asteroids *a, struct player *p, int grid_size, char grid[grid_size][grid_size]);
void heal(struct healthbar *h, struct player *p, struct score *s, int *remaingjunk, int grid_size, char grid[grid_size][grid_size], int object_x_coordinate[], int object_y_coordinate[]);
void moveplayer(char direction, bool *stop, int grid_size, char grid[grid_size][grid_size], struct player *p, bool *wantoheal);
void Drawgrid(int difficulty, int grid_size, int moves);
void gamedifficulty();
#endif //SPACEGAMEHEADER_H
