#pragma once

#include "user.hpp"

class Professor : public User{
    private:
        string position;
    public:
        Professor(int init_id, string init_name, int init_major_id, string position, string init_password);
        // void print();
};