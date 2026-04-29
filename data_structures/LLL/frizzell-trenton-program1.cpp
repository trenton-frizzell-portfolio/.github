/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 1
# Date:            10/7/2024
# Description:     .cpp file for program 1. Implements a data structure for a
#		   linear linked list of amusement parks. For each place, there
#                  will be a linear linked list of activities you can do at
#		   that place.
#
#*****************************************************************************/

#include "Frizzell-Trenton-Prog1.h"


CS_Fun::CS_Fun()  // default constructor // submission 1
{
	head = nullptr;
}


// destructor not required till finished product
CS_Fun::~CS_Fun()
{
	activity_node * activity_hold;

	venue_node * venue_hold = head;

	while (head)
	{
		venue_hold = head->next;

		activity_hold = head->head;
		while (activity_hold)
		{
			activity_node * temp = activity_hold;
			activity_hold = activity_hold->next;
			if(temp->anActivity.name)
			{
				delete [] temp->anActivity.name;
			}
			if(temp->anActivity.rules)
			{
				delete [] temp->anActivity.rules;
			}

			delete temp;
		}
		if(head->aVenue.name)
		{
			delete [] head->aVenue.name;
		}
		if(head->aVenue.description)
		{
			delete [] head->aVenue.description;
		}
		if(head->aVenue.hours)
		{
			delete [] head->aVenue.hours;
		}
		if(head->aVenue.location)
		{
			delete [] head->aVenue.location;
		}

		delete head;
		head = venue_hold;
	}
	head = nullptr;
}


//~venue::venue() {}

//~activity::activity(){}


// methods
// Adds a new place/venue
bool CS_Fun::add_venue(const venue & to_add) 
{
	/*
	create new node
	venue_node * temp = new venue_node;

	if list is empty
		add first item

	if name already exists
		return false

	if items in list 
		add new item to beginning of list 
		temp->next = head;
		head = temp;
		delete temp;
	*/

	/*     trying to make deep copy
	venue_node * temp = new venue_node;	// create new instance of venue node
	
	temp->aVenue = new venue_node;
	temp->aVenue.copy_from(to_add);
	temp->head = nullptr;			// set aVenue head to null
	temp->next = nullptr;

	
	*/     //  OLD CODE  //
	venue_node * temp = new venue_node;
	temp->aVenue = to_add;
	temp->head = nullptr;
	temp->next = nullptr;	
	

	if (!head)				// if no items in LLL
	{
		head = temp;			// assign head to the new item
		return true;
	}

	venue_node * curr = head;		// create new node for traversal

	while (curr->next)			// traverse the list
	{
		if(strcmp(temp->aVenue.name, curr->aVenue.name) == 0) // look for match
		{
			delete temp;		// if found, delete the new item
			return false;
		}
		curr = curr->next;		// go to next item, continue traversal
	}
	// arrive at end of list
	// checking for duplicate again in the case of only one item in list
	if(strcmp(temp->aVenue.name, curr->aVenue.name) == 0)
	{
		delete temp;
		return false;
	}

	curr->next = temp;			// adds new item to the end of the list

	return true;
}


// create copy function
bool CS_Fun::copy_from(const venue & to_copy)
{/*
	venue * this_venue = new venue;
	this_venue.name = new char[strlen(to_copy.name) + 1];
	strcpy(this_venue.name, to_copy.name);*/
	
	return true;
}


// Display all venues
bool CS_Fun::display_venues()
{
	if (!head) return false;
	display_venues(head);
	return true;
}


// Remove a particular place
bool CS_Fun::remove_venue(char to_remove[])
{
	venue_node * curr = head;

	// no items in list
	if (!head) return false;
	
	// 1 item in list case
	//if (head->next == nullptr) 
	//{
		if (strcmp(to_remove, head->aVenue.name) == 0)
		{
			curr = head;
			head = head->next;
			delete curr;
			// if match delete head
			//delete head;
			// head nullptr
			//head = nullptr;
			// delete after test
			return true;
		}
	//}
	// many items in list
	venue_node * prev = head;
	while(curr) {
		// compare passed in name with node name
		if (strcmp(to_remove, curr->aVenue.name) == 0) 
		{
			prev->next = curr->next;
			delete curr;
			return true;
		}
		prev = curr;
		curr = curr->next;
	}
	return false;
}


// Add an Activity for a particular venue
bool CS_Fun::add_activity(char search_name[], const activity & to_add) 
{
	// create a new activity node to hold the activity we want to add
	activity_node * temp = new activity_node;
	temp->anActivity = to_add;
	temp->next = nullptr;

	// search list of venues for match, case insensitive
	venue_node * curr = head;

	// loop venues
	while(curr)
	{
	    // check for name match
	    if(strcmp(search_name, curr->aVenue.name) == 0)
	    {
		//if match, add activity
		activity_node * current = curr->head;
		activity_node * prev = nullptr;	

		// while in list AND to add is alphabetically BEFORE
		while(current && strcmp(to_add.name, current->anActivity.name) > 0)
		{
		    prev = current;
		    current = current->next;
		}
		// arrived at insert location
		if (prev == nullptr)
		{
                    // if prev is null, it means we never entered the while loop above
                    // this happens when the list is empty or the new activity should be first
                    // Insert at the beginning of the list
                    temp->next = curr->head;
                    curr->head = temp;
            	}
            	else
            	{
                    // Insert in the middle or at the end
                    temp->next = current;
                    prev->next = temp;
            	}
	    // Successfully added
            return true;
            }
		// didnt find matching venue, move to next venue
        	curr = curr->next;
    	}
    	// no matching matching venue
    	delete temp;

    	return false;	
}


// Display all of the Activities for a particular venue  
bool CS_Fun::display_activities(char name_place[]) const 
{
	//search list of venues for a match
	venue_node * curr = head;
	// while still in VENUE list
	while(curr)
	{
		//compare search name with list of venue names
		if(strcmp(name_place, curr->aVenue.name) == 0)
		{
			cout << "Venue found!" << endl;
			//create node to traverse activities
			activity_node * current = curr->head;

			// if list is empty
			if (!curr->head) return false;

			// traverse activities to print
			// while at top of activities list
			while(current)
			{
				cout << "\nActivity name: " << current->anActivity.name << endl;
				cout << "Rules: " << current->anActivity.rules << endl;
				cout << "Fun level: " << current->anActivity.fun_level << endl;
				current = current->next;
			}
			return true;
		}
		curr = curr->next;
	}
	return false;
}



// function for displaying all places that are open on a particular day
bool CS_Fun::display_open_places(int search_day) 
{
	//compare search 
	venue_node * curr = head;

	// invalid input
	if (search_day < 0 || search_day > 6) return false;

	// empty list
	if (!curr) return false;

	// if list
	while (curr)
	{
		if (curr->aVenue.is_open[search_day] == true)
		{
			cout << "\n" <<  curr->aVenue.name << 
			" is open on the given day." << endl;
		}
		curr = curr->next;
	}
	return true;	
}



// recursive function for display venues
bool CS_Fun::display_venues(venue_node *& head) 
{
	// base case nothing to return 
	if(!head) return true;
	
	cout << "\npark name: " << head->aVenue.name << endl;
	cout << "description: " << head->aVenue.description << endl;
	cout << "hours: " << head->aVenue.hours << endl;
	cout << "location: " << head->aVenue.location << endl;

	return display_venues(head->next); // recursive call
}
