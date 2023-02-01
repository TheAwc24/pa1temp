// A class to make linked lists
// Some of this code was use from a previous class, editted for this assignment

#ifndef LISTSLINKING_H
#define LISTSLINKING_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// structure for holding commands
struct CommandsNode
{
	string name;
	string description;
	int points;
	CommandsNode *next;
};

struct ProfileNode
{
	string name;
	int points;
};

template <typename NODETYPE>
class ListsLinking
{
	private:
		// The start of list
		NODETYPE *head;

	public:
		// Constructor
		ListsLinking()
		{
			head = nullptr;
		}

		// Destructor
		~ListsLinking()
		{
			NODETYPE *currentPtr;
			NODETYPE *nextNode;

			// line up at the starting line
			currentPtr = head;

			while (currentPtr != nullptr)
			{
				// save next node location
				nextNode = currentPtr->next;

				// remove the node we're on
				delete currentPtr;

				// move to the next one
				currentPtr = nextNode;
			}
		}

		// add node to end of list, overloaded for commands
		void appendNode(string name, string description, int points)
		{
			NODETYPE *newNode;
			NODETYPE *currentPtr;
			int result;

			// Make sure this command isn't already in the game
			result = testSameness(name);
			if (result == 1)
			{
				cout << "Please try a different command." << endl;

				// Wait for enter
   				cout << "Please hit [ENTER] to return to the main menu." << endl;
    			// **BUG FIX: 2 ignores are required, as the first will catch the new line from the previous enter OR endl. Doing ignore(2) does not work, as it will correctly wait for 2 enter presses.
    			cin.ignore();
    			cin.ignore();

				return;
			}

			// make a new node
			newNode = new NODETYPE;
			newNode->name = name;
			newNode->description = description;
			newNode->points = points;
			newNode->next = nullptr;

			// insert the new node, either at the front if empty or at the end
			if (!head)
				head = newNode;
			else
			{
				currentPtr = head;

				while (currentPtr->next)
					currentPtr = currentPtr->next;

				currentPtr->next = newNode;
			}
		}

		// add node to end of list, overloaded for profiles
		void appendNode(string name, int points)
		{
			NODETYPE *newNode;
			NODETYPE *currentPtr;
			int result;

			// make a new node
			newNode = new NODETYPE;
			newNode->name = name;
			newNode->points = points;
			newNode->next = nullptr;

			// insert the new node, either at the front if empty or at the end
			if (!head)
				head = newNode;
			else
			{
				currentPtr = head;

				while (currentPtr->next)
					currentPtr = currentPtr->next;

				currentPtr->next = newNode;
			}
		}

		// delete a specific node
		int deleteNode(string name)
		{
			NODETYPE *currentPtr;
			NODETYPE *previousNode;

			// check to see if anything is in the list
			if (!head)
				return 1;

			// check to see if first value is what we want to delete
			if (head->name == name)
			{
				currentPtr = head->next;
				delete head;
				head = currentPtr;
				return 0;
			}
			else
			{
				currentPtr = head;

				// find the number in the node
				while (currentPtr != nullptr && currentPtr->name != name)
				{
					previousNode = currentPtr;
					currentPtr = currentPtr->next;
				}

				// if we found it, burn it to the ground and return
				if (currentPtr)
				{
					previousNode->next = currentPtr->next;
					delete currentPtr;
					return 0;
				}
			}
			return 1;
		}

		// give the list out to the console
		void displayAll() const
		{
			NODETYPE *currentPtr;

			// start line
			currentPtr = head;

			// run through the list
			while (currentPtr)
			{
				cout << currentPtr->name << "  "
					 << currentPtr->description << "  "
					 << currentPtr->points << " points" << endl;

				currentPtr = currentPtr->next;
			}
		}

		// Save commands
		void saveAll(string outputFile) const
		{
			NODETYPE *currentPtr;
			ofstream file (outputFile);

			// start line
			currentPtr = head;

			if (file.is_open())
			{
				// Start with head
				file << currentPtr->name << "," << currentPtr->description << "," << currentPtr->points;
				currentPtr = currentPtr->next;
				// Go through rest of list
				while (currentPtr)
				{
					file << endl << currentPtr->name << "," << currentPtr->description << "," << currentPtr->points;
					currentPtr = currentPtr->next;
				}
			}

			// Close file
			file.close();
		}

		// Selects a command based on where it is in the list
		NODETYPE* const selectCommand(const int selection)
		{
			NODETYPE *currentPtr;

			// start line
			// FOR TESTING
			cout << "The head is " << head->name << endl;
			currentPtr = head;

			// Find the command based on its location
			if (selection == 1)
				return currentPtr;
			else
			{
				for (int i = 0; i < selection; i++)
					currentPtr = currentPtr->next;
				return currentPtr;
			}
		}

		// Test nodes for duplicates
		int testSameness(const string name) const
		{
			NODETYPE *currentPtr;
			int result = 0;

			// start line
			currentPtr = head;

			// run through the list, checking for duplicates
			while (currentPtr && result != 1)
			{
				if (currentPtr->name == name)
				{
					cout << name << " is already in the game!"  << endl;
					result = 1;
				}
				else
					currentPtr = currentPtr->next;
			}

			// return the result
			return result;
		};
};
#endif