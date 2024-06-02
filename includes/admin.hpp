#include "user.hpp"

class Admin : public User{
    private:

    public:
        Admin(int init_id, string init_password, string init_name);
        string get_personal_info_string();
        
};