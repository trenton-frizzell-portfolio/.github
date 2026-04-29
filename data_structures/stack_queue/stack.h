/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:     Header file for program 2. Creates a stack data structure of
#				   a collection of video games. Contains a node to store the
#                  game object and a next pointer. Also contains a class with
#				   a pointer to head and stores an index to track the top of the
#				   list. The class contains member functions that allow the
#				   user to add, remove, and display from the list.
#*****************************************************************************/

#ifndef STACK_H
#define STACK_H

#include "game.h"

#define MAX 5

struct s_node
{
    s_game *entries;
    s_node *next;

	~s_node();
};


class stack
{
    public:
		stack();  // constructor
		~stack(); // destructor
		int push(const s_game &to_add);
		int pop();
		int peek(s_game &result) const;
		int display();
		int display(s_node *head, int index); 
		int display_header();

    private:
		s_node *head;
		int top_index;
};

#endif
