/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 1
# Date:            10/7/2024
# Description:     Main file for program 1. Creates a data structure for a
#		   linear linked list of amusement parks. For each place, there
#                  will be a linear linked list of activities you can do at
#		   that place.
#
#*****************************************************************************/

#include "Frizzell-Trenton-Prog1.h"

const int STR_SIZE = 100;
const char DAYS[7][10] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

int main () {

	CS_Fun fun_list;  // create a list

	char buffer[STR_SIZE];
	int choice = 0;
	bool success = false;
	//put char array here get rid of function



	cout << "\nWelcome to the fun park collection program." << endl;

	do {
		cout << "\nWhat would you like to do?\n"
			"\n1. Add a fun park"
			"\n2. Display all venues"
			"\n3. Add activity to a fun park"
			"\n4. List all activities for a venue"
			"\n5. Display all places that are open on a particular day"
			"\n6. Remove venue"
			"\n7. Quit\n" 
			"\nEnter choice value (1-7): ";
		cin >> choice;
		cin.clear();
		cin.ignore(STR_SIZE, '\n');

		switch(choice) {
			case 1:
			{

				venue to_add;
				
				cout << "Enter venue name: ";
				cin.get(buffer, STR_SIZE, '\n');	// use get instead of getline for char array
				cin.ignore(STR_SIZE, '\n');
				to_add.name = new char[strlen(buffer) + 1];
				strcpy(to_add.name, buffer); 

				
				cout << "Enter description: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.description = new char[strlen(buffer) + 1];
				strcpy(to_add.description, buffer);


				cout << "Enter operating hours: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.hours = new char[strlen(buffer) + 1];
				strcpy(to_add.hours, buffer);


				cout << "Enter location: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.location = new char[strlen(buffer) + 1];
				strcpy(to_add.location, buffer);

				 
				for (int i = 0; i < 7; i++)
				{
					cout << "Is the venue open on " << DAYS[i] << 
						" (1 for yes, 0 for no): ";
					cin >> to_add.is_open[i];
					//cin.ignore(STR_SIZE, '/n');
				}
			
				success = fun_list.add_venue(to_add);

				if (success)
					cout << "\nSuccessfully added." << endl;				
				else
					cerr << "\nAdd unsuccessful." << endl;

				break;
			}
			
			case 2: 
				success = fun_list.display_venues();

				if (!success)
					cerr << "\nNothing to display." << endl;
				break;

			case 3:
			{
				// create new activity struct
				activity activity_to_add;

				// enter venue to add to 
				cout << "Which venue would you like to add an activity to? ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');

				char * venue_to_find = new char[strlen(buffer) +1];
				strcpy(venue_to_find, buffer);


				// take in activity info
				cout << "Enter name of activity: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');

				activity_to_add.name = new char[strlen(buffer) + 1];
				strcpy(activity_to_add.name, buffer);


				cout << "Enter rules of activity: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');

				activity_to_add.rules = new char[strlen(buffer) + 1];
				strcpy(activity_to_add.rules, buffer); 


				int fun_level = 0;
				cout << "Enter fun level (1-5): ";
				cin >> fun_level;
				//cin.ignore(STR_SIZE, '\n');

				activity_to_add.fun_level = fun_level;

				success = fun_list.add_activity(venue_to_find, activity_to_add);

				if (success)
					cout << "\nSuccessfully added." << endl;				
				else
					cerr << "\nAdd unsuccessful." << endl;

				break;
			}

			case 4:
			{
				cout << "Display activities for which venue? ";

				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char * venue_to_find = new char[strlen(buffer) + 1];
				strcpy(venue_to_find, buffer);


				success = fun_list.display_activities(venue_to_find);

				if (!success)
					cerr << "\nNo activities to display." << endl;

				break;
			}
			case 5: 
			{	
				int search_day = -1;

				cout << "Which day would you like to search for which venues are open?\n"
					"Sunday = 0\n"
					"Monday = 1\n"
					"Tuesday = 2\n"
					"Wednesday = 3\n"
					"Thursday = 4\n"
					"Friday = 5\n"
					"Saturday = 6\n"
					"Enter choice value (0-6): ";
				cin >> search_day;

				success = fun_list.display_open_places(search_day);

				if (!success)
					cerr << "\nError" << endl;
				break;
			}

			case 6:
			{
				// remove
				cout << "Which venue would you like to remove? ";

				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char * venue_to_remove = new char[strlen(buffer) + 1];
				strcpy(venue_to_remove, buffer);

				success = fun_list.remove_venue(venue_to_remove);
				if (success)
					cout << "\nRemove success." << endl;				
				else
					cerr << "\nRemove fail." << endl;


				break;
			}

			case 7:
				break;

			default:
				cerr << "Invalid input, please try again.";
		}
	} while (choice != 7);
	
	cout << "\nThank you for using the fun park collection program." << endl;

	return 0;
}
