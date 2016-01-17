/**
* @file Pasrser.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A Parser class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* A parser objects which is the only one known with files inner logic 
* and order of the given information within the files
*/

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstdio>
#include "RankableInstrumentalSong.h"
#include "RankableLyricSong.h"
#include "SongMatchingParams.h"
#include "SongDataBase.h"

/**
* @class Parser
* @brief A parser objects which is the only one known with files inner logic 
* and order of the given information within the files
*/
class Parser
{
	private:

		/**
		* @brief Constructor
		*/
		Parser(){};

		/**
		* @brief Destructor
		*/
		~Parser(){};

		/**
		* @brief get the list of words from a given string
		* @param line - line to get the wordlist from
		* @return the word list in a string
		*/
		static std::string _getWordList(const std::string &line);
		
	public:

		/**
		* @brief builds a vector of all the diffrent kinds of songs given
		* @param songDataFile - the name of the song data file
		* @return a vector of the songs
		*/
		static std::vector<RankableSong*> buildSongDataBase(const std::string &songDataFile);

		/**
		* @brief builds a song matching parameters file from the given info
		* @param parametersFile - the name of the parameters data file
		* @return a songMatchingParams object with the initialized data
		*/
		static SongMatchingParams buildSongMatchParametrs(const std::string &parametersFile);

		/**
		* @brief builds a vector of all queries
		* @param queriesFile - the name of the queries file
		* @return a vector of all queries
		*/
		static std::vector<std::string> buildQueriesList(const std::string &queriesFile);

};

#endif


