#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

Solver* InitSolver(const char* ciphertext, QuadgramStats* stats) {
    Solver* solver = (Solver*)malloc(sizeof(Solver));
    if (!solver) {
        perror("Failed to allocate Solver");
        return NULL;
    }

    solver->ciphertext = ciphertext;
    solver->stats = stats;
    solver->key = GenrateRandomKey();
    solver->plaintext = NULL;
    return solver;
}

void DestroySolver(Solver* solver) {
    if (solver) {
        free(solver->key);
        free(solver->plaintext);
        free(solver);
    }
}

int Solve(Solver* solver) {
    return 0;
}

const char* GetPlaintext(Solver* solver) {
    return solver->plaintext;
}

const char* GetKey(Solver* solver) {
    return solver->key;
}

char* GenrateRandomKey(void) {
    char* random_key = (char*)malloc(kAlphabetSize + 1);
    if (!random_key) {
        perror("Failed to allocate memory for key");
        return NULL;
    }

    strcpy(random_key, kAlphabet);

    // Shuffle the alphabet "randomly"
    srand((unsigned int)time(NULL));
    for (size_t i = 0; i < kAlphabetSize - 1; ++i) {
        size_t j = i + rand() / (RAND_MAX / (kAlphabetSize - i) + 1);
        char temp = random_key[i];
        random_key[i] = random_key[j];
        random_key[j] = temp;
    }

    random_key[kAlphabetSize] = '\0';
    return random_key;
}

char* MutateKey(const char* key) {
    return NULL;
}

char* Decrypt(const char* text, const char* key) {
    return NULL;
}

double EvaluateFitness(const char* text, const QuadgramStats* stats) {
    return 0.0; 
}
