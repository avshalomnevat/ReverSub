#include "../include/common.h"
#include <stdio.h>


char *read_file(const char* path);

// Computes the index for a given quadgram based on its position in the lexicographical order of all possible 4-letter combinations using the English alphabet (A-Z).
// For example, "AAAA" maps to index 0, "AAAB" maps to index 1, ..., and "ZZZZ" maps to MAX_QUADGRAM_COUNT-1.
int get_index(const char* quadgram);

QuadgramStats* parse_quadgram_stats(const char* data);

void write_file(const char *path, char *data);

char* get_quadgram(int index);

// Debug
void print_stats(const QuadgramStats* stats);