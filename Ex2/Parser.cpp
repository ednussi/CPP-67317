#include "Parser.h"
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

const std::string SEPARATOR = "=";
const std::string END_OF_SONGS = "***";
const std::string TITLE = "title";
const std::string TAGS = "tags";
const std::string LYRICS = "lyrics";
const std::string LYRICS_BY = "lyricsBy";
const std::string INSTRUMENTS = "instruments";
const std::string PERFORMED_BY = "performedBy";
const std::string BPM = "bpm";
const std::string TAG_MATCH_SCORE = "tagMatchScore";
const std::string LYRICS_MATCH_SCORE = "lyricsMatchScore";
const std::string INSTRUMENT_MATCH_SCORE = "instrumentMatchScore";
const std::string BPM_WEIGHT = "bpmLikelihoodWeight";

typedef std::vector<RankableSong*> SongList;

/**
* @brief get the list of words from a given string
* @param line - line to get the wordlist from
* @return the word list in a string
*/
std::string Parser::_getWordList(const std::string &line)
{

	size_t pos1 = line.find("{");
	size_t pos2 = line.find("}");

	return line.substr(pos1 + 1, pos2 - pos1 - 1);
}

/**
* @brief builds a vector of all queries
* @param queriesFile - the name of the queries file
* @return a vector of all queries
*/
std::vector<std::string> Parser::buildQueriesList(const std::string &queriesFile)
{
	std::ifstream instream(queriesFile.c_str());

	std::string query = "";
	std::vector<std::string> queriesList;

	while (instream >> query)
	{
		if (query != "\n")
		{
			queriesList.push_back(query);
		}
	}

	return queriesList;
}

/**
* @brief builds a vector of all the diffrent kinds of songs given
* @param songDataFile - the name of the song data file
* @return a vector of the songs
*/
std::vector<RankableSong*> Parser::buildSongDataBase(const std::string &songDataFile)
{
	std::ifstream instream(songDataFile.c_str());

	std::string line = "";

	int lastSong = 0;
	SongList songList;

	while (instream.good() && !lastSong)
	{
		if (line.compare(SEPARATOR) != 0)
		{
			getline(instream, line);
			// Expect a line of "="
			if (END_OF_SONGS.compare(line) == 0)
			{
				lastSong = 1;
				break;
			}

		}

		getline(instream, line);
		// Expect a line of "title: ..."
		size_t pos = TITLE.size() + 2;
		std::string title = line.substr(pos);

		getline(instream, line);
		// Expect a line of "tags: {...}"
		std::string tags = _getWordList(line);

		std::string lyrics = "";
		std::string lyricsBy = "";
		std::string instruments = "";
		std::string performedBy = "";
		std::string bpmStr = "0";

		getline(instream, line);
		// Expect either lyrics or instruments.
		if (line.substr(0, LYRICS.size()).compare(LYRICS) == 0)
		{
			// Then we have a lyric song
			// Lets get the lyrics:
			lyrics = _getWordList(line);

			// Lets get the lyricsBy:
			getline(instream, line);
			pos = LYRICS_BY.size() + 2;
			lyricsBy = line.substr(pos);

			// insert to dataBase
			songList.push_back(new RankableLyricSong(title, tags, lyrics, lyricsBy));
		}
		else
		{
			// Then we have an instrumental song
			// Lets get the instruments:
			instruments = _getWordList(line);

			// Lets get the performedBy:
			getline(instream, line);
			pos = PERFORMED_BY.size() + 2;
			performedBy = line.substr(pos);

			// Lets see if we have bpm:
			if (!instream.good())
			{
				break;
			}
			getline(instream, line);
			if (END_OF_SONGS.compare(line) == 0)
			{
				lastSong = 1;
			}


			if (line.substr(0, BPM.size()).compare(BPM) == 0)
			{
				pos = BPM.size() + 2;
				bpmStr = line.substr(pos);
			}
			else
			{
				assert((line.compare(SEPARATOR) == 0) || (line.compare(END_OF_SONGS) == 0));
			}

			songList.push_back(new RankableInstrumentalSong(title, tags, instruments, performedBy, bpmStr));
		}
	}

	instream.close();

	return songList;

}

/**
* @brief builds a song matching parameters file from the given info
* @param parametersFile - the name of the parameters data file
* @return a songMatchingParams object with the initialized data
*/
SongMatchingParams Parser::buildSongMatchParametrs(const std::string &parametersFile)
{
	std::ifstream instream(parametersFile.c_str()); 

	std::string currentLine;
	size_t pos;
	int tagMatchScore, lyricsMatchScore, instrumentMatchScore, bpmWeight;

	// gets the tagMatchScore
	getline(instream, currentLine);
	pos = TAG_MATCH_SCORE.size() + 2;
	tagMatchScore = stoi(currentLine.substr(pos));

	// gets the lyricsMatchScore
	getline(instream, currentLine);
	pos = LYRICS_MATCH_SCORE.size() + 2;
	lyricsMatchScore = stoi(currentLine.substr(pos));

	// gets the instrumentMatchScore
	getline(instream, currentLine);
	pos = INSTRUMENT_MATCH_SCORE.size() + 2;
	instrumentMatchScore = stoi(currentLine.substr(pos));

	// gets the bpmWeight
	getline(instream, currentLine);
	pos = BPM_WEIGHT.size() + 2;
	bpmWeight = stoi(currentLine.substr(pos));

	// gets the uniqe words vals
	double avgBpm, deviationBpm;
	std::map<std::string, std::pair<double, double>> uniqeWords;
	std::string word;
	std::pair<double, double> wordValues;
	std::pair<std::string, std::pair<double, double>> mapElement;
	while (getline(instream, currentLine))
	{
		if ((currentLine != "\n") && (currentLine != ""))
		{
			pos = currentLine.find(":");
			word = currentLine.substr(0, pos);
			currentLine = currentLine.substr(pos + 1, std::string::npos);
			pos = currentLine.find(",");
			avgBpm = stod(currentLine.substr(0, pos));
			deviationBpm = stod(currentLine.substr(pos + 1, std::string::npos));
			wordValues = std::pair<double, double>(avgBpm, deviationBpm);
			mapElement = std::pair<std::string, std::pair<double, double>>(word, wordValues);
			uniqeWords.insert(mapElement);
		}
	}

	SongMatchingParams songMatchingParams(uniqeWords, tagMatchScore, instrumentMatchScore, lyricsMatchScore,
		bpmWeight);
	return songMatchingParams;
}