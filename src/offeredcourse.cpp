#include "../includes/offeredcourse.hpp"
OfferedCourse::OfferedCourse(int init_id, string init_name,int course_id, int init_capacity,int init_class_number,
                             string init_professor_name, Time ht, Date ed) :
    id(init_id), name(init_name), source_course_id(course_id), capacity(init_capacity),class_number(init_class_number),
    professor_name(init_professor_name),holding_time(ht), exam_date(ed){}

void OfferedCourse::write_general_info(vector<string>& output){
    output.push_back(to_string(id) + SPACE + name + SPACE + to_string(capacity) + SPACE + professor_name + NEWLINE);
}

void OfferedCourse::write_detailed_info(vector<string>& output){
    output.push_back(to_string(id) + SPACE + name + SPACE + to_string(capacity) + SPACE + professor_name 
                     + SPACE + holding_time.get_time_string() + SPACE + exam_date.get_date_string() 
                     + SPACE + to_string(class_number) + NEWLINE);
}

int OfferedCourse::get_id(){
    return id;
}

string OfferedCourse::get_name(){
    return name;
}

int OfferedCourse::get_course_id(){
    return source_course_id;
}

Time OfferedCourse::get_holding_time(){
    return holding_time;
}

Date OfferedCourse::get_exam_date(){
    return exam_date;
}

int OfferedCourse::get_last_channel_post_id(){
    return last_channel_post_id;
}

void OfferedCourse::add_post_to_channel(string author_name, Post* new_post){
    channel.push_back(make_pair(author_name, new_post));
    last_channel_post_id ++;
}

void OfferedCourse::write_channel(vector<string>& output){
    for(int i = channel.size() - 1; i >= 0; i--){
        output.push_back(to_string(channel[i].second->get_id()) + 
                         SPACE + channel[i].first + SPACE + channel[i].second->get_title() + NEWLINE);
    }
}

void OfferedCourse::write_post(int post_id, vector<string>& output){
    string author_name = channel[post_id - 1].first;
    Post* target_post = channel[post_id - 1].second;
    output.push_back(to_string(post_id) + SPACE + author_name + SPACE + target_post->get_title() +
                     SPACE + target_post->get_message() + NEWLINE);
}