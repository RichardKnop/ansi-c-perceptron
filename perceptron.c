#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LEARNING_RATE    0.1
#define MAX_ITERATION    100

float randomFloat()
{
    return (float)rand() / (float)RAND_MAX;
}

int calculateOutput(float weights[], float x, float y)
{
    float sum = x * weights[0] + y * weights[1] + weights[2];
    return (sum >= 0) ? 1 : -1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    float x[208], y[208], weights[3], localError, globalError;
    int outputs[208], patternCount, i, p, iteration, output;

    FILE *fp;
    if ((fp = fopen("test1.txt", "r")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    i = 0;
    while (fscanf(fp, "%f %f %d", &x[i], &y[i], &outputs[i]) != EOF) {
        if (outputs[i] == 0) {
            outputs[i] = -1;
        }
        i++;
    }
    patternCount = i;

    weights[0] = randomFloat();
    weights[1] = randomFloat();
    weights[2] = randomFloat();

    iteration = 0;
    do {
        iteration++;
        globalError = 0;
        for (p = 0; p < patternCount; p++) {
            output = calculateOutput(weights, x[p], y[p]);

            localError = outputs[p] - output;
            weights[0] += LEARNING_RATE * localError * x[p];
            weights[1] += LEARNING_RATE * localError * y[p];
            weights[2] += LEARNING_RATE * localError;

            globalError += (localError*localError);
        }

  /* Root Mean Squared Error */
  printf("Iteration %d : RMSE = %.4f\n", iteration,
                     sqrt(globalError/patternCount));
    } while (globalError != 0 && iteration<=MAX_ITERATION);

 printf("\nDecision boundary (line) equation: %.2f*x + %.2f*y + %.2f = 0\n",
             weights[0], weights[1], weights[2]);

    return 0;
}
