#include "CIndividual.h"

namespace NGroupingChallenge {

CIndividual::CIndividual(const std::vector<int>& genotypes, CGroupingEvaluator* evaluator)
    : genotypes_(genotypes), evaluator_(evaluator) {
    fitness_ = evaluator_->dEvaluate(genotypes_);
}

double CIndividual::getFitness() const {
    return fitness_;
}

const std::vector<int>& CIndividual::getGenotypes() const {
    return genotypes_;
}

void CIndividual::mutate(double mutationProbability, std::mt19937& randomEngine) {
    std::uniform_real_distribution<double> probDist(0.0, 1.0);
    std::uniform_int_distribution<int> groupDist(1, evaluator_->iGetUpperBound());

    for (int& gene : genotypes_) {
        if (probDist(randomEngine) < mutationProbability) {
            gene = groupDist(randomEngine);
        }
    }
    fitness_ = evaluator_->dEvaluate(genotypes_);
}

std::pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual& other, std::mt19937& randomEngine) const {
    std::uniform_int_distribution<int> pointDist(1, genotypes_.size() - 1);
    int crossoverPoint = pointDist(randomEngine);

    std::vector<int> child1Genotypes(genotypes_.begin(), genotypes_.begin() + crossoverPoint);
    child1Genotypes.insert(child1Genotypes.end(), other.genotypes_.begin() + crossoverPoint, other.genotypes_.end());

    std::vector<int> child2Genotypes(other.genotypes_.begin(), other.genotypes_.begin() + crossoverPoint);
    child2Genotypes.insert(child2Genotypes.end(), genotypes_.begin() + crossoverPoint, genotypes_.end());

    return { CIndividual(child1Genotypes, evaluator_), CIndividual(child2Genotypes, evaluator_) };
}

}
