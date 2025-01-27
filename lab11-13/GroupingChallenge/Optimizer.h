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

        void vInitialize();       // Inicjalizacja algorytmu genetycznego
        void vRunOptimization(); // Uruchomienie pełnej optymalizacji

    private:
        CGroupingEvaluator& c_evaluator;  // Referencja do klasy oceniającej
        CGeneticAlgorithm c_genetic_algo; // Instancja algorytmu genetycznego

        double d_current_best_fitness;    // Najlepsza wartość przystosowania
        std::vector<int> v_current_best;  // Najlepsze rozwiązanie genotypowe

        void vDisplayBestSolution();      // Wyświetlanie najlepszego rozwiązania
    };
}

#endif // OPTIMIZER_H
