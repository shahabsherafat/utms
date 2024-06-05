#pragma once
#include "medium.hpp"
#include "offeredcourse.hpp"

class TAForm : public Medium{
    private:
        OfferedCourse* course;
        
    public:
        TAForm(string init_message, int init_id, OfferedCourse* init_course);
        OfferedCourse* get_course();
        // int get_id();
};