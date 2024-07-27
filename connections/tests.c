// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "tests.h"

// run all tests from all modules
void runTests(void) {
	printf("\nCONNECTION TESTS\n");
	runAllConnectionTests();

	printf("\nFILE TESTS\n");
	runAllFileTests();

	printf("\nGAME TESTS\n");
	runAllGameTests();

	printf("\nHIGHSCORE TESTS\n");
	runAllHighscoreTests();

	printf("\nLIST TESTS\n");
	runAllListTests();
}