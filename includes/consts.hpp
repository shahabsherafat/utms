#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <vector>

using namespace std;

const string EMPTY_STRING = "";
const string FIELD_SEPARATOR = "-";
const char COMMA = ',';
const char SEMICOLON = ';';
const string QUESTION_MARK = "?";
const string SPACE = " ";
const string COLON = ":";
const string DASH = "-";
const string SLASH = "/";
const string NEWLINE = "\n";

const string POST_REQUEST = "POST";
const string GET_REQUEST = "GET";
const string DELETE_REQUEST = "DELETE";
const string PUT_REQUEST = "PUT";

const string SUCCESS_RESPONSE = "OK";
const string EMPTY_RESPONSE = "Empty";
const string NOT_FOUND_RESPONSE = "Not Found";
const string BAD_REQUEST_RESPONSE = "Bad Request";
const string PERMISSION_DENIED_RESPONSE = "Permission Denied";

const string LOGIN_COMMAND = "login";
const string LOGOUT_COMMAND = "logout";
const string SEE_COURSES_COMMAND = "courses";
const string ADD_POST_COMMAND = "post";
const string REMOVE_POST_COMMAND = "post";
const string SEE_PAGE_COMMAND = "personal_page";
const string SEE_POST_COMMAND = "post";
const string CONNECT_COMMAND = "connect";
const string NOTIFY_COMMAND = "notification";

const string ID_PARAMETER = "id";
const string PASSWORD_PARAMETER = "password";
const string TITLE_PARAMETER = "title";
const string MESSAGE_PARAMETER = "message";
const string POST_ID_PARAMETER = "post_id";


#define debug(x) cout << x << endl, exit(0);