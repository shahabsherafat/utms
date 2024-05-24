#pragma once
#include "consts.hpp"

class Course{
    protected:
        int id;
        string name;
        int credit;
        int prerequisite;
        vector<int> major_ids;
    public:
        Course(int init_id, string init_name, int init_credit, int init_prerequisite, vector<int> major_ids);
        // void print();

};