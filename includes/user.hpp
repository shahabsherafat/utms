#pragma once
#include "consts.hpp"
#include "post.hpp"
#include "taform.hpp"
#include "notification.hpp"
#include "date_and_time.hpp"
#include "offeredcourse.hpp"

class User{
    protected:
        int id;
        string password;
        string name;
        string profile_photo_address;
        int last_post_id = 0;
        vector<Medium*> media;
        vector<User*> connected_users;
        vector<notif> notifications;
    public:
        User(int init_id, string init_password, string init_name);
        ~User();
        int get_id();
        string get_name();
        string get_profile_image();
        string get_next_post_id();
        bool is_authenticated(string entered_password);
        void add_post(string title, string message, string image_address);
        void remove_post(int id);
        virtual string get_personal_info_string() = 0;
        void write_page_info(vector<string>& output);
        void write_post_by_id(int id, vector<string>& output);
        void write_notifications(vector<string>& output);
        void connect(User* connected);
        void add_notification(notif n);
        void notify_to_connected_users(notif n);
        void set_profile_photo(string photo_address);
        virtual void add_course_post_if_you_can(OfferedCourse* target_course, string title
                                                , string message, string image_address) = 0;
        virtual bool is_participating_in_this_course(int course_id) = 0;

        vector<vector<string>> get_posts();
};