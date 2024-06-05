#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string EMPTY_STRING = "";
const int EMPTY_INT = 0;
const string FIELD_SEPARATOR = "-";
const char COMMA = ',';
const char SEMICOLON = ';';
const string QUESTION_MARK = "?";
const string SPACE = " ";
const char COLON = ':';
const char DASH = '-';
const char SLASH = '/';
const string NEWLINE = "\n";
const char DOUBLE_QOUTATION = '\"';

const int STARTING_OFFERED_COURSES_ID = 1;
const int STARTING_COURSE_POST_ID = 1;

const int ADMIN_ID = 0;
const string ADMIN_PASSWORD = "UT_account";
const string ADMIN_NAME = "UT_account";

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
const string SEE_NOTIFICATIONS_COMMAND = "notification";
const string COURSE_OFFER_COMMAND = "course_offer";
const string COURSE_ENROLLMENT_COMMAND = "my_courses";
const string REMOVE_ENROLLED_COURSE_COMMAND = "my_courses";
const string SEE_ENROLLED_COURSES_COMMAND = "my_courses";
const string SET_PROFILE_COMMAND = "profile_photo";
const string COURSE_POST_COMMAND = "course_post";
const string SEE_COURSE_CHANNEL_COMMAND = "course_channel";
const string SEE_COURSE_POST_COMMAND = "course_post";
const string ADD_TA_FORM_COMMAND = "ta_form";
const int NUM_OF_COURSE_OFFER_ARGUMENTS = 6;
const int NUM_OF_ADD_POST_ARGUMENTS = 3;
const int NUM_OF_ADD_COURSE_POST_ARGUMENTS = 4;
const int NUM_OF_ADD_TA_FORM_ARGUMENTS = 2;

const string ID_PARAMETER = "id";
const string PASSWORD_PARAMETER = "password";
const string TITLE_PARAMETER = "title";
const string MESSAGE_PARAMETER = "message";
const string POST_IMAGE_ADDRESS_PARAMETER = "image";
const string POST_ID_PARAMETER = "post_id";
const string COURSE_ID_PARAMETER = "course_id";
const string PROFESSOR_ID_PARAMETER = "professor_id";
const string CAPACITY_PARAMETER = "capacity";
const string CLASS_NUMBER_PARAMETER = "class_number";
const string TIME_PARAMETER = "time";
const string EXAM_DATE_PARAMETER = "exam_date";
const string PROFILE_PHOTO_PARAMETER = "photo";

const string NEW_POST_NOTIFICATION = "New Post";
const string NEW_OFFERED_COURSE_NOTIFICATION = "New Course Offering";
const string GOTTEN_COURSE_NOTIFICATION = "Get Course";
const string DELETED_COURSE_NOTIFICATION = "Delete Course";
const string NEW_COURSE_POST_NOTIFICATION = "New Course Post";
const string NEW_FORM_NOTIFICATION = "New Form";

const string TA_FORM_FOR_TEXT = "TA form for";
const string COURSE_WORD = "course";
#define debug(x) cout << x << endl, exit(0);