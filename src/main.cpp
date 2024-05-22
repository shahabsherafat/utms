#include "../includes/socialmedia.hpp"
#include "../includes/iomanager.hpp"

int main(int argc, char* addresses[5]){
    SocialMedia* utms = new SocialMedia();
    IOManager* io = new IOManager(utms);
    io->read_majors(addresses[1]);
    io->read_users(addresses[2], addresses[4]);
    io->read_courses(addresses[3]);

    io->run_command_line(); 
    
    // utms->test_print();
    
    return 0;
}