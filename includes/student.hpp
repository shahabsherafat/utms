#pragma once

#include "user.hpp"

class Student : public User{
    private:
        int major_id;
        string major_name;
        int semester;
        vector<string> attended_courses = {"ap"};
        string get_personal_info_string();
    public:
        Student(int init_id, string init_name, int init_major_id, string init_major_name
                , int init_semester, string init_password);
        void write_page_info(vector<string>& output);
        void write_post_by_id(int id, vector<string>& output);
        void connect(User* connected);
        void add_notification(string notification_message);
};