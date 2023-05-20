#include <iostream>
#include <vector>
#include <map>
#include <string>

class Block;

std::map<int, Block*> blockMap;

class Block {
protected:
    int id;

public:
    Block(int blockId) : id(blockId) {}

    virtual void execute() = 0;
};

class CreateStudentBlock : public Block {
public:
    CreateStudentBlock(int blockId) : Block(blockId) {}

    void execute() override;
};

class CreateTeacherBlock : public Block {
public:
    CreateTeacherBlock(int blockId) : Block(blockId) {}

    void execute() override;
};

class CreateCourseBlock : public Block {
public:
    CreateCourseBlock(int blockId) : Block(blockId) {}

    void execute() override;
};

class EnrollStudentBlock : public Block {
public:
    EnrollStudentBlock(int blockId) : Block(blockId) {}

    void execute() override;
};

class Student {
private:
    std::string name;
    int age;

public:
    Student(const std::string& studentName, int studentAge) : name(studentName), age(studentAge) {}

    void display() const {
        std::cout << "Student Name: " << name << ", Age: " << age << std::endl;
    }
};

class Teacher {
private:
    std::string name;
    int age;

public:
    Teacher(const std::string& teacherName, int teacherAge) : name(teacherName), age(teacherAge) {}

    void display() const {
        std::cout << "Teacher Name: " << name << ", Age: " << age << std::endl;
    }
};

class Course {
private:
    std::string name;
    std::vector<Student*> students;

public:
    Course(const std::string& courseName) : name(courseName) {}

    void enrollStudent(Student* student) {
        students.push_back(student);
    }

    void display() const {
        std::cout << "Course Name: " << name << std::endl;
        std::cout << "Enrolled Students:" << std::endl;
        for (const auto& student : students) {
            student->display();
        }
        std::cout << std::endl;
    }
};

void CreateStudentBlock::execute() {
    std::string name;
    int age;
    std::cout << "Enter student name: ";
    std::cin >> name;
    std::cout << "Enter student age: ";
    std::cin >> age;

    Student* student = new Student(name, age);


    std::cout << "Student created with ID: " << id << std::endl;
}

void CreateTeacherBlock::execute() {
    std::string name;
    int age;
    std::cout << "Enter teacher name: ";
    std::cin >> name;
    std::cout << "Enter teacher age: ";
    std::cin >> age;

    Teacher* teacher = new Teacher(name, age);


    std::cout << "Teacher created with ID: " << id << std::endl;
}

void CreateCourseBlock::execute() {
    std::string name;
    std::cout << "Enter course name: ";
    std::cin >> name;

    Course* course = new Course(name);


    std::cout << "Course created with ID: " << id << std::endl;
}

void EnrollStudentBlock::execute() {
    int studentId, courseId;
    std::cout << "Enter student ID: ";
    std::cin >> studentId;
    std::cout << "Enter course ID: ";
    std::cin >> courseId;

    Student* student = dynamic_cast<Student*>(blockMap[studentId]);
    Course* course = dynamic_cast<Course*>(blockMap[courseId]);

    if (student && course) {
        course->enrollStudent(student);
        std::cout << "Student with ID " << studentId << " enrolled in course with ID " << courseId << std::endl;
    } else {
        std::cout << "Invalid student or course ID." << std::endl;
    }
}

int main() {
    int blockId = 1;

    while (true) {
        std::cout << "Select an option:" << std::endl;
        std::cout << "1. Create student" << std::endl;
        std::cout << "2. Create teacher" << std::endl;
        std::cout << "3. Create course" << std::endl;
        std::cout << "4. Enroll student in course" << std::endl;
        std::cout << "5. Display course details" << std::endl;
        std::cout << "6. Exit" << std::endl;

        int option;
        std::cin >> option;

        if (option == 1) {
            CreateStudentBlock* block = new CreateStudentBlock(blockId++);
            block->execute();
        } else if (option == 2) {
            CreateTeacherBlock* block = new CreateTeacherBlock(blockId++);
            block->execute();
        } else if (option == 3) {
            CreateCourseBlock* block = new CreateCourseBlock(blockId++);
            block->execute();
        } else if (option == 4) {
            EnrollStudentBlock* block = new EnrollStudentBlock(blockId++);
            block->execute();
        } else if (option == 5) {
            int courseId;
            std::cout << "Enter course ID: ";
            std::cin >> courseId;

            Course* course = dynamic_cast<Course*>(blockMap[courseId]);
            if (course) {
                course->display();
            } else {
                std::cout << "Invalid course ID." << std::endl;
            }
        } else if (option == 6) {
            break;
        } else {
            std::cout << "Invalid option." << std::endl;
        }
    }

    for (const auto& pair : blockMap) {
        delete pair.second;
    }

    return 0;
}
