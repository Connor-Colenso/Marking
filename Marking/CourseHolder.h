#pragma once
#include "Course.h"
#include <plog/Log.h>
#include <map>
#include <string>
#include <memory>

const enum CourseType {
    ExamOnlyCourse = 0,
    CourseworkOnlyCourse = 1,
    HybridCourse = 2
};

const class CourseHolder {
private:
    std::map<std::string, std::shared_ptr<Course>> map_id_to_course;
    std::map<std::string, std::string> map_id_to_name;
    std::map<std::string, Credits> map_id_to_credits;
public:
    CourseHolder(const std::string& file_path_name);
    CourseHolder();

    const std::shared_ptr<Course> getCourse(const std::string& course_code) const;
    const std::map<std::string, std::shared_ptr<Course>> getCourseMap() const;
    const std::string getCourseName(const std::string& course_code) const;
};
