#include "../includes/post.hpp"


Post::Post(string init_title, string init_message, int init_id, string init_image_address) : 
           Medium(init_message, init_id){
    title = init_title;
    image_address = init_image_address;
}

string Post::get_title(){
    return title;
}

string Post::get_image_address(){
    return image_address;
}