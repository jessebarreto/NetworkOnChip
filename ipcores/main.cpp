#include "systemc.h"
#include "top.h"

// Main test
int sc_main (int argc, char* argv[])
{
	top t("t");
	printf("\n\nStarting simulation...\n\n");
	sc_start();
	printf("\n\nSimulation stopped!\n\n");

	return 0;
}
