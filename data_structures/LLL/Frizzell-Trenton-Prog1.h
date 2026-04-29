/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 1
# Date:            10/7/2024
# Description:     Header file for program 1. Creates a data structure for a
#		   linear linked list of amusement parks. For each place, there
#                  will be a linear linked list of activities you can do at
#		   that place. Allows you to add a venue, display venues,
#		   remove venues, add activities, and display activities.
#
#*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

using namespace std;

const int DAYS_OF_WEEK = 7;

struct venue
{
	char * name;
	char * description;
	char * hours;
	char * location;
	bool is_open[7];
	//~venue();
};

struct activity
{
	char * name;
	char * rules;
	int fun_level;
	//~activity();
};

struct activity_node
{
	activity anActivity;
	activity_node * next;
};

struct venue_node
{
	venue aVenue;
	venue_node * next;
	activity_node * head;
};

class CS_Fun
{
	public:
		CS_Fun();  // default constructor, submission 1
		~CS_Fun(); // destructor
		// methods
		bool add_venue(const venue & to_add); // submission 1
		bool display_venues(); // submission 1				
		bool remove_venue(char to_remove[]);
		bool add_activity(char search_name[], const activity & to_add);
		bool display_activities(char name_place[]) const;
		bool display_open_places(int search_day);
		// create deep copy function
		bool copy_from(const venue & to_copy);
	private:
		bool display_venues(venue_node *& head); // display venues recursive
		venue_node * head; // venue head ptr
};

