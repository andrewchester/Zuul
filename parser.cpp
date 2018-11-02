#include <iostream>
#include <string.h>
#include <map>
#include "parser.h"
#include "player.h"

char* Parser::substr(char* str, int begin, int end){
  if (begin > end || begin < 0 || end >= strlen(str))
	return str;

  char* substr = new char[end - begin + 1];
  for(int i = 0; i < sizeof(substr); i++)
    substr[i] = 0;

  for (int i = begin; i <= end; i++)
    substr[i - begin] = str[i];

  return substr;
}

void Parser::toLower(char* str){
  //Loops over str
  for(int i = 0; i < strlen(str); i++){
    int asciiValue = (int)str[i]; //Get the ascii value of the character
    if(asciiValue >= 65 && asciiValue <= 90) //If it's uppercase
      str[i] = (char)(asciiValue + 32); //Make it lowercase by increasing the ascii value by 32
  }
}

//Return true or false based on if input is a valid command
bool Parser::isValid(char* input){
    this->toLower(input);
    if(strncmp(input, "go ", 3) == 0) return true;
    if(strncmp(input, "drop ", 5) == 0) return true;
    if(strncmp(input, "help", 4) == 0) return true;
    if(strncmp(input, "quit", 4) == 0) return true;
    if(strncmp(input, "pickup ", 7) == 0) return true;
    return false;
}
bool Parser::parseCommand(char* command, Player* player){
    if(strncmp(command, "go ", 3) == 0){
      char* direction = substr(command, 3, strlen(command) - 1);	
      if(player->getCurrentRoom()->has(direction))
		 player->setCurrentRoom(player->getCurrentRoom()->get(direction));
      else
		std::cout << "Not a valid direction" << std::endl;
      
	  delete direction;
      return true;
    }
    if(strncmp(command, "drop ", 5) == 0){
		char* item = substr(command, 5, strlen(command) - 1);
		std::vector<char*>::iterator it;
		if(player->hasItem(item)){
			player-getCurrentRoom()->addItem(player->getItem(item));
		}
		
        return true;
    }
    if(strncmp(command, "pickup ", 7) == 0){
        return true;
    }

    if(strncmp(command, "help", 4) == 0)
        std::cout << "Commands are: go, drop, pickup,  help, and quit" << std::endl;
    if(strncmp(command, "quit", 4) == 0)
        return false;
    return true;
}

