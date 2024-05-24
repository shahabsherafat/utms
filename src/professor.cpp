#include "../includes/professor.hpp"

Professor::Professor(int init_id, string init_name, int init_major_id, string init_major_name, 
                     string init_position, string init_password) : 
                     User(init_id, init_password, init_name)
{
    major_id = init_major_id;
    major_name = init_major_name;
    position = init_position;
}

string Professor::get_personal_info_string(){
    string personal_info = name + SPACE + major_name + SPACE + position;

    if(offered_courses.size() != 0){
        personal_info += SPACE;

        for(int i = 0; i<offered_courses.size(); i++){
            if(i == offered_courses.size() - 1){
                personal_info += offered_courses[i];
            }

            else{
                personal_info += offered_courses[i] + COMMA;
            }
        }
    }

    personal_info += NEWLINE;
    return personal_info;
}


void Professor::write_page_info(vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        output.push_back(to_string(p->get_id()) + SPACE + p->get_title() + NEWLINE);
    }
}

void Professor::write_post_by_id(int id, vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        if(p->get_id() == id){
            output.push_back(to_string(id) + SPACE + p->get_title() + SPACE + p->get_message() + NEWLINE);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}