/*
 * test_main.c
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit.h"
#include "Basic.h"
#include "test_cell.h"

CU_pSuite pSuite = NULL;

int main(void)
{
	puts("Test Target"); /* prints !!!Hello World!!! */

	if(CU_initialize_registry() != CUE_SUCCESS)
	{
		return -1;
	}

	pSuite = CU_add_suite("cell_suite", NULL, NULL);
	if (NULL == pSuite) {
	 CU_cleanup_registry();
	 return CU_get_error();
	}

	CU_add_test(pSuite, "Test Cell create", test_cell_create);
	CU_basic_run_tests();

	CU_cleanup_registry();

	return EXIT_SUCCESS;
}
