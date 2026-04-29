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

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

using namespace std;

class s_game
{
    public:
		s_game(); // default constructor	
		s_game(char *title, char *platform, char *genre, char *progression,
			   char *acheivements, int rating);
		~s_game(); // destructor
		int copy_game(const s_game & new_game);
		int display();
    private:
		char *title;
		char *platform;
		char *genre;
		char *progression;
		char *acheivements;
		int rating;
};

class q_game
{
    public:
		q_game();
		q_game(char *title, char *series, char *platform, char *genre, 
	    	   char *progression, char *acheivements, int rating);
		~q_game();
		int copy_game(const q_game & new_game);
		int display();
    private:
		char *title;
		char *series;
		char *platform;
		char *genre;
		char *progression;
		char *acheivements;
		int rating;
};

#endif
