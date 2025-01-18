#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define kReadMode "r"
#define kWriteMode "w"

char* ReadFile(const char* filepath) {
	if (filepath == NULL) {
		filepath = kDefaultInputPath;
	}
	
	FILE* file = fopen(filepath, kReadMode);
	if (file == NULL) {
		fprintf(stderr, "Error opening file %s: %s\n", filepath, strerror(errno));
		return NULL;
	}
	
	if (fseek(file, 0, SEEK_END) != 0) {
		fprintf(stderr, "Error seeking file: %s\n", strerror(errno));
		fclose(file);
		return NULL;
	}
	
	long length = ftell(file);
	if (length == -1) {
		fprintf(stderr, "Error getting file size: %s\n", strerror(errno));
		fclose(file);
		return NULL;
	}
	
	char* buffer = malloc(length + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		fclose(file);
		return NULL;
	}
	
	if (fseek(file, 0, SEEK_SET) != 0) {
		fprintf(stderr, "Error seeking file: %s\n", strerror(errno));
		free(buffer);
		fclose(file);
		return NULL;
	}
	
	size_t bytes_read = fread(buffer, 1, length, file);
	
	buffer[bytes_read] = '\0';
	fclose(file);
	return buffer;
}

int GetQuadgramIndex(const char* quadgram) {
	if (quadgram == NULL || strlen(quadgram) != kQuadgramSize) {
		return -1;
	}
	
	int index = 0;
	for (int i = 0; i < kQuadgramSize; i++) {
		if (quadgram[i] < 'A' || quadgram[i] > 'Z') {
			return -1;
		}
		index = index * kAlphabetSize + (quadgram[i] - kAlphabet[0]);
	}
	return index;
}

QuadgramStats* ParseQuadgramStats(const char* data) {
	if (data == NULL) {
		return NULL;
	}
	
	QuadgramStats* stats = malloc(sizeof(QuadgramStats));
	if (stats == NULL) {
		return NULL;
	}
	
	stats->scores = calloc(kMaxQuadgramCount, sizeof(double));
	if (stats->scores == NULL) {
		free(stats);
		return NULL;
	}
	
	stats->count = 0;
	char line[kMaxLineLength];
	const char* ptr = data;
	
	while (sscanf(ptr, "%s", line) == 1) {
		char quadgram[kQuadgramSize + 1];
		strncpy(quadgram, line, kQuadgramSize);
		quadgram[kQuadgramSize] = '\0';
		
		int frequency;
		ptr += strlen(line) + 1;
		
		if (sscanf(ptr, "%d", &frequency) == 1) {
			int index = GetQuadgramIndex(quadgram);
			if (index >= 0) {
				stats->scores[index] = frequency;
				stats->count++;
			}
		}
		
		while (*ptr != '\n' && *ptr != '\0') {
			ptr++;
		}
		if (*ptr == '\n') {
			ptr++;
		}
	}
	
	return stats;
}

int WriteFile(const char* filepath, const char* data) {
	if (data == NULL) {
		return -1;
	}
	
	if (filepath == NULL) {
		filepath = kDefaultOutputPath;
	}
	
	FILE* file = fopen(filepath, kWriteMode);
	if (file == NULL) {
		fprintf(stderr, "Error opening file %s: %s\n", filepath, strerror(errno));
		return -1;
	}
	
	if (fprintf(file, "%s", data) < 0) {
		fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
		fclose(file);
		return -1;
	}
	
	fclose(file);
	return 0;
}

char* GetQuadgramFromIndex(int index) {
	if (index < 0 || index >= kMaxQuadgramCount) {
		return NULL;
	}
	
	char* quadgram = malloc(kQuadgramSize + 1);
	if (quadgram == NULL) {
		return NULL;
	}
	
	for (int i = kQuadgramSize - 1; i >= 0; i--) {
		quadgram[i] = kAlphabet[0] + (index % kAlphabetSize);
		index /= kAlphabetSize;
	}
	quadgram[kQuadgramSize] = '\0';
	
	return quadgram;
}

void PrintQuadgramStats(const QuadgramStats* stats) {
	if (stats == NULL) {
		return;
	}
	
	printf("Number of quadgrams: %d\n", stats->count);
	
	for (int i = 0; i < kMaxQuadgramCount; i++) {
		if (stats->scores[i] > 0) {
			char* quadgram = GetQuadgramFromIndex(i);
			if (quadgram != NULL) {
				printf("%s: %d\n", quadgram, stats->scores[i]);
				free(quadgram);
			}
		}
	}
}

void FreeQuadgramStats(QuadgramStats* stats) {
	if (stats != NULL) {
		free(stats->scores);
		free(stats);
	}
}
