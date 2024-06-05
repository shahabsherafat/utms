#pragma once
#include "consts.hpp"
#include "course.hpp"
#include "date_and_time.hpp"
#include "post.hpp"

class OfferedCourse{
    private:
        int id;
        string name;
        int source_course_id;
        int capacity;
        int class_number;
        string professor_name;
        Time holding_time;
        Date exam_date;
        vector<pair<string, Post*>> channel;
        int last_channel_post_id = STARTING_COURSE_POST_ID;

    public:
        OfferedCourse(int init_id, string init_name,int course_id, int init_capacity,int init_class_number,
                      string init_professor_name, Time ht, Date ed);

        void write_general_info(vector<string>& output);
        void write_detailed_info(vector<string>& output);

        int get_id();
        string get_name();
        int get_course_id();
        Time get_holding_time();
        Date get_exam_date();
        int get_last_channel_post_id();
        void add_post_to_channel(string author_name, Post* new_post);
        
        void write_channel(vector<string>& output);
        void write_post(int post_id, vector<string>& output);
};