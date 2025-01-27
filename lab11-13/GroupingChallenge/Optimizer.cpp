#include "Optimizer.h"
#include <iostream>
#include <limits>

using namespace NGroupingChallenge;

COptimizer::COptimizer(CGroupingEvaluator& cEvaluator, size_t popSize, double crossProb, double mutProb, size_t maxIterations)
    : c_evaluator(cEvaluator),
      c_genetic_algo(cEvaluator, popSize, crossProb, mutProb, maxIterations),
      d_current_best_fitness(std::numeric_limits<double>::max()) {
}

void COptimizer::vInitialize() {
    c_genetic_algo.initializePopulation();

    d_current_best_fitness = std::numeric_limits<double>::max();
    v_current_best.clear();
    v_current_best.resize(c_evaluator.iGetNumberOfPoints());
}

void COptimizer::vRunOptimization() {
    c_genetic_algo.run();

    const CIndividual& best_individual = c_genetic_algo.getBestIndividual();
    v_current_best = best_individual.getGenotypes();
    d_current_best_fitness = best_individual.getFitness();

    vDisplayBestSolution();
}

void COptimizer::vDisplayBestSolution() {
    std::cout << c_genetic_algo.toString();
}
