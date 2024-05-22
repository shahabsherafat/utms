#pragma once

#include "consts.hpp"

class User{
    protected:
        int id;
        string name;
        int major_id;
        string password;
    public:
        User(int init_id, string init_name, int init_major_id, string init_password);
        int get_id();
        bool is_authenticated(string entered_password);
        // virtual void print() = 0;
        string get_password(){return password;}
};

// stringstream S(str) 

// S>> method >> command

// GET                     sjdfskb