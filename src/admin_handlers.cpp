#include "../includes/admin_handlers.hpp"

ProfessorDashboardHandler::ProfessorDashboardHandler(string _file_path, SocialMedia* _utms) :
    TemplateHandler(_file_path){

    utms = _utms;
}

map<string, string> ProfessorDashboardHandler::handle(Request* req){
    map<string, string> context;
    
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    string user_type = utms->get_logged_in_user_type();
    if(!(user_type == PROFESSOR_TYPE)){
        context["error"] = "/" + user_type + "/dashboard";
        return context;
    }

    Professor* logged_in_professor = (Professor*)utms->get_logged_in_user();
    context["ID"] = to_string(logged_in_professor->get_id());
    context["NAME"] = logged_in_professor->get_name();
    context["MAJOR"] = utms->find_major_name_by_id(logged_in_professor->get_major_id());

    string prof = logged_in_professor->get_profile_image();
    if(prof == EMPTY_STRING)
       context["IMAGE"] = DEFAULT_PROFILE_PICTURE_PATH;
    else
        context["IMAGE"] = "/" + prof;

    return context;
}

AdminDashboardHandler::AdminDashboardHandler(string _file_path, SocialMedia* _utms) :
    TemplateHandler(_file_path){

    utms = _utms;
}

map<string, string> AdminDashboardHandler::handle(Request* req){
    map<string, string> context;

    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    string user_type = utms->get_logged_in_user_type();
    if(!(user_type == ADMIN_TYPE)){
        context["error"] = "/" + user_type + "/dashboard";
        return context;
    }

    Admin* logged_in_admin = (Admin*)utms->get_logged_in_user();
    context["ID"] = to_string(logged_in_admin->get_id());
    context["NAME"] = logged_in_admin->get_name();

    string prof = logged_in_admin->get_profile_image();
    if(prof == EMPTY_STRING)
       context["IMAGE"] = DEFAULT_PROFILE_PICTURE_PATH;
    else
        context["IMAGE"] = "/" + prof;

    return context;
}

CourseOfferPageHandler::CourseOfferPageHandler(string filePath, SocialMedia* utms_)
    :TemplateHandler(filePath){
    
    utms = utms_;
}

map<string, string> CourseOfferPageHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    if(utms->get_logged_in_user_type() != ADMIN_TYPE){
        context["error"] = "/access_denied_dashboard";
        return context;
    }

    return context;
}

CourseOfferHandler::CourseOfferHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* CourseOfferHandler::callback(Request* req){
    string course_id = req->getBodyParam("course_id"), professor_id = req->getBodyParam("professor_id"), 
        capacity = req->getBodyParam("capacity"), time = req->getBodyParam("time"),
        exam_date = req->getBodyParam("exam_date"), class_number = req->getBodyParam("class_number");
    
    cout << "course id: " << course_id << "professor id: " << professor_id 
        << "capacity: " << capacity << "time: " << time << "exam date: " 
        << exam_date << "class number: " << class_number << endl;

    Response* res;

    if(!is_natural(course_id) or !is_natural(professor_id) or !is_natural(class_number) or !is_natural(capacity)){
        res = Response::redirect("/course_offer?error=1");
        return res;
    }

    try{
        utms->offer_new_course(stoi(course_id), stoi(professor_id), 
            stoi(capacity), time, exam_date, stoi(class_number));
    }
    catch(const runtime_error& r){
        if(r.what() == NOT_FOUND_RESPONSE)
            res = Response::redirect("/course_offer?error=2");
        else if(r.what() == PERMISSION_DENIED_RESPONSE)
            res = Response::redirect("/course_offer?error=3");

        return res;
    }
    
    res = Response::redirect("/admin/dashboard?error=0");
    return res;
}