#pragma once

#include "user.hpp"

class Student : public User{
    private:
        int semester;
    public:
        Student(int init_id, string init_name, int init_major_id, int init_semester, string init_password);
        // void print();
};