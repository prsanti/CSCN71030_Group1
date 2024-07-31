// CSCN71030 - Spring 2024 - Project 2: Connections
// Group 1 - Paul, Iggy, Karl, Alli

#include "tests.h"
#define FILENAME "connectionsData.txt"
#define TEST_HIGHSCORE_FILENAME "highscore_test.txt"


// ALL MODULES

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

void runAllConnectionTests() {
	createConnectionTest();
}

void runAllFileTests() {
	countLinesTest();
	getRandomLineTest();
	loadDataTest();
}

void runAllListTests() {
	createListTest();
}


void runAllGameTests() {
	test_initializeGame();
	test_processCorrectGuess();
	test_processIncorrectGuess();
	test_splitGuessIntoWords();
	test_capitalizeString();
	test_isGuessAConnection();
}

void runAllHighscoreTests() {
	test_save_and_load_highscore();
	test_verify_highscore_display();
}









// CONNECTION MODULE FUNCTION DEFINITIONS

// manual test functions for connection module
bool createConnectionTest(void) {
	printf("REQ_CON_001\n");
	printf("Create Connection struct shall be tested.\n");

	bool expected = true;
	bool result = true;

	char name[MAXWORD] = "testName";
	char wordList[MAXCONNECTIONS][MAXWORD] = { "test1", "test2", "test3", "test4" };

	CONNECTION temp = createConnection(name, wordList);

	if (temp.name == '\0') {
		result = false;
	}

	for (int i = 0; i < MAXCONNECTIONS; i++) {
		if (temp.words[i] == '\0') {
			result = false;
		}
	}

	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		printf("Created CONNECTION: \n");
		printConnection(temp);
		return false;
	}
}










// FILE MODULE FUNCTION DEFINITIONS

// manual tests
// REQ_IO_001
bool countLinesTest(void) {
	printf("REQ_IO_001\n");
	printf("Count total lines from text file data shall be tested. \n");
	int expected = 48;

	FILE* fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		fprintf(stderr, "Test failed: Error opening file\n");
		return false;
	}

	int result = countLines(fp);

	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		return false;
	}
}

// REQ_IO_002
bool getRandomLineTest(void) {
	printf("REQ_IO_002\n");
	printf("Get random line from text file shall be tested.\n");

	// a random num from 0 to 43 will be the return
	char testBuffer[MAXBUFFER] = { '\0' };

	FILE* fp = fopen(FILENAME, "r");

	// print error if cannot open file
	if (fp == NULL) {
		fprintf(stderr, "Test failed: Error opening file\n");
		return false;
	}

	getRandomLine(fp, testBuffer);

	// check if buffer is assigned a correct line:
	if (testBuffer != '\0') {
		printf("Test passed\n");
		printf("Buffer returned: %s\n", testBuffer);
		return true;
	}
	else {
		printf("test failed\n");
		printf("Buffer returned: %s\n", testBuffer);
		return false;
	}
}

// REQ_IO_003
bool loadDataTest(void) {
	printf("REQ_IO_003\n");
	printf("Load data from text file and set data to an array of Connections shall be tested\n");

	bool expected = true;

	CONNECTION* connectionArr[TOTALCONNECTIONS];

	bool result = loadData(FILENAME, connectionArr);

	// manually check if connections are made in the array
	for (int i = 0; i < MAXCONNECTIONS; i++) {
		printConnection(*connectionArr[i]);
		// check if name and wasGuessed marker are valid when initialized
		if (*connectionArr[i]->name == '\0' || connectionArr[i]->wasGuessed == true) {
			result = false;
		}

		// check each connection words if they exist and are valid
		for (int j = 0; j < TOTALCONNECTIONS; j++) {
			if (connectionArr[i]->words[j] == '\0') {
				result = false;
			}
		}
	}

	if (expected == result) {
		printf("Test passed\n");
		return true;
	}
	else {
		printf("Test failed\n");
		return false;
	}
}











// LIST MODULE

// manual test functions for list module
bool createListTest(void) {
	printf("REQ_LIST_001\n");
	printf("Create a linked list by creating nodes and linking them together to make a linked list.\n");

	NODE* head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL) {
		fprintf(stderr, "Error allocating memory for head node\n");
		exit(EXIT_FAILURE);
	}

	// Create pointer array of connections
	CONNECTION* connectionArr[TOTALCONNECTIONS];

	// Read file data and load data into connection array
	if (!loadData(FILENAME, connectionArr)) {
		// Close program with error
		exit(EXIT_FAILURE);
	}

	// Create linked list
	createList(head, connectionArr);

	// check each node
	traverse(head);

	// Free the linked list after the game ends
	deleteNode(head);

	printf("test passed\n");
}












