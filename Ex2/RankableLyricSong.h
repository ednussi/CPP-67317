/**
* @file RankableLyricSong.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A RankableLyricSong class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* A Rankable Lyric Song class extending the rankable song class and stands for a 
* specific kind of song with uniqe characteristics 
*/

#ifndef RANKABLE_LYRIC_SONG_H
#define RANKABLE_LYRIC_SONG_H

#include "RankableSong.h"

typedef std::unordered_map<std::string, int> LyricsMap;

/**
* @class RankableLyricSong
* @brief A Rankable Lyric Song class extending the rankable song class and stands for a 
*		 specific kind of song with uniqe characteristics 
*/
class RankableLyricSong :
	public RankableSong
{
private:
	LyricsMap _lyrics;
	std::string _lyricsBy;

	/**
	* @brief initializes a lyrics list
	* @param lyrics - a string containning the song lyrics
	*/
	void _initializeLyricsMap(const std::string &lyrics);


public:

	/**
	* @brief Constructor
	* @param title - it's title
	* @param tagsData - it's tagsData
	* @param lyrics - the song lyrics
	* @param lyricsBy - who wrote it's lyrics
	*/
	RankableLyricSong(const std::string &title, 
					  const std::string &tagsData, 
					  const std::string &lyrics,
					  const std::string &lyricsBy);
	
	/**
	* @brief Destructor
	*/
	virtual ~RankableLyricSong(){};

	/**
	* @brief Calculates the song score
	* @param query - query to match score by
	* @param songsParams - songs Parameters to match score by
	*/
	void calcScore(const std::string &query, 
				   const SongMatchingParams &songsParams)override;

	/**
	* @brief checks if the word is in the lyrics
	* @param word - word to check
	* @return true iff the word is in the lyrics
	*/
	bool isInLyrics(const std::string &word)const;

	/**
	* @brief Prints out it's data
	* @param os - the outstream to print out to
	*/
	virtual void printData(std::ostream &os)const override;
};

#endif

