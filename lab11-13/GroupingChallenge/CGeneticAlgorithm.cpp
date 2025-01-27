#include "CGeneticAlgorithm.h"
#include <algorithm>
#include <sstream> // Do formatowania tekstu

namespace NGroupingChallenge {

CGeneticAlgorithm::CGeneticAlgorithm(CGroupingEvaluator& evaluator, int populationSize, double crossoverProbability, double mutationProbability, int maxGenerations)
    : evaluator_(evaluator),
      populationSize_(populationSize),
      crossoverProbability_(crossoverProbability),
      mutationProbability_(mutationProbability),
      maxGenerations_(maxGenerations),
      bestIndividual_({}, &evaluator) {
    randomEngine_.seed(std::random_device{}());
}

void CGeneticAlgorithm::initializePopulation() {
    std::uniform_int_distribution<int> groupDist(1, evaluator_.iGetUpperBound());

    for (int i = 0; i < populationSize_; ++i) {
        std::vector<int> genotypes(evaluator_.iGetNumberOfPoints());
        for (int& gene : genotypes) {
            gene = groupDist(randomEngine_);
        }
        population_.emplace_back(genotypes, &evaluator_);
    }

    bestIndividual_ = population_[0];
    updateBestIndividual();
}

void CGeneticAlgorithm::run() {
    for (int generation = 0; generation < maxGenerations_; ++generation) {
        std::vector<CIndividual> nextGeneration;

        while (nextGeneration.size() < populationSize_) {
            CIndividual& parent1 = selectParent();
            CIndividual& parent2 = selectParent();

            std::uniform_real_distribution<double> probDist(0.0, 1.0);
            if (probDist(randomEngine_) < crossoverProbability_) {
                auto [child1, child2] = parent1.crossover(parent2, randomEngine_);
                nextGeneration.push_back(child1);
                if (nextGeneration.size() < populationSize_) {
                    nextGeneration.push_back(child2);
                }
            } else {
                nextGeneration.push_back(parent1);
                if (nextGeneration.size() < populationSize_) {
                    nextGeneration.push_back(parent2);
                }
            }
        }

        for (CIndividual& individual : nextGeneration) {
            individual.mutate(mutationProbability_, randomEngine_);
        }

        population_ = std::move(nextGeneration);
        updateBestIndividual();
    }
}

const CIndividual& CGeneticAlgorithm::getBestIndividual() const {
    return bestIndividual_;
}

CIndividual& CGeneticAlgorithm::selectParent() {
    std::uniform_int_distribution<int> indexDist(0, population_.size() - 1);
    int idx1 = indexDist(randomEngine_);
    int idx2 = indexDist(randomEngine_);
    return (population_[idx1].getFitness() < population_[idx2].getFitness()) ? population_[idx1] : population_[idx2];
}

void CGeneticAlgorithm::updateBestIndividual() {
    auto bestIter = std::min_element(population_.begin(), population_.end(), [](const CIndividual& a, const CIndividual& b) {
        return a.getFitness() < b.getFitness();
    });

    if (bestIter != population_.end() && bestIter->getFitness() < bestIndividual_.getFitness()) {
        bestIndividual_ = *bestIter;
    }
}

std::string CGeneticAlgorithm::toString() const {
    std::ostringstream oss;

    // Informacje o stanie algorytmu
    oss << "Genetic Algorithm State:\n";
    oss << "Population Size: " << populationSize_ << "\n";
    oss << "Crossover Probability: " << crossoverProbability_ << "\n";
    oss << "Mutation Probability: " << mutationProbability_ << "\n";
    oss << "Max Generations: " << maxGenerations_ << "\n";
    oss << "Best Fitness: " << bestIndividual_.getFitness() << "\n";

    // Informacje o populacji (każda linia to jeden osobnik)
    oss << "Current Population:\n";
    for (size_t i = 0; i < population_.size(); ++i) {
        oss << " - Individual " << i + 1 << " (Fitness: " << population_[i].getFitness() << "): ";
        for (int gene : population_[i].getGenotypes()) {
            oss << gene << " ";
        }
        oss << "\n";
    }

    return oss.str();
}

}