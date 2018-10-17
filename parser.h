#include <fstream>
#include <vector>
#include <map>

#include "room.h"

class Parser{
    private:
        void toLower(char* str);
    public:
        bool isValid(char* command);
        bool parseCommand(char* command);
        void parseFromFile(std::vector<Room*>* rooms, const char* path);
        void parseConnectionsFromFile(std::vector<Room*>* rooms, const char* path);
};