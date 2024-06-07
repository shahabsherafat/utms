#include "../includes/taform.hpp"

TAForm::TAForm(string init_message, int init_id, OfferedCourse* init_course) : 
           Medium(init_message, init_id){
    course = init_course;
}

OfferedCourse* TAForm::get_course(){
    return course;
}

int TAForm::get_num_of_requests(){
    return TA_requests.size();
}

void TAForm::write_requests(vector<string>& output){
    for(string request : TA_requests){
        output.push_back(request);
    }
}

vector<int> TAForm::get_requesting_students_ids(){
    return requests_ids;
}

void TAForm::add_request(int ta_id, string request_text){
    requests_ids.push_back(ta_id);
    TA_requests.push_back(request_text);
}