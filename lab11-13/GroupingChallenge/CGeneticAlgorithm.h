#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include "GroupingEvaluator.h"
#include "CIndividual.h"
#include <vector>
#include <random>
#include <string>

namespace NGroupingChallenge {

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(CGroupingEvaluator& evaluator, int populationSize, double crossoverProbability, double mutationProbability, int maxGenerations);

    void initializePopulation();      // Inicjalizuje populację
    void runOneGeneration();          // Wykonuje jedną generację
    const CIndividual& getBestIndividual() const; // Zwraca najlepszy osobnik
    int getMaxGenerations() const { return maxGenerations_; } // Zwraca liczbę generacji
    std::string toString() const;
    std::string toStringShort() const;       // Zwraca szczegóły algorytmu jako string

private:
    CIndividual& selectParent();      // Wybór rodzica
    void updateBestIndividual();      // Aktualizacja najlepszego osobnika

    std::vector<CIndividual> population_;
    CIndividual bestIndividual_;
    CGroupingEvaluator& evaluator_;
    int populationSize_;
    double crossoverProbability_;
    double mutationProbability_;
    int maxGenerations_;
    std::mt19937 randomEngine_;
};

}

#endif
