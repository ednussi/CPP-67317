#include "Rankable.h"

/**
* @brief Constructor
* @param score - it's score
*/
Rankable::Rankable(int score) : _score(score)
{
}

/**
* @returns Score
*/
int Rankable::getScore()const
{
	return _score;
}

/**
* @brief reset Scores
*/
void Rankable::resetScore()
{
	_score = DEF_SCORE;
}