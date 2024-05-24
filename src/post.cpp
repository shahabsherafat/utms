#include "../includes/post.hpp"

Post::Post(string init_title, string init_message, int init_id){
    title = init_title;
    message = init_message;
    id = init_id;
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