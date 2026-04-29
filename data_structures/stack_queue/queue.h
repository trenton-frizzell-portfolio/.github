/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:     Header file for program 2. Creates a queue data structure
#		   		   of a collection of video games. Contains a node to store the
#                  game object and a next pointer. Also contains a class with
#		   		   a pointer to rear as well as member functions that allow
#		   		   the user to add, remove, and display from the list.
#*****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include "game.h"

struct queue_node
{
    q_game series_game;
    queue_node *next;

	~queue_node();
};


class queue
{
    public:
		queue(); // constructor
		~queue(); // destructor
		int enqueue(const q_game &to_add);
		int dequeue(q_game &to_remove);
		int peek(q_game &result) const;
		int display();
		int display(queue_node *rear);
		int display_header();
    private:
		queue_node *rear;
};

#endif
