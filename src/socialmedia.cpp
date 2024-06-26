#include "../includes/socialmedia.hpp"

SocialMedia::SocialMedia(){
    Admin* admin = new Admin(ADMIN_ID, ADMIN_PASSWORD, ADMIN_NAME);
    users.push_back(admin);
}

SocialMedia::~SocialMedia(){
    for(User* u : users){
        delete(u);
    }

    for(Course* c : courses){
        delete(c);
    }

    for(OfferedCourse* o : offered_courses){
        delete(o);
    }
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

Course* SocialMedia::find_course_by_id(int id){
    for(Course* c : courses){
        if(c->get_id() == id){
            return c;
        }
    }
    
    throw runtime_error(NOT_FOUND_RESPONSE);
}

OfferedCourse* SocialMedia::find_offered_course_by_id(int id){
    for(OfferedCourse* o : offered_courses){
        if(o->get_id() == id){
            return o;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

Student* SocialMedia::find_student_by_id(int student_id){
    for(User* s : users){
        if(s->get_id() == student_id){
            return (Student*) s;
        }
    }
}

void SocialMedia::notify_every_one(notif n){
    for(User* u : users){
        u -> add_notification(n);
    }
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

void SocialMedia::add_post(string title, string message, string image_address){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(dynamic_cast<Admin*>(logged_in_user)){
        notif n;
        n.user_id = ADMIN_ID;
        n.user_name = ADMIN_NAME;
        n.notif_message = NEW_POST_NOTIFICATION;
        notify_every_one(n);
    }

    logged_in_user->add_post(title, message, image_address);
}

void SocialMedia::connect(int id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(id == logged_in_user -> get_id() or dynamic_cast<Admin*>(logged_in_user)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    User* connected_user = find_user_by_id(id);
    connected_user -> connect(logged_in_user);
    logged_in_user -> connect(connected_user);
}

void SocialMedia::set_profile_photo(string photo_address){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    logged_in_user->set_profile_photo(photo_address);
}

void SocialMedia::add_course_post(int course_id, string title, string message, string image_address){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    OfferedCourse* target_course = find_offered_course_by_id(course_id);
    logged_in_user->add_course_post_if_you_can(target_course, title, message, image_address);

    notif n;n.user_id = target_course->get_id();n.user_name = target_course->get_name();
    n.notif_message = NEW_COURSE_POST_NOTIFICATION;

    for(User* u : users){
        if(u->is_participating_in_this_course(course_id) and u != logged_in_user){
            u->add_notification(n);
        }
    }
}

void SocialMedia::add_ta_form(int course_id, string message){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Professor*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    Professor* professor = (Professor*) logged_in_user;
    OfferedCourse* target_course = find_offered_course_by_id(course_id);
    professor->add_ta_form_if_you_can(target_course, message);
}

void SocialMedia::close_ta_form(int ta_form_id, vector<bool> results){
    Professor* professor = (Professor*) logged_in_user;
    TAForm* target_ta_form = professor->get_ta_form(ta_form_id);
    vector<int> student_ids = target_ta_form->get_requesting_students_ids();
    OfferedCourse* target_course = target_ta_form->get_course();
    notif n; n.user_id = target_course->get_id(); n.user_name = target_course->get_name();

    for(int i = 0; i < student_ids.size(); i++){
        Student* target_student = find_student_by_id(student_ids[i]);

        if(results[i]){
            n.notif_message = ACCEPTED_TA_REQUEST_NOTIFICATION;
            target_student->add_assisting_course(target_course);
        }
        else{
            n.notif_message = REJECTED_TA_REQUEST_NOTIFICATION;
        }

        target_student->add_notification(n);
    }
}

void SocialMedia::ta_request(int professor_id, int form_id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Student*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    User* target_user = find_user_by_id(professor_id);
    if(!dynamic_cast<Professor*>(target_user)){
        throw runtime_error(NOT_FOUND_RESPONSE);
    }
    Professor* professor = (Professor*)target_user;
    TAForm* target_ta_form = professor->get_ta_form(form_id);
    int min_semester = find_course_by_id(target_ta_form->get_course()->get_course_id()) -> get_min_semester();
    if(((Student*)logged_in_user)->get_semester() <= min_semester){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    target_ta_form->add_request(logged_in_user->get_id(), ((Student*)logged_in_user)->get_ta_request_text());
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
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    logged_in_user -> write_notifications(output);
}

void SocialMedia::write_enrolled_courses(vector<string>& output){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Student*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    Student* student = (Student*) logged_in_user;
    student -> write_enrolled_courses(output);
}

void SocialMedia::write_course_channel(int course_id, vector<string>& output){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
    
    OfferedCourse* target_course = find_offered_course_by_id(course_id);

    if(!logged_in_user->is_participating_in_this_course(course_id)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    target_course->write_detailed_info(output);
    target_course->write_channel(output);
}

void SocialMedia::write_course_post(int course_id, int post_id, vector<string>& output){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
    
    OfferedCourse* target_course = find_offered_course_by_id(course_id);

    if(!logged_in_user->is_participating_in_this_course(course_id)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    target_course->write_detailed_info(output);
    target_course->write_post(post_id, output);
}

void SocialMedia::write_ta_form_requests(int ta_form_id, vector<string>& output){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Professor*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    Professor* professor = (Professor*)logged_in_user;
    professor->write_ta_form_requests_if_you_can(ta_form_id, output);
}

Time SocialMedia::make_time_by_string(string time_string){
    stringstream time_factors(time_string);
    string weekday, start_end, startstr, endstr;
    getline(time_factors, weekday, COLON);
    getline(time_factors, start_end);
    stringstream interavl(start_end);
    getline(interavl, startstr, DASH);
    getline(interavl, endstr, DASH);
    Time t(weekday, stoi(startstr), stoi(endstr));
    return t;
}

Date SocialMedia::make_date_by_string(string date_string){
    stringstream date_factors(date_string);
    string year_string, month_string, day_string;
    getline(date_factors, year_string, SLASH);
    getline(date_factors, month_string, SLASH);
    getline(date_factors, day_string, SLASH);
    Date d(stoi(year_string), stoi(month_string), stoi(day_string));
    return d;
}

void SocialMedia::offer_new_course(int course_id, int professor_id, int capacity, string time,
                      string date, int class_number){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Admin*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    Course* course = find_course_by_id(course_id);
    User* unknown_user = find_user_by_id(professor_id);
    if(!dynamic_cast<Professor*>(unknown_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
    
    Professor* professor = (Professor*) unknown_user;
    if(!course -> can_professor_take_this_course(professor -> get_major_id())){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
    
    Time holding_time = make_time_by_string(time);
    Date exam_date = make_date_by_string(date);

    OfferedCourse* new_offered_course = new OfferedCourse(last_offered_course_id, course -> get_name(), course ->get_id(),
    capacity, class_number, professor -> get_name(), holding_time, exam_date);

    try{
        professor -> add_offered_course(new_offered_course);
    }
    catch(runtime_error& r){
        delete new_offered_course;
        throw;
    }

    last_offered_course_id ++;
    offered_courses.push_back(new_offered_course);

    notif n;
    n.user_id = professor -> get_id();
    n.user_name = professor -> get_name();
    n.notif_message = NEW_OFFERED_COURSE_NOTIFICATION;

    notify_every_one(n);
}

void SocialMedia::remove_post(int id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    logged_in_user -> remove_post(id);
}

void SocialMedia::remove_enrolled_course(int id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Student*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    Student* student = (Student*) logged_in_user;
    OfferedCourse* offered_course = find_offered_course_by_id(id);
    student -> remove_enrolled_course(offered_course);
}

void SocialMedia::enroll_course(int id){
    if(!is_logged_in){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!dynamic_cast<Student*>(logged_in_user)){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }
    Student* student = (Student*) logged_in_user;

    OfferedCourse* desired_offered_course = find_offered_course_by_id(id);
    Course* desired_course = find_course_by_id(desired_offered_course -> get_course_id());
    
    if(!desired_course -> can_student_take_this_course(student -> get_major_id(), student -> get_semester())){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    if(!desired_course -> can_student_take_this_course(student -> get_major_id(), student -> get_semester())){
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    }

    student -> add_attended_course(desired_offered_course);
}