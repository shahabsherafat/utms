#include "../includes/admin.hpp"

Admin::Admin(int init_id, string init_password, string init_name) : 
             User(init_id, init_password, init_name){
}

string Admin::get_personal_info_string(){
    return name + NEWLINE;
}