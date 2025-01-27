#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include "GroupingEvaluator.h"
#include "CIndividual.h"
#include <vector>
#include <random>
#include <string> // Dodano, aby użyć std::string

namespace NGroupingChallenge {

class CGeneticAlgorithm {
public:
    CGeneticAlgorithm(CGroupingEvaluator& evaluator, int populationSize, double crossoverProbability, double mutationProbability, int maxGenerations);

    void initializePopulation();
    void run();
    const CIndividual& getBestIndividual() const;

    // Dodano metodę toString
    std::string toString() const;

private:
    CIndividual& selectParent();
    void updateBestIndividual();

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
