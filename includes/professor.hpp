#pragma once
#include "user.hpp"
#include "offeredcourse.hpp"

class Professor : public User{
    private:
        int major_id;
        string major_name;
        string position;
        vector<OfferedCourse*> offered_courses;

    public:
        Professor(int init_id, string init_name, int init_major_id,string init_major_name, 
                  string position, string init_password);
        string get_personal_info_string();
        int get_major_id();
        string get_name();
        void add_offered_course(OfferedCourse* o);
        
};