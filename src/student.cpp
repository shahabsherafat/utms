#include "../includes/student.hpp"

Student::Student(int init_id, string init_name, int init_major_id, string init_major_name, 
                 int init_semester, string init_password):
                 User(init_id, init_password, init_name)
{
    major_id = init_major_id;
    major_name = init_major_name;
    semester = init_semester;
}

string Student::get_personal_info_string(){
    string personal_info = name + SPACE + major_name + SPACE + to_string(semester);

    if(attended_courses.size() != 0){
        personal_info += SPACE;

        for(int i = 0; i<attended_courses.size(); i++){
            if(i == attended_courses.size() - 1){
                personal_info += attended_courses[i] -> get_name();
            }

            else{
                personal_info += attended_courses[i] -> get_name() + COMMA;
            }
        }
    }
    personal_info += NEWLINE;
    return personal_info;
}

int Student::get_major_id(){
    return major_id;
}

int Student::get_semester(){
    return semester;
}

void Student::add_attended_course(OfferedCourse* o){
    Time holding_time = o->get_holding_time();
    Date exam_date = o->get_exam_date();

    for(OfferedCourse* of : attended_courses){
        if(of->get_holding_time().intersects(holding_time) or of->get_exam_date().intersects(exam_date)){
            throw runtime_error(PERMISSION_DENIED_RESPONSE);
        }
    }
    attended_courses.push_back(o);
    notif n;n.user_id = id;n.user_name = name;n.notif_message = GOTTEN_COURSE_NOTIFICATION;
    notify_to_connected_users(n);
}

void Student::write_enrolled_courses(vector<string>& output){
    if(attended_courses.size() == 0){
        throw runtime_error(EMPTY_RESPONSE);
    }
    for(OfferedCourse* o : attended_courses){
        o -> write_detailed_info(output);
    }
}

void Student::remove_enrolled_course(OfferedCourse* o){
    bool is_in = false;

    for(OfferedCourse* of : attended_courses){
        if(of == o){
            is_in = true;
            attended_courses.erase(remove(attended_courses.begin(), attended_courses.end(), of), attended_courses.end());
            break;
        }
    }

    if(!is_in){
        throw runtime_error(NOT_FOUND_RESPONSE);
    }

    notif n;n.user_id = id;n.user_name = name;n.notif_message = DELETED_COURSE_NOTIFICATION;
    notify_to_connected_users(n);
}