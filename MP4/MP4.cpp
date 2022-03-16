// MP4.cpp : 12.9.2021 : Kaden Wince
// Description: This program lets a single user play a text-based adventure game where they are going through
// a cavern trying to hunt the enemy.
//

#include <iostream>
#include <vector>
using namespace std;

// Classes
class Round {   // Concept -- Class
public:
    Round();
    int get_enemyLoc();
    int get_vultureLoc();
    int get_taffyLoc();
    int get_playerLoc();
    void put_playerLoc(int pl);
private:
    int enemyLoc;
    int vultureLoc;
    int taffyLoc;
    int playerLoc;
};
Round::Round() {
    // Randomizes all of the asset locations when it is constructed
    enemyLoc    = rand() % 20 + 1;                // Concept -- Assignment statement
    vultureLoc = rand() % 20 + 1;
    taffyLoc   = rand() % 20 + 1;
    playerLoc = 1;
}
int Round::get_enemyLoc() {
    return enemyLoc;
}
int Round::get_vultureLoc() {
    return vultureLoc;
}
int Round::get_taffyLoc() {
    return taffyLoc;
}
int Round::get_playerLoc() {
    return playerLoc;
}
void Round::put_playerLoc(int pl) {
    playerLoc = pl;
}

// Function Prototypes
void printInstructions();
int getNumInput(vector<int> adjRoom);  // Concept -- Function Definition with a Vector as a Parameter and Function Call
char getCharInput(int round);
void printSigns(vector<vector<int>> map, int round, int pLoc, int eLoc);

int main() {
    // Set up the game map
    vector<vector<int>> map{          // Concept -- 2D Array / Vector
        {-1, -1, -1},// Invalid
        {2, 5, 8},   // 1
        {1, 3, 10},  // 2
        {2, 4, 12},  // 3
        {3, 5, 14},  // 4
        {1, 4, 6},   // 5
        {5, 7, 15},  // 6
        {6, 8, 17},  // 7
        {1, 7, 9},   // 8
        {8, 10, 18}, // 9
        {2, 9, 11},  // 10
        {10, 12, 19},// 11
        {3, 11, 13}, // 12
        {12, 14, 20},// 13
        {4, 13 ,15}, // 14
        {6, 14, 16}, // 15
        {15, 17, 20},// 16
        {7, 16, 18}, // 17
        {9, 17, 19}, // 18
        {11, 18, 20},// 19
        {13, 16, 19} // 20
    };

    // Set up the start of the game
    srand(time(0));       // Set the random seed so we get random values for asset locations
    printInstructions();  // Print the beginning instructions of the game
    int numRound = 1;     // Number to keep track of what round we are on

    bool playing = true;  // Keep track of whether they quit the game or not

    // Loop to loop through each round
    while (playing) {                           // Concept -- for/while/do while loop

        Round currentRound;                     // Creates a variable for the current round that autogenerates the locations
        bool notDone = true;                    // Tells whether or not the round is over
        cout << "Round " << numRound << ":\n"; 

        while (notDone) {
            // Display the current room and tunnels
            cout << endl;
            printSigns(map, numRound, currentRound.get_playerLoc(), currentRound.get_enemyLoc()); // Prints out the clues to where enemy is
            cout << "You are in room " << currentRound.get_playerLoc() << endl;                   // Tells the player what room they are in
            cout << "Tunnels lead to rooms ";                                                     // Tells the player what the adjacent rooms are
            for (int i = 0; i < map[currentRound.get_playerLoc()].size(); i++) {
                cout << map[currentRound.get_playerLoc()][i];
                if (i == map[currentRound.get_playerLoc()].size() - 1) { cout << endl; }
                else { cout << ", "; }
            }

            // Ask the option for what they want to do and get their choice
            cout << "Move, Exit, Instructions, or ";
            // Determine which option to cout based on what round it is
            switch (numRound) {                        // Concept -- Switch Statement
            case 1: cout << "Candy Cane: "; break;     
            case 2: cout << "Sword Toothpick: "; break;
            case 3: cout << "Pastry Torch: "; break;
            }
            char userChoice = getCharInput(numRound);  // Get what they want to do

            // Functions for which each choice does
            if (userChoice == 'E') { goto endProgram; }// Concept -- If Statement

            if (userChoice == 'I') { printInstructions(); }

            if (userChoice == 'M') {
                cout << "Where to? ";
                int location = getNumInput(map[currentRound.get_playerLoc()]); // Concept -- Function Definition with a Vector as a Parameter

                // Check to see if it landed in a vulture location;
                if (location == currentRound.get_vultureLoc()) {
                    location = rand() % 20 + 1;
                    cout << "Vultures transport you to room " << location << endl;
                }

                // Check to see if it landed in a taffy pit
                if (location == currentRound.get_taffyLoc()) {
                    if (numRound == 1 || numRound == 3) {
                        cout << "Sorry, you landed in the taffy pit.\n";
                        goto endProgram;
                    }

                    if (numRound == 2) {
                        cout << "Sorry, you landed in the taffy pit.\n";
                        numRound++;
                        notDone = false;
                    }
                }
                // Set the current location player is trying to go to
                currentRound.put_playerLoc(location);
            }

            // Functionality for the user choice of trying to kill the enemy
            if (userChoice == 'C' || userChoice == 'S' || userChoice == 'F') {
                cout << "Room to aim at? ";
                int userLoc = getNumInput(map[currentRound.get_playerLoc()]);

                // Goes through and checks if they find the enemy and what happens with each round
                if (numRound == 1) {
                    if (userLoc == currentRound.get_enemyLoc()) {
                        cout << "Great Job! You found the enemy!\n" << "You win this round!\n\n";
                        numRound++;
                        notDone = false;
                    }
                    else {
                        cout << "You did not find the enemy!\n" << "The snow-stealing peeps wins the war!\n";
                        goto endProgram;
                    }
                }

                else if (numRound == 2) {
                    if (userLoc == currentRound.get_enemyLoc()) {
                        cout << "Great Job! You found the enemy!\n" << "Peeps win the war!\n";
                        goto endProgram;
                    }
                    else {
                        cout << "You did not find the rubber ducks.\n" << "Now the rubber ducks will make an advance!\n";
                        numRound++;
                        notDone = false;
                    }
                }

                else if (numRound == 3) {
                    if (userLoc == currentRound.get_enemyLoc()) {
                        cout << "Great Job! You found the enemy!\n" << "The rubber ducks win the war!\n";
                        notDone = false;
                        goto endProgram;
                    }
                    else {
                        cout << "The snow-stealing peeps wins the war!\n";
                        goto endProgram;
                    }
                }
            }
        }
    }

// Goes to here if we need to end the program
endProgram:
    cout << "Thanks for playing!\n";
    system("pause");
}

