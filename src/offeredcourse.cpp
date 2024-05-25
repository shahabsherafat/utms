#include "../includes/offeredcourse.hpp"

OfferedCourse::OfferedCourse(int init_id, string init_name, int init_capacity,int init_class_number,
                             string init_professor_name, Time ht, Date ed) :
    id(init_id), name(init_name), capacity(init_capacity),class_number(init_class_number),
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