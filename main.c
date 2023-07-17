#include <stdio.h>
#include <stdlib.h>
#include <time.h> // to feed random seed
#include "conio.h" // conio.h provided by https://github.com/casualsnek/linuxconio

#define true 1
#define false 0
#define FRAME_WIDTH 40
#define FRAME_HEIGHT 20
#define EDGE 90

// create a playing field in the console
void frame(int x, int y, int w, int h){
	// drawing left and right edges
	for (int i = y; i < h + 2; ++i){
		gotoxy(x, i);
		printf("║");

		gotoxy(x + w, i);
		printf("║");
	}

	// drawing top and bottom edges
	for (int i = y; i < w + 1; ++i){
		gotoxy(i, y);
		printf("═");

		gotoxy(i, y + h);
		printf("═");
	}

	// drawing the corners
	gotoxy(x, y);
	printf("╔");
	gotoxy(x, y + h);
	printf("╚");
	gotoxy(x + w, y);
	printf("╗");
	gotoxy(x + w, y + h);
	printf("╝");
}



void snake(int x, int y){
	gotoxy(x, y);
	printf("#");
	gotoxy(EDGE, EDGE);

}

struct coordinates{
	int x;
	int y;
};

struct directions{
	int up;
	int down;
	int left;
	int right;
};


void changeDirection(struct directions* directions, char direction){
	if (direction == 'U'){
		directions->up = false;
		directions->down = false;
		directions->left = false;
		directions->right = false;

		directions-> up = true;

	}
	else if (direction == 'D'){
		directions->up = false;
		directions->down = false;
		directions->left = false;
		directions->right = false;

		directions->down = true;
	}

	else if (direction == 'L'){
		directions->up = false;
		directions->down = false;
		directions->left = false;
		directions->right = false;

		directions->left = true;
	}

	else if (direction == 'R'){
		directions->up = false;
		directions->down = false;
		directions->left = false;
		directions->right = false;

		directions->right = true;
	}
}


int main(){

	int size = 3;
	int x = 10;
	int y  = 10;
	int score = 0;

	int foodX = 40;
	int foodY = 10;

	// creating arrays for the coordinates
	struct coordinates* all_coordinates;
	all_coordinates = calloc(255, sizeof(struct coordinates));
	if (all_coordinates == NULL){
		fprintf(stderr, " Array not allocated...\n");
	 	return 1;
	}

	for (int i = 0; i < size; ++i){
		all_coordinates[i - size].x = x - i;
		all_coordinates[i].y = y;
	}

	// these will determain witch directions the snake will move
	struct directions directions;
	directions.up = false;
	directions.down = false;
	directions.left = false;
	directions.right = true;

	// this will capture the keypress
	int key;

	int running = true;
	while(running){
		// feeding the
		srand(time(NULL));

		// KEYPRESS 
		while (kbhit()) {
			key = getch();
			switch (key) {
				case 65: changeDirection(&directions, 'U'); break;
				case 66: changeDirection(&directions, 'D'); break;
				case 68: changeDirection(&directions, 'L'); break;
				case 67: changeDirection(&directions, 'R'); break;
				case 113: running = false; break;
				case 81: running = false; break;
			}

		}

		
		// snake movement
		if (directions.up){
			y--;
			for (int i = 0; i < size; ++i){
				all_coordinates[i - 1].x = all_coordinates[i].x;
				all_coordinates[i - 1].y = all_coordinates[i].y;
			}
			all_coordinates[size - 1].x = x;
			all_coordinates[size - 1].y = y;

		}
		
		else if (directions.down){
			y++;
			for (int i = 0; i < size; ++i){
				all_coordinates[i - 1].x = all_coordinates[i].x;
				all_coordinates[i - 1].y = all_coordinates[i].y;
			}
			all_coordinates[size - 1].x = x;
			all_coordinates[size - 1].y = y;
		}

		else if (directions.left){
			x--;
			for (int i = 0; i < size; ++i){
				all_coordinates[i - 1].x = all_coordinates[i].x;
				all_coordinates[i - 1].y = all_coordinates[i].y;
			}
			all_coordinates[size - 1].x = x;
			all_coordinates[size - 1].y = y;

		}

		else if (directions.right){
			x++;
			for (int i = 0; i < size; ++i){
				all_coordinates[i - 1].x = all_coordinates[i].x;
				all_coordinates[i - 1].y = all_coordinates[i].y;
			}
			all_coordinates[size - 1].x = x;
			all_coordinates[size - 1].y = y;

		}


		// collition detection:
		if (x == foodX && y == foodY){
			score++;
			foodX = rand() % FRAME_WIDTH - 4;
			foodY = rand() % FRAME_HEIGHT - 4;
			size++;
			all_coordinates[size - 1].x = x;
			all_coordinates[size - 1].y = y;
		}

		if (foodX > FRAME_WIDTH - 2) foodX = FRAME_WIDTH - 4;
		else if(foodY > FRAME_HEIGHT - 2) foodY = FRAME_HEIGHT - 4;
		else if(foodX < 4) foodX = 6;
		else if(foodY < 4) foodY = 6;

		// if snake collides with itself, game over
		for (int i = 0; i < size - 2; ++i){
			if (x == all_coordinates[i].x && y == all_coordinates[i].y){
				running = false;
			}
		}

		// if snake collides with the walls game over
		if (x < 1 || x > FRAME_WIDTH - 1 || y < 3 || y > FRAME_HEIGHT){
			running = false;
		}


		// RENDER
		textcolor(GREEN);

		// title
		gotoxy(1,1);
		printf(".:Snake in C By: Lu:. \t   score %i", score);
		//drawing the fram
		frame(1,2,FRAME_WIDTH, FRAME_HEIGHT);
		// drawing the snake
		for (int i = 0; i < size; ++i) snake(all_coordinates[i].x, all_coordinates[i].y);
		
		gotoxy(foodX, foodY);
		printf("0");

		// moving the cursor away so everythong can be dsiplayed properly
		gotoxy(EDGE, EDGE);
		system("sleep 0.06");
		system("clear");
	
	}


	// once memory is not longer used, clear it
	all_coordinates = NULL;
	free(all_coordinates);
	printf("\n");
	return 0;
}

