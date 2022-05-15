#pragma once
#include <map>
#include <string>
#include <memory>
#include "Course.h"

enum CourseType {
	ExamOnlyCourse = 0,
	CourseworkOnlyCourse = 1,
	HybridCourse = 2
};

class CourseHolder {
private:
	std::map<std::string, std::shared_ptr<Course>> map_id_to_course;
	std::map<std::string, std::string> map_id_to_name;
	std::map<std::string, Credits> map_id_to_credits;
public:
	//CourseHolder(std::vector<Course*> courses);
	CourseHolder(std::string file_path_name);

	std::shared_ptr<Course> getCourse(std::string course_code);
	const std::map<std::string, std::shared_ptr<Course>> getCourseMap() const;
	std::string getCourseName(const std::string& course_code);
};

