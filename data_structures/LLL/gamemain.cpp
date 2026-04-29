/******************************************************************************
# Name:            Trenton Frizzell, tfrizz2@pdx.edu
# Assignment:      Program 2
# Date:            10/21/2024
# Description:     Client program for project 2. 
#
#*****************************************************************************/

#include "stack.h"
#include "queue.h"

using namespace std;

#define STR_SIZE 100

int main () {

	stack stack_list;  // create a list

	char buffer[STR_SIZE];
	int rating = 0;
	int choice = 0;
	int success = -1;
	//put char array here get rid of function



	cout << "\nLet's categorize your games." << endl;

	do {
		cout << "\nWhat would you like to do?\n"
			"\n1. Add non-series game"
			"\n2. Display non-series games"
			"\n3. Pop"
			"\n4. Peek"
			"\n5. "
			"\n6. "
			"\n7. Quit\n" 
			"\nEnter choice value (1-7): ";
		cin >> choice;
		cin.clear();
		cin.ignore(STR_SIZE, '\n');

		switch(choice) {
			case 1:
			{
				//s_game to_add;
				
				char title[4] = {'H', 'A', 'L', 'O'};
				char platform[5] = {'X', '-', 'B', 'O', 'X'};
				char genre[3] = {'F', 'P', 'S'};
				char progression[4] = {'A', 'B', 'C', 'D'};
				char acheivements[4] = {'E', 'F', 'G', 'H'};
				s_game to_add(title, platform , genre, progression, acheivements, 10);
				
				
				
				
				/*
				cout << "Enter game title: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.title = new char[strlen(buffer) + 1];
				strcpy(to_add.title, buffer); 

				
				cout << "What platform: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.platform = new char[strlen(buffer) + 1];
				strcpy(to_add.platform, buffer);


				cout << "What genre: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.genre = new char[strlen(buffer) + 1];
				strcpy(to_add.genre, buffer);


				cout << "Progression: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.progression = new char[strlen(buffer) + 1];
				strcpy(to_add.progression, buffer);


				cout << "Acheivements: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				to_add.acheivements = new char[strlen(buffer) + 1];
				strcpy(to_add.acheivements, buffer);

				cout << " Rate the game (1-5): ";
				cin >> to_add.rating;
				*/
				
				to_add.display();


				success = stack_list.push(to_add);


				if (success == 1)
					cout << "success" << endl;

				break;
			}
			case 2:
				//display();
				stack_list.display();

				break;
			case 3:
				success = stack_list.pop();
				if (success == 1)
					cout << "success" << endl;
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
		}
	} while (choice != 7);

	return 0;
}
