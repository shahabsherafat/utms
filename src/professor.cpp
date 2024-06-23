#include "../includes/professor.hpp"

Professor::Professor(int init_id, string init_name, int init_major_id, string init_major_name, 
                     string init_position, string init_password) : 
                     User(init_id, init_password, init_name)
{
    major_id = init_major_id;
    major_name = init_major_name;
    position = init_position;
}

string Professor::get_personal_info_string(){
    string personal_info = name + SPACE + major_name + SPACE + position;

    if(offered_courses.size() != 0){
        personal_info += SPACE;

        for(int i = 0; i<offered_courses.size(); i++){
            if(i == offered_courses.size() - 1){
                personal_info += offered_courses[i] -> get_name();
            }

            else{
                personal_info += offered_courses[i] -> get_name() + COMMA;
            }
        }
    }

    personal_info += NEWLINE;
    return personal_info;
}

int Professor::get_major_id(){
    return major_id;
}

string Professor::get_name(){
    return name;
}

string Professor::get_position(){
    return position;
}

void Professor::add_offered_course(OfferedCourse* o){
    Time time = o->get_holding_time();

    for(OfferedCourse* of : offered_courses){
        if(of->get_holding_time().intersects(time)){
            throw runtime_error(PERMISSION_DENIED_RESPONSE);
        }
    }   
    offered_courses.push_back(o);
}

void Professor::add_course_post_if_you_can(OfferedCourse* target_course, string title,
                                           string message, string image_address){
    if(find(offered_courses.begin(), offered_courses.end(), target_course) == offered_courses.end())
        throw runtime_error(PERMISSION_DENIED_RESPONSE);

    Post* new_post = new Post(title, message, target_course->get_last_channel_post_id(), image_address);
    target_course->add_post_to_channel(name, new_post);
}

bool Professor::is_participating_in_this_course(int course_id){
    for(OfferedCourse* of : offered_courses){
        if(of->get_id() == course_id){
            return true;
        }
    }

    return false;
}

void Professor::add_ta_form_if_you_can(OfferedCourse* target_course, string message){
    if(find(offered_courses.begin(), offered_courses.end(), target_course) == offered_courses.end())
        throw runtime_error(PERMISSION_DENIED_RESPONSE);
    
    last_post_id ++;
    TAForm* new_ta_form = new TAForm(message, last_post_id, target_course);
    media.push_back(new_ta_form);

    notif n; n.user_id = id; n.user_name = name; n.notif_message = NEW_FORM_NOTIFICATION;
    for(User* cu : connected_users)
        cu->add_notification(n);
}

void Professor::write_ta_form_requests_if_you_can(int ta_form_id, vector<string>& output){
    TAForm* target_ta_form = get_ta_form(ta_form_id);
    int num_of_requests = target_ta_form->get_num_of_requests();
    output.push_back(WE_HAVE_RECEIVED_TEXT + SPACE + to_string(num_of_requests) + 
                        SPACE + FOR_TEACHING_ASSISTANT_TEXT + NEWLINE);
    target_ta_form->write_requests(output);
    return;
}

TAForm* Professor::get_ta_form(int ta_form_id){
    for(Medium* m : media){
        if(m->get_id() == ta_form_id and dynamic_cast<TAForm*>(m)){
            TAForm* target_ta_form = (TAForm*)m;
            return target_ta_form;
        }
    }
    
    throw runtime_error(NOT_FOUND_RESPONSE);
}