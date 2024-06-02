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
                personal_info += offered_courses[i] -> get_name();
            }

            else{
                personal_info += offered_courses[i] -> get_name() + COMMA;
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

void Professor::add_offered_course(OfferedCourse* o){
    Time time = o->get_holding_time();

    for(OfferedCourse* of : offered_courses){
        if(of->get_holding_time().intersects(time)){
            throw runtime_error(PERMISSION_DENIED_RESPONSE);
        }
    }   
    offered_courses.push_back(o);
}