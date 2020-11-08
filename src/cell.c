/*
 * cell.c
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */

#include "cell.h"
#include <stddef.h>
#include <stdlib.h>

Cell_t *cell_create(void)
{
	Cell_t *cell = NULL;

	cell = malloc(sizeof(Cell_t));
	cell->state = CELL_DEAD;

	return cell;
}

int cell_set_neighborhood(Cell_t *cell, Cell_t **neighbours)
{
	int status = -1;

	if ((cell != NULL) && (neighbours != NULL)) {
		cell->neighbours = neighbours;
		status = 0;
	}
	return status;
}

int cell_process_one_turn(Cell_t *cell)
{
	int status = -1;
	int nb_alive_cells = 0;
	int i = 0;

	if (cell != NULL) {
		for (i = 0; i < CELL_NEIGHBOURS_NUMBER; i++) {
			if (cell->neighbours[i]->state == CELL_ALIVE) {
				nb_alive_cells++;
			}
		}

		if (cell->state == CELL_ALIVE) {
			if (nb_alive_cells < 2) {
				cell->state = CELL_DEAD;
			} else if (nb_alive_cells > 3) {
				cell->state = CELL_DEAD;
			}
		} else if (cell->state == CELL_DEAD) {
			if (nb_alive_cells == 3) {
				cell->state = CELL_ALIVE;
			}
		}

		status = 0;
	}
	return status;
}
