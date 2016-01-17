#include "SongMatchingParams.h"

/**
* @brief Constructor.
* @param uniqeWords - the list of uniqe words which have a devation and avrg bpm
* @param tagMatchScore - the tags match score
* @param instrumentMatchScore - the instrumentals match score if exists
* @param lyricsMatchScore - the lyrics match score if they exsits
* @param bpmWeight - the score of the bpm if exists
*/
SongMatchingParams::SongMatchingParams(const UniqeWordsMap &uniqeWords, int tagMatchScore, 
									   int instrumentMatchScore, int lyricsMatchScore, 
									   int bpmWeight) : _tagMatchScore(tagMatchScore),
													    _lyricsMatchScore(lyricsMatchScore),
													    _instrumentMatchScore(instrumentMatchScore),
													    _bpmWeight(bpmWeight),
													    _uniqeWords(uniqeWords)
{
}

/**
* @brief get the tag match score
* @return tag match score
*/
int SongMatchingParams::getTagMatchScore() const
{
	return _tagMatchScore;
}

/**
* @brief get the lyrics match score
* @return lyrics match score
*/
int SongMatchingParams::getLyricsMatchScore() const
{
	return _lyricsMatchScore;
}

/**
* @brief get the instrumet match score
* @return instrumet match score
*/
int SongMatchingParams::getInstrumentMatchScore() const
{
	return _instrumentMatchScore;
}

/**
* @brief get the bpm match score
* @return bpm match score
*/
int SongMatchingParams::getBpmWeight() const
{
	return _bpmWeight;
}

/**
* @brief checks if the word is a uniqe word
* @param word - word to check
* @return true iff the word is a uniqe word
*/
bool SongMatchingParams::isUniqeWord(const std::string &word) const
{
	return (_uniqeWords.find(word) != _uniqeWords.end());
}

/**
* @brief get the avrege bpm match score
* @return avrege bpm match score
*/
double SongMatchingParams::getAvgBpm(const std::string &word) const
{
	return _uniqeWords.find(word)->second.first;
}

/**
* @brief get the devation bpm match score
* @return devation bpm match score
*/
double SongMatchingParams::getDeviationBpm(const std::string &word) const
{
	return _uniqeWords.find(word)->second.second;
}