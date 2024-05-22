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
    Student* new_student = new Student(id, name, major_id, semester, password);
    users.push_back(new_student);
}

void SocialMedia::add_professor(int id, string name, int major_id, string position, string password){
    Professor* new_student = new Professor(id, name, major_id, position, password);
    users.push_back(new_student);
}

void SocialMedia::login(int id, string password){
    if(is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    for(User* u : users){
        if(u->get_id() == id){
            if(u->is_authenticated(password)){
                is_logged_in = true;
                logged_in_user = u;
                return;
            }

            else{
                throw runtime_error(PERMISSION_DENIED_RESPONSE);
            }
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

void SocialMedia::logout(){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    is_logged_in = false;
    logged_in_user = NULL;
}

void SocialMedia::write_all_offered_courses(vector<string> output){
    if(offered_courses.size() == 0){
        throw runtime_error(EMPTY_RESPONSE);
    }

    for(OfferedCourse* o : offered_courses){
        o->write_general_info(output);
    }
}

void SocialMedia::write_offered_course_by_id(int id, vector<string> output){
    for(OfferedCourse* o : offered_courses){
        if(o->get_id() == id){
            o->write_detailed_info(output);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

// void SocialMedia::test_print(){
//     for(Course* c : courses)
//         c->print();
//     for(Major* m : majors)
//         m->print();
//     for(User* u : users)
//         u->print();
// }