// GAME MODULE FUNCTION DEFINITIONS

// Mock data for testing
NODE sampleNode1 = { .c = {.words = {"red", "blue", "green", "yellow"}, .wasGuessed = false }, .next = NULL };
NODE sampleNode2 = { .c = {.words = {"apple", "banana", "cherry", "date"}, .wasGuessed = false }, .next = NULL };

// Test case: REQ_GM_001
void test_initializeGame() {
	GAME_STATE gameState;
	HIGHSCORE highscore;
	sampleNode1.next = &sampleNode2;  // Link sampleNode1 to sampleNode2

	initializeGame(&gameState, &sampleNode1, &highscore, "samplePlayer");  // Initialize the game state with the sample nodes and highscore

	// Check if the game state is initialized correctly
	if (strcmp(gameState.player.name, "samplePlayer") == 0 &&
		gameState.player.score == 0 &&
		gameState.lives == MAX_LIVES &&
		gameState.isGameOver == false) {
		printf("REQ_GM_001: Game state initializes correctly - PASSED\n");  // Output PASSED if all conditions are met
	}
	else {
		printf("REQ_GM_001: Game state initializes correctly - FAILED\n");  // Output FAILED if any condition is not met
	}
}

// Test case: REQ_GM_002
void test_processCorrectGuess() {
	GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
	gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1
	gameState.lives = MAX_LIVES;  // Initialize the lives to the maximum allowed

	char* correctGuess[MAX_WORDS_PER_GUESS] = { "red", "blue", "green", "yellow" };  // Define a correct guess
	GUESS_RESULT result = isGuessAConnection(&gameState, correctGuess);  // Check if the guess is a correct connection

	if (result.isConnection == true && result.matchedConnection == &sampleNode1) {
		handleCorrectGuess(&gameState, result);  // Handle the correct guess
		if (gameState.lives == MAX_LIVES && sampleNode1.c.wasGuessed == true) {
			printf("REQ_GM_002: Game processes a correct guess correctly - PASSED\n");  // Output PASSED if conditions are met
		}
		else {
			printf("REQ_GM_002: Game processes a correct guess correctly - FAILED\n");  // Output FAILED if conditions are not met
		}
	}
	else {
		printf("REQ_GM_002: Game processes a correct guess correctly - FAILED\n");  // Output FAILED if the guess is not recognized as correct
	}
}

// Test case: REQ_GM_003
void test_processIncorrectGuess() {
	GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
	gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1
	gameState.lives = MAX_LIVES;  // Initialize the lives to the maximum allowed

	char* incorrectGuess[MAX_WORDS_PER_GUESS] = { "purple", "orange", "black", "white" };  // Define an incorrect guess
	GUESS_RESULT result = isGuessAConnection(&gameState, incorrectGuess);  // Check if the guess is an incorrect connection

	if (result.isConnection == false) {
		handleIncorrectGuess(&gameState);  // Handle the incorrect guess
		if (gameState.lives == MAX_LIVES - 1) {
			printf("REQ_GM_003: Game processes an incorrect guess correctly - PASSED\n");  // Output PASSED if lives decrement as expected
		}
		else {
			printf("REQ_GM_003: Game processes an incorrect guess correctly - FAILED\n");  // Output FAILED if lives do not decrement correctly
		}
	}
	else {
		printf("REQ_GM_003: Game processes an incorrect guess correctly - FAILED\n");  // Output FAILED if the guess is incorrectly recognized as correct
	}
}

// Test case: REQ_GM_004
void test_splitGuessIntoWords() {
	char guess[MAXBUFFER] = "red blue green yellow";  // Sample input string
	char* splitGuess[MAX_WORDS_PER_GUESS];  // Array to store the split words
	int wordCount = splitGuessIntoWords(guess, splitGuess, MAX_WORDS_PER_GUESS);  // Split the input string into words

	// Check if the words were split correctly
	if (wordCount == 4 &&
		strcmp(splitGuess[0], "red") == 0 &&
		strcmp(splitGuess[1], "blue") == 0 &&
		strcmp(splitGuess[2], "green") == 0 &&
		strcmp(splitGuess[3], "yellow") == 0) {
		printf("REQ_GM_004: User input handling and splitting into words - PASSED\n");  // Output PASSED if all words are correct
	}
	else {
		printf("REQ_GM_004: User input handling and splitting into words - FAILED\n");  // Output FAILED if any word is incorrect
	}
}

