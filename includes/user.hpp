#pragma once

#include "consts.hpp"
#include "post.hpp"
#include "notification.hpp"
#include "date_and_time.hpp"

class User{
    protected:
        int id;
        string password;
        string name;

        int last_post_id = 0;
        vector<Post*> posts;

        vector<User*> connected_users;
        vector<notif> notifications;
    public:
        User(int init_id, string init_password, string init_name);
        ~User();
        int get_id();
        bool is_authenticated(string entered_password);
        void add_post(string title, string message);
        void remove_post(int id);
        virtual string get_personal_info_string() = 0;
        void write_page_info(vector<string>& output);
        void write_post_by_id(int id, vector<string>& output);
        void write_notifications(vector<string>& output);
        void connect(User* connected);
        void add_notification(notif n);
        void notify_to_connected_users(notif n);

};