/*


*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <random>
#include <memory>
#include "ListsLinking.h"
using namespace std;

// Function Prototypes; Main Menu
void gameRules (int&);
void newGame(int&, const ListsLinking<CommandsNode>, ProfileNode[]);
void loadGame(int&, int, ProfileNode[], const ListsLinking<CommandsNode>);
void addCommand(int&, ListsLinking<CommandsNode>&);
void removeCommand(int&, ListsLinking<CommandsNode>&);
void displayCommands(int&, ListsLinking<CommandsNode>&);

// Function Prototypes; Loading & Saving
void inputCommands(ListsLinking<CommandsNode>&);
int countLines(string);
void inputProfiles(ProfileNode[], int);
void saveProfiles(ProfileNode[]);

// Function Prototypes; Random
void waitForEnter();

// Function Prototypes; Game Functions
int theGame(const ListsLinking<CommandsNode>, string, int, ProfileNode[]);
void getCommands(ListsLinking<CommandsNode>, const int, int[], const int, CommandsNode&, CommandsNode&, CommandsNode&);
bool usedBefore(const int[], const int, const int);

// Main script
int main()
{
    // Variables to be used
    int menuSelection = 0, lines;
    ListsLinking<CommandsNode> commandsList;
    string profileFile = "profiles.csv";

    // Load commands and profiles into the game
    inputCommands(commandsList);
    lines = countLines(profileFile);
    ProfileNode *profileList{ new ProfileNode[lines]{} };
    inputProfiles(profileList, lines);

    // Loop for Main Menu
    // When selected, it will shoot player to appropriate function
    do {
        // Clear console
        system("clear");

        // List menu
        cout << "Learning Linux Commands" << endl << endl
             << "Please select an option listed below:" << endl
             << "1. Game Rules" << endl
             << "2. Play New Game" << endl
             << "3. Load Previous Game" << endl
             << "4. Add Command" << endl
             << "5. Remove Command" << endl
             << "6. Display All Commands" << endl
             << "7. Save and Exit" << endl << endl;

        // Get input
        cin >> menuSelection;
        
        // Send user to appropriate function, checking for valid response in the process
        if (menuSelection == 1)
            gameRules(menuSelection);
        else if (menuSelection == 2)
            newGame(menuSelection, commandsList, profileList);
        else if (menuSelection == 3)
            loadGame(menuSelection, lines, profileList, commandsList);
        else if (menuSelection == 4)
            addCommand(menuSelection, commandsList);
        else if (menuSelection == 5)
            removeCommand(menuSelection, commandsList);
        else if (menuSelection == 6) {
            displayCommands(menuSelection, commandsList);
        }
        else if (menuSelection == 7)
            cout << "Thanks for playing!" << endl;
        else {
            cout << "Invlaid reponse, please try again" << endl;
            menuSelection = 0;
        }
    } while (menuSelection == 0);

    // Save commands
    commandsList.saveAll("commands.csv");

    // Save profiles
    saveProfiles(profileList);

    // End game
    return 0;
}

// Display the game rules
void gameRules(int& menu) {
    // Display rules on cleared terminal
    system("clear");
    cout << "Learning Linux Commands" << endl << endl
         << "In this game, you will match Linux/Bash commands to their description." << endl
         << "You will be presented with the command, and given 3 descriptions." << endl
         << "One of these will be right and two will be wrong." << endl
         << "If you get the answer right, you will earn points." << endl
         << "However, if you answer wrong, points will be removed from your score." << endl
         << "The points earned/removed are located next to the correct description." << endl << endl
         << "After each game, your total will be saved." << endl
         << "You will enter a profile name, and when you come back, you can load your score back." << endl << endl
         << "Have fun playing!" << endl << endl;
    
    // Wait for Enter
    waitForEnter();

    // Change menu variable to return to main menu
    menu = 0;
    return;
}

// Play a new game
void newGame(int& menu, const ListsLinking<CommandsNode> list, ProfileNode profiles[]) {
    // Let us play this great game!!
    theGame(list, "", 0, profiles);

    // Reset menu selection and return
    menu = 0;
    return;
}

// Load a previous game/profile
void loadGame(int& menu, int lines, ProfileNode profiles[], const ListsLinking<CommandsNode> commands) {
    string name;
    int points, found = 0, result;

    // Clear terminal
    system("clear");

    // Ask for profile
    cout << "What is the profile you'd like to use?" << endl;
    cin.clear();
    cin >> name;

    // Search profile array
    for (int i = 0; i < lines; i++)
    {
        // If a profile exists, start a game with it
        if (profiles[i].name == name)
        {
            cout << "Profile " << name << " found! Loading this profile now." << endl;
            points = profiles[i].points;
            found = 1;
            theGame(commands, name, points, profiles);
        }
    }

    // If we didn't find a profile, alert the user and ask if they want to start a new game
    // or go back to the main menu
    if (found == 0)
    {
        cout << "Profile not found! Would you like to:" << endl
             << "1. Start a new game" << endl
             << "2. Return to main menu" << endl;
        cin.clear();
        cin >> result;
        if (result == 1)
            theGame(commands, "", 0, profiles);
    }

    // Reset menu selection and return
    menu = 0;
    return;
}

// Add a new command to the game
void addCommand(int& menu, ListsLinking<CommandsNode>& list) {
    string name, description;
    int points;

    // Clear terminal
    system("clear");

    // Ask for information
    cout << "Please enter the name of the command:" << endl;
    cin.clear();
    cin >> name;
    cout << endl << "Using parentheses, please enter the description of " << name << ":" << endl;
    cin.ignore();
    getline(cin, description);
    cout << endl << "Please enter the point value (1-4) of " << name << ":" << endl;
    cin.clear();
    cin >> points;
    while (points < 1 || points > 4)
    {
        cout << "Please enter a point value between 1 & 4 :" << endl;
        cin.clear();
        cin >> points;
    }

    // Add command to list
    cout << endl << endl
         << "Thank you, I will now add that command to the game!" << endl;
    list.appendNode(name, description, points);

    // Wait for enter
    waitForEnter();

    // Reset menu selection and return
    menu = 0;
    return;
}

// Remove a command from the game
void removeCommand(int& menu, ListsLinking<CommandsNode>& list) {
    string name;
    int result;

    // Clear terminal
    system("clear");

    // Ask for command to remove
    cout << "What command would you like to remove?" << endl;
    cin >> name;

    // Call function from list
    result = list.deleteNode(name);

    // See if it was successful
    if (result == 0)
        cout << "Command removed!" << endl;
    else 
        cout << "Command not found, therefore not removed." << endl;

    // Wait for enter
    waitForEnter();

    // Reset menu selection and return
    menu = 0;
    return;
}

// List all the commands in the game
void displayCommands(int& menu, ListsLinking<CommandsNode>& list) {
    // Clear terminal
    system("clear");

    // Call command from class
    list.displayAll();

    // Wait for enter
    waitForEnter();
    
    // Reset menu selection
    menu = 0;
    return;
}

// Input the commands from the file
void inputCommands(ListsLinking<CommandsNode>& commandsList) {
    string name, description, pointsString;
    int points;
    ifstream commandsFile ("commands.csv");

    // Use loops to add new nodes. Points will have to be read as a string, then converted to int
    if (commandsFile.is_open())
    {
        // Make nodes
        while (!commandsFile.eof())
        {
            getline(commandsFile, name, ',');
            getline(commandsFile, description, ',');
            getline(commandsFile, pointsString);
            points = stoi(pointsString);
            commandsList.appendNode(name, description, points);
        }

        // Close file
        commandsFile.close();
    }
    // If file didn't open, throw error
    else
        throw runtime_error("Failed to load file, game initialization failed. Please make sure 'commands.csv' is in the directory!");
}

int countLines(string inputFile)
{
    // Thine variables
    string line;
    int count = 0;
    ifstream file (inputFile);

    // Count how many lines are in the file
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, line);
            count++;
        }

        // Close file
        file.close();
    }
    else
        throw runtime_error("Failed to load file, game initialization failed. Please make sure " + inputFile + " is in the directory!");

    // Return result
    return count;
}

void inputProfiles(ProfileNode profiles[], int lines)
{
    string name, pointsString;
    int points;
    ifstream profilesFile ("profiles.csv");

    // Make nodes
    if (profilesFile.is_open())
    {
        for (int i = 0; i < lines; i++)
        {
            getline(profilesFile, name, ',');
            getline(profilesFile, pointsString);
            points = stoi(pointsString);
            profiles[i] = {name, points};
        }

        // Close file
        profilesFile.close();
    }
    // If file didn't open, throw error
    else
        throw runtime_error("Failed to load file, game initialization failed. Please make sure 'profiles.csv' is in the directory!");
}

void saveProfiles(ProfileNode profiles[])
{
    ofstream profilesFile ("profiles.csv");

    // Save profiles to file, overriding lines
    if (profilesFile.is_open())
    {
        // Start at beginning
        profilesFile << profiles[0].name << "," << profiles[0].points;
        // Continue on
        for (int i = 1; !profilesFile.eof(); i++)
        {
            profilesFile << endl << profiles[i].name << "," << profiles[i].points;
        }
    }

    // Close file
    profilesFile.close();
}

void waitForEnter()
{
    // Wait for enter
    cout << "Please hit [ENTER] to continue..." << endl;
    // **BUG FIX: 2 ignores are required, as the first will catch the new line from the previous enter OR endl. Doing ignore(2) does not work, as it will correctly wait for 2 enter presses.
    cin.ignore();
    cin.ignore();
}

int randomNumber(const int MIN, const int MAX)
{
    int result;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(MIN, MAX);
    result = distr(gen);
    return result;
}

int theGame(const ListsLinking<CommandsNode> commands, string user, int incomingPoints, ProfileNode profiles[])
{
    int points = incomingPoints, questionAmount, commandAmount, order, answer = 0, isCorrect = 0;
    const int MINQUESTIONS = 5;
    const int MAXQUESTIONS = 30;
    CommandsNode correctCommand, firstWrong, secondWrong, *first, *second, *third;

    // If we're not loading a game, get a profile name
    if (user.empty())
    {
        cout << "Please enter a 1 word name to use for your profile:" << endl
             << "NOTE: If you enter a name already use, you will override that profile!" << endl;
        cin >> user;
    }

    // Get the amount of questions desired for game
    cout << endl << "Thank you!" << endl
         << "How many questions, from " << MINQUESTIONS << " to " << MAXQUESTIONS << ", would you like to play?" << endl;
    cin >> questionAmount;

    // Make an array to store used commands, now that we know the size, then initialize it
    int questionsAsked[questionAmount];
    for (int i = 0; i < questionAmount; i++)
        questionsAsked[i] = -1;

    // Wait for the user to be ready
    cout << "You are now ready to start." << endl;
    waitForEnter();

    // Find out how many commands are in the game
    commandAmount = countLines("commands.csv");

    // Start the rounds, using a loop
    for (int i = 0; i < questionAmount; i++)
    {
        // Clear terminal
        system("clear");

        // Get commands to use
        getCommands(commands, commandAmount, questionsAsked, i, correctCommand, firstWrong, secondWrong);

        // Determine the description order
        order = randomNumber(1, 6);
        if (order == 1)
        {
            first = &correctCommand;
            second = &firstWrong;
            third = &secondWrong;
        }
        else if (order == 2)
        {
            first = &correctCommand;
            second = &secondWrong;
            third = &firstWrong;
        }
        else if (order == 3)
        {
            first = &firstWrong;
            second = &correctCommand;
            third = &secondWrong;
        }
        else if (order == 4)
        {
            first = &secondWrong;
            second = &firstWrong;
            third = &correctCommand;
        }
        else if (order == 5)
        {
            first = &secondWrong;
            second = &correctCommand;
            third = &firstWrong;
        }
        else if (order == 6)
        {
            first = &firstWrong;
            second = &secondWrong;
            third = &correctCommand;
        }

        // Output to display (finally)
        cout << "-------------------------------------------------" << endl
             << "Profile: " << user << "    Points: " << points << endl
             << "-------------------------------------------------" << endl
             << "What is the description of the command : " << correctCommand.name << endl
             << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl
             << "1. " << first->description << " (" << first->points << "pts)" << endl
             << "2. " << second->description << " (" << second->points << "pts)" << endl
             << "3. " << third->description << " (" << third->points << "pts)" << endl;
        // Get users answer
        cin >> answer;

        // See if answer was correct
        if (order == 1)
        {
            if (answer == 1)
                isCorrect = 1;
        }
        else if (order == 2)
        {
            if (answer == 1)
                isCorrect = 1;;
        }
        else if (order == 3)
        {
            if (answer == 2)
                isCorrect = 1;
        }
        else if (order == 4)
        {
            if (answer == 3)
                isCorrect = 1;
        }
        else if (order == 5)
        {
            if (answer == 2)
                isCorrect = 1;
        }
        else if (order == 6)
        {
            if (answer == 3)
                isCorrect = 1;
        }

        // If correct, add to total, otherwise remove from total
        if (isCorrect == 1)
        {
            points += correctCommand.points;

            cout << "That's correct! -- You have earned " << correctCommand.points << " point(s)" << endl
                 << "Current Score: " << points << endl;
        }
        else
        {
            points -= correctCommand.points;

            cout << "Sorry, that's wrong! -- You have lost " << correctCommand.points << " point(s)" << endl
                 << "Current Score: " << points << endl;
        }

        // Wait for enter to continue to next round
        waitForEnter();
    }

    // Save total points
    int lines = countLines("profiles.csv");
    for (int i = 0; i < lines; i++)
    {
        // If a profile exists, enter new total
        if (profiles[i].name == user)
            profiles[i].points = points;
    }
    // Otherwise make a new profile
    ProfileNode *tempProfile{ new ProfileNode[lines + 1]{} };
    for (int i = 0; i < lines; i++)
        tempProfile[i] = profiles[i];
    delete [] profiles;
    profiles = tempProfile;
    profiles[lines + 1] = {user, points};

    cout << "You've reached the end of the game." << endl
         << "Here's your final point total " << user << "." << endl
         << "Points: " << points << endl;

    waitForEnter();

    // Return points back to newGame function
    return points;
}

// Function to get the command and wrong descriptions for each round
void getCommands(ListsLinking<CommandsNode> commands, const int commandAmount, int questionsAsked[], int round, CommandsNode& right, CommandsNode& wrong1, CommandsNode& wrong2)
{
    int currentCommand = 0, currentFirst = 0, currentSecond = 0;
    CommandsNode *temp1, *temp2, *temp3;

    // Get the command to be used
    do
    {
        currentCommand = randomNumber(0, commandAmount);
    } while (usedBefore(questionsAsked, currentCommand, round));
    temp1 = commands.selectCommand(currentCommand);
    right.name = temp1->name;
    right.description = temp1->description;
    right.points = temp1->points;

    // Get the wrong descriptions
    do
    {
        currentFirst = randomNumber(0, commandAmount);
    } while (currentFirst == currentCommand);

    do
    {
        currentSecond = randomNumber(0, commandAmount);
    } while (currentSecond == currentCommand && currentSecond == currentFirst);
    
    temp2 = commands.selectCommand(currentFirst);
    wrong1.name = temp2->name;
    wrong1.description = temp2->description;
    wrong1.points = temp2->points;

    temp3 = commands.selectCommand(currentSecond);
    wrong2.name = temp3->name;
    wrong2.description = temp3->description;
    wrong2.points = temp3->points;

    // Add command being used to array
    questionsAsked[round] = currentCommand;

    return;
}

bool usedBefore(const int commands[], const int command, const int round)
{
    // Check if we've played yet
    if (round == 0)
        return false;
    // If command has been used before, send true
    for (int i = 0; i < round; i++)
    {
        if (commands[i] == command)
            return true;
    }

    // If not, send false
    return false;
}