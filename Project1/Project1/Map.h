#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
char** CreateMap(char* filename);
void drawMap(char** map);
void starterSettings();
void startgame();
void newGame();
bool Can( char* tile);
void Nextmap();
void Movement(char** map);
void GenerateMap(char* filename);
#endif //!MAP_H
