#include "../include/score-strategy.hpp"

#include <cmath>

namespace score_strategy {

int DoubleScorePerLineStrategy::computeScore(int preScore, int linesDestroyed) {
    return std::pow(preScore, linesDestroyed + 1);
}

} // namespace score_strategy
