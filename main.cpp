/* 
Name: Queenie Leung, NSHE 1007386899, CS 302 1004, Ast 2
Description: Puzzle game to find and complete a path
             
Input: User inputs puzzle.txt file and start
       and end coordinates
Output: Program outputs and a visual of the puzzle
        completed starting with 0 to 9 then A-Z
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

const int boardSize = 7;
char grid[boardSize][boardSize]; // 7x7 grid to hold characters
int xStart, yStart, xFinish, yFinish; // starting and ending coordinates

// step counter to keep track of the number of steps taken
int stepCounter = 0; 
int emptySpaces = 0; // number of vacant spots

// step values array of const characters
const char steps[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 

//sorry i couldnt figure it out... so i had to use a simple way
//as to how to access it individually instead
//of a whole group
//char counter(int num)
//{   char c;
//    if (num >= 10) 
//    {
//      c = 'A'+ num - 10;
//    } 
//    else 
//    {
//      c = '0'+ num;
//    }
//    return c;
//}

//****function declarations************ 
//descriptors are
bool isValidMove(int x, int y); 
bool findPath(char grid[][7], int x, int y, int stepCounter); 

int main() 
{
    cout << endl; //spacing format 
    // read the input file and initialize grid
    ifstream input;
    string line;
    cout << "Enter config file: ";
    cin >> line;

//check if file open/not will loop until user gives proper input
	while (true) 
    {
		input.open(line);

	    //if cannot open it, let user re-enter the file name
        if(!input.is_open()) 
        {
            //cout << nameOfPuzzle << " not found" << endl; //DEBUG
			std::cout << "Enter config file: ";
			cin >> line;
			//cout << endl;
		}
        else  //if the file is open break out of the while loop
        { break;    }
	}   
       // std::cout << endl; //formatting

    for(int i = 0; i< boardSize; i++)
    {
        getline(input, line);
        for(int j = 0; j < boardSize; j++)
        {
            grid[i][j] = line[j]; //each line of .txt file read into line
                                // then each char in string 'line' is assigned to 
                                //an element on the grid (s = space for example pzle01)
                                //row = r and column = c
   //     c ->
   //     0 1 2 3 4 5 6   example positions
   // r 0 _ s s s s _ _  grid[i][j] at 0,0 = '_' grid [i][j] at 01 = ' '
   // | 1 _ _ s s s _ _  grid[i][j] at 1, 2 = ' '
   // v 2 _ s s s s _ _
   //   3 _ s s s s _ _
   //   4 _ _ _ s s _ _
   //   5 _ _ s s _ _ _
   //   6 _ _ s s s s _  grid[i][j] at 6,6 = '_'
            
            //count empty spots
            if(grid[i][j] == ' ') //if it is empty increment empty spaces
            {
                emptySpaces++;
            }
        }
       // if(input.eof()) DEBUG
       // { break;    }   DEBUG
    }

    // get starting and ending coordinates
    cout << endl;

while (true) 
    {
        std::cout << "Please enter starting coordinates: ";
        if (std::cin >> xStart >> yStart) 
        {
            if (xStart >= 0 && xStart <= 7 && yStart >= 0 && yStart <= 7) 
            {   break; } // means it did not hit the fail bit
            
            else 
            {
                //std::cout << "BAD input. Coordinates must be between 0 and 7." << std::endl; //DEBUG
                std::cin.clear(); // clear error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
            }
        } 
        else 
        {
            //std::cout << "BAD input. Please enter two integers." << std::endl; // DEBUG
            std::cin.clear(); // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
        }
    } 
       // cout << endl; //formatting

    cout << endl;

while (true) 
    {
        std::cout << "Please enter end coordinates: ";
        if (std::cin >> xFinish >> yFinish) {
            if (xFinish >= 0 && xFinish <= 7 && yFinish >= 0 && yFinish <= 7) 
            {   break;  } // means it did not hit the fail bit
            else 
            {
                //std::cout << "BAD input. Coordinates must be between 0 and 7." << std::endl; //DEBUG
                std::cin.clear(); // clear error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
            }
        } 
        else 
        {
            //std::cout << "BAD input. Please enter two integers." << std::endl; // DEBUG
            std::cin.clear(); // clear error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore invalid input
        }
    } 

    cout << endl;
    
    // call the recursive function to find the path
    //grid is the 2D array, xStart and yStart are the user inputs and 0 is because
    //0 as we havent moved from the start position yet
    bool result = findPath(grid, xStart, yStart, 0);
    //another bool set to false 
    bool found = false;
    //checks if result is true then set found from false to true.
    if(result)
    {   found = true;   }
   
    // print the final grid if path is found
    if (found) 
    {
        for (int i = 0; i < boardSize; i++) //rows of grid array
        {
            for (int j = 0; j < boardSize; j++) //columns of grid array for each row
            {
                cout << grid[i][j] << " "; //prints whats in the array
            }
            cout << endl;               //spacing to go to next row once exit inner for loop
        }
    }
    else //not sure if there is an error as Jimi said all paths should be viable
        // and no trick questions
    {
         cout << "No viable Path not found!" << endl;//DEBUG ERROR MESSAGE
    }

    //cout << endl; //spacing format after print
}
/*********FUNCTION DESCRIPTORS*****************/

