#ifndef REVERSUB_UTILS_H_
#define REVERSUB_UTILS_H_

#include "common.h"
#include <stdio.h>

// Default file paths
#define kDefaultInputPath "data/input/cipher.txt"
#define kDefaultOutputPath "data/output/plain.txt"
#define kMaxLineLength 256

// Returns dynamically allocated buffer with file contents.
// Caller must free the returned buffer.
// Returns NULL on error.
char* ReadFile(const char* filepath);

// Writes data to specified file.
// Returns 0 on success, -1 on error.
int WriteFile(const char* filepath, const char* data);

// Computes index for a quadgram in lexicographical order.
// Returns -1 if quadgram contains invalid characters.
int GetQuadgramIndex(const char* quadgram);

// Parses quadgram statistics from raw data.
// Returns NULL on error.
QuadgramStats* ParseQuadgramStats(const char* data);

// Converts index back to quadgram string.
// Returns NULL on error. Caller must free returned string.
char* GetQuadgramFromIndex(int index);

// Prints quadgram statistics.
void PrintQuadgramStats(const QuadgramStats* stats);

// Frees QuadgramStats structure.
void FreeQuadgramStats(QuadgramStats* stats);


#endif // REVERSUB_UTILS_H_