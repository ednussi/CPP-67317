#include "RankableLyricSong.h"

/**
* @brief initializes a lyrics list
* @param lyrics - a string containning the song lyrics
*/
void RankableLyricSong::_initializeLyricsMap(const std::string &lyrics)
{
	std::istringstream iss(lyrics);
	std::string word;
	LyricsMap::iterator it;
	while (iss >> word)
	{
		it = _lyrics.find(word);
		if (it == _lyrics.end())
		{
			//new word
			_lyrics.insert({ word, 1 });
		}
		else
		{
			//increase word count
			it->second++;
		}
	}
}

/**
* @brief Constructor
* @param title - it's title
* @param tagsData - it's tagsData
* @param lyrics - the song lyrics
* @param lyricsBy - who wrote it's lyrics
*/
RankableLyricSong::RankableLyricSong(const std::string &title, 
								 	const std::string &tagsData,
									 const std::string &lyrics, 
									 const std::string &lyricsBy) :
									 RankableSong(title, tagsData), 
									 _lyricsBy(lyricsBy)
{
	_initializeLyricsMap(lyrics);
}

/**
* @brief checks if the word is in the lyrics
* @param word - word to check
* @return true iff the word is in the lyrics
*/
bool RankableLyricSong::isInLyrics(const std::string &word)const
{
	return (_lyrics.find(word) != _lyrics.end());
}

/**
* @brief Calculates the song score
* @param query - query to match score by
* @param songsParams - songs Parameters to match score by
*/
void RankableLyricSong::calcScore(const std::string &query, 
								  const SongMatchingParams &songsParams)
{
	RankableSong::calcScore(query, songsParams);

	if (isInLyrics(query))
	{
		_score += _lyrics.find(query)->second * songsParams.getLyricsMatchScore();
	}
}

/**
* @brief Prints out it's data
* @param os - the outstream to print out to
*/
void RankableLyricSong::printData(std::ostream &os)const
{
	RankableSong::printData(os);
	os << '\t' << "lyrics by: " << _lyricsBy << std::endl;
}