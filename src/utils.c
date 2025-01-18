#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

#define READ_MODE "r"
#define WRITE_MODE "w"
#define MAX_LINE_LENGTH 256

const char* DEFAULT_FILES[] = {
    "data/input/cipher.txt",
    "data/output/plain.txt"
};

char *read_file(const char* path) {
	if (path == NULL) {
        path = DEFAULT_FILES[0];  // Use default input file if no path is provided
    }
	
    // Open the file for reading
	FILE *file = fopen(path, READ_MODE);
	
    // Move to the end of the file to determine the length
	fseek(file, 0, SEEK_END);
	
    // Get the location of the file pointer (the file length)
	long length = ftell(file);
	
	// +1 For null-terminator
	char *buffer = malloc(length + 1);
	
	fseek(file, 0, SEEK_SET);
	
	// Read the content of the file into the buffer
    size_t bytes_read = fread(buffer, 1, length, file);
	buffer[bytes_read] = '\0';
	
	fclose(file);
	return buffer;
}


int get_index(const char* quadgram) {
    // Assuming the quadgram consists of uppercase English letters (A-Z)
    // We map each letter to its 0-based index ('A' -> 0, 'B' -> 1, ..., 'Z' -> 25)
    int index = 0;
    for (int i = 0; i < QUADGRAM_LENGTH; i++) {
        index = index * ALPHABET_LENGTH + (quadgram[i] - ALPHABET[0]);
    }
    return index;
}

QuadgramStats* parse_quadgram_stats(const char* data) {
	// Initialize
	QuadgramStats* stats = (QuadgramStats*)malloc(sizeof(QuadgramStats));
	memset(stats->scores, 0, sizeof(stats->scores));
	stats->count = 0;
	
	// Go over data line-by-line
	char line[MAX_LINE_LENGTH];
    const char* ptr = data;
	while (sscanf(ptr, "%s", line) == 1) {
		// Extract the quadgram (first 4 chars of the line)
		char quadgram[5];
		strncpy(quadgram, line, 4);
		quadgram[4] = '\0';
		
		int frequency;
        ptr += strlen(line) + 1; // Move pointer past the quadgram
        if (sscanf(ptr, "%d", &frequency) == 1) {
            int index = get_index(quadgram);

            // Store the frequency in the corresponding index in the scores array
            stats->scores[index] = frequency;
            stats->count += frequency;
        }
		
		// Move to the next line
		while (*ptr != '\n' && *ptr != '\0') {
            ptr++;
        }
        if (*ptr == '\n') {
            ptr++;
        }
	}
	
	return stats;
}

void write_file(const char *path, char *data) {
	if (path == NULL) {
        path = DEFAULT_FILES[1];  // Use default input file if no path is provided
    }
	
	FILE *file = fopen(path, WRITE_MODE);
	fprintf(file, "%s", data);
	fclose(file);
}