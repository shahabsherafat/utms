#include "consts.hpp"

class Post{
    private:
        int id;
        string title;
        string message;
        
    public:
        Post(string init_title, string init_message, int init_id);
        int get_id();
        string get_title();
        string get_message();

};