//parseFromFile() reads in data from a txt file and generates rooms from it
//It takes the map to add the rooms to, and the path from which to get the room data
/*
  Format of rooms.txt:
    commas instead of spaces, for some reason, when looping over all the characters,  it doesn't recognize spaces
    A '|' indicates that there's a string with spaces that need to be added in, it's closed by '|' as well.
    The first variable is the name, the second is the description, then it has its items off the end.
    The object is closed with a /, you need a comma between the end of the variable and the / so the parser knows to stop
    Example:
      examplename,|description,here|exampleitem1,exampleitem2,/
*/
void Parser::parseFromFile(std::vector<Room*>* rooms, const char* path){
  std::ifstream file(path); //Initializing file from the path variable passed in
  char c; //This holds the current character, when iterating over the file, it goes character by characetr(the other method that went line by line used std::string, which we're not allowed to use) 
  std::vector<char*> values; //This holds the spliced strings, which are the ones in between the commas
  char current[100];//This holds the current string, it will gradually fill up with characters until it reaches a comma
  for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill the string with zeros
  int pos = 0; //Holds the current pos in the string, used to know where to add the character from the file
  bool copyingString = false;
  while(file >> c){ //Loop over each character in file
    if(c == ',' && !copyingString){ //The end of a variable is reached, indicated by a comma
      char* copy = new char[100]; //Create a copy of current cause we can't pass be passing a pointer to the same character array all the time, later we'll free the memory associated with the copy
      strcpy(copy, current); //Copying current
      values.push_back(copy); //Add whatever is in current(using copy) to values, should just be all the characters added since the last space or the start of the line
      pos = 0; //Reset the position so we begin writing to current at the start of the array
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
    }else if(c == '/'){ //If we reach the end of the object, we know we've gotten all the data for the room into values
      //Creating copies of all of the variables in values(even though we've got pointers for those but they're getting deleted this works anyways)
      char* name = new char[strlen(values.at(0))]; //Creating a copy of the name
      char* description = new char[strlen(values.at(0))];

      strcpy(name, values.at(0)); //Copying first item in values to name
      strcpy(description, values.at(1));  //Copying the second item, which should be the description, to description

      //Add the rest of the values as items
      Room* newRoom = new Room(name, description);
      for(std::vector<char*>::iterator it = values.begin() + 2; it != values.end(); ++it){ //From the y value, loop to the end of the array. These values should all be the items.
        char* itemPointer = new char[strlen(*it)]; //Create a copy of it, it'll be deleted in the destructor of Room
        strcpy(itemPointer, *it);
        newRoom->addItem(itemPointer); //Add the item
      }
      rooms->push_back(newRoom); //Add the new room just created to rooms
      values.clear(); //values.clear() calls the destructor of every object in the vector, so no need to iterate over the vector deleting the pointers
      pos = 0; //Reset position
      for(int i = 0; i < strlen(current); i++) current[i] = 0; //Fill current with zeros
      current[0] = '\0';
    }else if(c == '|'){
      if(copyingString){
        copyingString = false;
        char* copy = new char[100]; //Create a copy of current cause we can't pass be passing a pointer to the same character array all the time, later we'll free the memory associated with the copy
        strcpy(copy, current); //Copying current
        values.push_back(copy); //Add whatever is in current(using copy) to values, should just be all the characters added since the last space or the start of the line
        pos = 0; //Reset the position so we begin writing to current at the start of the array
        for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
      }else{
        copyingString = true;
      }
    }else {
      if(c != 0 && c != ',') //If c isn't a zero, then write it to current
        current[pos] = c;
      if (c == ',')
        current[pos] = ' ';
      if(pos + 1 < sizeof(current))
        pos++; //Increment position when we write to current
    }
  }
  file.close(); //Close the file stream
}
/*
  This function generates the connections between the rooms from the file connections.txt
  Format of connections.txt:
    The purpose of this is to map all the initialized rooms to each other using the pointer values NORTH, SOUTH, EAST, WEST, which are null, the map must contain initialized rooms with name values
    Similar format to rooms.txt, it reads in characters until it sees '>', Then it takes all the characters before it as the room's name. The connected rooms are seperated by spaces in the format N E S W
    Example:
        examplename>0,0,testroom,0,/

    In this example, the room 'examplename' would only be connected to testroom to the south.
*/
void Parser::parseConnectionsFromFile(std::vector<Room*>* rooms, const char* path){
  std::ifstream file(path); //Initializing file from the path variable passed in
  char c; //This holds the current character, when iterating over the file, it goes character by characetr(the other method that went line by line used std::string, which we're not allowed to use) 
  std::vector<char*> values; //This holds the spliced strings, which are the ones in between the commas
  char current[100];//This holds the current string, it will gradually fill up with characters until it reaches a comma
  Room* currentRoom;
  for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill the string with zeros
  int pos = 0; //Holds the current pos in the string, used to know where to add the character from the file
  while(file >> c){ //Loop over each character in file
    if(c == ','){ //The end of a variable is reached, indicated by a comma
      char* copy = new char[75]; //Create a copy of current cause we can't pass be passing a pointer to the same character array all the time, later we'll free the memory associated with the copy
      strcpy(copy, current); //Copying current
      values.push_back(copy); //Add whatever is in current(using copy) to values, should just be all the characters added since the last space or the start of the line
      pos = 0; //Reset the position so we begin writing to current at the start of the array
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
    }else if(c == '/'){ //If we reach the end, we know we've gotten all the data for the room connections
      if(currentRoom == 0){
        std::cout << "currentRoom is null during assignment" << std::endl;
        return;
      }
      //There should be 4 items in values, one for each NORTH, EAST, SOUTH, WEST
      //If one of them isn't null, then we need to generate the connection by setting the pointer values in currentRoom
      if(*values.at(0) != '0'){  //NORTH
        std::vector<Room*>::iterator it;
        for(it = rooms->begin(); it != rooms->end(); ++it){
          if(strcmp((*it)->getName(), values.at(0)) == 0){
            currentRoom->getExits()->insert(std::pair<const char*, Room*>("north", *it));
            break;
          }
        }
      }else {
        currentRoom->getExits()->insert(std::pair<const char*, Room*>("north", 0));        
      }
      
      if(*values.at(1) != '0'){  //EAST
        std::vector<Room*>::iterator it;
        for(it = rooms->begin(); it != rooms->end(); ++it){
          if(strcmp((*it)->getName(), values.at(1)) == 0){
            currentRoom->getExits()->insert(std::pair<const char*, Room*>("east", *it));
            break;
          }
        }
      }else {
        currentRoom->getExits()->insert(std::pair<const char*, Room*>("east", 0));        
      }

      if(*values.at(2) != '0'){  //SOUTH
        std::vector<Room*>::iterator it;
        for(it = rooms->begin(); it != rooms->end(); ++it){
          if(strcmp((*it)->getName(), values.at(2)) == 0){
            currentRoom->getExits()->insert(std::pair<const char*, Room*>("south", *it));
            break;
          }
        }
      }else {
        currentRoom->getExits()->insert(std::pair<const char*, Room*>("south", 0));        
      }

      if(*values.at(3) != '0'){  //WEST
        std::vector<Room*>::iterator it;
        for(it = rooms->begin(); it != rooms->end(); ++it){
          if(strcmp((*it)->getName(), values.at(3)) == 0){
            currentRoom->getExits()->insert(std::pair<const char*, Room*>("west", *it));
            break;
          }
        }
      }else {
        currentRoom->getExits()->insert(std::pair<const char*, Room*>("west", 0));        
      }

      for (std::vector<char*>::iterator it = values.begin(); it != values.end(); ++it) delete *it; //Delete all the copied pointers from before
      values.clear(); //Empty the vector
      pos = 0; //Reset position
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros

    }else if(c == '>'){
      //Loop over the map and see if the name entered is in the map, if it is, then set currentRoom equal to it. This is why all rooms need to be initialized before running this function
      std::vector<Room*>::iterator it;
      for(it = rooms->begin(); it != rooms->end(); ++it){
        if(strcmp((*it)->getName(), current) == 0){
          currentRoom = *it;
          break;
        } 
      }
      if(currentRoom == 0){
        std::cout << "Couldn't find a room with the name of " << current << std::endl;
        break;
      }

      pos = 0; //Reset the position so we begin writing to current at the start of the array
      for(int i = 0; i < sizeof(current); i++) current[i] = 0; //Fill current with zeros
    }else {
      if(c != 0 && c != ',') //If c isn't a zero, then write it to current
        current[pos] = c;
      if(pos + 1 < sizeof(current))
        pos++; //Increment position when we write to current
    }
  }
  file.close(); //Close the file stream
}
