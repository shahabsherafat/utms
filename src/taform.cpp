#include "../includes/taform.hpp"

TAForm::TAForm(string init_message, int init_id, OfferedCourse* init_course) : 
           Medium(init_message, init_id){
    course = init_course;
}

OfferedCourse* TAForm::get_course(){
    return course;
}