// Test case: REQ_GM_005
void test_capitalizeString() {
	char testString[MAXBUFFER] = "red blue green yellow";  // Sample input string
	capitalizeString(testString);  // Capitalize the string

	if (strcmp(testString, "RED BLUE GREEN YELLOW") == 0) {
		printf("REQ_GM_005: String capitalization function - PASSED\n");  // Output PASSED if capitalization is correct
	}
	else {
		printf("REQ_GM_005: String capitalization function - FAILED\n");  // Output FAILED if capitalization is incorrect
	}
}

// Test case: REQ_GM_006
void test_isGuessAConnection() {
	GAME_STATE gameState;       // Declare a GAME_STATE variable to store the game state
	gameState.head = &sampleNode1;  // Set the head of the linked list to sampleNode1

	char* correctGuess[MAX_WORDS_PER_GUESS] = { "red", "blue", "green", "yellow" };  // Define a correct guess
	GUESS_RESULT correctResult = isGuessAConnection(&gameState, correctGuess);  // Check if the guess is correct

	char* incorrectGuess[MAX_WORDS_PER_GUESS] = { "purple", "orange", "pink", "white" };  // Define an incorrect guess
	GUESS_RESULT incorrectResult = isGuessAConnection(&gameState, incorrectGuess);  // Check if the guess is incorrect

	if (correctResult.isConnection == true && incorrectResult.isConnection == false) {
		printf("REQ_GM_006: Guess validation against connections - PASSED\n");  // Output PASSED if correct guess recognized and incorrect guess not recognized
	}
	else {
		printf("REQ_GM_006: Guess validation against connections - FAILED\n");  // Output FAILED if any condition is not met
	}
}












// HIGHSCORE MODULE FUNCTION DEFINITIONS

// Test function for saving and loading high scores (REQ_HSM_001)
void test_save_and_load_highscore() {
	HIGHSCORE scores;
	initializeHighscores(&scores);

	addScore(&scores, "Alice", 1);
	addScore(&scores, "Bob", 2);
	addScore(&scores, "Charlie", 3);

	saveHighscores(scores, TEST_HIGHSCORE_FILENAME);

	HIGHSCORE loadedScores;
	initializeHighscores(&loadedScores);
	loadHighscores(&loadedScores, TEST_HIGHSCORE_FILENAME);

	if (loadedScores.numscores == 3 &&
		strcmp(loadedScores.scores[0].name, "Alice") == 0 && loadedScores.scores[0].score == 1 &&
		strcmp(loadedScores.scores[1].name, "Bob") == 0 && loadedScores.scores[1].score == 2 &&
		strcmp(loadedScores.scores[2].name, "Charlie") == 0 && loadedScores.scores[2].score == 3) {
		printf("Test REQ_HSM_001: Pass\n");
	}
	else {
		printf("Test REQ_HSM_001: Fail\n");
		printf("Expected: 3 scores, (Alice, 1), (Bob, 2), (Charlie, 3)\n");
		printf("Actual: %d scores, (%s, %d), (%s, %d), (%s, %d)\n",
			loadedScores.numscores,
			loadedScores.scores[0].name, loadedScores.scores[0].score,
			loadedScores.scores[1].name, loadedScores.scores[1].score,
			loadedScores.scores[2].name, loadedScores.scores[2].score);
	}
}

// Test function for verifying the display of high scores (REQ_HSM_002)
void test_verify_highscore_display() {
	HIGHSCORE scores;
	initializeHighscores(&scores);

	// Add some test scores
	addScore(&scores, "Alice", 1);
	addScore(&scores, "Bob", 2);
	addScore(&scores, "Charlie", 3);

	// Expected output format for manual verification
	printf("Expected Output:\n");
	printf("Alice - 1\n");
	printf("Bob - 2\n");
	printf("Charlie - 3\n");

	// Call the function to display high scores
	printf("Actual Output:\n");
	printHighscores(scores);
}