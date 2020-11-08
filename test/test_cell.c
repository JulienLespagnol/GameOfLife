/*
 * test_cell.c
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */
#include "CUnit.h"
#include "cell.h"
#include <stddef.h>

void test_cell_create(void)
{
	Cell_t *cell = NULL;
	Cell_t *neighborhood[CELL_NEIGHBOURS_NUMBER];

	cell = cell_create();
	CU_ASSERT_NOT_EQUAL(NULL, cell);

	for (int i = 0; i < CELL_NEIGHBOURS_NUMBER; i++) {
		neighborhood[i] = cell_create();
		CU_ASSERT_NOT_EQUAL(NULL, neighborhood[i]);
	}

	CU_ASSERT_EQUAL(CELL_DEAD, cell->state);

	CU_ASSERT_EQUAL(-1, cell_set_neighborhood(NULL, NULL));
	CU_ASSERT_EQUAL(-1, cell_set_neighborhood(cell, NULL));
	CU_ASSERT_EQUAL(-1, cell_set_neighborhood(NULL, neighborhood));
	CU_ASSERT_EQUAL(0, cell_set_neighborhood(cell, neighborhood));
	CU_ASSERT_EQUAL(-1, cell_process_one_turn(NULL));

	/** Test all dead */
	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_DEAD, cell->state);

	/* - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */
	neighborhood[0]->state = CELL_ALIVE;
	neighborhood[1]->state = CELL_ALIVE;
	neighborhood[2]->state = CELL_ALIVE;
	neighborhood[3]->state = CELL_DEAD;
	neighborhood[4]->state = CELL_DEAD;
	neighborhood[5]->state = CELL_DEAD;
	neighborhood[6]->state = CELL_DEAD;
	neighborhood[7]->state = CELL_DEAD;

	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_ALIVE, cell->state);

	/* Any live cell with fewer than two live neighbours dies, as if by underpopulation. */
	cell->state = CELL_ALIVE;
	neighborhood[0]->state = CELL_ALIVE;
	neighborhood[1]->state = CELL_DEAD;
	neighborhood[2]->state = CELL_DEAD;
	neighborhood[3]->state = CELL_DEAD;
	neighborhood[4]->state = CELL_DEAD;
	neighborhood[5]->state = CELL_DEAD;
	neighborhood[6]->state = CELL_DEAD;
	neighborhood[7]->state = CELL_DEAD;

	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_DEAD, cell->state);

	/* Any live cell with two or three live neighbours lives on to the next generation. */
	cell->state = CELL_ALIVE;
	neighborhood[0]->state = CELL_ALIVE;
	neighborhood[1]->state = CELL_ALIVE;
	neighborhood[2]->state = CELL_DEAD;
	neighborhood[3]->state = CELL_DEAD;
	neighborhood[4]->state = CELL_DEAD;
	neighborhood[5]->state = CELL_DEAD;
	neighborhood[6]->state = CELL_DEAD;
	neighborhood[7]->state = CELL_DEAD;

	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_ALIVE, cell->state);

	cell->state = CELL_ALIVE;
	neighborhood[0]->state = CELL_ALIVE;
	neighborhood[1]->state = CELL_ALIVE;
	neighborhood[2]->state = CELL_ALIVE;
	neighborhood[3]->state = CELL_DEAD;
	neighborhood[4]->state = CELL_DEAD;
	neighborhood[5]->state = CELL_DEAD;
	neighborhood[6]->state = CELL_DEAD;
	neighborhood[7]->state = CELL_DEAD;

	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_ALIVE, cell->state);

	/* Any live cell with more than three live neighbours dies, as if by overpopulation. */
	cell->state = CELL_ALIVE;
	neighborhood[0]->state = CELL_ALIVE;
	neighborhood[1]->state = CELL_ALIVE;
	neighborhood[2]->state = CELL_ALIVE;
	neighborhood[3]->state = CELL_ALIVE;
	neighborhood[4]->state = CELL_DEAD;
	neighborhood[5]->state = CELL_DEAD;
	neighborhood[6]->state = CELL_DEAD;
	neighborhood[7]->state = CELL_DEAD;

	CU_ASSERT_EQUAL(0, cell_process_one_turn(cell));
	CU_ASSERT_EQUAL(CELL_DEAD, cell->state);
}
