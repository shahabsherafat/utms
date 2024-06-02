#include "../includes/iomanager.hpp"

IOManager::IOManager(SocialMedia* social_media){
    utms = social_media;
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

    return false;
}

bool IOManager::is_arithmetic(string id){
    if(is_number(id)){
        return stoi(id) >= 0;
    }

    return false;
}

int IOManager::find_index(const vector<string>& parameters, string parameter){
    auto it = find(parameters.begin(), parameters.end(), parameter);

    if (it != parameters.end()){ 
        int index = it - parameters.begin();
        return index; 
    } 

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    } 
}

string IOManager::get_qouted_text(stringstream& arguments){
    string source_string = arguments.str(), result_text;
    int index = source_string.find(DOUBLE_QUOTATION);

    if(index == -1){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    source_string.erase(0, index+1);
    index = source_string.find(DOUBLE_QUOTATION);

    if(index == -1){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    result_text = source_string.substr(0, index);
    source_string.erase(0, index+1);
    arguments.str(source_string);
    return result_text;
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

    else if(command == ADD_POST_COMMAND)
        handle_add_post(line_stream);

    else if(command == CONNECT_COMMAND)
        handle_connect(line_stream);

    else if(command == COURSE_OFFER_COMMAND)
        handle_course_offer(line_stream);

    else if(command == SET_PROFILE_COMMAND)
        handle_set_profile_photo(line_stream);

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
}

void IOManager::handle_GET_request(stringstream& line_stream){
    string command, sign;
    line_stream >> command >> sign;

    if(command == SEE_COURSES_COMMAND)
        handle_see_courses(line_stream);

    else if(command == SEE_PAGE_COMMAND)
        handle_see_personal_page(line_stream);

    else if(command == SEE_POST_COMMAND)
        handle_see_post(line_stream);

    else if(command == SEE_NOTIFICATIONS_COMMAND)
        handle_see_notifications();

    else if(command == SEE_ENROLLED_COURSES_COMMAND)
        handle_see_enrolled_courses();

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
}

void IOManager::handle_DELETE_request(stringstream& line_stream){
    string command, sign;
    line_stream >> command >> sign;

    if(sign != QUESTION_MARK)
        throw runtime_error(BAD_REQUEST_RESPONSE);

    if(command == REMOVE_POST_COMMAND)
        handle_remove_post_by_id(line_stream);
    
    else if(command == REMOVE_ENROLLED_COURSE_COMMAND)
        handle_remove_enrolled_course(line_stream);

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
}

void IOManager::handle_PUT_request(stringstream& line_stream){
    string command, sign;
    line_stream >> command >> sign;

    if(sign != QUESTION_MARK)
        throw runtime_error(BAD_REQUEST_RESPONSE);

    if(command == COURSE_ENROLLMENT_COMMAND)
        handle_course_enroll(line_stream);

    else
        throw runtime_error(NOT_FOUND_RESPONSE);
}

void IOManager::handle_login(stringstream& arguments){
    string parameter1, value1, parameter2, value2;
    arguments >> parameter1 >> value1 >> parameter2 >> value2;

    if(parameter1 == ID_PARAMETER and parameter2 == PASSWORD_PARAMETER){
        if(!is_arithmetic(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->login(stoi(value1), value2);
    }

    else if(parameter1 == PASSWORD_PARAMETER and parameter2 == ID_PARAMETER){
        if(!is_arithmetic(value2)){
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

void IOManager::assign_post_factors(stringstream& arguments, string& title, string& message, string& image_address){
    string parameter, source_string = arguments.str();
    arguments >> parameter;

    if(parameter != EMPTY_STRING){
        if(parameter == POST_IMAGE_ADDRESS_PARAMETER){
            arguments >> image_address;

            if(image_address == EMPTY_STRING)
                throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        else if(parameter == TITLE_PARAMETER)
            title = get_qouted_text(arguments);

        else if(parameter == MESSAGE_PARAMETER)
            message = get_qouted_text(arguments);

        else 
            throw runtime_error(BAD_REQUEST_RESPONSE);
    }
}

void IOManager::handle_add_post(stringstream& arguments){
    string title, message, image_address;
    assign_post_factors(arguments, title, message, image_address);
    utms->add_post(title, message, image_address);
    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_connect(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;
    vector<string> output;

    if(parameter1 == ID_PARAMETER){
        if(!is_natural(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms -> connect(stoi(value1));
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_course_offer(stringstream& arguments){
    vector<string> parameters(NUM_OF_COURSE_OFFER_ARGUMENTS), values(NUM_OF_COURSE_OFFER_ARGUMENTS);
    int course_id, professor_id, capacity, class_number;
    string time, exam_date, temp;

    for(int i = 0; i < NUM_OF_COURSE_OFFER_ARGUMENTS; i++){
        arguments >> parameters[i];
        arguments >> values[i];
    }

    temp = values[find_index(parameters, COURSE_ID_PARAMETER)];
    if(!is_natural(temp)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }
    course_id = stoi(temp);

    temp = values[find_index(parameters, PROFESSOR_ID_PARAMETER)];
    if(!is_natural(temp)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }
    professor_id = stoi(temp);

    temp = values[find_index(parameters, CAPACITY_PARAMETER)];
    if(!is_natural(temp)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }
    capacity = stoi(temp);

    temp = values[find_index(parameters, CLASS_NUMBER_PARAMETER)];
    if(!is_natural(temp)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }
    class_number = stoi(temp);

    time = values[find_index(parameters, TIME_PARAMETER)];
    exam_date = values[find_index(parameters, EXAM_DATE_PARAMETER)];
    utms -> offer_new_course(course_id, professor_id, capacity, time, exam_date, class_number);
    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_set_profile_photo(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;

    if(parameter1 == PROFILE_PHOTO_PARAMETER){
        utms -> set_profile_photo(value1);
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    cout << SUCCESS_RESPONSE << endl;
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

void IOManager::handle_see_personal_page(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;
    vector<string> output;

    if(parameter1 == ID_PARAMETER){
        if(!is_arithmetic(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->write_page_info_by_id(stoi(value1), output);
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    for(string response : output){
        cout << response;
    }
}

void IOManager::handle_see_post(stringstream& arguments){
    string parameter1, value1, parameter2, value2;
    arguments >> parameter1 >> value1 >> parameter2 >> value2; 
    vector<string> output;

    if(!is_arithmetic(value1) or !is_arithmetic(value2)){
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    if(parameter1 == ID_PARAMETER and parameter2 == POST_ID_PARAMETER){
        utms->write_post_by_id(stoi(value1), stoi(value2), output);
    }

    else if(parameter1 == POST_ID_PARAMETER and parameter2 == ID_PARAMETER){
        utms->write_post_by_id(stoi(value2), stoi(value1), output);
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    for(string response : output){
        cout << response;
    }
}

void IOManager::handle_see_notifications(){
    vector<string> output;
    utms -> write_notifications(output);

    for(string response : output){
        cout << response;
    }
}

void IOManager::handle_see_enrolled_courses(){
    vector<string> output;
    utms -> write_enrolled_courses(output);

    for(string response : output){
        cout << response;
    }
}

void IOManager::handle_remove_post_by_id(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;

    if(parameter1 == ID_PARAMETER){
        if(!is_natural(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->remove_post(stoi(value1));
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }
    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_remove_enrolled_course(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;

    if(parameter1 == ID_PARAMETER){
        if(!is_natural(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->remove_enrolled_course(stoi(value1));
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    cout << SUCCESS_RESPONSE << endl;
}

void IOManager::handle_course_enroll(stringstream& arguments){
    string parameter1, value1;
    arguments >> parameter1 >> value1;

    if(parameter1 == ID_PARAMETER){
        if(!is_natural(value1)){
            throw runtime_error(BAD_REQUEST_RESPONSE);
        }

        utms->enroll_course(stoi(value1));
    }

    else{
        throw runtime_error(BAD_REQUEST_RESPONSE);
    }

    cout << SUCCESS_RESPONSE << endl;
}