#include <stdio.h>
#include <stdlib.h>
#include "flash_mem_sim.h"

void main(void)
{
	int test_var = 0;

	test_var = flash_read();

	printf("Hello! Test Var = %d \n", test_var);

	system("pause");
}