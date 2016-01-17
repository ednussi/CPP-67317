#include "RankableSong.h"

/**
* @brief Constructor
* @param title - it's title
* @param tagsData - it's tagsData
*/
RankableSong::RankableSong(const std::string &title, 
						   const std::string &tagsData) : Rankable(), Song(title, tagsData)
{
}

/**
* @brief Prints out it's data
* @param os - the outstream to print out to
*/
void RankableSong::printData(std::ostream &os)const
{
	os << _title << '\t' << _score;
}

/**
* @brief Calculates the rankableSong score
* @param query - query to match score by
* @param songsParams - songs Parameters to match score by
*/	
void RankableSong::calcScore(const std::string &query, 
							 const SongMatchingParams &songsParams)
{
	TagsMap::iterator foungTag = _tagsMap.find(query);
	if (foungTag != _tagsMap.end())
	{
		_score += songsParams.getTagMatchScore() * foungTag->second;
	}
}