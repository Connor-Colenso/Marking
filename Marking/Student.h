#include<string>
#include<map>
#include<string>
#include <nlohmann/json.hpp>
#include<regex>
#include<fstream>
#include"CourseResult.h"

using json = nlohmann::json;

class Student
{

public:

	// variables:
	std::string identifier{}, givenName{}, familyName{}, email{};
	std::map<std::string, std::vector<double>> grades{};
	std::map<std::string, CourseResult> results{};

	// default constructor
	Student() = default;

	// constructor:
	Student(std::string identifier, std::string givenName, std::string familyName, std::string email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results);

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(student, identifier, givenName, familyName, email, grades);

	// accessors
	std::string getIdentifier();
	std::string getGivenName();
	std::string getFamilyName();
	std::string getEmail();
	std::map<std::string, std::vector<double>> getGrades();
    std::map<std::string, CourseResult> getResults();

	// validation functions
	std::smatch validateIdentifier();
	std::smatch validateEmail();

};

class StudentHolder
{
private:
	std::vector<Student> students;
public:
	StudentHolder(std::vector<Student> students) : students(students) {};
	StudentHolder() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(StudentHolder, students);

};

static StudentHolder CreateStudentHolder(std::string file_path_name)
{

}
