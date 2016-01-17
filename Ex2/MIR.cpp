/**
* @file MIR.cpp
* @author  ednussi
* @date 06/09/2015
*
* @brief A Manager forfile for a MIR system
*
* @section LICENSE
* free for everyone
*/

#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define SUCCESS 0
#define FAIL 1
#define CORRECT_PARA_NUM 4
#define SONG_DATA_FILE 1
#define PARAMETERS_DATA_FILE 2
#define QUERIES_DATA_FILE 3
#define QUERY_WORD "Query word: "
#define USAGE "Usage: MIR < songs file name > < parameters file name > < queries file name >"
#define ERROR_CANT_OPEN "Error! Can't open file: "
const std::string NEW_QUERY_SEPERATOR = "----------------------------------------";

typedef std::vector<std::string> QueriesList;

/**
* @brief run all the queries given one by one - prints out the resaults in
* 		 needed order for each query
* @param queriesList - the list of the queries
* @param songsDataBase - the initialized data base with all songs and parameters for 
*						 rating the scores
*/
void runQueries(const QueriesList &queriesList, SongDataBase &songsDataBase)
{
	for (std::string query : queriesList)
	{
		std::cout << NEW_QUERY_SEPERATOR << std::endl << QUERY_WORD << query << std::endl << std::endl;
		songsDataBase.runQuery(query);
	}
}

bool checkQueries(std::string queriesFile)
{
	std::ifstream instream(queriesFile.c_str());
	if (!instream.is_open())
	{
		return false;
	}

	return true;
}

bool checkArgs(int argc, char* argv[])
{
	bool returnVal = true;

	if (argc != CORRECT_PARA_NUM)
	{
		std::cerr << USAGE << std::endl;
		return false;
	}

	std::ifstream instreamPara(argv[PARAMETERS_DATA_FILE]);
	if (!instreamPara.is_open())
	{
		std::cerr << ERROR_CANT_OPEN << argv[PARAMETERS_DATA_FILE] << "." << std::endl;
		returnVal = false;
	}

	std::ifstream instreamSongs(argv[SONG_DATA_FILE]);
	if (!instreamSongs.is_open())
	{
		std::cerr << ERROR_CANT_OPEN << argv[SONG_DATA_FILE] << "." << std::endl;
		returnVal = false;
	}

	if (!checkQueries(argv[QUERIES_DATA_FILE]))
	{
		std::cerr << ERROR_CANT_OPEN << argv[QUERIES_DATA_FILE] << "." << std::endl;
		returnVal = false;
	}

	return returnVal;
}

/**
* @brief Main Function which runs the MIR system
* @return 0 if all went OK
*/
int main(int argc, char* argv[])
{
	if (checkArgs(argc, argv))
	{
		SongDataBase songsDataBase(Parser::buildSongDataBase(std::string(argv[SONG_DATA_FILE])),
			Parser::buildSongMatchParametrs(std::string(argv[PARAMETERS_DATA_FILE])));
		// run on all queries
		runQueries(Parser::buildQueriesList(std::string(argv[QUERIES_DATA_FILE])), songsDataBase);
		return SUCCESS;
	}

	if (checkQueries(std::string(argv[QUERIES_DATA_FILE])))
	{
		std::ifstream instream(argv[PARAMETERS_DATA_FILE]);
		std::string query;
		while (!instream.eof())
		{
			getline(instream, query);

			if (query.length() == 0 || !instream.good())
			{
				break;
			}

			std::cout << NEW_QUERY_SEPERATOR << QUERY_WORD << std::endl << std::endl;
		}
	}

	return FAIL;
} 