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
        void assign_post_factors(stringstream& arguments, string& title, string& message, string& image_address);
        void handle_add_post(stringstream& arguments);
        void handle_connect(stringstream& arguments);
        void handle_course_offer(stringstream& arguments);
        void handle_set_profile_photo(stringstream& arguments);

        void handle_see_courses(stringstream& arguments);
        void handle_see_personal_page(stringstream& arguments);
        void handle_see_post(stringstream& arguments);
        void handle_see_notifications();
        void handle_see_enrolled_courses();

        void handle_remove_post_by_id(stringstream& arguments);
        void handle_remove_enrolled_course(stringstream& arguments);
        void handle_course_enroll(stringstream& arguments);

        bool is_number(string id);
        bool is_natural(string id);
        bool is_arithmetic(string id);
        int find_index(const vector<string>& input, string parameter);
        string get_qouted_text(stringstream& arguments);
};