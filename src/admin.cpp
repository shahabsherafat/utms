#include "../includes/admin.hpp"


Admin::Admin(int init_id, string init_password, string init_name) : 
             User(init_id, init_password, init_name){
}

string Admin::get_personal_info_string(){
    return name + NEWLINE;
}

void Admin::add_course_post_if_you_can(OfferedCourse* target_course, string title,
                                       string message, string image_address){
    throw runtime_error(PERMISSION_DENIED_RESPONSE);
}

bool Admin::is_participating_in_this_course(int course_id){
    return false;
}
