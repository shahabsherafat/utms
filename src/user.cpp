#include "../includes/user.hpp"

User::User(int init_id, string init_password, string init_name){
    name = init_name;
    id = init_id;
    password = init_password;
}

int User::get_id(){
    return id;
}

bool User::is_authenticated(string entered_password){
    return entered_password == password;
}

void User::add_post(string title, string message){
    last_post_id ++;
    Post* new_post = new Post(title, message, last_post_id);
    notif n;
    n.user_name = name;n.user_id = id;n.notif_message = NEW_POST_NOTIFICATION;
    notify_to_connected_users(n);
    posts.push_back(new_post);
}

void User::remove_post(int id){
    for(Post* p : posts){
        if(p->get_id() == id){
            posts.erase(remove(posts.begin(), posts.end(), p), posts.end());
            delete (p);
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
    
    for(notif n : notifications){
        output.push_back(to_string(n.user_id) + SPACE + n.user_name + COLON + SPACE + n.notif_message + NEWLINE);
    }

    notifications.clear();
}

void User::write_post_by_id(int id, vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        if(p->get_id() == id){
            output.push_back(to_string(id) + SPACE + p->get_title() + SPACE + p->get_message() + NEWLINE);
            return;
        }
    }

    throw runtime_error(NOT_FOUND_RESPONSE);
}

void User::write_page_info(vector<string>& output){
    output.push_back(get_personal_info_string());

    for(Post* p : posts){
        output.push_back(to_string(p->get_id()) + SPACE + p->get_title() + NEWLINE);
    }
}