/*

FUNCTION_IDENTIFIER:check to see if the move is valid
parameters: int x and int y
return value: true or false as it is a bool
description: returns true or false if the move is within the bounds

*/
bool isValidMove(int x, int y) 
{
    // check if the move is within the bounds 
    //of the grid and the spot is empty or open with no '_'
    if(x>=0 && x < boardSize && y >=0 && y < boardSize && grid[x][y] == ' ')
    {   return true;    } 
    else
    {   return false;   } //if the above is not true return false that means either
                        //not empty or outside the boardsize
   // return false;  //return false as it was giving an error on compiler or something? 
    
}

/*

FUNCTION_IDENTIFIER:this checks to see if we filled up all the empty
spaces on the grid. This is the 
parameters: char grid array of 7x7, int x, int y and int stepCounter
return value: true or false as it is a bool
description: Checks if all empty ' ' spaces equal the amount of stepCounter
then checks if xFinish is equal to yFinish

*/
bool findPath(char grid[][7], int x, int y, int stepCounter) 
{
    // If all previously empty spaces contain a step 
    //counter and the current location is the end location, 
    //return true
    //stepCounter == emptyspaces - 1 since stepCounter starts at 1 but 
    //our count starts at 0
    if (stepCounter == emptySpaces - 1 && x == xFinish && y == yFinish) 
    {
        // mark the last step and return
        //base case
        grid[x][y] = steps[stepCounter]; //steps array will use the char
                                        //given in the counter ie. step 0 = 0
                                        //step 10 = A in the array
        return true;
    }

    // If the current location is the end location 
    //but not all the previously empty space spots 
    //are filled, return false
    if (x == xFinish && y == yFinish) 
    {
        return false;
    }

    // check if the move is within the bounds of the grid and the
    // current location is an empty space spot
    if (isValidMove(x, y)) 
    {
        // mark the current location with the step value
        grid[x][y] = steps[stepCounter];//steps array will use the char
                                        //given in the counter ie. step 0 = 0
                                        //step 10 = 'A' in the array

        // recursive calls to move up, down, left and right
        //multiple OR for the IF check if we can go left
        //if we can go left, if we can go down, if we can go up
        if (findPath(grid, x - 1, y, stepCounter + 1) || 
            findPath(grid, x + 1, y, stepCounter + 1) || 
            findPath(grid, x, y - 1, stepCounter + 1) || 
            findPath(grid, x, y + 1, stepCounter + 1)) 
            {   return true;    } //return true for if you can go in
                                  // that direction
        
        // unmark the current location if the move leads to a dead end
       else
       { 
            grid[x][y] = ' ';        
       }
    }

    // return false if all moves lead 
    //to no good viable path found 
    return false;
}