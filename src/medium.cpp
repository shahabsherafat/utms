#include "../includes/medium.hpp"

int Medium::get_id(){
    return id;
}

string Medium::get_message(){
    return message;
}

Medium::Medium(string init_message, int init_id){
    message = init_message;
    id = init_id;
}