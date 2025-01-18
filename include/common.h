#ifndef COMMON_H
#define COMMON_H

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ALPHABET_LENGTH 26
#define QUADGRAM_LENGTH 4


// Total number of possible 4-letter combinations using the English alphabet = 26^4
// MAX_QUADGRAM_COUNT (456,976) represents the theoretical maximum number of unique quadgrams.
// Note: Not all possible combinations are used in English words, so the actual count varies by dataset. 
// In our dataset (https://github.com/DominicBreuker/cryptanalysis/blob/master/data/en/quadrams.txt), there are 389,373 quadgrams.
#define MAX_QUADGRAM_COUNT 456976

typedef struct {
    double scores[MAX_QUADGRAM_COUNT]; 
    int count;
} QuadgramStats;

#endif