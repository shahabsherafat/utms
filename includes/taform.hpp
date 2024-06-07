#pragma once
#include "medium.hpp"
#include "offeredcourse.hpp"

class TAForm : public Medium{
    private:
        OfferedCourse* course;
        vector<string> TA_requests;
        vector<int> requests_ids;
        
    public:
        TAForm(string init_message, int init_id, OfferedCourse* init_course);
        OfferedCourse* get_course();
        void write_requests(vector<string>& output);
        int get_num_of_requests();
        vector<int> get_requesting_students_ids();
        void add_request(int ta_id, string request_text);
};