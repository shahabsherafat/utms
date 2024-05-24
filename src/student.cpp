#include "../includes/student.hpp"

Student::Student(int init_id, string init_name, int init_major_id, string init_major_name, 
                 int init_semester, string init_password):
                 User(init_id, init_password, init_name)
{
    major_id = init_major_id;
    major_name = init_major_name;
    semester = init_semester;
}

string Student::get_personal_info_string(){
    string personal_info = name + SPACE + major_name + SPACE + to_string(semester);

    if(attended_courses.size() != 0){
        personal_info += SPACE;

        for(int i = 0; i<attended_courses.size(); i++){
            if(i == attended_courses.size() - 1){
                personal_info += attended_courses[i];
            }

            else{
                personal_info += attended_courses[i] + COMMA;
            }
        }
    }

    personal_info += NEWLINE;
    return personal_info;
}

void Student::write_page_info(vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        output.push_back(to_string(p->get_id()) + SPACE + p->get_title() + NEWLINE);
    }
}

void Student::write_post_by_id(int id, vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        if(p->get_id() == id){
            output.push_back(to_string(id) + SPACE + p->get_title() + SPACE + p->get_message() + NEWLINE);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}