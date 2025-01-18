#ifndef REVERSUB_COMMON_H_
#define REVERSUB_COMMON_H_

#define kAlphabet "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define kAlphabetSize 26
#define kQuadgramSize 4

// Maximum number of possible quadgrams (26^4)
#define kMaxQuadgramCount 456976

typedef struct {
	int* scores;
	int count;
} QuadgramStats;

#endif  // REVERSUB_COMMON_H_
