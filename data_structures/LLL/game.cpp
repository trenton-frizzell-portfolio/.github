/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:	   Header file for program 2. Creates an abstract data type of
#		   		   a video game object. The public section contains a
#		   		   constructor, destructor, and functions to create and copy.
#		   		   The private section contains all of the data points for the
#		   		   game object.
#*****************************************************************************/

#include "game.h"

// default constructor	
s_game::s_game()
{
	char *title = nullptr;
	char *platform = nullptr;
	char *genre = nullptr;
	char *progression = nullptr;
	char *acheivements = nullptr;
	int rating = 0;
} 

// constructor
s_game::s_game(char *new_title, char *new_platform, char *new_genre, 
			   char *new_progression, char *new_acheivements, int new_rating)
{
	//set title to new title
	title = new char[strlen(new_title) + 1];
	strcpy(title, new_title);
	
	platform = new char[strlen(new_platform) + 1];
	strcpy(platform, new_platform);

	genre = new char[strlen(new_genre) + 1];
	strcpy(genre, new_genre);

	progression = new char[strlen(new_progression) + 1];
	strcpy(progression, new_progression);

	acheivements = new char[strlen(new_acheivements) + 1];
	strcpy(acheivements, new_acheivements);

	rating = new_rating;
}

s_game::~s_game() // destructor
{
}

int s_game::copy_game(const s_game &new_game)
{
	title = new char[strlen(new_game.title) + 1];
	strcpy(title, new_game.title);

	platform = new char[strlen(new_game.platform) + 1];
	strcpy(platform, new_game.platform);

	genre = new char[strlen(new_game.genre) + 1];
	strcpy(genre, new_game.genre);

	progression = new char[strlen(new_game.progression) + 1];
	strcpy(progression, new_game.progression);

	acheivements = new char[strlen(new_game.acheivements) + 1];
	strcpy(acheivements, new_game.acheivements);

	rating = new_game.rating;

	return 1;
}

int s_game::display()
{

	cout << title << " " << platform << " " << 
			genre << " " << progression << " " << 
			acheivements << " " << rating << endl;

	return 1;
}

