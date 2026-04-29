/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:     Implementation file for stack.h. 
#
#
#*****************************************************************************/

#include "stack.h"


s_node::~s_node()
{
	if (entries) delete [] entries;
	entries = nullptr;
	next = nullptr;	
}


stack::stack() // constructor
{
    head = nullptr;
    top_index = 0;
}


stack::~stack() // destructor
{
	while (head)
	{
		s_node* temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
}


int stack::push(const s_game &to_add)
{
    // if no list OR list maxed out
    if (!head || top_index == MAX)
    {
		s_node *temp = head;
		head = new s_node;
		head->next = temp;
		head->entries = new s_game[MAX];
		top_index = 0;
    }
    head->entries[top_index].copy_game(to_add);
    ++top_index;

	return 1;
}


int stack::pop()
{
	if (!top_index) 
	{
		return 0;
	}
	s_node *hold = head->next;
	// if no top index
	if (!top_index)
	{
		// check if there is another stack
		if (head->entries)
		{
			delete [] head->entries;
			delete head;
			head = hold;
			top_index = MAX;
		}
	}
	// deletes top item
	--top_index;

	return 1;
}


int stack::peek(s_game &found_at_top) const
{
	// head is null ptr
	if (!head) return 0;	
	// top index is 0, then the top of the stack is at
	// index 4 for the next node. If head->next is 
	// nullptr, then there is nothing to do, return fail
	if (top_index == 0)
	{
		if (head->next == nullptr)
			return 0;
		// access previous stack
		found_at_top.copy_game(head->next->entries[MAX - 1]);
	}
	// OTHERWISE the top of the stack is at top index - 1 location of heads array
	else
		found_at_top.copy_game(head->entries[top_index - 1]);

	return 1;
}


int stack::display() // wrapper	
{
	if (!head) return 0; // no items

	display_header();

	return display(head, top_index);
}


int stack::display(s_node *head, int index) // recursive   
{
	if (!head) return 0; // no items

	for (int i = index - 1; i >= 0; i--) // if list is full
	{
		head->entries[i].display(); 
	}
	return display(head->next, MAX);
}

int stack::display_header()
{
	cout << endl;
	cout << setw(10) << right << "Title" << setw(18) << right << "Platform" <<             
           setw(19) << right << "Genre" << setw(15) << right <<     
           "progression" << setw(13) << right << "Acheivements" << 
           setw(8) << right << "Rating" << endl;
	cout << string(101, '-') << endl;
	return 1;
}
