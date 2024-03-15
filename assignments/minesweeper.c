#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMap(int rows, int cols, char map[rows][cols]){

	//function that prints a map

	int i, j;

	for (i = 0; i < rows+1; i++){
		for (j = 0; j < cols+1; j++){

			if (i == 0){
				printf("%2i", j);
			}else if (j == 0 ){
				printf("%2i", i);
			}else{
				printf("%2c", map[i-1][j-1]);
			}
		}
		printf("\n");
	}
}

void addProximities(int rows, int cols, char map[rows][cols]){

	//function that adds proximity information

	int r, c, count;

	for (r = 0; r < rows; r++){
		for (c = 0; c < cols; c++){

			if (map[r][c] != '*'){

				count = 0;

				if (r-1 >= 0 && c-1 >= 0 && map[r-1][c-1] == '*'){
					count++;
				}
				if (r-1 >= 0 && map[r-1][c] == '*'){
					count++;
				}
				if (r-1 >= 0 && c+1 < cols && map[r-1][c+1] == '*'){
					count++;
				}
				if (c-1 >= 0 && map[r][c-1] == '*'){
					count++;
				}
				if (c+1 < cols && map[r][c+1] == '*'){
					count++;
				}
				if (r+1 < rows && c-1 >= 0 && map[r+1][c-1] == '*'){
					count++;
				}
				if (r+1 < rows && map[r+1][c] == '*'){
					count++;
				}
				if (r+1 < rows && c+1 < cols && map[r+1][c+1] == '*'){
					count++;
				}

				if (count != 0){
					map[r][c] = count + '0';
				}
			}
		}
	}
}

void initialize_view(int rows, int cols, _Bool view[rows][cols]){

	//Function that initializes view array

	int i, j;

	for (i = 0; i < rows; i++){
			for (j = 0; j < cols; j++){
				view[i][j] = 0; //False
			}
		}
}

void temp_map(int rows, int cols, _Bool view[rows][cols], char map[rows][cols], char map_temp[rows][cols]){

	//Function that modifies map_temp

	int i, j;

	for (i = 0; i < rows; i++){
		for (j = 0; j < cols; j++){
			if (view[i][j] == 1){
				map_temp[i][j] = map[i][j];
			}else{
				map_temp[i][j] = '?';
			}
		}
	}
}

int main(void){

	setvbuf(stdout, NULL, _IONBF, 0);

	int rows, cols, mines_max;

	//To choose the number of rows, columns and mines
	printf("Please enter in R, C, and M (e.g., 12 30 10): ");
	scanf("%i %i %i", &rows, &cols, &mines_max);

	int i, j;

	//Printing hidden map
	for (i = 0; i < rows + 1; i++){
		for (j = 0; j < cols + 1; j++){
			if (i == 0){
				printf("%2i", j);
			}else if (j == 0 ){
				printf("%2i", i);
			}else{
				printf("%2c", '?');
			}
		}
			printf("\n");
	}

	char map[rows][cols];

	//Creating map of dots

	for (i = 0; i < rows; i++){
		for (j = 0; j < cols; j++){
			map[i][j] = '.';
		}
	}

	int seed = time(NULL);
	srand(seed);

	//Placing mines randomly
	int num_of_mines = 0;

	while (num_of_mines < mines_max){

		i = rand() % rows;
		j = rand() % cols;

		if (map[i][j] != '*'){
			map[i][j] = '*';
			num_of_mines++;
		}
	}

	//Adding proximity information
	addProximities(rows, cols, map);

	_Bool view[rows][cols];

	//Initializing view array with all zeros
	initialize_view(rows, cols, view);

	int r, c, r_coord, c_coord;
	int num_guesses = 0;

	_Bool continue_game = 1; //True

	printf("Please enter in a coordinate pair (e.g., 1 1): ");
	scanf("%i %i", &r_coord, &c_coord);

	r = r_coord - 1;
	c = c_coord - 1;

	while(continue_game){

		//Checking whether coordinates are appropriate
		if (r >= 0 && r < rows && c >= 0 && c < cols){

			//Temporary map
			char map_temp[rows][cols];

			if (map[r][c] == '*'){
				printf("BOOM!!!\n");
				//Printing final map
				printMap(rows, cols, map);
				continue_game = 0; //False
				continue;
			}else if (map[r][c] == '.'){ //To display neighbors when proximity = 0

				view[r][c] = 1; //True

				if (r-1 >= 0 && c-1 >= 0){
					view[r-1][c-1] = 1;
					num_guesses++;
				}
				if (r-1 >= 0){
					view[r-1][c] = 1;
					num_guesses++;
				}
				if (r-1 >= 0 && c+1 < cols){
					view[r-1][c+1] = 1;
					num_guesses++;
				}
				if (c-1 >= 0){
					view[r][c-1] = 1;
					num_guesses++;
				}
				if (c+1 < cols){
					view[r][c+1] = 1;
					num_guesses++;
				}
				if (r+1 < rows && c-1 >= 0){
					view[r+1][c-1] = 1;
					num_guesses++;
				}
				if (r+1 < rows){
					view[r+1][c] = 1;
					num_guesses++;
				}
				if (r+1 < rows && c+1 < cols){
					view[r+1][c+1] = 1;
					num_guesses++;
				}

				num_guesses++;

				if (num_guesses == rows*cols - mines_max){
					printf("Congratulations, you won!!!\n");
					//Printing final map
					printMap(rows, cols, map);
					continue_game = 0; //False
					continue;
				}

				//Filling temporary map
				temp_map(rows, cols, view, map, map_temp);

				//Printing temporary map
				printMap(rows, cols, map_temp);
			}else{

				view[r][c] = 1; //True

				num_guesses++;

				if (num_guesses == rows*cols - mines_max){
					printf("Congratulations, you won!!!\n");
					//Printing final map
					printMap(rows, cols, map);
					continue_game = 0; //False
					continue;
				}

				//Filling temporary map
				temp_map(rows, cols, view, map, map_temp);

				//Printing temporary map
				printMap(rows, cols, map_temp);
			}

			printf("Please enter in a coordinate pair (e.g., 1 1): ");
			scanf("%i %i", &r_coord, &c_coord);
		}else {
			printf("Coordinates are out of range. Please enter in a coordinate pair again: ");
			scanf("%i %i", &r_coord, &c_coord);
		}
		r = r_coord - 1;
		c = c_coord - 1;
	}

	return 0;
}



