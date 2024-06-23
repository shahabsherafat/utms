#include "common_handlers.hpp"

class StudentDashboardHandler : public TemplateHandler {
private:
    SocialMedia* utms;

public:
    StudentDashboardHandler(string file_path, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class CourseEnrollPageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    CourseEnrollPageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class CourseEnrollHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    CourseEnrollHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class RemoveCoursePageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    RemoveCoursePageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class RemoveCourseHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    RemoveCourseHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class SeeMyCoursesHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    SeeMyCoursesHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};
