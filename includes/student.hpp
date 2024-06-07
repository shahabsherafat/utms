#pragma once
#include "user.hpp"

class Student : public User{
    private:
        int major_id;
        string major_name;
        int semester;
        vector<OfferedCourse*> attended_courses;
        vector<OfferedCourse*> assisting_courses;
    public:
        Student(int init_id, string init_name, int init_major_id, string init_major_name
                , int init_semester, string init_password);
        string get_personal_info_string();
        int get_major_id();
        int get_semester();
        void add_attended_course(OfferedCourse* o);
        void write_enrolled_courses(vector<string>& output);
        void remove_enrolled_course(OfferedCourse* o);
        void add_course_post_if_you_can(OfferedCourse* target_course, string title,
                                        string message, string image_address);
        bool is_participating_in_this_course(int course_id);
        void add_assisting_course(OfferedCourse* assisting_course);
        string get_ta_request_text();
};