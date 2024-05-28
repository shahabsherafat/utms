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
        int get_id();
        string get_name();
        bool can_professor_take_this_course(int major_id);
        bool can_student_take_this_course(int major_id, int semester);
};