#pragma once
#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include <cstdlib>
#include "socialmedia.hpp"
#include "user.hpp"
#include "read_and_check_functions.hpp"


#include "../server/server.hpp"

class LoginPageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    LoginPageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class LoginHandler : public RequestHandler {
private:
    int last_session_id = 1;
    SocialMedia* utms;
public:
    LoginHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class GuideToDashboardHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    GuideToDashboardHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class LogoutHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    LogoutHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class LoginCheckAndShowPageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    LoginCheckAndShowPageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class AddPostHandler : public RequestHandler {
private:
    SocialMedia* utms;
    Server* server;
public:
    AddPostHandler(SocialMedia* utms_, Server* server_);
    Response* callback(Request*) override;
};


class SetProfileHandler : public RequestHandler {
private:
    SocialMedia* utms;
    Server* server;
public:
    SetProfileHandler(SocialMedia* utms_, Server* server);
    Response* callback(Request*) override;
};

class SeeCoursesHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    SeeCoursesHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};

class SearchUserHandler : public RequestHandler {
private:
    SocialMedia* utms;
public:
    SearchUserHandler(SocialMedia* utms_);
    Response* callback(Request*) override;
};

class PersonalPageHandler : public TemplateHandler {
private:
    SocialMedia* utms;
public:
    PersonalPageHandler(string filePath, SocialMedia* utms_);
    map<string, string> handle(Request* req);
};


#endif // HANDLERS_HPP_INCLUDE