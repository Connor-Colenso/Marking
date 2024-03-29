#include "gtest/gtest.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Course.h"
#include "..\Marking\CourseHolder.h"
#include "..\Marking\Student.h"
#include "..\Marking\StudentHolder.h"

TEST(StudentHolder, Constructor_Invalid_Filepath) {
    EXPECT_ANY_THROW(StudentHolder s(R"(../Test Data - DO NOT EDIT/does_not_Exist.json)"););
}

TEST(CourseHolder, Constructor_Invalid_Filepath) {
    EXPECT_ANY_THROW(CourseHolder s(R"(../Test Data - DO NOT EDIT/does_not_Exist.json)"););
}

TEST(StudentHolder, Constructor_From_Filepath_Small_Students_JSON) {
    StudentHolder s(R"(../Test Data - DO NOT EDIT/small_students.json)");

    Student student_0 = s.getStudent("JS12345678");
    Student student_1 = s.getStudent("GF12345678");

    std::vector<double>student_0_AMF_grades = { 75 };
    std::vector<double>student_0_NLA_grades = { 70, 35, 50, 50 };
    std::vector<double>student_0_PDE_grades = { 80, 20, 35 };

    std::vector<double>student_1_AMF_grades = { 30 };
    std::vector<double>student_1_NLA_grades = { 80, 75, 50, 50 };
    std::vector<double>student_1_PDE_grades = { 50, 50, 35 };

    EXPECT_EQ(student_0.getEmail(), "js123@gmail.org");
    EXPECT_EQ(student_0.getFamilyName(), "Smith");
    EXPECT_EQ(student_0.getGivenName(), "John");
    EXPECT_EQ(student_0.getIdentifier(), "JS12345678");
    EXPECT_EQ(student_0.getGrades().at("AMF123"), student_0_AMF_grades);
    EXPECT_EQ(student_0.getGrades().at("NLA123"), student_0_NLA_grades);
    EXPECT_EQ(student_0.getGrades().at("PDE123"), student_0_PDE_grades);

    EXPECT_EQ(student_1.getEmail(), "gf123@gmail.com");
    EXPECT_EQ(student_1.getFamilyName(), "Fazio");
    EXPECT_EQ(student_1.getGivenName(), "Gio");
    EXPECT_EQ(student_1.getIdentifier(), "GF12345678");
    EXPECT_EQ(student_1.getGrades().at("AMF123"), student_1_AMF_grades);
    EXPECT_EQ(student_1.getGrades().at("NLA123"), student_1_NLA_grades);
    EXPECT_EQ(student_1.getGrades().at("PDE123"), student_1_PDE_grades);
}

TEST(CourseHolder, Constructor_From_Filepath_Small_Courses_JSON) {
    CourseHolder s(R"(../Test Data - DO NOT EDIT/small_courses.json)");

    std::vector<double> AMF_weights = { 1 };
    EXPECT_EQ((*s.getCourse("AMF123")).getWeights(), AMF_weights);
    EXPECT_EQ((*s.getCourse("AMF123")).getNumberOfCredits(), Credits::TwentyCredits);

    std::vector<double> NLA_weights = { 0.02, 0.02, 0.02, 0.94 };
    EXPECT_EQ((*s.getCourse("NLA123")).getWeights(), NLA_weights);
    EXPECT_EQ((*s.getCourse("NLA123")).getNumberOfCredits(), Credits::TwentyCredits);

    std::vector<double> PDE_weights = { 0.05, 0.05, 0.90 };
    EXPECT_EQ((*s.getCourse("PDE123")).getWeights(), PDE_weights);
    EXPECT_EQ((*s.getCourse("PDE123")).getNumberOfCredits(), Credits::TenCredits);
}

TEST(CourseHolder, Test_Maps) {
    CourseHolder c(R"(../Test Data - DO NOT EDIT/small_courses.json)");

    EXPECT_EQ(c.getCourseName("AMF123"), "Advance Math Finance");
    EXPECT_EQ(c.getCourseName("NLA123"), "Numerical Linear Algebra");
    EXPECT_EQ(c.getCourseName("PDE123"), "Partial Differential Equations");
}

