#include "Optimizer.h"
#include "GaussianGroupingEvaluatorFactory.h"

int main() {
    // Parametry algorytmu genetycznego
    int numberOfGroups = 3;
    int numberOfPoints = 5;
    size_t popSize = 10;
    double crossProb = 0.7;
    double mutProb = 0.1;
    size_t maxIterations = 100;

    // Tworzenie fabryki GaussianGroupingEvaluatorFactory
    NGroupingChallenge::CGaussianGroupingEvaluatorFactory factory(numberOfGroups, numberOfPoints);

    // Dodawanie wymiarów do fabryki
    factory.cAddDimension(-10.0, 10.0, 1.0, 5.0)
           .cAddDimension(-20.0, 20.0, 2.0, 6.0);

    // Tworzenie instancji GroupingEvaluator
    NGroupingChallenge::CGroupingEvaluator* evaluator = factory.pcCreateEvaluator();

    // Tworzenie optymalizatora i uruchamianie algorytmu
    NGroupingChallenge::COptimizer optimizer(*evaluator, popSize, crossProb, mutProb, maxIterations);
    optimizer.vInitialize();
    optimizer.vRunOptimization();

    // Usuwanie evaluator (dynamicznie alokowanego)
    delete evaluator;

    return 0;
}
