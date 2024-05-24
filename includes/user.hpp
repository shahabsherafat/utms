#pragma once

#include "consts.hpp"
#include "post.hpp"
class User{
    protected:
        int id;
        string password;
        string name;

        int last_post_id = 0;
        vector<Post*> posts;

        vector<User*> connected_users;
        vector<string> notifications;
    public:
        User(int init_id, string init_password, string init_name);
        int get_id();
        bool is_authenticated(string entered_password);
        void add_post(string title, string message);
        void remove_post(int id);
        virtual void write_page_info(vector<string>& output) = 0;
        virtual void write_post_by_id(int id, vector<string>& output);
        void write_notifications(vector<string>& output);
        void connect(User* connected);
        void add_notification(string notification_text);
        void notify_to_connected_users(string notification_text);

};