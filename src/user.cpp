#include "../includes/user.hpp"

User::User(int init_id, string init_password, string init_name){
    name = init_name;
    id = init_id;
    password = init_password;
}

User::~User(){
    for(Medium* p : media){
        delete p;
    }
}

int User::get_id(){
    return id;
}

bool User::is_authenticated(string entered_password){
    return entered_password == password;
}

void User::add_post(string title, string message, string image_address){
    last_post_id ++;
    Post* new_post = new Post(title, message, last_post_id, image_address);
    notif n;
    n.user_name = name;n.user_id = id;n.notif_message = NEW_POST_NOTIFICATION;
    notify_to_connected_users(n);
    media.push_back(new_post);
}

void User::remove_post(int id){
    for(Medium* m : media){
        if(m->get_id() == id){
            media.erase(remove(media.begin(), media.end(), m), media.end());
            delete (m);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

void User::connect(User* connected){
    for(User* u : connected_users){
        if(u -> get_id() == connected->get_id()){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }
    }

    connected_users.push_back(connected);
}

void User::add_notification(notif n){
    notifications.push_back(n);
}

void User::notify_to_connected_users(notif n){
    for(User* u : connected_users){
        u->add_notification(n);
    }
}

void User::write_notifications(vector<string>& output){
    if(notifications.size() == 0){
        throw runtime_error(EMPTY_RESPONSE);
    }
    
    for(int i = notifications.size() - 1; i >= 0; i--){
        output.push_back(to_string(notifications[i].user_id) + SPACE + notifications[i].user_name +
                         COLON + SPACE + notifications[i].notif_message + NEWLINE);
    }

    notifications.clear();
}

void User::write_post_by_id(int post_id, vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Medium* m : media){
        if(m->get_id() == post_id){
            if(dynamic_cast<Post*>(m)){
                Post* post = (Post*)m;
                output.push_back(to_string(post_id) + SPACE + post->get_title() + 
                                 SPACE + post->get_message() + NEWLINE);
            }
            
            else{
                TAForm* ta_form = (TAForm*)m;
                OfferedCourse* course = ta_form->get_course();
                output.push_back(to_string(post_id) + SPACE + TA_FORM_FOR_TEXT + SPACE +
                                 course->get_name() + SPACE + COURSE_WORD + NEWLINE);
                course->write_detailed_info(output);
                output.push_back(ta_form->get_message() + NEWLINE);
            }
            
            return;
        }
    }
    throw runtime_error(NOT_FOUND_RESPONSE);
}

void User::write_page_info(vector<string>& output){
    output.push_back(get_personal_info_string());

    for(int i = media.size() - 1; i >= 0; i--){
        if(dynamic_cast<Post*>(media[i])){
            Post* post = (Post*)media[i];
            output.push_back(to_string(post->get_id()) + SPACE + post->get_title() + NEWLINE);
        }
        
        else{
            TAForm* ta_form = (TAForm*)media[i];
            OfferedCourse* course = ta_form->get_course();
            output.push_back(to_string(id) + SPACE + TA_FORM_FOR_TEXT + SPACE +
                                course->get_name() + SPACE + COURSE_WORD + NEWLINE);
        }
    }
}

void User::set_profile_photo(string photo_address){
    profile_photo_address = photo_address;
}
