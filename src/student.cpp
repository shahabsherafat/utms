#include "../includes/student.hpp"

Student::Student(int init_id, string init_name, int init_major_id, int init_semester, string init_password):
                 User(init_id, init_name, init_major_id, init_password)
{
    semester = init_semester;
}

// void Student::print(){
//     cout << "Student : " << endl << id << endl << name << endl << major_id << endl << semester << endl << password << endl;
// }