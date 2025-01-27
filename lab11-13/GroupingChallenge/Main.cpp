#include "Optimizer.h"
#include "GaussianGroupingEvaluatorFactory.h"



// Parametry algorytmu genetycznego
static int numberOfGroups = 3;
static int numberOfPoints = 5;
static size_t popSize = 10;
static double crossProb = 0.7;
static double mutProb = 0.1;
static size_t maxIterations = 5;



int main() {
    NGroupingChallenge::CGaussianGroupingEvaluatorFactory factory(numberOfGroups, numberOfPoints);

    factory.cAddDimension(-10.0, 10.0, 1.0, 5.0)
           .cAddDimension(-20.0, 20.0, 2.0, 6.0);

    NGroupingChallenge::CGroupingEvaluator* evaluator = factory.pcCreateEvaluator();

    NGroupingChallenge::COptimizer optimizer(*evaluator, popSize, crossProb, mutProb, maxIterations);
    optimizer.vInitialize();
    optimizer.vRunOptimization();

    delete evaluator;

    return 0;
}
