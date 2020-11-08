/*
 * cell.h
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */

#ifndef CELL_H_
#define CELL_H_

#define CELL_NEIGHBOURS_NUMBER 8

typedef enum
{
	CELL_ALIVE = 0,
	CELL_DEAD,

}CellState_t;

typedef struct Cell
{
	CellState_t state;
	struct Cell **neighbours;

}Cell_t;


Cell_t *cell_create(void);
int cell_set_neighborhood(Cell_t *cell, Cell_t **neighbours);
#endif /* CELL_H_ */
