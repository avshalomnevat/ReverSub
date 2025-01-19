#ifndef REVERSUB_SOLVER_H_
#define REVERSUB_SOLVER_H_

#include "common.h"

// Default parameters for the solver
#define kDefaultMaxIterations 1000
#define kDefaultRestarts 10
#define kMinScore -99999.0

// Solver struct definition
typedef struct Solver {
    char* key;
    char* plaintext;
    const char* ciphertext;
    QuadgramStats* stats;
} Solver;

// Function declarations
Solver* InitSolver(const char* ciphertext, QuadgramStats* stats);
void DestroySolver(Solver* solver);
int Solve(Solver* solver);
const char* GetPlaintext(Solver* solver);
const char* GetKey(Solver* solver);

// Utility functions
char* GenrateRandomKey(void);
char* MutateKey(const char* key);
char* Decrypt(const char* text, const char* key);
double EvaluateFitness(const char* text, const QuadgramStats* stats);

#endif  // REVERSUB_SOLVER_H_
