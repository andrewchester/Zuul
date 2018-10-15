class Parser{
    private:
        void toLower(char* str);
    public:
        bool isValid(char* command);
        bool parseCommand(char* command);
};