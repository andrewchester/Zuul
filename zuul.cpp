/*
* Andrew Chester, Per. 2 Zuul
* Zuul is a text based console game that allows you to explore rooms and pickup items
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include "room.h"
#include "player.h"

//parseFromFile() reads in data from a txt file and generates rooms from it
//It takes the vector to add the rooms to, and the path from which to get the room data
/*
  Format of txt:

    commas between variables, for some reason, when looping over all the characters,  it doesn't recognize spaces, so I used commas instead
    first three variables are name, x, and y, the rest are items to be added to the room
    the end of a room object is marked with /

    Example:
      examplename,0,0,exampleitem,exampleitem2,/
*/
void parseFromFile(std::vector<Room*>* rooms, const char* path){
  std::ifstream file(path); //Initializing file from the path variable passed in
  char c; //This holds the current character, when iterating over the file, it goes character by characetr(the other method that went line by line used std::string, which we're not allowed to use) 
  std::vector<char*> values; //This holds the spliced strings, which are the ones in between the commas
  char current[30];//This holds the current string, it will gradually fill up with characters until it reaches a comma
  for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill the string with zeros
  int pos = 0; //Holds the current pos in the string, used to know where to add the character from the file
  while(file >> c){ //Loop over each character in file
    if(c == ','){ //The end of a variable is reached, indicated by a comma
      char* copy = new char[30]; //Create a copy of current cause we can't pass be passing a pointer to the same character array all the time, later we'll free the memory associated with the copy
      strcpy(copy, current); //Copying current
      values.push_back(copy); //Add whatever is in current(using copy) to values, should just be all the characters added since the last space or the start of the line
      pos = 0; //Reset the position so we begin writing to current at the start of the array
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
    }else if(c == '/'){ //If we reach the end of the object, we know we've gotten all the data for the room into values
      //Creating copies of all of the variables in values(even though we've got pointers for those but they're getting deleted this works anyways)
      char* name = new char[strlen(values.at(0))]; //Creating a copy of the name
      strcpy(name, values.at(0)); //Copying first item in values to name
      int* x = new int; //Allocating memory for 2 ints
      int* y = new int;
      *x = atoi(values.at(1)); //Setting the values of those ints to the items at indexes 1,2 of values, which should be the x, y of the room
      *y = atoi(values.at(2));
      Room* newRoom = new Room(name, x, y); //Create a new room using the first three values in the values vector, which should always be name, x, y
      for(std::vector<char*>::iterator it = values.begin() + 3; it != values.end(); ++it){ //From the y value, loop to the end of the array. These values should all be the items.
        char* itemPointer = new char[strlen(*it)]; //Create a copy of it, it'll be deleted in the destructor of Room
        strcpy(itemPointer, *it);
        newRoom->addItem(itemPointer); //Add the item
      }
      rooms->push_back(newRoom); //Add the new room just created to rooms
      for (std::vector<char*>::iterator it = values.begin(); it != values.end(); ++it) delete *it; //Delete all the copied pointers from before
      values.clear(); //Empty the vector
      pos = 0; //Reset position
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
    }else {
      if(c != 0) //If c isn't a zero, then write it to current
        current[pos] = c;
      pos++; //Increment position when we write to current
    }
  }
  file.close(); //Close the file stream
}

int main(){
  std::vector<Room*> rooms; //Vector to hold all the rooms in the game
  parseFromFile(&rooms, "rooms.txt"); //Parse rooms.txt and add all the rooms into rooms, more information in the comments surrounding parseFromFile()
  
  Player p = Player(rooms.at(0));
  std::cout << "Player is in: " << p.getCurrentRoom()->getName() << std::endl;
  
  std::cout << "Items in " << p.getCurrentRoom()->getName() << ": "; 
  p.getCurrentRoom()->printItems();
  std::cout << std::endl;
  
  p.pickup("rug");

  std::cout << "Items in " << p.getCurrentRoom()->getName() << ": "; 
  p.getCurrentRoom()->printItems();
  std::cout << std::endl;

  return 0;
}
