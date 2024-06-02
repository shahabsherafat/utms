#include "../includes/post.hpp"


Post::Post(string init_title, string init_message, int init_id, string init_image_address){
    id = init_id;
    title = init_title;
    message = init_message;
    image_address = init_image_address;
}

int Post::get_id(){
    return id;
}

string Post::get_title(){
    return title;
}

string Post::get_message(){
    return message;
}