TEST(ExamOnly, Get_Score_And_Get_Result_EXAM_ONLY) {
    CourseHolder s(R"(../Test Data - DO NOT EDIT/small_courses.json)");

    // Fail exam.
    std::vector<double> fake_AMF_grades_0 = { 30 };
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_0).getResult(), false);
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_0).getScore(), 30);

    // Barely pass AMF exam.
    std::vector<double> fake_AMF_grades_1 = { 40 };
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_1).getResult(), true);
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_1).getScore(), 40);

    // Pass AMF exam.
    std::vector<double> fake_AMF_grades_2 = { 70 };
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_2).getResult(), true);
    EXPECT_EQ((*s.getCourse("AMF123")).getGrade(fake_AMF_grades_2).getScore(), 70);
}

TEST(CourseworkOnly, Get_Score_And_Get_Result_COURSEWORK_ONLY) {
    CourseHolder s(R"(../Test Data - DO NOT EDIT/small_courses.json)");

    // Fail.
    std::vector<double> fake_NLA_grades_0 = { 39, 39, 39, 39 };
    EXPECT_FALSE((*s.getCourse("NLA123")).getGrade(fake_NLA_grades_0).getResult());
    EXPECT_NEAR((*s.getCourse("NLA123")).getGrade(fake_NLA_grades_0).getScore(), 39, 10e-5);

    // Barely pass.
    std::vector<double> fake_NLA_grades_2 = { 41, 41, 41, 41 };
    EXPECT_TRUE((*s.getCourse("NLA123")).getGrade(fake_NLA_grades_2).getResult());
    EXPECT_NEAR((*s.getCourse("NLA123")).getGrade(fake_NLA_grades_2).getScore(), 41, 10e-5);
}

TEST(Hybrid, Get_Score_And_Get_Result_HYBRID_ONLY) {
    CourseHolder s(R"(../Test Data - DO NOT EDIT/small_courses.json)");

    // Fail exam and fail coursework.
    std::vector<double> fake_PDE_grades_0 = { 10, 10, 10 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_0).getResult(), false);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_0).getScore(), 10);

    // Fail PDE exam but pass coursework.
    std::vector<double> fake_PDE_grades_1 = { 10, 100, 100 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_1).getResult(), false);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_1).getScore(), 95.5);

    // Pass PDE exam but fail coursework.
    std::vector<double> fake_PDE_grades_2 = { 100, 0, 0 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_2).getResult(), false);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_2).getScore(), 5);

    // Barely pass PDE exam and fail coursework.
    std::vector<double> fake_PDE_grades_3 = { 40, 0, 0 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_3).getResult(), false);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_3).getScore(), 2);

    // Fail PDE exam and barely pass coursework.
    std::vector<double> fake_PDE_grades_4 = { 2, 0, 0 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_4).getResult(), false);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_4).getScore(), 0.1);

    // Pass PDE exam and pass coursework.
    std::vector<double> fake_PDE_grades_5 = { 100, 100, 100 };
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_5).getResult(), true);
    EXPECT_EQ((*s.getCourse("PDE123")).getGrade(fake_PDE_grades_5).getScore(), 100);
}

TEST(Course, Validation_Checks) {
    CourseHolder c(R"(../Test Data - DO NOT EDIT/invalid_courses.json)");

    EXPECT_FALSE((*c.getCourse("AMFE123")).validateIdentifer().size());
    EXPECT_FALSE((*c.getCourse("AMFE123")).validateWeights());

    EXPECT_TRUE((*c.getCourse("NLA123")).validateIdentifer().size());
    EXPECT_TRUE((*c.getCourse("NLA123")).validateWeights());
}

TEST(Student, Validation_Checks) {
    StudentHolder s(R"(../Test Data - DO NOT EDIT/invalid_students.json)");

    EXPECT_FALSE(s.getStudent("JSA12345678").validateIdentifier().size());
    EXPECT_FALSE(s.getStudent("JSA12345678").validateEmail().size());
    EXPECT_FALSE(s.getStudent("JSA12345678").validateGrades());

    EXPECT_TRUE(s.getStudent("AA12345678").validateIdentifier().size());
    EXPECT_TRUE(s.getStudent("AA12345678").validateEmail().size());
    EXPECT_TRUE(s.getStudent("AA12345678").validateGrades());
}
