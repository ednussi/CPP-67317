/**
* @file RankableSong.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A RankableSong class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* A Rankable Song song class extending both rankable and song classes containning the 
* song has interface of rankable with the paramters of a song
*/

#ifndef RANKABLE_SONG_H
#define RANKABLE_SONG_H

#include "SongMatchingParams.h"
#include "Rankable.h"
#include "Song.h"
#include <iostream>

#define DEFAULT_TITLE ""
#define DEFAULT_TAGS_DATA ""

/**
* @class RankableSong
* @brief A Rankable Song song class extending both rankable and song classes containning the 
*	     song has interface of rankable with the paramters of a song
*/
class RankableSong : public Rankable, public Song
{
protected:
	
	/**
	* @brief Constructor
	* @param title - it's title
	* @param tagsData - it's tagsData
	*/
	RankableSong(const std::string &title = DEFAULT_TITLE, const std::string &tagsData = DEFAULT_TAGS_DATA);

public:

	/**
	* @brief Destructor
	*/
	virtual ~RankableSong(){};

	/**
	* @brief Prints out it's data
	* @param os - the outstream to print out to
	*/
	virtual void printData(std::ostream &os)const;

	/**
	* @brief Calculates the rankableSong score
	* @param query - query to match score by
	* @param songsParams - songs Parameters to match score by
	*/	
	virtual void calcScore(const std::string &query, const SongMatchingParams &songsParams);
};

#endif
