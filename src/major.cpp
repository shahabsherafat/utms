#include "../includes/major.hpp"


Major::Major(int init_id, string init_name){
    id = init_id;
    name = init_name;
}

string Major::get_name(){
    return name;
}

int Major::get_id(){
    return id;
}