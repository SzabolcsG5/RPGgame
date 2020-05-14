#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include <Windows.h>
#include <conio.h>
int choice;
int length, width;
int playerX, playerY, playerHP;
char mapName[15];
char** CreateMap(char* filename)
{
	FILE* fin = fopen(filename, "r");
	if (!fin) {
		printf("Sikertelen");//igen vagyis hol
		exit(1);
	}
	fscanf(fin, "%i%i\n", &length, &width);
	char** map = (char**)(calloc(length, sizeof(char*)));
	for (int i = 0;i < length;i++) {
		map[i] = (char*)(calloc(width, sizeof(char)));
	}
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			fscanf(fin, "%c\n", &map[i][j]);
		}
	}
	return map;
}
void drawR(char** map) {
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");

	}
}

void drawMap(char** map)
{ //2-3 tipusu "karakter"
	//drawR(map);
	printf("You are on ");
	printf(mapName);
	printf("\nLives: ");
	//printf(choice);
	for (int i = 0;i < playerHP;i++) {
		printf("* ");
	}
	printf("\n");
	for (int i = 0;i < length;i++) {
		for (int j = 0;j < width;j++) {
			if (map[i][j] == '1' && (i == 0 || i == length - 1)) {
				printf("-");
			}
			else if (map[i][j] == '1' && (j == 0 || j == width - 1)) {
				printf("|");
			}
			if (map[i][j] == '0') {
				printf(" ");
			}
			if (map[i][j] == 'P') {
				printf("P");
			}
			if (map[i][j] == '2') {
				printf("#");
			}
			if (map[i][j] == '3') {
				printf("E");//az ellenségek
			}
			if (map[i][j] == '4') {
				printf(" ");
			}

		}

		printf("\n");

	}
	printf(" Fel: W\n Bal: A\n Le: S\n Jobb: D\n ");

}


void startgame() {
	
	
   strcpy(mapName,"Map.txt");
	playerHP = 1;
	playerX = 1;
	playerY = 1;
	printf("Shall we begin?\n");
	printf("Press anything above 0 to start\n");
	printf("Press 0 to exit\n");
	if (!scanf("%d", &choice) == 1) {
		printf("Failed to read integer.\n");
	}
	while (choice != 0) {
		if (playerHP == 0) {
			choice = 0;
			system("CLS");
			printf("You ran out of health, game over");
			return 0;
			
		}
		system("CLS");
		char** map;
		map = CreateMap(mapName);
		//int previousX, previousY;

		map[playerX][playerY] = 'P';


		Movement(map);

	}
		system("CLS");
		printf("OK boomer\n");
		Sleep(2000);
	    exit(1);
	

}
bool Can(char* element)
{   
	if ('1' == element) {

		printf("Can't go through that");
		Sleep(2000);
		return false;
	}
	else if ('3'==element){
		if (playerHP == 1) {
			choice = 0;
		}
		playerHP--;
		return true;
	}
	else if ('2' == element) {
		playerHP++;
		return true;
	}
	else if ('4' == element) {
		Nextmap();
		return false;
	}
	else {
		return true;
    }
   
	
}
void Nextmap()
{
	if (strcmp(mapName, "Map.txt")) {
		strcpy(mapName, "Map2.txt");
}
	else if (strcmp(mapName, "Map2.txt")) {
		strcpy(mapName, "Map3.txt");
	}
}
void Movement(char** map)
{
	while (!playerX == 0 && !playerY == 0) {

		int previousX, previousY;
		char option = getchar();
		previousX = playerX;
		previousY = playerY;
		if (option == 'W' && Can(map[playerX - 1][playerY])) {
			playerX--;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';
			
		}
		else if (option == 'S' && Can(map[playerX + 1][playerY])) {
			playerX++;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';
		}
		else if (option == 'D' && Can(map[playerX][playerY+1])) {
			playerY++;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';

		}
		else if (option == 'A' && Can(map[playerX][playerY - 1])) {
			playerY--;
			map[playerX][playerY] = 'P';
			map[previousX][previousY] = '0';
		}
		
		
		//Sleep(5000);
		system("CLS");
		drawMap(map);

	}
}
