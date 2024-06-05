#include "user.hpp"

class Admin : public User{
    private:

    public:
        Admin(int init_id, string init_password, string init_name);
        string get_personal_info_string();
        void add_course_post_if_you_can(OfferedCourse* target_course, string title,
                                        string message, string image_address);
        bool is_participating_in_this_course(int course_id);
};