/**
 printInstructions Function - prints out the instructions for the game to the console
 */
void printInstructions() {
    cout << "Welcome to Rubber Ducks vs. Peeps Game\n";
    cout << "The Debugging Rubber Ducks are tracking down the evil Snow Stealing Peeps living in a 20-room cave system.\n";
    cout << "The Snow Stealing Peeps are taking all the snow and magically creating snow beasties.\n\n";
    cout << "Using their cunning skill and logic, the rubber ducks are going to hunt down the snow stealing peeps.\n";
    cout << "The peeps cannot hide their sugary stench smell or muffle their squishy marshmallow footsteps.\n\n";
    cout << "This text-based adventure game will have three rounds. In round 1 and round 3, the user will\n";
    cout << "be playing the role of the rubber ducks. In round 2, the tables will be turned, and the user\n";
    cout << "will be play as the Snow Stealer Peeps.\n\n";
    cout << "For each round, you will be moving through the cave system trying to find your enemy.\n";
    cout << "You can move to any of the ajointing rooms. You can also view the instructors or exit the game.\n\n";
    cout << "You will have a warning that you will be approaching your enemy if you hear footsteps or smell sugar.\n\n";
    cout << "If you think you have located the enemy, you can use your candy cane arrow (round 1) or\n";
    cout << "toothpick sword (round 2 or 3) to capture the enemy and win around.                                 ,~~.\n";
    cout << "                                                                                               ,   (  ' )>\n";
    cout << "Hazards:                                                                                       )`~~'   (\n";
    cout << "Taffy - the rubber ducks or peeps can get 'stuck' on the taffy and this will end the          (  .__)   )\n";
    cout << "game/round.                                                                                    `-.____,' \n";
    cout << "Vultures - these carry ducks or peeps to a random location within the cave system\n\n";
}

/**
 getNumInput Function - gets an input from the player and then checks if its valid or not
 @param adjRoom -- a vector of the adjacent rooms to the players rooms
 @return int -- return which adjacent room the player chose
 */
int getNumInput(vector<int> adjRoom) {
    int input = -99;
    while (true) {
        // Cins the input and checks to make sure its a valid input
        cin >> input;
        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

        // Checks the input given to make sure its a valid input for the program to use
        bool correct = false;
        if (input > 20 || input < 1) { correct = false; }
        for (int i = 0; i < adjRoom.size(); i++) {
            if (adjRoom[i] == input) { correct = true; }
        }

        // If it is a correct input then return it, if not then let them try again
        if (correct) { return input; }
        if (!correct) { cout << "You can't get there from here. Please enter a new room: "; }
    }
}

/**
 getCharInput Function - gets an input from the player and then checks if its valid or not
 @param round -- what current round the game is at
 @return int -- returns which action the player wants to do
 */
char getCharInput(int round) {
    char input = '?';
    while (true) {
        // Cins the input and checks to make sure its a valid input
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
        }

        // Checks the input given to make sure its a valid input for the program to use
        bool correct = false;
        input = toupper(input);
        if (input == 'M' || input == 'E' || input == 'I') { correct = true; }
        if (input == 'C' && round == 1) { correct = true; }
        if (input == 'S' && round == 2) { correct = true; }
        if (input == 'F' && round == 3) { correct = true; }

        // If it is a correct input then return it, if not then let them try again
        if (correct) { return input; }
        if (!correct) { cout << "Not a valid input: "; }
    }
}

/**
 printSigns Function - prints out a clue to how far the enemy is away
 @param map -- the entire dodecahedral map of the game
 @param round -- what the current round the game is on
 @param pLoc -- the current player location
 @param eLoc -- the current enemy location
 */
void printSigns(vector<vector<int>> map, int round, int pLoc, int eLoc) {
    for (int i = 0; i < map[pLoc].size(); i++) {                          // Go through each adjacent room from pLoc and see if enemy is there
        if (map[pLoc][i] == eLoc) { cout << "I hear footsteps!\n"; }
        if (round == 1 || round == 3) {                                   // Only round 1 and 3
            for (int j = 0; j < map[pLoc].size(); j++) {                  // Go through each adjacent of the adjacent to see if enemy is there
                if (map[map[pLoc][i]][j] == eLoc) { cout << "I smell marshmallows!\n"; return; }
            }
        }
    }
}
