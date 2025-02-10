#ifndef SCORE_STATEGY_HPP
#define SCORE_STATEGY_HPP

namespace score_strategy {

class ScoreStrategy {
    virtual int computeScore(int preScore, int linesDestroyed) = 0;
    virtual ~ScoreStrategy() {}
};

class DoubleScorePerLineStrategy : ScoreStrategy {
    int computeScore(int preScore, int linesDestroyed) override;
};
} // namespace score_strategy

#endif // SCORE_STATEGY_HPP