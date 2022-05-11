#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <regex>
#include <fstream>
#include <nlohmann/json.hpp>
#include "CourseResult.h"

class Student {

	// Declare variables.
	std::string identifier{}, givenName{}, familyName{}, email{};
	std::map<std::string, std::vector<double>> grades{};
	std::map<std::string, CourseResult> results{};

	CourseResult courseHolder;
	// Constructors.
	Student(const std::string identifier, 
			const std::string given_name, 
			const std::string family_name, 
			const std::string email, 
			const std::map<std::string, 
			std::vector<double>> grades, 
			const std::map<std::string, CourseResult> results);
	explicit Student(const std::string& file_path_name);

	// Member Functions.
	std::string getIdentifier();
	std::string getGivenName();
	std::string getFamilyName();
	std::string getEmail();
	bool getGrades(std::string course_code, std::vector<double>* grades);
	std::map<std::string, CourseResult> getResults();
	bool needsResit();
	int numberOfCredits();

	// Misc Functions.
	std::smatch validateIdentifier(const std::string& identifier);
	std::smatch validateEmail(const std::string& email);
};