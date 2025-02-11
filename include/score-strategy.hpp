#ifndef SCORE_STATEGY_HPP
#define SCORE_STATEGY_HPP

namespace score_strategy {

class ScoreStrategy {
public:
    virtual int computeScore(int preScore, int linesDestroyed) = 0;
    virtual ~ScoreStrategy() {}
};

class SquareLineScoreStrategy : public ScoreStrategy {
public:
    int computeScore(int preScore, int linesDestroyed) override;
};
} // namespace score_strategy

#endif // SCORE_STATEGY_HPP