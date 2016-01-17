#include "Song.h"


/**
* @brief initializes a tags list
* @param tagsData - a string containning the data about tags
*/
void Song::initializeTagsMap(const std::string &tagsData)
{
	std::istringstream iss(tagsData);
	std::string tag;
	int tagValue;
	while (iss >> tag)
	{
		while (iss >> tagValue)
		{
			// cout << "tag is: " << tag << " tagValue is: " << tagValue << endl;
			_tagsMap.insert({ tag, tagValue });
			break;
		}
	}
}

/**
* @brief Constructor
* @param title - it's title
* @param tagsData - it's tagsData
*/
Song::Song(const std::string &title, const std::string &tagsData) : _title(title)
{
	initializeTagsMap(tagsData);
}
