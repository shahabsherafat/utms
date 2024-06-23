#include "../includes/socialmedia.hpp"
#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "../includes/student_handlers.hpp"
#include "../includes/admin_handlers.hpp"
#include "../includes/common_handlers.hpp"
#include "../includes/read_and_check_functions.hpp"

void mapServerPaths(Server& server, SocialMedia* utms) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    server.get(DEFAULT_PROFILE_PICTURE_PATH, new ShowImage("static" + DEFAULT_PROFILE_PICTURE_PATH));
    server.get("/login", new LoginPageHandler("static/login_page.html", utms));
    server.post("/login", new LoginHandler(utms));
    server.get("/dashboard", new GuideToDashboardHandler(utms));
    server.get("/student/dashboard", new StudentDashboardHandler("template/dashboard_student.html", utms));
    server.get("/admin/dashboard", new AdminDashboardHandler("template/dashboard_admin.html", utms));
    server.get("/professor/dashboard", new ProfessorDashboardHandler("template/dashboard_professor.html", utms));
    server.get("/logout", new LogoutHandler(utms));
    server.get("/access_denied_login", new ShowPage("static/access_denied_login.html"));
    server.get("/access_denied_dashboard", new ShowPage("static/access_denied_dashboard.html"));

    server.get("/add_post", new LoginCheckAndShowPageHandler("static/add_post_page.html", utms));
    server.post("/add_post", new AddPostHandler(utms, &server));
    server.get("/set_profile", new LoginCheckAndShowPageHandler("static/set_profile_page.html", utms));
    server.post("/set_profile", new SetProfileHandler(utms, &server));
    server.get("/see_courses", new SeeCoursesHandler("template/see_courses_page.html", utms));
    server.get("/search_user", new LoginCheckAndShowPageHandler("static/search_user_page.html", utms));
    server.post("/search_user", new SearchUserHandler(utms));
    server.get("/personal_page", new PersonalPageHandler("template/personal_page.html", utms));
    server.get("/course_enroll", new CourseEnrollPageHandler("static/course_enroll_page.html", utms));
    server.post("/course_enroll", new CourseEnrollHandler(utms));
    server.get("/remove_course", new RemoveCoursePageHandler("static/remove_course_page.html", utms));
    server.post("/remove_course", new RemoveCourseHandler(utms));
    server.get("/attending_courses", new SeeMyCoursesHandler("template/see_attending_courses_page.html", utms));
    server.get("/course_offer", new CourseOfferPageHandler("static/course_offer_page.html", utms));
    server.post("/course_offer", new CourseOfferHandler(utms));
}

int main(int argc, char* addresses[5]) {
    SocialMedia* utms = new SocialMedia();
    read_majors(addresses[1], utms);
    read_users(addresses[2], addresses[4], utms);
    read_courses(addresses[3], utms);

    try {
        int port = 5000;
        Server server(port);
        mapServerPaths(server, utms);
        cout << "Server running on port: " << port << endl;
        server.run();
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        delete(utms);
    }
    catch (const Server::Exception& e) {
        cerr << e.getMessage() << endl;
        delete(utms);
    }

    delete(utms);
    return 0;
}