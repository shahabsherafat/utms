#pragma once
#include "consts.hpp"

class Medium{
    private:
        int id;
        string message;
        
    public:
        Medium(string init_message, int init_id);
        virtual int get_id();
        string get_message();
};