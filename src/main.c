#include "../include/utils.h"

#define QUADGRAMS_FILE "data/quadgrams.txt"


int main(int argc, char* argv[]) {
	printf("ReverSub\n");

	if (argc < 3) {
		printf("Using default files\n");
	}
	
    QuadgramStats* stats = parse_quadgram_stats(read_file(QUADGRAMS_FILE));
	print_stats(stats);

    char* ciphertext = read_file(argv[1]);
	printf("%s\n", ciphertext);
    //Solution* solution = solve_cipher(ciphertext, stats);
    
    write_file(argv[2], ciphertext);
	
	return 0;
}