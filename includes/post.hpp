#include "consts.hpp"

class Post{
    private:
        int id;
        string title;
        string message;
        string image_address;
        
    public:
        Post(string init_title, string init_message, int init_id, string init_image_address);
        int get_id();
        string get_title();
        string get_message();
};