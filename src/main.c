#include "../include/utils.h"
#include "../include/solver.h"
#include <stdlib.h>

#define kQuadgramsFile "data/quadgrams.txt"

int main(int argc, char* argv[]) {
	printf("ReverSub Cipher Solver\n");
	
	const char* input_file = (argc > 1) ? argv[1] : NULL;
	const char* output_file = (argc > 2) ? argv[2] : NULL;
	
	char* quadgram_data = ReadFile(kQuadgramsFile);
	if (quadgram_data == NULL) {
		return EXIT_FAILURE;
	}
	
	QuadgramStats* stats = ParseQuadgramStats(quadgram_data);
	free(quadgram_data);
	
	if (stats == NULL) {
		return EXIT_FAILURE;
	}
	
	// PrintQuadgramStats(stats);
	
	char* ciphertext = ReadFile(input_file);
	if (ciphertext == NULL) {
		FreeQuadgramStats(stats);
		return EXIT_FAILURE;
	}
	
	// printf("Ciphertext:\n%s\n", ciphertext);
	
	if (WriteFile(output_file, ciphertext) != 0) {
		free(ciphertext);
		FreeQuadgramStats(stats);
		return EXIT_FAILURE;
	}
	
	Solver* solver = InitSolver(ciphertext, stats);
    if (!solver) {
		free(ciphertext);
		FreeQuadgramStats(stats);
		return EXIT_FAILURE;
	}
	
    const char* random_key = GetKey(solver);
    printf("Generated Random Key: %s\n", random_key);
	
	free(ciphertext);
	FreeQuadgramStats(stats);
	return EXIT_SUCCESS;
}