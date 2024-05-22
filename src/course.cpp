#include "../includes/course.hpp"

Course::Course(int init_id, string init_name, int init_credit, int init_prerequisite, vector<int> init_major_ids){
    id = init_id;
    name = init_name;
    credit = init_credit;
    prerequisite = init_prerequisite;
    major_ids = init_major_ids;
}

// void Course::print(){
//     cout << "Course : " << endl << id << endl << name << endl << credit << endl << prerequisite << endl;
//     for(int i : major_ids){
//         cout << "mid : " << i << endl;
//     }
// }