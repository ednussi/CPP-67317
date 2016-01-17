/**
* @file SongMatchingParams.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A SongMatchingParams class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* conatins all songs parametrs in order to rank and see a rankable song score
*/

#ifndef SONG_MATCHING_PARAMS_H
#define SONG_MATCHING_PARAMS_H

#include <map>
#include <string>

#define DEF_TAG_MATCH_SCORE 0
#define DEF_INSTRUMENT_MATCH_SCORE 0
#define DEF_LYRICS_MATCH_SCORE 0
#define DEF_BPM_MATCH_SCORE 0

typedef std::map<std::string, std::pair<double, double>> UniqeWordsMap;

/**
* @class SongMatchingParams
* @brief conatins all songs parametrs in order to rank and see a rankable song score
*/
class SongMatchingParams
{

	private:
		int _tagMatchScore;
		int _lyricsMatchScore;
		int _instrumentMatchScore;
		int _bpmWeight;
		UniqeWordsMap _uniqeWords;

	public:

		/**
		* @brief Constructor.
		* @param uniqeWords - the list of uniqe words which have a devation and avrg bpm
		* @param tagMatchScore - the tags match score
		* @param instrumentMatchScore - the instrumentals match score if exists
		* @param lyricsMatchScore - the lyrics match score if they exsits
		* @param bpmWeight - the score of the bpm if exists
		*/
		SongMatchingParams(
			const UniqeWordsMap &uniqeWords = UniqeWordsMap(),
			int tagMatchScore = DEF_TAG_MATCH_SCORE,
			int instrumentMatchScore = DEF_INSTRUMENT_MATCH_SCORE,
			int lyricsMatchScore = DEF_LYRICS_MATCH_SCORE,
			int bpmWeight = DEF_BPM_MATCH_SCORE);

		/**
		* @brief Destructor
		*/
		~SongMatchingParams(){};

		/**
		* @brief get the tag match score
		* @return tag match score
		*/
		int getTagMatchScore() const;

		/**
		* @brief get the lyrics match score
		* @return lyrics match score
		*/
		int getLyricsMatchScore() const;

		/**
		* @brief get the instrumet match score
		* @return instrumet match score
		*/
		int getInstrumentMatchScore() const;

		/**
		* @brief get the bpm match score
		* @return bpm match score
		*/
		int getBpmWeight() const;

		/**
		* @brief checks if the word is a uniqe word
		* @param word - word to check
		* @return true iff the word is a uniqe word
		*/
		bool isUniqeWord(const std::string &word) const;

		/**
		* @brief get the avrege bpm match score
		* @return avrege bpm match score
		*/
		double getAvgBpm(const std::string &word) const;

		/**
		* @brief get the devation bpm match score
		* @return devation bpm match score
		*/
		double getDeviationBpm(const std::string &word) const;
};

#endif