#pragma once
#include "consts.hpp"
#include "course.hpp"
#include "date_and_time.hpp"

class OfferedCourse{
    private:
        int id;
        string name;
        int capacity;
        int class_number;
        string professor_name;
        Time holding_time;
        Date exam_date;

    public:
        OfferedCourse(int init_id, string init_name, int init_capacity,int init_class_number,
                      string init_professor_name, Time ht, Date ed);

        void write_general_info(vector<string>& output);
        void write_detailed_info(vector<string>& output);

        int get_id();
};