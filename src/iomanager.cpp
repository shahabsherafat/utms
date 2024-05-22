#include "../includes/iomanager.hpp"

IOManager::IOManager(SocialMedia* social_media){
    utms = social_media;
}

void IOManager::read_courses(string courses_file_address){
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

void IOManager::read_majors(string majors_file_address){
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

void IOManager::read_users(string students_file_address, string professors_file_address){
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

void IOManager::run_command_line(){
    string line;
    string request;
    
    while(getline(cin, line)){
        stringstream line_stream(line);
        line_stream >> request;

        try{
            if(request == POST_REQUEST)
                handle_POST_request(line_stream);

            else if(request == GET_REQUEST)
                handle_GET_request(line_stream);

            else if(request == DELETE_REQUEST)
                handle_DELETE_request(line_stream);

            else if(request == PUT_REQUEST)
                handle_PUT_request(line_stream);

            else
                throw runtime_error(BAD_REQUEST_RESPONSE);

        }

        catch(runtime_error& r){
            cout << r.what() << endl;
        }
    }
}

void IOManager::handle_POST_request(stringstream& line_stream){
    string command, sign;
    line_stream >> command >> sign;

    if(sign != QUESTION_MARK)
        throw runtime_error(BAD_REQUEST_RESPONSE);

    if(command == LOGIN_COMMAND)
        handle_login(line_stream);

    else if(command == LOGOUT_COMMAND)
        handle_logout();

    //Other commands will be added later.

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
    
}

void IOManager::handle_login(stringstream& arguments){
    string parameter1, value1, parameter2, value2;
    arguments >> parameter1 >> value1 >> parameter2 >> value2;

    if(parameter1 == ID_PARAMETER and parameter2 == PASSWORD_PARAMETER){
        if(!is_natural(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->login(stoi(value1), value2);
    }

    else if(parameter1 == PASSWORD_PARAMETER and parameter2 == ID_PARAMETER){
        if(!is_natural(value2)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->login(stoi(value2), value1);
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_logout(){
    utms->logout();
    cout << SUCCESS_RESPONSE << endl;
}

bool IOManager::is_number(string id){
    try{
        stoi(id);
        return true;
    }

    catch(exception& e){
        return false;
    }
}

bool IOManager::is_natural(string id){
    if(is_number(id)){
        return stoi(id) > 0;
    }
}

void IOManager::handle_GET_request(stringstream& line_stream){
    string command, sign;
    line_stream >> command >> sign;

    if(command == SEE_COURSES_COMMAND)
        handle_see_courses(line_stream);

    //Other commands will be added later.

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
    
}

void IOManager::handle_see_courses(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;
    vector<string> output;

    if(parameter1 == EMPTY_STRING){
        utms -> write_all_offered_courses(output);
    }

    else if(parameter1 == ID_PARAMETER and is_natural(value1)){
        utms -> write_offered_course_by_id(stoi(value1), output);
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    for(string response : output){
        cout << response;
    }
}

void IOManager::handle_DELETE_request(stringstream& line_stream){

}

void IOManager::handle_PUT_request(stringstream& line_stream){

}