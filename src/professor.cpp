#include "../includes/professor.hpp"

Professor::Professor(int init_id, string init_name, int init_major_id, string init_position, string init_password) : 
                     User(init_id, init_name, init_major_id, init_password)
{
    position = init_position;
}

// void Professor::print(){
//     cout << "Professor : " << endl << id << endl << name << endl << major_id << endl << position << endl << password << endl;
// }