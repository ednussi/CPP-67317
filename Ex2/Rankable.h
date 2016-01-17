/**
* @file Rankable.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A Rankable class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
An abstract Rankable class represnting a ranking interface with ability to calc score
*/

#ifndef RANKABLE_H
#define RANKABLE_H

#define DEF_SCORE 0

/**
* @class Rankable
* @brief An abstract Rankable class represnting a ranking interface with ability to calc score
*/
class Rankable
{

protected:
	int _score;

public:

	/**
	* @brief Constructor
	* @param score - it's score
	*/
	Rankable(int score = DEF_SCORE);

	/**
	* @brief Destructor 
	*/
	virtual ~Rankable(){};

	/**
	* @returns Score
	*/
	virtual int getScore()const;

	/**
	* @brief reset Scores
	*/
	virtual void resetScore();

};

#endif

