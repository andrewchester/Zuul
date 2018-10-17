#include <fstream>
#include <map>

#include "room.h"

class Parser{
    private:
        void toLower(char* str);
    public:
        bool isValid(char* command);
        bool parseCommand(char* command);
        void parseFromFile(std::map<char*, Room*>* rooms, const char* path);
};