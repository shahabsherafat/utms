#include "../includes/socialmedia.hpp"

SocialMedia::SocialMedia(){

}

void SocialMedia::add_course(int id, string name, int credit, int prerequisite, vector<int> major_ids){
    Course* new_course = new Course(id, name, credit, prerequisite, major_ids);
    courses.push_back(new_course);
}

void SocialMedia::add_major(int id, string name){
    Major* new_major = new Major(id, name);
    majors.push_back(new_major);
}

void SocialMedia::add_student(int id, string name, int major_id, int semester, string password){
    string major_name = find_major_name_by_id(major_id);
    Student* new_student = new Student(id, name, major_id, major_name, semester, password);
    users.push_back(new_student);
}

void SocialMedia::add_professor(int id, string name, int major_id, string position, string password){
    string major_name = find_major_name_by_id(major_id);
    Professor* new_professor = new Professor(id, name, major_id, major_name, position, password);
    users.push_back(new_professor);

}

string SocialMedia::find_major_name_by_id(int major_name){
    for(Major* m : majors){
        if(m->get_id() == major_name){
            return m->get_name();
        }
    }
}

User* SocialMedia::find_user_by_id(int id){
    for(User* u : users){
        if(u->get_id() == id){
            return u;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

void SocialMedia::login(int id, string password){
    if(is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    User* desired_user = find_user_by_id(id);

    if(desired_user->is_authenticated(password)){
        is_logged_in = true;
        logged_in_user = desired_user;
    }

    else{
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
}

void SocialMedia::logout(){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    is_logged_in = false;
    logged_in_user = NULL;
}

void SocialMedia::add_post(string title, string message){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    logged_in_user->add_post(title, message);
}

void SocialMedia::connect(int id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(id == logged_in_user -> get_id()){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    User* connected_user = find_user_by_id(id);
    connected_user -> connect(logged_in_user);
    logged_in_user -> connect(connected_user);
}


void SocialMedia::write_all_offered_courses(vector<string>& output){
    if(offered_courses.size() == 0){
        throw runtime_error(EMPTY_RESPONSE);
    }

    for(OfferedCourse* o : offered_courses){
        o->write_general_info(output);
    }
}

void SocialMedia::write_offered_course_by_id(int id, vector<string>& output){
    for(OfferedCourse* o : offered_courses){
        if(o->get_id() == id){
            o->write_detailed_info(output);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

void SocialMedia::write_page_info_by_id(int id, vector<string>& output){
    User* desired_user = find_user_by_id(id);
    desired_user->write_page_info(output);
}

void SocialMedia::write_post_by_id(int user_id, int post_id, vector<string>& output){
    User* desired_user = find_user_by_id(user_id);
    desired_user-> write_post_by_id(post_id, output);
}

void SocialMedia::write_notifications(vector<string>& output){
    logged_in_user -> write_notifications(output);
}





void SocialMedia::remove_post(int id){
    logged_in_user->remove_post(id);
}



// void SocialMedia::test_print(){
//     for(Course* c : courses)
//         c->print();
//     for(Major* m : majors)
//         m->print();
//     for(User* u : users)
//         u->print();
// }