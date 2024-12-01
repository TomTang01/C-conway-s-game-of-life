#include "sim.h"
#include "board.h"

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t mod(int x, size_t N) { return (x + x / N * N) % N; }

/**
 * process one row of the board
 */
static void do_row(Cell *dest, Cell *src, size_t row, size_t rows, size_t cols) {
	size_t neighbors = 0;
	Cell *current;
	for(size_t i = 0; i < cols; i++) {
		current = src + cols * row + i;
		neighbors += *(src + cols * row + mod(i-1, cols)); // left
		neighbors += *(src + cols * row + mod(i+1, cols)); // right
		neighbors += *(src + cols * mod(row-1, rows) + i); // top
		neighbors += *(src + cols * mod(row+1, rows) + i); // bottom
		neighbors += *(src + cols * mod(row-1, rows) + mod(i-1, cols)); // top left
		neighbors += *(src + cols * mod(row-1, rows) + mod(i+1, cols)); // top right
		neighbors += *(src + cols * mod(row+1, rows) + mod(i+1, cols)); // bottom right
		neighbors += *(src + cols * mod(row+1, rows) + mod(i-1, cols)); // bottom left
		
		if(*current == 1) {
			if(neighbors <= 1 || neighbors >= 4) {
				*(dest + cols * row + i) = 0;
			} else {
				*(dest + cols * row + i) = 1;
			}
		} else {
			if(neighbors == 3 || neighbors == 6) {
				*(dest + cols * row + i) = 1;
			} else {
				*(dest + cols * row + i) = 0;
			}
		}
		neighbors = 0;
	}
}

/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void sim_loop(Board *board, unsigned int steps) {
	for(unsigned int j=0; j<steps; j++) {
		for(unsigned int i=0; i<(*board).nrows; i++) {
			do_row((*board).next_buffer, (*board).buffer, i, (*board).nrows, (*board).ncols);
		}
		swap_buffers(board);
		(*board).gen++;
	}
}
