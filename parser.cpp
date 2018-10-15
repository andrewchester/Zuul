#include <iostream>
#include <string.h>
#include "parser.h"

void Parser::toLower(char* str)
{
  //Loops over str
  for(int i = 0; i < strlen(str); i++)
  {
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
bool Parser::parseCommand(char* command){
    if(strncmp(command, "go ", 3) == 0){
        return true;
    }
    if(strncmp(command, "drop ", 5) == 0){
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