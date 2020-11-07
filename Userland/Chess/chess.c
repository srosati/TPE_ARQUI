#include "../lib.h"
#include "chess.h"
#include <stdint.h>

static BOARD board;

static uint64_t pawn[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x180000000, 0x1FF8000000,
	0xFFFF000000, 0x1FFFF800000, 0x1FFFF800000, 0x3FFFFC00000, 0x1FFFF800000, 0xFFFF000000, 0xFFFF000000, 0x1FF8000000,
	0x7E0000000, 0xFF0000000, 0x1FF8000000, 0x3FFC000000, 0x7FFE000000, 0x7FFE000000, 0xFFFF000000, 0xFFFF000000, 0x1FFFF800000,
	0x3FFFFC00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint64_t rook[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xE739CE00000, 0xE739CE00000,
	0xE739CE00000, 0xFFFFFE00000, 0xFFFFFE00000, 0xFFFFFE00000, 0xFFFFFE00000, 0xFFFFFE00000, 0xFFFFFE00000, 0x3FFC000000, 
	0xFF0000000, 0xFF0000000, 0x1FF8000000, 0x3FFC000000, 0x7FFE000000, 0x7FFE000000, 0xFFFF000000, 0xFFFF000000, 0x1FFFF800000,
	0x3FFFFC00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint64_t knight[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC00000000, 0xE00000000,
	0x3FE0000000, 0xFFF0000000, 0x3FFF8000000, 0xFFFFC000000, 0x3FFFFE000000, 0xFFFFFF000000, 0x3FFFFFF800000, 0x7FFFFFFC00000,
	0x7FF9FFFE00000, 0x1FF0FFFF00000,0xF81FFFC00000, 0x1FFFC00000, 0x3FFF800000, 0x7FFF000000, 0xFFFF000000, 0xFFFF000000,
	0xFFFF000000, 0xFFFF000000,	0x1FFFF800000, 0x3FFFFC00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 
	0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint64_t bishop[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x180000000, 0x3C0000000, 0x7E0000000, 
	0xFF0000000, 0x1FF8000000, 0x7FFE000000, 0x1FFFF800000, 0x3FFFFC00000, 0x1FFFF800000, 0x7FFE000000, 0x1FF8000000,
	0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x7FFE000000, 0xFFFF000000, 0xFFFF000000,
	0xFFFF000000, 0xFFFF000000, 0x1FFFF800000, 0x3FFFFC00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000,
	0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint64_t queen[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3C0000000, 0x8007E0010000, 0xC007E0030000,
	0x7003C00E0000, 0x3FFFFFFC0000, 0x1FFFFFF80000, 0xFFFFFF00000, 0x7FFFFE00000, 0xFFFF000000, 0x7FFF000000, 0xFFFF800000,
	0x1FFFFC00000, 0xFFFF800000, 0x7FFE000000, 0x3FFC000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 
	0x1FF8000000, 0x7FFE000000, 0xFFFF000000, 0xFFFF000000, 0xFFFF000000, 0xFFFF000000, 0x1FFFF800000, 0x3FFFFC00000, 
	0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint64_t king[] = {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3C0000000, 0x7E0000000, 0xFF0000000, 0x3C0000000,
	0x1FFFF800000, 0x1FFFF800000, 0x1FFFF800000, 0xFF0000000, 0xFF0000000, 0xFF0000000, 0x7FFE000000, 0x1FFFF800000,
	0x1FFFF800000, 0xFFFC000000, 0x3FFC000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000, 0x1FF8000000,
	0x7FFE000000, 0xFFFF000000, 0xFFFF000000, 0xFFFF000000, 0xFFFF000000, 0x1FFFF800000, 0x3FFFFC00000, 0x7FFFFE00000,
	0x7FFFFE00000, 0x7FFFFE00000, 0x7FFFFE00000, 0xFFFFFF00000, 0x1FFFFFF80000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

static uint32_t timers[] = {0, 0};

static uint8_t turn = PLAYER_W;

static POINT textWriters[2] = {{110, 120}, {862, 120}};

static POINT timer1 = {110, 100};

static POINT timer2 = {862, 100};

static char won = -1;

int main() {
	printTimer(timer1, "00", "00");
	printTimer(timer2, "00", "00");
	initBoard();
	drawBoard();
	uint8_t interval = setInterval(18, &updateTimer);
	while(1) {
		if (won != -1) {
			putChar('0'+interval, 0, 0);
			stopInterval(interval);
			return 0;
		}

		uint8_t valid = readMove();

		if (valid)
			turn = (turn == PLAYER_W)? PLAYER_B: PLAYER_W;
		else
			print("I");
	}
	return 0;
}

void newLine(POINT * p, uint16_t x) {
	p->x = x;
	p->y += Y_INCREMENT;
}

void putc(char c, POINT * p) {
	putChar(c, p->x, p->y);
	p->x += X_INCREMENT;
}

void print(char * str) {
	POINT * p = &textWriters[turn];
	uint16_t aux = p->x;
	while (*str != 0) {
		putChar(*str, p->x, p->y);
		p->x += X_INCREMENT;
		str++;
	}
	newLine(p, aux);
}

void initBoard() {
	uint64_t backgroundColor;
	for (int i = 0; i < SQUARES; ++i) {
		backgroundColor = (backgroundColor == WHITE_SQUARE)?BLACK_SQUARE:WHITE_SQUARE;
		for (int j = 0; j < SQUARES; ++j) {
			SQUARE square;
			square.empty = 0;
			square.row = i;
			square.col = j;
			if (i == 1 || i == SQUARES-2) {
				PIECE piece;
				piece.color = BLACK;
				piece.moved = 0;
				if (i == 1)
					piece.color = WHITE;

				piece.type = PAWN;
				square.piece = piece;
			} else if (i == 0 || i == SQUARES-1) {
				PIECE piece;
				piece.color = BLACK;
				piece.moved = 0;
				if (i == 0)
					piece.color = WHITE;
				
				if (j == 0 || j == SQUARES-1) {
					piece.type = ROOK;
				} else if (j == 1 || j == SQUARES-2) {
					piece.type = KNIGHT;
				} else if (j == 2 || j == SQUARES-3) {
					piece.type = BISHOP;
				} else if (j == 3) {
					piece.type = KING;
				} else {
					piece.type = QUEEN;
				}
				square.piece = piece;
			} else {
				square.empty = 1;
			}
			square.backgroundColor = backgroundColor;
			board.squares[i][j] = square;
			backgroundColor = (backgroundColor == WHITE_SQUARE)?BLACK_SQUARE:WHITE_SQUARE;
		}
	}
}

void drawBoard() {
	POINT numPos = {STARTING_PIXEL_X -  2 * X_INCREMENT, STARTING_PIXEL_Y + (SQUARE_SIZE-X_INCREMENT)/2};
	POINT charPos = {STARTING_PIXEL_X + (SQUARE_SIZE-Y_INCREMENT)/2, STARTING_PIXEL_Y - Y_INCREMENT};

	uint8_t num = SQUARES;
	char ch = 'a';
	for (int i = 0; i < SQUARES; ++i) {
		for (int j = 0; j < SQUARES; ++j) {
			SQUARE square = board.squares[i][j];
			drawSquare(square);
		}
		putChar(ch, charPos.x, charPos.y);
		putChar('0'+num, numPos.x, numPos.y);
		ch++;
		num--;
		numPos.y += SQUARE_SIZE;
		charPos.x += SQUARE_SIZE;
	}
}

void movePiece(SQUARE * old, SQUARE * new) {
	if (!new->empty && new->piece.type == KING)
		won = turn;

	old->empty = 1;

	new->piece = old->piece;
	new->piece.moved = 1;
	new->empty = 0;

	drawSquare(*old);
	drawSquare(*new);
}

uint8_t canMove(uint8_t type, uint8_t fromRow, uint8_t fromCol, uint8_t toRow, uint8_t toCol) {
	if (type == ROOK) {
		int incX = 1;
		int incY = 1;

		if (fromRow == toRow) {
			incX = 0;
			if (fromCol > toCol)
				incY = -1;
		} else if (fromCol == toCol) {
			incY = 0;
			if (fromRow > toRow)
				incX = -1;
		} else {
			return 0;
		}

		int i = fromRow + incX;
		int j = fromCol + incY;

		while (i != toRow || j != toCol) {
			if (!board.squares[i][j].empty)
				return 0;

			i += incX;
			j += incY;
		}

		return 1;
	} else if (type == BISHOP) {
		int dx = toRow - fromRow;
		if (dx < 0) dx *= -1;
		int dy = toCol - fromCol;
		if (dy < 0) dy *= -1;

		if (dx != dy)
			return 0;

		int incX = 1;
		int incY = 1;

		if (fromRow > toRow)
			incX = -1;

		if (fromCol > toCol)
			incY = -1;

		int i = fromRow + incX;
		int j = fromCol + incY;

		while (i != toRow) {
			if (!board.squares[i][j].empty)
				return 0;

			i += incX;
			j += incY;
		}

		return 1;
	} else if (type == PAWN) {
		if ((fromCol == toCol) && ((turn == PLAYER_W && fromRow == 1) || (turn == PLAYER_B && fromRow == (SQUARES-2)))) {
			int inc = (turn==PLAYER_W)?1:-1;
			if (toRow == (fromRow + 2 * inc) && board.squares[fromRow + inc][fromCol].empty)
				return 1;
		}
		uint8_t auxRow = (turn == PLAYER_W)?fromRow+1:fromRow-1;

		if (toRow != auxRow) return 0;

		return (fromCol == toCol && board.squares[auxRow][toCol].empty) 
			|| (!board.squares[auxRow][toCol].empty && (((fromCol+1) == toCol) || (fromCol-1) == toCol));
	} else if (type == KING) {
		int dx = toRow - fromRow;
		if (dx < 0) dx *= -1;
		int dy = toCol - fromCol;
		if (dy < 0) dy *= -1;

		return dx <= 1 && dy <= 1;
	} else if (type == KNIGHT) {
		int dx = toRow - fromRow;
		if (dx < 0) dx *= -1;
		int dy = toCol - fromCol;
		if (dy < 0) dy *= -1;

		return (dx == 1 && dy == 2) || (dx == 2 && dy == 1); 
	} else if (type == QUEEN) {
		return canMove(ROOK, fromRow, fromCol, toRow, toCol) || canMove(BISHOP, fromRow, fromCol, toRow, toCol);
	}

	return 0;
}

uint8_t readMove() {
	POINT * p = &textWriters[turn];
	uint16_t startX = p->x;

	char fromRow = -1;
	char fromCol = -1;

	uint8_t toRow;
	uint8_t toCol;

	char c = getChar();
	putc(c, p);
	if (c == '0') {
		c = getChar();
		putc(c, p);
		if (c == '-') {
			c = getChar();
			putc(c, p);
			if (c == '0') {
				c = getChar();
				uint8_t kingCol = 3;
				uint8_t r = (turn == PLAYER_W)?0:SQUARES-1;

				SQUARE * kingSq = &(board.squares[r][kingCol]);
				SQUARE * rookSq;
				SQUARE * newKingSq;
				SQUARE * newRookSq;

				if (c == '\n') {
					//enroque corto
					uint8_t rookCol = 0;
					rookSq = &(board.squares[r][rookCol]);

					newRookSq = &(board.squares[r][rookCol+2]);
					newKingSq = &(board.squares[r][rookCol+1]);
				} else if (c == '-') {
					putc(c, p);
					c = getChar();
					putc(c, p);
					if (c == '0') {
						//enroque largo
						uint8_t rookCol = SQUARES - 1;
						rookSq = &(board.squares[r][rookCol]);

						newRookSq = &(board.squares[r][kingCol+1]);
						newKingSq = &(board.squares[r][kingCol+2]);
						SQUARE aux = board.squares[r][kingCol+3];
						if (!aux.empty) {
							newLine(p, startX);
							return 0;
						}
					}

					if (kingSq->empty || kingSq->piece.moved || rookSq->empty || rookSq->piece.moved || !newRookSq->empty || !newKingSq->empty) {
						putc('c', p);
						newLine(p, startX);
						return 0;
					}

					movePiece(rookSq, newRookSq);
					movePiece(kingSq, newKingSq);

					newLine(p, startX);
					return 1;
				}
			}
		} 

		newLine(p, startX);
		return 0;
	}

	uint8_t pieceType = PAWN;
	uint64_t pieceColor = (turn == PLAYER_W)?WHITE:BLACK;

	if (c == 'K')
		pieceType = KING;
	else if (c == 'Q')
		pieceType = QUEEN;
	else if (c == 'R')
		pieceType = ROOK;
	else if (c == 'B')
		pieceType = BISHOP;
	else if (c == 'N')
		pieceType = KNIGHT;

	if (pieceType != PAWN) {
		c = getChar();
		putc(c, p);
	}

	if (c >= '1' && c <= '8'){
		fromRow = '8' - c;
		c = getChar();
		putc(c, p);
	}

	if (c < 'a' || c > 'h') {
		newLine(p, startX);
		return 0;
	}

	toCol = c - 'a';

	c = getChar();
	putc(c, p);

	if (c >= 'a' && c <= 'h') {
		if (fromRow == -1) {
			uint8_t aux = c - 'a';
			fromCol = toCol;
			toCol = aux;
			c = getChar();
			putc(c, p);
		} else {
			newLine(p, startX);
			return 0;
		}
	}

	if (c < '1' || c > '8'){
		newLine(p, startX);
		return 0;
	}

	toRow = '8' - c;

	SQUARE * destination = &(board.squares[toRow][toCol]);
	if (!destination->empty && destination->piece.color == pieceColor) {
		newLine(p, startX);
		return 0;
	}

	SQUARE * origin;

	uint8_t found = 0;

	uint8_t startRowCount = 0;
	uint8_t endRowCount = SQUARES;

	uint8_t startColCount = 0;
	uint8_t endColCount = SQUARES;

	if (fromRow != -1) { // Specified starting row
		startRowCount = fromRow;
		endRowCount = fromRow+1;
	}

	if (fromCol != -1) { // Specified starting column
		startColCount = fromCol;
		endColCount = fromCol+1;
	}

	for (int i = startRowCount; i < endRowCount && !found; ++i) {
		for (int j = startColCount; j < endColCount; ++j) {
			SQUARE * sq = &(board.squares[i][j]);
			if (sq->empty) continue;

			PIECE piece = sq->piece;
			if (piece.type != pieceType || piece.color != pieceColor) continue;

			if (!canMove(pieceType, i, j, toRow, toCol)) continue;

			found = 1;
			origin = sq;
			break;
		}
	}

	if (!found) {
		newLine(p, startX);
		return 0;
	}


	movePiece(origin, destination);

	newLine(p, startX);

	return 1;
}

void drawSquare(SQUARE square) {
	uint16_t pos_x = STARTING_PIXEL_X + square.col * SQUARE_SIZE;
	uint16_t pos_y = STARTING_PIXEL_Y + square.row * SQUARE_SIZE;
	uint64_t toDraw[SQUARE_SIZE] = {0};

	if (!square.empty) {
		uint8_t type = square.piece.type;
		if (type == PAWN) {
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = pawn[i];
		} else if (type == ROOK){
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = rook[i];
		} else if (type == KNIGHT){
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = knight[i];
		} else if (type == BISHOP){
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = bishop[i];
		} else if (type == QUEEN){
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = queen[i];
		} else if (type == KING){
			for (int i = 0; i < SQUARE_SIZE; ++i)
				toDraw[i] = king[i];
		}
	}

	for (int i = 0; i < SQUARE_SIZE; ++i) {
		for (int j = 0; j < SQUARE_SIZE; ++j) {
			uint64_t color = square.backgroundColor;

			uint8_t bit = (toDraw[j] >> (SQUARE_SIZE-1-i)) & 1;
			if (bit)
				color = square.piece.color;
			
			drawPixel(pos_x + i, pos_y + j, color);
		}
	}
}

void toStr(uint8_t num, char s[], uint8_t len) {
	while (num && len > 0) {
		s[len-1] = '0'+(num%10);
		num/=10;
		len--;
	}
}

void printTimer(POINT pos, char m[3], char s[3]) {
	putc(m[0], &pos);
	putc(m[1], &pos);
	putc(':', &pos);
	putc(s[0], &pos);
	putc(s[1], &pos);
}

void updateTimer() {
	timers[turn]++;
	int dif = timers[0] - timers[1];
	if (dif < 0) dif *= -1;

	if (dif > 60)
		won = turn;

	POINT p = (turn == PLAYER_W)?timer1:timer2;
	uint8_t seconds = timers[turn] % 60;
	uint8_t minutes = timers[turn] / 60;
	char s[3] = {'0', '0', 0};
	char m[3] = {'0', '0', 0};
	toStr(seconds, s, 2);
	toStr(minutes, m, 2);
	printTimer(p, m, s);
}
