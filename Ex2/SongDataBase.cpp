#include "SongDataBase.h"
#include "SortHelper.h"

#define MINIMAL_SCORE_TO_SHOW 0

/**
* @brief Constructor
* @param songsList - the list of all the songs
* @param songsParams - the ranking and scoring parameters object
*/
SongDataBase::SongDataBase(const std::vector<RankableSong*> &songsList, const SongMatchingParams &songsParams) :
_songsList(songsList), _songsParams(songsParams)
{

}

/**
* @brief Destructor
*/
SongDataBase::~SongDataBase()
{
	if(!_songsList.empty())
	{
		for (RankableSong* song : _songsList)
		{
			delete song;
			song = nullptr;
		}
		_songsList.clear();
	}
}

/**
* @brief prints out all the queries results
*/
void SongDataBase::_printQueryResults()
{
	SortHelper sorter;
	for (RankableSong* song : _songsList)
	{
		sorter.addItem(song->getScore());
	}

	std::vector<int> sortedSongs = sorter.getSortedOrderInVector();
	for (int  index = 0; index < sorter.size(); index++)
	{
		if (_songsList[sortedSongs[index]]->getScore() > MINIMAL_SCORE_TO_SHOW)
		{
			_songsList[sortedSongs[index]]->printData(std::cout);
		}
	}
}

/**
* @brief reset all scores
*/
void SongDataBase::_resetScores()
{
	for (RankableSong* song : _songsList)
	{
		song->resetScore();
	}
}

/**
* @brief run a single query
* @param query - the query
*/
void SongDataBase::runQuery(const std::string &query)
{
	//calculates all of the songs scores
	for (RankableSong* song : _songsList)
	{
		song->calcScore(query, _songsParams); // gets song score
	}

	_printQueryResults();
	_resetScores();
}