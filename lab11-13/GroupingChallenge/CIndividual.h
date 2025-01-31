#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include "GroupingEvaluator.h"
#include <vector>
#include <utility>
#include <random>
#include <iostream>

namespace NGroupingChallenge {

class CIndividual {
public:
    CIndividual(const std::vector<int>& genotypes, CGroupingEvaluator* evaluator);

    double getFitness() const;
    const std::vector<int>& getGenotypes() const;
    void mutate(double mutationProbability, std::mt19937& randomEngine);
    void deterministicMutate(const std::vector<CIndividual>& population, std::mt19937& randomEngine);
    std::pair<CIndividual, CIndividual> crossover(const CIndividual& other, std::mt19937& randomEngine) const;

private:
    std::vector<int> genotypes_;
    double fitness_;
    CGroupingEvaluator* evaluator_;
};

}

#endif
