#include "../includes/course.hpp"

Course::Course(int init_id, string init_name, int init_credit, int init_prerequisite, vector<int> init_major_ids){
    id = init_id;
    name = init_name;
    credit = init_credit;
    prerequisite = init_prerequisite;
    major_ids = init_major_ids;
}

int Course::get_id(){
    return id;
}

string Course::get_name(){
    return name;
}

bool Course::can_take_this_course(int major_id){
    if(find(major_ids.begin(), major_ids.end(), major_id) != major_ids.end()){
        return true;
    }

    else{
        return false;
    }
}