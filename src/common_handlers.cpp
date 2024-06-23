#include "../includes/common_handlers.hpp"

LoginPageHandler::LoginPageHandler(string filePath, SocialMedia* utms_) : TemplateHandler(filePath){
    utms = utms_;
}

map<string, string> LoginPageHandler::handle(Request* req){
    map<string, string> context;
    if(utms->is_servicing(req->getSessionId())){
        context["error"] = "/access_denied_dashboard";
        return context;
    }

    return context;
}

LoginHandler::LoginHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* LoginHandler::callback(Request* req) {
    string id = req->getBodyParam("id");
    string password = req->getBodyParam("password");
    cout << "id: " << id << ",\tpassword: " << password << endl;
    Response* res;

    if(!is_arithmetic_number(id)){
        res = Response::redirect(LOGIN_NOT_A_VALID_ID_ERROR_URL);
        return res;
    }

    try{
        utms->login(stoi(id), password, to_string(last_session_id));
    }
    catch(const runtime_error& r){
        if(r.what() == PERMISSION_DENIED_RESPONSE){
            res = Response::redirect(LOGIN_WRONG_PASSWORD_ERROR_URL);
        }
        else if(r.what() == NOT_FOUND_RESPONSE){
            res = Response::redirect(LOGIN_NOT_FOUND_ID_ERROR_URL);
        }

        return res;
    }
    
    string user_type = utms->get_logged_in_user_type();
    res = Response::redirect("/" + user_type + "/dashboard");
    res->setSessionId(to_string(last_session_id));
    last_session_id++;
    return res;
}

GuideToDashboardHandler::GuideToDashboardHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* GuideToDashboardHandler::callback(Request* req){
    Response* res;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        res = Response::redirect("/access_denied_login");
        return res;
    }

    string user_type = utms->get_logged_in_user_type();
    res = Response::redirect("/" + user_type + "/dashboard");
    return res;
}

LogoutHandler::LogoutHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* LogoutHandler::callback(Request* req){
    string session_id = req->getSessionId();
    utms->logout(session_id);
    Response* res = Response::redirect("/");
    return res;
}

LoginCheckAndShowPageHandler::LoginCheckAndShowPageHandler(string filePath, SocialMedia* utms_)
     : TemplateHandler(filePath){
    utms = utms_;
}

map<string, string> LoginCheckAndShowPageHandler::handle(Request* req){
    map<string, string> context;

    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    return context;
}

AddPostHandler::AddPostHandler(SocialMedia* utms_, Server* server_){
    utms = utms_;
    server = server_;
}

Response* AddPostHandler::callback(Request* req){
    string title = req->getBodyParam("title");
    string message = req->getBodyParam("message");
    string post_image = req->getBodyParam("post-image"), post_image_name = EMPTY_STRING;
    cout << "title: " << title << ",\tmessage: " << message << ",\timage: " << post_image << endl;
    Response* res;

    User* desired_user = utms->get_logged_in_user();
    if(post_image != EMPTY_STRING){
        post_image_name = "post_images/" + to_string(desired_user->get_id()) + "_" +
            desired_user->get_next_post_id() + ".png";
        utils::writeToFile(post_image, post_image_name);
        server->get("/" + post_image_name, new ShowImage(post_image_name));
    }

    utms->add_post(title, message,  post_image_name);
    string user_type = utms->get_logged_in_user_type();
    res = Response::redirect("/" + user_type + "/dashboard?error=0");
    return res;
}

SetProfileHandler::SetProfileHandler(SocialMedia* utms_, Server* server_){
    utms = utms_;
    server = server_;
}

Response* SetProfileHandler::callback(Request* req){
    string profile_image = req->getBodyParam("profile-image");
    cout << "new image: " << profile_image << endl;
    Response* res;

    User* desired_user = utms->get_logged_in_user();
    string profile_image_name = "profile_images/" + to_string(desired_user->get_id()) + ".png";
    utms->set_profile_photo(profile_image_name);
    utils::writeToFile(profile_image, profile_image_name);
    server->get("/" + profile_image_name, new ShowImage(profile_image_name));

    string user_type = utms->get_logged_in_user_type();
    res = Response::redirect("/" + user_type + "/dashboard?error=0");
    return res;
}

SeeCoursesHandler::SeeCoursesHandler(string filePath, SocialMedia* utms_)
     : TemplateHandler(filePath){
    utms = utms_;
}

map<string, string> SeeCoursesHandler::handle(Request* req){
    map<string, string> context;

    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    vector<vector<string>> courses;
    utms->write_all_offered_courses(courses);
    context["SIZE"] = to_string(courses.size());

    for(int i = 0; i < courses.size(); i++){
        vector<string> course = courses[i];
        context["id" + to_string(i)] = course[0];
        context["name" + to_string(i)] = course[1];
        context["capacity" + to_string(i)] = course[2];
        context["pr_name" + to_string(i)] = course[3];
    }

    return context;
}

SearchUserHandler::SearchUserHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* SearchUserHandler::callback(Request* req){
    string id = req->getBodyParam("id");
    cout << "id: " << id << endl;
    Response* res;

    if(!is_natural(id)){
        res = Response::redirect("/search_user?error=2");
        return res;
    }

    if(!utms->is_there_this_user(stoi(id))){
        res = Response::redirect("/search_user?error=1");
        return res;
    }

    res = Response::redirect("/personal_page?id=" + id);
    
    return res;
}

PersonalPageHandler::PersonalPageHandler(string filePath, SocialMedia* utms_) : TemplateHandler(filePath){
    utms = utms_;
}

map<string, string> PersonalPageHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    string id = req->getQueryParam("id");
    cout << "id: " << id << endl;
    User* desired_user = utms->get_user_by_id(stoi(id));
    context["NAME"] = desired_user->get_name();

    if(desired_user->get_profile_image() != EMPTY_STRING)
        context["IMAGE"] = "/" + desired_user->get_profile_image();
    else
        context["IMAGE"] = DEFAULT_PROFILE_PICTURE_PATH;

    if(dynamic_cast<Student*>(desired_user)){
        Student* desired_student = (Student*)desired_user;
        context["TYPE"] = STUDENT_TYPE;
        context["SEMESTER"] = to_string(desired_student->get_semester());
    }
    else if(dynamic_cast<Professor*>(desired_user)){
        Professor* desired_professor = (Professor*)desired_user;
        context["TYPE"] = PROFESSOR_TYPE;
        context["POSITION"] = desired_professor->get_position();
    }
    else if(dynamic_cast<Admin*>(desired_user)){
        Admin* desired_admin = (Admin*)desired_user;
        context["TYPE"] = ADMIN_TYPE;
    }

    vector<vector<string>> posts = desired_user->get_posts();
    context["size"] = to_string(posts.size());
    for(int i = 0; i < posts.size(); i++){
        context["title" + to_string(i)] = posts[i][0];
        
        if(posts[i][1] != EMPTY_STRING)
            context["pic" + to_string(i)] = "/" + posts[i][1];
        else
            context["pic" + to_string(i)] = DEFAULT_IMAGE_PATH;
    }

    return context;
}