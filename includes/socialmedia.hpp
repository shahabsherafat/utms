#pragma once
#include "course.hpp"
#include "major.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "offeredcourse.hpp"

class SocialMedia{
    private:
        vector<Course*> courses;
        vector<Major*> majors;
        vector<User*> users;
        vector<OfferedCourse*> offered_courses;

        
        bool is_logged_in = false;
        User* logged_in_user = NULL;

    public:
        SocialMedia();
        void add_course(int id, string name, int credit, int prerequisite, vector<int> major_ids);
        void add_major(int id, string name);
        void add_student(int id,string name,int major_id,int semester,string password);
        void add_professor(int id,string name,int major_id,string position,string password);
        void login(int id, string password);
        void logout();
        void write_all_offered_courses(vector<string> output);
        void write_offered_course_by_id(int id, vector<string> output);
        // void test_print();


};