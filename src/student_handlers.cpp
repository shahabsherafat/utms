#include "../includes/student_handlers.hpp"

StudentDashboardHandler::StudentDashboardHandler(string _file_path, SocialMedia* _utms) :
    TemplateHandler(_file_path){
    
    utms = _utms;
}

map<string, string> StudentDashboardHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    string user_type = utms->get_logged_in_user_type();
    if(!(user_type == STUDENT_TYPE)){
        context["error"] = "/" + user_type + "/dashboard";
        return context;
    }

    Student* logged_in_student = (Student*)utms->get_logged_in_user();
    context["ID"] = to_string(logged_in_student->get_id());
    context["NAME"] = logged_in_student->get_name();
    context["MAJOR"] = utms->find_major_name_by_id(logged_in_student->get_major_id());
    
    string prof = logged_in_student->get_profile_image();
    if(prof == EMPTY_STRING)
       context["IMAGE"] = DEFAULT_PROFILE_PICTURE_PATH;
    else
        context["IMAGE"] = "/" + prof;

    return context;
}

CourseEnrollPageHandler::CourseEnrollPageHandler(string filePath, SocialMedia* utms_)
    :TemplateHandler(filePath){
    
    utms = utms_;
}

map<string, string> CourseEnrollPageHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    if(utms->get_logged_in_user_type() != STUDENT_TYPE){
        context["error"] = "/access_denied_dashboard";
        return context;
    }

    return context;
}

CourseEnrollHandler::CourseEnrollHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* CourseEnrollHandler::callback(Request* req){
    string id = req->getBodyParam("id");
    cout << "id: " << id << endl;
    Response* res;

    if(!is_natural(id)){
        res = Response::redirect("/course_enroll?error=3");
        return res;
    }

    try{
        utms->enroll_course(stoi(id));
    }
    catch(const runtime_error& r){
        if(r.what() == PERMISSION_DENIED_RESPONSE)
            res = Response::redirect("/course_enroll?error=1");

        else if(r.what() == NOT_FOUND_RESPONSE)
            res = Response::redirect("/course_enroll?error=2");

        return res;
    }
    
    res = Response::redirect("/student/dashboard?error=0");
    return res;
}

RemoveCoursePageHandler::RemoveCoursePageHandler(string filePath, SocialMedia* utms_)
    :TemplateHandler(filePath){
    
    utms = utms_;
}

map<string, string> RemoveCoursePageHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    if(utms->get_logged_in_user_type() != STUDENT_TYPE){
        context["error"] = "/access_denied_dashboard";
        return context;
    }

    return context;
}

RemoveCourseHandler::RemoveCourseHandler(SocialMedia* utms_){
    utms = utms_;
}

Response* RemoveCourseHandler::callback(Request* req){
    string id = req->getBodyParam("id");
    cout << "id: " << id << endl;
    Response* res;

    if(!is_natural(id)){
        res = Response::redirect("/remove_course?error=2");
        return res;
    }

    try{
        utms->remove_enrolled_course(stoi(id));
    }
    catch(const runtime_error& r){
        if(r.what() == NOT_FOUND_RESPONSE)
            res = Response::redirect("/remove_course?error=1");

        return res;
    }
    
    res = Response::redirect("/student/dashboard?error=0");
    return res;
}

SeeMyCoursesHandler::SeeMyCoursesHandler(string filePath, SocialMedia* utms_)
     : TemplateHandler(filePath){
    utms = utms_;
}

map<string, string> SeeMyCoursesHandler::handle(Request* req){
    map<string, string> context;
    try{
        utms->change_logged_in_user(req->getSessionId());
    }
    catch(const runtime_error& r){
        context["error"] = "/access_denied_login";
        return context;
    }

    if(utms->get_logged_in_user_type() != STUDENT_TYPE){
        context["error"] = "/access_denied_dashboard";
        return context;
    }

    Student* desired_student = (Student*)utms->get_logged_in_user();
    vector<vector<string>> courses;
    desired_student->write_enrolled_courses(courses);
    context["SIZE"] = to_string(courses.size());

    for(int i = 0; i < courses.size(); i++){
        vector<string> course = courses[i];
        context["id" + to_string(i)] = course[0];
        context["name" + to_string(i)] = course[1];
        context["capacity" + to_string(i)] = course[2];
        context["pr_name" + to_string(i)] = course[3];
        context["time" + to_string(i)] = course[4];
        context["exam_date" + to_string(i)] = course[5];
        context["class_number" + to_string(i)] = course[6];
    }

    return context;
}
