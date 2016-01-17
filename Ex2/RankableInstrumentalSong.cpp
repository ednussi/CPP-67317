#include "RankableInstrumentalSong.h"
#include <sstream>
#include <math.h>

#define NO_BPM_VALUE 0

/**
* @brief initializes an instrument list of instruments the song is played by
* @param instrumentsData - a string containning the data about instruments is played by
*/
void RankableInstrumentalSong::_initializeInstrumentsList(const std::string &instrumentsData)
{
	std::istringstream iss(instrumentsData);
	std::string instrument;
	while (iss >> instrument)
	{
		_instrumentList.insert(instrument);
	}
}

/**
* @brief Constructor
* @param title - it's title
* @param tagsData - it's tagsData
* @param instrumentsData - the instruments it was played by
* @param performedBy - who was it performed by
* @param bpm - it's bpm
*/
RankableInstrumentalSong::RankableInstrumentalSong(const std::string &title, 
												   const std::string &tagsData,
												   const std::string &instrumentsData,
												   const std::string &performedBy, 
												   const std::string &bpm) :
												   RankableSong(title, tagsData), 
												   _performedBy(performedBy), _bpm(stod(bpm))
{
	_initializeInstrumentsList(instrumentsData);
}

/**
* @brief checks if the instrument was used to play the song
* @param instrument - instrument to check
* @return true iff the instrument was used to play the song
*/
bool RankableInstrumentalSong::playedWithInstrument(const std::string &instrument)const
{
	return (_instrumentList.find(instrument) != _instrumentList.end());
}

/**
* @brief Calculates the song score
* @param query - query to match score by
* @param songsParams - songs Parameters to match score by
*/
void RankableInstrumentalSong::calcScore(const std::string &query, 
										 const SongMatchingParams &songsParams)
{
	RankableSong::calcScore(query, songsParams);
	
	if (playedWithInstrument(query))
	{
		_score += songsParams.getInstrumentMatchScore();
	}

	if (_bpm != NO_BPM_VALUE)
	{
		if (songsParams.isUniqeWord(query))
		{
			_score += int(songsParams.getBpmWeight() * 
						 exp(-1 * pow(_bpm - songsParams.getAvgBpm(query), 2) /
						 (2 * pow(songsParams.getDeviationBpm(query), 2))));
		}
	}
}

/**
* @brief Prints out it's data
* @param os - the outstream to print out to
*/
void RankableInstrumentalSong::printData(std::ostream &os)const
{
	RankableSong::printData(os);
	os << '\t' << "performed by: " << _performedBy << std::endl;
}