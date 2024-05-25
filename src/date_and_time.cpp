#include "../includes/date_and_time.hpp"

bool Time::intersects(Time t){
    return t.week_day == week_day and ((t.start_time > start_time and t.start_time < end_time)
                                        or (t.end_time > start_time and t.end_time < end_time)
                                        or (start_time > t.start_time and end_time < t.end_time));
}