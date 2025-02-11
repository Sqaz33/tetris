#include "../include/score-strategy.hpp"

#include <cmath>

namespace score_strategy {

int SquareLineScoreStrategy::computeScore(int preScore, int linesDestroyed) {
    return linesDestroyed ? std::pow(2, linesDestroyed) : 0;
}

} // namespace score_strategy
