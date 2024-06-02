#pragma once
#include "consts.hpp"

class Time{
    private:
        string week_day;
        int start_time;
        int end_time;
        
    public:
        Time(string wd, int st, int et) : week_day(wd), start_time(st), end_time(et){}
        string get_time_string(){return week_day + COLON + to_string(start_time) + DASH + to_string(end_time);}
        bool intersects(Time t);
};

class Date{
    private:
        int year;
        int month;
        int day;
    public:
        Date(int y, int m, int d) : year(y), month(m), day(d){}
        string get_date_string(){return to_string(year) + SLASH + to_string(month) + SLASH + to_string(day);}
        bool intersects(Date d);
};