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

void CIndividual::deterministicMutate(const std::vector<CIndividual>& population, std::mt19937& randomEngine) {
    if (genotypes_.empty()) return;

    std::uniform_int_distribution<int> indexDist(0, genotypes_.size() - 1);
    int mutationIndex = indexDist(randomEngine);

    int upperBound = evaluator_->iGetUpperBound();
    std::vector<int> frequency(upperBound + 1, 0);

    for (size_t i = 0; i < population.size(); i++) {
        if (mutationIndex < population[i].genotypes_.size()) {
            frequency[population[i].genotypes_[mutationIndex]]++;
        }
    }

    int mostFrequentGene = genotypes_[mutationIndex];
    int maxCount = 0;

    for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] > maxCount) {
            mostFrequentGene = i;
            maxCount = frequency[i];
        }
    }
    // std::cout << "zmienilem na miejscu " <<  mutationIndex << " na most_frequent_gen: " << mostFrequentGene << std::endl;
    genotypes_[mutationIndex] = mostFrequentGene;
    fitness_ = evaluator_->dEvaluate(genotypes_);
}

std::pair<CIndividual, CIndividual> CIndividual::crossover(const CIndividual& other, std::mt19937& randomEngine) const {
    std::uniform_int_distribution<int> pointDist(1, genotypes_.size() - 1);
    int crossoverPoint = pointDist(randomEngine);

    std::vector<int> child1(genotypes_.begin(), genotypes_.begin() + crossoverPoint);
    child1.insert(child1.end(), other.genotypes_.begin() + crossoverPoint, other.genotypes_.end());

    std::vector<int> child2(other.genotypes_.begin(), other.genotypes_.begin() + crossoverPoint);
    child2.insert(child2.end(), genotypes_.begin() + crossoverPoint, genotypes_.end());

    return { CIndividual(child1, evaluator_), CIndividual(child2, evaluator_) };
}

}
