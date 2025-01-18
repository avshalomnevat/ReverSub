#include "../include/utils.h"

#define QUADGRAMS_FILE "data/quadgrams.txt"

int main(int argc, char* argv[]) {
    QuadgramStats* stats = parse_quadgram_stats(read_file(QUADGRAMS_FILE));
	
    char* ciphertext = read_file(argv[1]);
	
    // Solution* solution = solve_cipher(ciphertext, stats);
    
    write_file(argv[2], ciphertext);
	
	return 0;
}