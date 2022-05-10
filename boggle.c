#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint8_t debug = 0;
#define DBG(...) (debug ? printf(__VA_ARGS__) : 0)

/*
Letters came from boardgamegeek.com/thread/300883/letter-distribution
every 6 letters is a new die
*/
char letters[151] = "aaafrsaaeeeeaafirsadennnaeeeem"
				"aeegmuaegmnnafirsybjkqxzccenst"
				"ceiiltceilptceipstddhnotdhhlor"
				"dhlnordhlnoreiiittemotttensssu"
				"fiprsygorrvwiprrrynootuwooottu";

/*
Dice are represented in an implicit circularly linked list.  Each index
into the array refers to a single die, and correlates into the letters
array above.  The value stored at each index refers to the next die in
the list.  This allows us to generate a permutation of all the dice,
without repeating.

Note that this could have been done with a heap, but this seemed simpler.
*/
uint8_t head = 0;
uint8_t dice[25] = {1, 2, 3, 4, 5,
					6, 7, 8, 9, 10,
					11, 12, 13, 14, 15,
					16, 17, 18, 19, 20,
					21, 22, 23, 24, 0};

/*
randomly pick one of the 25 dice, remove it from play, roll it, and
return the corresponding character.
*/
char roll() {
	uint8_t i = rand() % 25;
	uint8_t j = head;

	while(i --> 0) {
		j = dice[j];
	}

	i = dice[j];
	dice[j] = dice[i];

	if(i == head) {
		head = dice[i];
	}

	j = rand() % 6;
	DBG("%d %d %c\n", i, j, letters[i*5+j]);
	return letters[i*5+j];
}

/*
board contains the template for outputting the board.  It has room for
a 5 single characters per line, separated by spaces.  Note that puts
appends a newline, thus no newline after the string.
*/
char board[50] = "         \n"
				"         \n"
				"         \n"
				"         \n"
				"         ";

int main(int argc, char **argv) {
	if(argc > 1 && argv[1][1] == 'd') debug = 1;
	uint8_t i = 5;
	uint8_t j;
	srand(time(0));

	while(i-->0) {
		j = 5;
		while(j-->0) {
			board[i*10+j*2] = roll();
		}
	}

	puts(board);
}
