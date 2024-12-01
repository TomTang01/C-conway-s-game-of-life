/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "board.h"
#include "cse30life.h"

/**
 * create a new board - STUDENT
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc buf1 and buf2
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, setCell in the next buffer
 * - swap the buffers
 * - close the file
 * - return the boards pointer
 */
Board *create_board(const char *filename) {
	FILE *fp;

	Board *board = malloc(sizeof(Board));

	if(board == NULL) {
		return NULL;
	}

	if((fp = fopen(filename, "r")) == NULL) {
		return NULL;
	}

	int num1;
	int num2;

	fscanf(fp, "%d", &num1);
	(*board).nrows = num1;
	fscanf(fp, "%d", &num1);
	(*board).ncols = num1;

	(*board).buf1 = malloc((*board).nrows * (*board).ncols * sizeof(Cell));
	(*board).buf2 = malloc((*board).nrows * (*board).ncols * sizeof(Cell));

	if((*board).buf1 == NULL || (*board).buf2 == NULL) {
		return NULL;
	}

	(*board).buffer = (*board).buf1;
	(*board).next_buffer = (*board).buf2;

	clear_board(board);

	int index_to_change;
	while(fscanf(fp, "%d %d", &num1, &num2) > 0) {
		index_to_change = get_index((*board).ncols, num1, num2);
		if(num1 < 0 || num2 < 0 || num1 >= (int)((*board).nrows) || num2 >= (int)((*board).ncols)) {
			fprintf(stderr, "Invalid index %d %d\n", num1, num2);
			return NULL;
		}
		*((*board).next_buffer + index_to_change) = 1;
	}

	(*board).gen = 0;

	swap_buffers(board);

	if(fclose(fp) == EOF) {
		return NULL;
	}
	return board;
}

/**
 * delete a board
 *
 * note: this is a deep delete - STUDENT
 * the pointer to the boards structure should be set to NULL
 * after the memory is freed.
 */
void delete_board(Board **bpp) {
	free ((**bpp).buffer);
	free ((**bpp).next_buffer);
	free (*bpp);
	*bpp = NULL;
}

/**
 * set all the Cells to 0 - STUDENT
 */
void clear_board(Board *board) {
	for(int i=0; i<(int)((*board).nrows * (*board).ncols); i++) {
		*((*board).buffer + i) = 0;
		*((*board).next_buffer + i) = 0;
	}
}

/**
 * swap the current and next buffers
 */
void swap_buffers(Board *board) {
	Cell *temp;
       	temp = (*board).buffer;
	(*board).buffer = (*board).next_buffer;
  	(*board).next_buffer = temp;	
}

/**
 * get a cell index
 */
size_t get_index(size_t ncols, size_t row, size_t col) {
	return(row * ncols + col);
}
