#include "../includes/read_and_check_functions.hpp"

bool is_number(string id){
    try{
        stoi(id);
        return true;
    }

    catch(exception& e){
        return false;
    }
}

bool is_natural(string id){
    if(is_number(id)){
        return stoi(id) > 0;
    }

    return false;
}

bool is_arithmetic_number(string id){
    if(is_number(id)){
        return stoi(id) >= 0;
    }

    return false;
}

void read_courses(string courses_file_address, SocialMedia* utms){
    string line;
    ifstream file(courses_file_address);
    getline(file, line);

    while(getline(file, line)){
        istringstream course_line(line);
        vector<string> info;

        for (string factor; getline(course_line, factor, COMMA); info.push_back(factor));
        if(info.size() == 1 or info.size() == 0) break;

        vector<int> major_ids;
        istringstream majors(info[4]);

        for (string major_id; getline(majors, major_id, SEMICOLON); major_ids.push_back(stoi(major_id)));

        utms->add_course(stoi(info[0]), info[1], stoi(info[2]), stoi(info[3]), major_ids);
    }
}

void read_majors(string majors_file_address, SocialMedia* utms){
    string line;
    ifstream file(majors_file_address);
    getline(file, line);

    while(getline(file, line)){
        istringstream major_line(line);
        vector<string> info;

        for (string factor; getline(major_line, factor, COMMA); info.push_back(factor));
        if(info.size() == 1 or info.size() == 0) break;

        utms->add_major(stoi(info[0]), info[1]);
    }
}

void read_users(string students_file_address, string professors_file_address, SocialMedia* utms){
    string line;
    ifstream students_file(students_file_address);
    ifstream professors_file(professors_file_address);
    getline(students_file, line);
    getline(professors_file, line);

    while(getline(students_file, line)){
        istringstream student_line(line);
        vector<string> info;

        for (string factor; getline(student_line, factor, COMMA); info.push_back(factor));
        if(info.size() == 1 or info.size() == 0) break;

        utms->add_student(stoi(info[0]), info[1], stoi(info[2]), stoi(info[3]), info[4]);
    }

    while(getline(professors_file, line)){
        istringstream professor_line(line);
        vector<string> info;

        for (string factor; getline(professor_line, factor, COMMA); info.push_back(factor));
        if(info.size() == 1 or info.size() == 0) break;

        utms->add_professor(stoi(info[0]), info[1], stoi(info[2]), info[3], info[4]);
    }
}
