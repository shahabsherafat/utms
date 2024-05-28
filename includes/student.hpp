#pragma once

#include "user.hpp"
#include "offeredcourse.hpp"

class Student : public User{
    private:
        int major_id;
        string major_name;
        int semester;
        vector<OfferedCourse*> attended_courses;
    public:
        Student(int init_id, string init_name, int init_major_id, string init_major_name
                , int init_semester, string init_password);
        string get_personal_info_string();
        int get_major_id();
        int get_semester();
        void add_attended_course(OfferedCourse* o);
        void write_enrolled_courses(vector<string>& output);
        void remove_enrolled_course(OfferedCourse* o);
};