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

int Professor::get_major_id(){
    return major_id;
}

string Professor::get_name(){
    return name;
}

void Professor::add_working_time(Time t){
    for(Time time : working_times){
        if(time.intersects(t)){
            throw runtime_error(PERMISSION_DENIED_RESPONSE);
        }
    }

    working_times.push_back(t);
}