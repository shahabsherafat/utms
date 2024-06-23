#pragma once
#include <iostream>
#include "socialmedia.hpp"

using namespace std;
void read_majors(string majors_file_address, SocialMedia* utms);
void read_courses(string courses_file_address, SocialMedia* utms);
void read_users(string students_file_address, string professors_file_address, SocialMedia* utms);
bool is_number(string id);
bool is_natural(string id);
bool is_arithmetic_number(string id);