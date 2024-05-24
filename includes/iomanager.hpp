#pragma once
#include "consts.hpp"
#include "socialmedia.hpp"

class IOManager{
    private:
        SocialMedia* utms;


    public:
        IOManager(SocialMedia* social_media);
        void read_majors(string majors_file_address);
        void read_courses(string courses_file_address);
        void read_users(string students_file_address, string professors_file_address);

        void run_command_line();
        
        void handle_POST_request(stringstream& line_stream);
        void handle_GET_request(stringstream& line_stream);
        void handle_DELETE_request(stringstream& line_stream);
        void handle_PUT_request(stringstream& line_stream);

        void handle_login(stringstream& arguments);
        void handle_logout();
        void handle_add_post(stringstream& arguments);
        void handle_connect(stringstream& arguments);

        void handle_see_courses(stringstream& arguments);
        void handle_see_personal_page(stringstream& arguments);
        void handle_see_post(stringstream& arguments);
        void handle_see_notifications();


        void handle_remove_post_by_id(stringstream& arguments);




        bool is_number(string id);
        bool is_natural(string id);
        bool is_arithmetic(string id);
        



        



};