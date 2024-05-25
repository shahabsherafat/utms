#pragma once

#include "user.hpp"

class Professor : public User{
    private:
        int major_id;
        string major_name;
        string position;
        vector<string> offered_courses;
        vector<Time> working_times;

    public:
        Professor(int init_id, string init_name, int init_major_id,string init_major_name, 
                  string position, string init_password);
        string get_personal_info_string();
        int get_major_id();
        string get_name();
        void write_page_info(vector<string>& output);
        void write_post_by_id(int id, vector<string>& output);
        void connect(User* connected);
        void add_notification(string notification_message);
        void add_working_time(Time t);
        
};