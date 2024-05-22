#include "../includes/user.hpp"

User::User(int init_id, string init_name, int init_major_id, string init_password){
    id = init_id;
    name = init_name;
    major_id = init_major_id;
    password = init_password;
}

int User::get_id(){
    return id;
}

bool User::is_authenticated(string entered_password){
    return entered_password == password;
}
