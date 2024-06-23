#include "common_handlers.hpp"

class ProfessorDashboardHandler : public TemplateHandler {
private:
    SocialMedia* utms;

public:
    ProfessorDashboardHandler(string file_path, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class AdminDashboardHandler : public TemplateHandler {
private:
    SocialMedia* utms;
    
public:
    AdminDashboardHandler(string file_path, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class CourseOfferPageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    CourseOfferPageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class CourseOfferHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    CourseOfferHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};