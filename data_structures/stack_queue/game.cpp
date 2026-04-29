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
s_game::s_game() : title(nullptr), platform(nullptr), genre(nullptr), 
				   progression(nullptr), acheivements(nullptr), rating (0)
{
	//char *title = nullptr;
	//char *platform = nullptr;
	//char *genre = nullptr;
	//char *progression = nullptr;
	//char *acheivements = nullptr;
	//int rating = 0;
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
	if(title) 
	{
		delete [] title;
	}
	title = nullptr;

	if(platform) 
	{
		delete [] platform;
	}
	platform = nullptr;

	if(genre) 
	{
		delete [] genre;
	}
	genre = nullptr;

	if(progression) 
	{
		delete [] progression;
	}
	progression = nullptr;

	if(acheivements) 
	{
		delete [] acheivements;
	}
	acheivements = nullptr;

	rating = 0;
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
  	cout << setw(19) << left << title << setw(17) << left << 
  	platform << setw(14) << left << genre << setw(13) << left << 
	progression << setw(12) << left << acheivements << setw(12) << 
	left << rating << endl;

	return 1;
}


// default constructor for queue game	
q_game::q_game() : title(nullptr), series(nullptr), platform(nullptr), 
				   genre(nullptr), progression(nullptr), acheivements(nullptr), rating(0)
{
	//char *title = nullptr;
	//char *series = nullptr;
	//char *platform = nullptr;
	//char *genre = nullptr;
	//char *progression = nullptr;
	//char *acheivements = nullptr;
	//int rating = 0;
} 


// QUEUE constructor
q_game::q_game(char *new_title, char *new_series, char *new_platform, 
			   char *new_genre, char *new_progression, char *new_acheivements, 
			   int new_rating)
{
	//set title to new title
	title = new char[strlen(new_title) + 1];
	strcpy(title, new_title);

	series = new char[strlen(new_series) + 1];
	strcpy(series, new_series);

	series = new char[strlen(new_series) + 1];
	strcpy(series, new_series);
	
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


q_game::~q_game() // destructor
{
	if(title) 
	{
		delete [] title;
	}
	title = nullptr;

	if(series) 
	{
		delete [] series;
	}
	series = nullptr;

	if(platform) 
	{
		delete [] platform;
	}
	platform = nullptr;

	if(genre) 
	{
		delete [] genre;
	}
	genre = nullptr;

	if(progression) 
	{
		delete [] progression;
	}
	progression = nullptr;

	if(acheivements) 
	{
		delete [] acheivements;
	}
	acheivements = nullptr;

	rating = 0;
}

int q_game::copy_game(const q_game &new_game)
{
	
	title = new char[strlen(new_game.title) + 1];
	strcpy(title, new_game.title);

	series = new char[strlen(new_game.series) + 1];
	strcpy(series, new_game.series);

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

int q_game::display()
{
  	cout << setw(19) << left << title << setw(17) << left << series <<
  	setw(17) << left << platform << setw(14) << left << genre << 
	setw(13) << left << progression << setw(12) << left << acheivements << 
	setw(12) << left << rating << endl;

	return 1;
}
