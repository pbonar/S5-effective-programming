#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "GroupingEvaluator.h"
#include "CGeneticAlgorithm.h"
#include <vector>
#include <iostream>

namespace NGroupingChallenge {
    class COptimizer {
    public:
        COptimizer(CGroupingEvaluator& cEvaluator, size_t popSize, double crossProb, double mutProb, size_t maxIterations);

        void vInitialize();
        void vRunOptimization();

    private:
        CGroupingEvaluator& c_evaluator;
        CGeneticAlgorithm c_genetic_algo;

        double d_current_best_fitness;
        std::vector<int> v_current_best;

        void vDisplayBestSolution();
    };
}

#endif // OPTIMIZER_H
