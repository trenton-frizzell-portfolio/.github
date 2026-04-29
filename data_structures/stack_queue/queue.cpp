/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:     Header file for program 1. Creates a data structure for a
#		   		   linear linked list of amusement parks. For each place, there
#                  will be a linear linked list of activities you can do at
#		   		   that place. Allows you to add a venue, display venues,
#		   		   remove venues, add activities, and display activities.
#
#*****************************************************************************/

#include "queue.h"

queue_node::~queue_node()
{
//	if (queue_game) delete queue_game;
    next = nullptr;
}


queue::queue() // constructor
{
	rear = nullptr;
}


queue::~queue() // destructor
{
	queue_node *curr = rear->next;
	do // do while curr != rear next
	{
		queue_node *temp = curr;
		curr = curr->next;
		delete temp;
		temp = nullptr;
	} while (curr != rear->next);
	delete rear;
	rear = nullptr;
}


int queue::enqueue(const q_game &to_add)
{
	// rear is nullptr, no items. add first
	// and have it point to itself
	if (!rear) // no items
	{
		rear = new queue_node;
		rear->next = rear; // important
		rear->series_game.copy_game(to_add);
	}
	else // more than one item
	{
		queue_node *temp = rear->next; // hold onto front
		rear->next = new queue_node; // add new rear node	
		rear = rear->next; // traverse to it
		rear->next = temp; // connect
		rear->series_game.copy_game(to_add); // call copy
	} 

	return 1;
}


int queue::dequeue(q_game &to_remove)
{
	if (!rear) return 0;
	// If there is only one item, delete the node and set rear
	// to nullptr
	if (rear->next == rear)
	{
		//rear->series_game.copy_game(to_remove);			//FIXME seg fault
		delete rear;
		rear = nullptr;
	}
	// Otherwise, hold onto the front’s next, delete the front
	// (rear->next), and reconnect
	else
	{
		queue_node *temp = rear->next; // hold front
		rear->next = temp->next; // reconnect
		//temp->series_game.copy_game(to_remove);			//FIXME
		delete temp; // remove fronts node
	}
	return 1;
}


int queue::peek(q_game &result) const
{
	if(!rear) return 0;
	// peeking rear->next
	result.copy_game(rear->next->series_game);
	return 1;
}


int queue::display()
{
	if (!rear) return 0;

	display_header();

	return display(rear->next);
}


int queue::display(queue_node *rear)
{
	rear->series_game.display();
	if (rear == this->rear)
		return 1;
	else
		return display(rear->next);
}


int queue::display_header()
{
	cout << endl;
	cout << setw(10) << right << "Title" << setw(10) << right << "Series" <<
			setw(10) << right << "Platform" << setw(19) << right << "Genre" << 
			setw(15) << right << "progression" << setw(13) << right << 
			"Acheivements" << setw(8) << right << "Rating" << endl;
	cout << string(101, '-') << endl;

	return 1;
}
