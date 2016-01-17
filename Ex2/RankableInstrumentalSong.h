/**
* @file RankableInstrumentalSong.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A RankableInstrumentalSong class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* A Rankable Instrumental Song class extending the rankable song class and stands for a
* specific kind of song with uniqe characteristics
*/

#ifndef RANKABLE_INSTRUMENTAL_SONG_H
#define RANKABLE_INSTRUMENTAL_SONG_H

#include "RankableSong.h"
#include <set>

/**
* @class RankableInstrumentalSong
* @brief A Rankable Instrumental Song class extending the rankable song class and stands for a
*		 specific kind of song with uniqe characteristics
*/
class RankableInstrumentalSong :
	public RankableSong
{
private:
	typedef std::set<std::string> InstrumentList;
	InstrumentList _instrumentList;
	std::string _performedBy;
	double _bpm;

	/**
	* @brief initializes an instrument list of instruments the song is played by
	* @param instrumentsData - a string containning the data about instruments is played by
	*/
	void _initializeInstrumentsList(const std::string &instrumentsData);

public:

	/**
	* @brief Constructor
	* @param title - it's title
	* @param tagsData - it's tagsData
	* @param instrumentsData - the instruments it was played by
	* @param performedBy - who was it performed by
	* @param bpm - it's bpm
	*/
	RankableInstrumentalSong(const std::string &title, 
							 const std::string &tagsData,
							 const std::string &instrumentsData, 
							 const std::string &performedBy,
							 const std::string &bpm);
	
	/**
	* @brief Destructor
	*/
	virtual ~RankableInstrumentalSong(){};

	/**
	* @brief checks if the instrument was used to play the song
	* @param instrument - instrument to check
	* @return true iff the instrument was used to play the song
	*/
	bool playedWithInstrument(const std::string &instrument)const;

	/**
	* @brief Calculates the song score
	* @param query - query to match score by
	* @param songsParams - songs Parameters to match score by
	*/
	void calcScore(const std::string &query, 
				   const SongMatchingParams &songsParams)override;

	/**
	* @brief Prints out it's data
	* @param os - the outstream to print out to
	*/
	virtual void printData(std::ostream &os)const override;
};

#endif

