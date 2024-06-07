#pragma once
#include "medium.hpp"

class Post : public Medium{
    private:
        string title;
        string image_address;
        
    public:
        Post(string init_title, string init_message, int init_id, string init_image_address);
        string get_title();
};