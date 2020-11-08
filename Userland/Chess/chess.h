#ifndef CHESS_H
#define CHESS_H

#include <stdint.h>

#define PLAYER_W 0
#define PLAYER_B 1

#define WHITE 0
#define BLACK 0xFFFFFF

#define WHITE_SQUARE 0xEDB879
#define BLACK_SQUARE 0x80391E

#define SQUARES 8
#define SQUARE_SIZE 64
#define STARTING_PIXEL_X 250
#define STARTING_PIXEL_Y 100

#define X_INCREMENT 8
#define Y_INCREMENT 16

#define PAWN 0
#define ROOK 1
#define KNIGHT 2
#define BISHOP 3
#define QUEEN 4
#define KING 5


typedef struct {
	uint64_t color;
	uint8_t type;
	uint8_t moved;
} PIECE;

typedef struct {
	PIECE piece;
	uint8_t empty;
	uint64_t backgroundColor;
	uint8_t row;
	uint8_t col;
} SQUARE;

typedef struct {
	SQUARE squares[SQUARES][SQUARES];
} BOARD;

typedef struct {
	uint16_t x;
	uint16_t y;
} POINT;


void newLine(POINT * p, uint16_t x);

void putc(char c, POINT * p);

void print(char * str);

void initBoard();

void drawBoard();

void movePiece(SQUARE * old, SQUARE * new);

uint8_t canMove(uint8_t type, uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol);

uint8_t readMove();

void drawSquare(SQUARE square);

void toStr(uint8_t num, char s[], uint8_t len);

void printTimer(POINT pos, char m[3], char s[3]);

void updateTimer();

#endif