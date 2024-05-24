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
    notify_to_connected_users(to_string(id) + SPACE + name + COLON + SPACE + NEW_POST_NOTIFICATION + NEWLINE);
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

void User::write_post_by_id(int id, vector<string>& output){
}

void User::connect(User* connected){
    for(User* u : connected_users){
        if(u -> get_id() == connected->get_id()){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }
    }

    connected_users.push_back(connected);
}

void User::add_notification(string notification_text){
    notifications.push_back(notification_text);
}

void User::notify_to_connected_users(string notification_text){
    for(User* u : connected_users){
        u->add_notification(notification_text);
    }
}

void User::write_notifications(vector<string>& output){
    if(notifications.size() == 0){
        throw runtime_error(EMPTY_RESPONSE);
    }
    
    output = notifications;
    notifications.clear();
}