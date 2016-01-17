/**
* @file SongDataBase.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A SongDataBase class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* A song data base class containning all the information of the program
*/

#ifndef SONG_DATA_BASE_H
#define SONG_DATA_BASE_H

#include "RankableSong.h"
#include "SongMatchingParams.h"
#include <vector>

/**
* @class Song
* @brief A song data base class containning all the information of the program
*/
class SongDataBase
{
private:

	int _tagMatchScore, _lyricsMatchScore, _instrumentalMatchScore, _bpmWeight;
	std::vector<RankableSong*> _songsList;
	SongMatchingParams _songsParams;
	
	/**
	* @brief prints out all the queries results
	*/
	void _printQueryResults();
	
	/**
	* @brief reset all scores
	*/
	void _resetScores();

public:

	/**
	* @brief Constructor
	* @param songsList - the list of all the songs
	* @param songsParams - the ranking and scoring parameters object
	*/
	SongDataBase(const std::vector<RankableSong*> &songsList, const SongMatchingParams &songsParams);

	/**
	* @brief Destructor
	*/
	~SongDataBase();

	/**
	* @brief run a single query
	* @param query - the query
	*/
	void runQuery(const std::string &query);
};

#endif
