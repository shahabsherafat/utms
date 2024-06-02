#pragma once
#include "consts.hpp"
class Major{
    private:
        int id;
        string name;
    public:
        Major(int init_id, string init_name);
        int get_id();
        string get_name();
};