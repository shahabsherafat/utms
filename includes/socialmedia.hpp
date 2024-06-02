#pragma once
#include "course.hpp"
#include "major.hpp"
#include "user.hpp"
#include "student.hpp"
#include "professor.hpp"
#include "admin.hpp"
#include "offeredcourse.hpp"
#include "notification.hpp"

class SocialMedia{
    private:
        vector<Course*> courses;
        vector<Major*> majors;
        vector<User*> users;
        vector<OfferedCourse*> offered_courses;
        bool is_logged_in = false;
        User* logged_in_user = NULL;
        int last_offered_course_id = STARTING_OFFERED_COURSES_ID;
    public:
        SocialMedia();
        ~SocialMedia();
        
        void add_course(int id, string name, int credit, int prerequisite, vector<int> major_ids);
        void add_major(int id, string name);
        void add_student(int id,string name,int major_id,int semester,string password);
        void add_professor(int id,string name,int major_id,string position,string password);

        Time make_time_by_string(string time_string);
        Date make_date_by_string(string date_string);
        string find_major_name_by_id(int major_id);
        User* find_user_by_id(int id);
        Course* find_course_by_id(int id);
        OfferedCourse* find_offered_course_by_id(int id);
        void notify_every_one(notif n);

        void login(int id, string password);
        void logout();
        void add_post(string title, string message, string image_address);
        void connect(int id);
        void offer_new_course(int course_id, int professor_id, int capacity, string time,
                              string date, int class_number);
        void set_profile_photo(string photo_address);

        void write_all_offered_courses(vector<string>& output);
        void write_offered_course_by_id(int id, vector<string>& output);
        void write_page_info_by_id(int id, vector<string>& output);
        void write_post_by_id(int user_id, int post_id, vector<string>& output);
        void write_notifications(vector<string>& output);
        void write_enrolled_courses(vector<string>& output);

        void remove_post(int id);
        void remove_enrolled_course(int id);

        void enroll_course(int id);
};