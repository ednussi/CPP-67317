/**
* @file Song.h
* @author  ednussi
* @date 06/09/2015
*
* @brief A Song class
*
* @section LICENSE
* free for everyone
*
* @section DESCRIPTION
* An abstract song class containning the song most basic parameters
*/

#ifndef SONG_H
#define SONG_H

#include <unordered_map>
#include <sstream>

typedef std::unordered_map<std::string, int> TagsMap;

/**
* @class Song
* @brief An abstract song class containning the song most basic parameters
*/
class Song
{
	protected:
		std::string _title;
		TagsMap _tagsMap;

		/**
		* @brief initializes a tags list
		* @param tagsData - a string containning the data about tags
		*/
		void initializeTagsMap(const std::string &tagsData);

	public:

		/**
		* @brief Constructor
		* @param title - it's title
		* @param tagsData - it's tagsData
		*/
		Song(const std::string &title, const std::string &tagsData);

		/**
		* @brief Destructor
		*/
		virtual ~Song(){};
};

#endif

