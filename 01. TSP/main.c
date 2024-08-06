#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CITIES 5
#define POP_SIZE 50
#define GENERATIONS 1000
#define MUTATION_RATE 0.01

int distanceMatrix[NUM_CITIES][NUM_CITIES] = {
    {0, 10, 15, 20, 25},
    {10, 0, 35, 25, 30},
    {15, 35, 0, 30, 20},
    {20, 25, 30, 0, 15},
    {25, 30, 20, 15, 0}
};

int population[POP_SIZE][NUM_CITIES];
double fitness[POP_SIZE];
int newPopulation[POP_SIZE][NUM_CITIES];


void generateRandomTour(int *tour) {
    for (int i = 0; i < NUM_CITIES; i++) {
        tour[i] = i;
    }
    for (int i = 0; i < NUM_CITIES; i++) {
        int j = rand() % NUM_CITIES;
        int temp = tour[i];
        tour[i] = tour[j];
        tour[j] = temp;
    }
}


void initPopulation() {
    for (int i = 0; i < POP_SIZE; i++) {
        generateRandomTour(population[i]);
    }
}


double calculateDistance(int *tour) {
    double totalDistance = 0.0;
    for (int i = 0; i < NUM_CITIES - 1; i++) {
        totalDistance += distanceMatrix[tour[i]][tour[i + 1]];
    }
    totalDistance += distanceMatrix[tour[NUM_CITIES - 1]][tour[0]];
    return totalDistance;
}


void calculateFitness() {
    for (int i = 0; i < POP_SIZE; i++) {
        fitness[i] = 1.0 / calculateDistance(population[i]);
    }
}


void tournamentSelection(int *parent1, int *parent2) {
    int bestIndex1 = 0;
    int bestIndex2 = 1;

    // Ensure that bestIndex1 is always less than bestIndex2
    if (fitness[bestIndex1] < fitness[bestIndex2]) {
        int temp = bestIndex1;
        bestIndex1 = bestIndex2;
        bestIndex2 = temp;
    }

    // Find the two indices with the highest fitness values
    for (int i = 2; i < POP_SIZE; i++) {
        if (fitness[i] > fitness[bestIndex1]) {
            bestIndex2 = bestIndex1;
            bestIndex1 = i;
        } else if (fitness[i] > fitness[bestIndex2]) {
            bestIndex2 = i;
        }
    }

    // Set parent1 to the best individual
    for (int i = 0; i < NUM_CITIES; i++) {
        parent1[i] = population[bestIndex1][i];
    }

    // Set parent2 to the second best individual
    for (int i = 0; i < NUM_CITIES; i++) {
        parent2[i] = population[bestIndex2][i];
    }
}


void crossover(int *parent1, int *parent2, int *child) {
    int crossoverPoint = rand() % NUM_CITIES;

    // Initialize child with -1 to indicate unfilled positions
    for (int i = 0; i < NUM_CITIES; i++) {
        child[i] = -1;
    }

    // Copy the segment from parent1 to child
    for (int i = 0; i <= crossoverPoint; i++) {
        child[i] = parent1[i];
    }

    // Fill in the remaining positions in the child from parent2
    int currentPos = crossoverPoint + 1;
    for (int i = 0; i < NUM_CITIES; i++) {
        int city = parent2[i];
        // Check if city is already in the child
        int found = 0;
        for (int j = 0; j < NUM_CITIES; j++) {
            if (child[j] == city) {
                found = 1;
                break;
            }
        }
        // If city is not in the child, add it
        if (!found) {
            if (currentPos >= NUM_CITIES) {
                currentPos = 0;
            }
            child[currentPos++] = city;
        }
    }
}


void mutate(int *tour) {
    for (int i = 0; i < NUM_CITIES; i++) {
        if ((double)rand() / RAND_MAX < MUTATION_RATE) {
            int j = rand() % NUM_CITIES;
            int temp = tour[i];
            tour[i] = tour[j];
            tour[j] = temp;
        }
    }
}

void geneticAlgorithm() {
    initPopulation();
    calculateFitness();

    for (int generation = 0; generation < GENERATIONS; generation++) {
        for (int i = 0; i < POP_SIZE; i += 2) {
            int parent1[NUM_CITIES], parent2[NUM_CITIES];
            int child1[NUM_CITIES], child2[NUM_CITIES];

            tournamentSelection(parent1, parent2);
            crossover(parent1, parent2, child1);
            crossover(parent2, parent1, child2);
            mutate(child1);
            mutate(child2);

            for (int j = 0; j < NUM_CITIES; j++) {
                newPopulation[i][j] = child1[j];
                newPopulation[i + 1][j] = child2[j];
            }
        }

        for (int i = 0; i < POP_SIZE; i++) {
            for (int j = 0; j < NUM_CITIES; j++) {
                population[i][j] = newPopulation[i][j];
            }
        }

        calculateFitness();
    }

    int bestIndex = 0;
    for (int i = 1; i < POP_SIZE; i++) {
        if (fitness[i] > fitness[bestIndex]) {
            bestIndex = i;
        }
    }

    printf("Best route: ");
    for (int i = 0; i < NUM_CITIES; i++) {
        printf("%d ", population[bestIndex][i]);
    }
    printf("\nBest distance: %lf\n", 1.0 / fitness[bestIndex]);
}

int main() {
    srand(time(NULL));
    geneticAlgorithm();
    return 0;
}

// SamujjalChoudhury
