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
	queue queue_list;

	char buffer[STR_SIZE];
	int rating = 0;
	int choice = 0;
	int success = -1;


	cout << "\nLet's categorize your games." << endl;

	do {
		cout << "\nWhat would you like to do?\n"
			"\n1. Push (non-series game)"
			"\n2. Display (non-series games)"
			"\n3. Pop"
			"\n4. Peek (non-series game)"
			"\n5. Enqueue (series game)"
			"\n6. Display (series games)"
			"\n7. Dequeue"
			"\n8. Peek (series game)"
			"\n9. Quit\n" 
			"\nEnter choice value (1-9): ";
		cin >> choice;
		cin.clear();
		cin.ignore(STR_SIZE, '\n');

		switch(choice) {
			case 1:
			{
				/*
				char t[4] = {'H', 'A', 'L', 'O'};
				char *title = new char[strlen(t) + 1];
				strcpy(title, t);  
				char p[5] = {'X', '-', 'B', 'O', 'X'};
				char *platform = new char[strlen(p) + 1];
				strcpy(platform, p); 
				char g[3] = {'F', 'P', 'S'};
				char *genre = new char[strlen(g) + 1];
				strcpy(genre, g); 
				char pr[6] = {'L', 'I', 'N', 'E', 'A', 'R'};
				char *progression = new char[strlen(pr) + 1];
				strcpy(progression, pr); 
				char a[4] = {'N', 'O', 'N', 'E'};
				char *acheivements = new char[strlen(a) + 1];
				strcpy(acheivements, a); 
				s_game to_add(title, platform , genre, progression, acheivements, 10);
				*/
				
				//s_game to_add;
				//    USER INPUT FOR GAMES        COMPLETE (uncomment to use)
				cout << "Enter game title: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *title = new char[strlen(buffer) + 1];
				strcpy(title, buffer); 

				
				cout << "What platform: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *platform = new char[strlen(buffer) + 1];
				strcpy(platform, buffer);


				cout << "What genre: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *genre = new char[strlen(buffer) + 1];
				strcpy(genre, buffer);


				cout << "Progression: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *progression = new char[strlen(buffer) + 1];
				strcpy(progression, buffer);


				cout << "Acheivements: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *acheivements = new char[strlen(buffer) + 1];
				strcpy(acheivements, buffer);

				cout << "Rate the game (1-5): ";
				cin >> rating;
				
				s_game to_add(title, platform , genre, progression, acheivements, rating);
			
				// here to check if constructor is working
				stack_list.display_header();
				to_add.display();

				success = stack_list.push(to_add);


				if (success == 1)
					cout << "success" << endl;


				// delete items after passed in to constructor
				delete [] title;
				title = nullptr;

				delete [] platform;
				platform = nullptr;

				delete [] genre;
				genre = nullptr;

				delete [] progression;
				progression = nullptr;

				delete [] acheivements;
				acheivements = nullptr;
				

				break;
			}
			case 2:
			{
				success = stack_list.display();
		
				if (success == 0)
					cout << "Nothing to display" << endl;

				break;
			}
			case 3:
			{
				success = stack_list.pop();

				if (success == 1)
					cout << "success" << endl;
				else
					cout << "fail" << endl;

				break;
			}
			case 4:
			{
				s_game peek_game;
				success = stack_list.peek(peek_game);

				if (success == 1)
				{
					cout << "success" << endl;
					stack_list.display_header();
					peek_game.display();
				}

				break;
			}
			case 5:
			{
				/*
				char t[4] = {'H', 'A', 'L', 'O'};
				char *title = new char[strlen(t) + 1];
				strcpy(title, t);
				char s[4] = {'H', 'A', 'L', 'O'};
				char *series = new char[strlen(s) + 1];
				strcpy(series, s);
				char p[5] = {'X', '-', 'B', 'O', 'X'};
				char *platform = new char[strlen(p) + 1];
				strcpy(platform, p); 
				char g[3] = {'F', 'P', 'S'};
				char *genre = new char[strlen(g) + 1];
				strcpy(genre, g); 
				char pr[6] = {'L', 'I', 'N', 'E', 'A', 'R'};
				char *progression = new char[strlen(pr) + 1];
				strcpy(progression, pr); 
				char a[4] = {'N', 'O', 'N', 'E'};
				char *acheivements = new char[strlen(a) + 1];
				strcpy(acheivements, a); 
				q_game to_add(title, series, platform , genre, progression, acheivements, 10);
				*/

				//q_game to_add;
				//    USER INPUT FOR GAMES        COMPLETE (uncomment to use)
				cout << "Enter game title: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *title = new char[strlen(buffer) + 1];
				strcpy(title, buffer); 

				cout << "Series name: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *series = new char[strlen(buffer) + 1];
				strcpy(series, buffer);
				
				cout << "What platform: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *platform = new char[strlen(buffer) + 1];
				strcpy(platform, buffer);


				cout << "What genre: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *genre = new char[strlen(buffer) + 1];
				strcpy(genre, buffer);


				cout << "Progression: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *progression = new char[strlen(buffer) + 1];
				strcpy(progression, buffer);


				cout << "Acheivements: ";
				cin.get(buffer, STR_SIZE, '\n');
				cin.ignore(STR_SIZE, '\n');
				char *acheivements = new char[strlen(buffer) + 1];
				strcpy(acheivements, buffer);

				cout << "Rate the game (1-5): ";
				cin >> rating;
				
				q_game to_add(title, series, platform , genre, progression, acheivements, rating);

				// show game just added
				queue_list.display_header();
				to_add.display();

				success = queue_list.enqueue(to_add);

				if (success == 1)
					cout << "success" << endl;
				
				delete [] title;
				title = nullptr;

				delete [] series;
				series = nullptr;

				delete [] platform;
				platform = nullptr;

				delete [] genre;
				genre = nullptr;

				delete [] progression;
				progression = nullptr;

				delete [] acheivements;
				acheivements = nullptr;

				break;
			}
			case 6:	
			{
				success = queue_list.display();
		
				if (success == 0)
					cout << "Nothing to display" << endl;
				break;
			}
			case 7:
			{
				q_game to_remove;
				success = queue_list.dequeue(to_remove);

				if (success == 1)
					cout << "success" << endl;
				else
					cout << "fail" << endl;
				break;
			}
			case 8: // peek
			{
				q_game peek_game;
				//success = queue_list.peek(peek_game);
				
				//if (success == 1)
				//	cout << "success" << endl;
				//peek_game.display();

				if (queue_list.peek(peek_game) == 0)
				{
					cout << "ERROR: Cannot peek at an empty stack." << endl;
					break;
				}
				queue_list.display_header();
				peek_game.display();
	
				break;

			}
			case 9:
				break;
		}
	} while (choice != 9);

	return 0;
}
