#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include <Windows.h>
#include <conio.h>
//global variables to be accesible all around the code 
int choice; 
int length, width;
int playerX, playerY, playerHP;
char mapName[15];
char** CreateMap(char* filename)
{
	FILE* fin = fopen(filename, "r");//opening the file for reading purposes
	if (!fin) {
		printf("Error");
		exit(1);
	}
	fscanf(fin, "%i%i\n", &length, &width);
	char** map = (char**)(calloc(length, sizeof(char*)));//allocating space for the map array
	for (int i = 0;i < length;i++) {
		map[i] = (char*)(calloc(width, sizeof(char)));
	}
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			fscanf(fin, "%c\n", &map[i][j]);//populating the array
		}
	}
	return map;
}
void drawMap(char** map)
   {  //drawing the map and header and footer
	printf("You are on the ");
	//checking which map you are on
	if (strcmp(mapName,"Map1.txt") == 0) {
		printf("first stage");
	}
	else if (strcmp(mapName, "Map2.txt") == 0) {
		printf("second stage");
	}
	else if (strcmp(mapName, "Map3.txt") == 0) {
		printf("final stage");
	}
	printf("\nLives: ");
	for (int i = 0;i < playerHP;i++) {
		printf("* ");
	}
	printf("\n");
	//logic for drawing the map elements
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			if (map[i][j] == '1' && (i == 0 || i == length - 1)) {
				printf("-");//walls
			}
			else if (map[i][j] == '1' && (j == 0 || j == width - 1)) {
				printf("|");//walls
			}
			if (map[i][j] == '0' || map[i][j] == '7' || map[i][j] == '8' || map[i][j] == '9') {
				printf(" ");//walkable terrain
			}
			if (map[i][j] == 'P') {//player
				printf("P");
			}
			if (map[i][j] == '2') {//hp gain
				printf("+");
			}
			if (map[i][j] == '3') {
				printf("E");//enemy
			}
			if (map[i][j] == '4') {
				printf("V");//Victory
			}
			if (map[i][j] == '5') {
				printf("X");//tougher enemies
			}
			if (map[i][j] == '6') {
				printf("#");//walls
			}

		}

		printf("\n");

	}
	printf("Controls:\n");
	printf("Up: w\nLeft: a\nDown: s\nRight: d\n");
	printf("\n");
	printf("Hints:\n");
	printf("(E - enemy, X - tougher enemy, + additional life, # - wall which deals damage, V-victory)\n");
}


void startgame() {
	//initializing rand
	srand(time(0));
	//generate the maps
	GenerateMap("Map1.txt");
	GenerateMap("Map2.txt");
	GenerateMap("Map3.txt");
	//copying the map name
	strcpy(mapName, "Map1.txt");
	//starter message
	printf("Shall we begin?\n");
	printf("Press anything above 0 to start\n");
	printf("Press 0 to exit\n");
	if (!scanf("%d", &choice) == 1) {
		printf("Failed to read integer.\n");
	}
	while (choice != 0) {

		newGame();

	}
	//setting win/loss conditions
	if (playerHP == 0) {
		system("CLS");
		printf("You ran out of health, game over\n");
		Sleep(2000);
		exit(1);
	}
	else {
		system("CLS");
		printf("You win, congratulations!");
	}

}

void starterSettings() {
	//starting player settings
	playerHP = 3;
	playerX = 1;
	playerY = 1;
}
void newGame()
{   //initializing starting settings
	starterSettings();
	system("CLS");
	char** map;
	//Creating map array
	map = CreateMap(mapName);
	map[playerX][playerY] = 'P';
	//game logic
	Movement(map);
}
bool Can(char* element)
{   //checking movement conditions
	if ('1' == element) {

		printf("Can't go through that");
		Sleep(1000);
		return false;
	}
	else if ('3' == element) {
		if (playerHP == 1) { //condition to slay the player in case they have 1 life
			choice = 0;
		}
		playerHP--;
		return true;
	}
	else if ('2' == element) {
		playerHP++ ;
		return true;
	}
	else if ('4' == element) {
		Nextmap(); //the "victory" tile
		return false;
	}
	if ('5' == element) {

		if (playerHP == 2 || playerHP==1) {
			choice = 0;
		}
		playerHP=playerHP-2; //a harder enemy that deals more damage
		return true;
	}
	if ('6' == element) {

		printf("Can't go through that");
		if (playerHP == 1) { 
			choice = 0;
		}
		playerHP--; //penalty for slamming into walls
		Sleep(500);
		return false;
	}
	else {
		return true;
	}


}
void Nextmap()
{   //changing maps if you won the previous map
	//the order of the if clauses is this way to ensure that you don't just jump to the final map
	if (strcmp(mapName, "Map3.txt") == 0) {
		choice = 0;
	}
	else if (strcmp(mapName, "Map2.txt") == 0) {
		strcpy(mapName, "Map3.txt");
	}
	else if (strcmp(mapName, "Map1.txt") == 0) {
		strcpy(mapName, "Map2.txt");
	}
	newGame();
}
void Movement(char** map)
{ //the turn logic
	while (!playerX == 0 && !playerY == 0 && choice != 0) {

		int previousX, previousY;
		char option = getchar();
		previousX = playerX;
		previousY = playerY;
		if (option == 'w' && Can(map[playerX - 1][playerY])) {
			playerX--;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';

		}
		else if (option == 's' && Can(map[playerX + 1][playerY])) {
			playerX++;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';
		}
		else if (option == 'd' && Can(map[playerX][playerY + 1])) {
			playerY++;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';

		}
		else if (option == 'a' && Can(map[playerX][playerY - 1])) {
			playerY--;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';
		}


		//Sleep(5000);
		system("CLS");
		drawMap(map);

	}
}

void GenerateMap(char* filename)
{   //creates a txt file with random map elements
	FILE* fin = fopen(filename, "w");
	int length = 12;
	int width = 22;
	int number;
	if (!fin) {
		printf("Error");
		exit(1);
	}
	fprintf(fin, "%i %i\n", length, width);
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			if (i == 0 || i == length - 1) {
				fprintf(fin, "1");
			}
			else if (j == 0 || j == width - 1) {
				fprintf(fin, "1");
			}
			else if (i == 0 && j == 0) {
				fprintf(fin, "0");
			}
			else {
				number = rand() % 10;
				if (number == 1) {
					number = 0;
				}
				fprintf(fin, "%i", number);
			}
			
		} 
		fprintf(fin,"\n");
	}
	fclose(fin);
}