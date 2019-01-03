//
//  main.cpp
//  Contest
//
//  Created by Andrey Danilov on 09.05.16.
//  Copyright © 2016 Andrey Danilov. All rights reserved.
//

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <assert.h>
using namespace std;

class StudentName;
class StudentScore;
class StudentTasks;


class Student{
public:
    StudentName *name;
    StudentTasks *tasks;
    StudentScore *score;
    Student(StudentName *n, StudentTasks *t, StudentScore *s){
        name = n;
        tasks = t;
        score = s;
    }
};

class StudentName{
public:
    string name;
    int id;
    static vector<Student> *students;
    StudentName(string n, int id = -1){
        name = n;
        this->id = id;
    }
    StudentName(StudentName&& other){
        name = other.name;
        id = other.id;
        (*students)[id].name = this;
    }
    StudentName&& operator= (StudentName&& other){
        name = other.name;
        id = other.id;
        (*students)[id].name = this;
        return move(*this);
    }
    bool operator < (const StudentName& other) const{
        return name < other.name;
    }
};

class StudentScore{
public:
    int score;
    int id;
    static vector<Student> *students;
    StudentScore(int s, int id = -1){
        score = s;
        this->id = id;
    }
    StudentScore(StudentScore&& other){
        score = other.score;
        id = other.id;
        (*students)[id].score = this;
    }
    StudentScore&& operator= (StudentScore&& other){
        score = other.score;
        id = other.id;
        (*students)[id].score = this;
        return move(*this);
    }
    bool operator < (const StudentScore& other) const{
        if(id >= 0 && other.id >= 0)
            return (score < other.score) || (score == other.score && (*students)[id].name < (*students)[other.id].name);
        return score < other.score;
    }
};

class StudentTasks{
public:
    int tasks;
    int id;
    static vector<Student> *students;
    StudentTasks(int t, int id = -1){
        tasks = t;
        this->id = id;
    }
    StudentTasks(StudentTasks&& other){
        tasks = other.tasks;
        id = other.id;
        (*students)[id].tasks = this;
    }
    StudentTasks&& operator= (StudentTasks&& other){
        tasks = other.tasks;
        id = other.id;
        (*students)[id].tasks = this;
        return move(*this);
    }
    bool operator < (const StudentTasks& other) const{
        if(id >= 0 && other.id >= 0)
            return (tasks < other.tasks) || (tasks == other.tasks && (*students)[id].name < (*students)[other.id].name);
        return tasks < other.tasks;
    }
};

class Task{
public:
    int number;
    int soulutions;
    int points;
    static vector<Task*> *vectorPtr;
    Task(int n, int p){
        number = n;
        points = p;
        soulutions = 0;
        (*vectorPtr)[number] = this;
    }
    Task(Task && other){
        number = other.number;
        soulutions = other.soulutions;
        points = other.points;
        (*vectorPtr)[number] = this;
        
    }
    
    Task&& operator= (Task && other){
        number = other.number;
        soulutions = other.soulutions;
        points = other.points;
        (*vectorPtr)[number] = this;
        return move(*this);
    }
    
    bool operator < (const Task& t) const{
        return (soulutions < t.soulutions) || (soulutions == t.soulutions && number < t.number);
    }
};

vector<Task*> *Task::vectorPtr;
vector<Student> *StudentName::students;
vector<Student> *StudentTasks::students;
vector<Student> *StudentScore::students;


int main(int argc, const char * argv[]) {
    cout    << "Commands available:\n"
            << "SOLVED <student name> <task number>\n"
            << "STUD_STAT <student name>\n"
            << "STUDS_BY_TASKS\n"
            << "STUDS_BY_BALLS\n"
            << "STUDS_MORE_TASKS <number of tasks>\n"
            << "STUDS_MORE_BALLS <number of balls>\n"
            << "TASKS_BY_SOLUTIONS\n"
            << "EXIT\n"
            << "Now enter number of tasks and their score:\n";
    vector<Task*> tasks_ptr;
    vector<Student> students;
    set<StudentName> studentNameSet;
    set<StudentScore> studentScoreSet;
    set<StudentTasks> studentTaskSet;
    set<Task> taskSet;
    Task::vectorPtr = &tasks_ptr;
    StudentScore::students = StudentTasks::students = StudentName::students = &students;
    int n;
    int id = 0;
    cin >> n;
    for(int i = 0; i < n; ++i){
        int points;
        cin >> points;
        tasks_ptr.push_back(0);
        Task task(i, points);
        taskSet.insert(move(task));
    }
    string command;
    while(true){
        cin >> command;
        if(command == "SOLVED"){
            string studentName;
            int taskNumber;
            cin >> studentName >> taskNumber;
            --taskNumber;
            if(studentNameSet.count(StudentName(studentName, 0)) == 0){
                StudentName name(studentName, id);
                StudentTasks task(1, id);
                StudentScore score(tasks_ptr[taskNumber]->points, id); //создание студента
                students.push_back(Student(&name, &task, &score));
                ++id;
                Task currentTask(move(*tasks_ptr[taskNumber]));
                taskSet.erase(currentTask);
                ++currentTask.soulutions;
                taskSet.insert(move(currentTask)); //изменение числа решений задачи
                
                studentNameSet.insert(move(name));
                studentScoreSet.insert(move(score));
                studentTaskSet.insert(move(task)); //сохранение студента в деревьях
            }
            else{
                int id = studentNameSet.find(StudentName(studentName, 0))->id;
                StudentScore score = move(*students[id].score);
                StudentTasks tasks = move(*students[id].tasks);
                studentScoreSet.erase(score);
                studentTaskSet.erase(tasks);
                score.score += tasks_ptr[taskNumber]->points;
                ++tasks.tasks;
                studentScoreSet.insert(move(score));
                studentTaskSet.insert(move(tasks)); //изменение уже существующего студента
                
                Task currentTask(move(*tasks_ptr[taskNumber]));
                taskSet.erase(currentTask);
                ++currentTask.soulutions;
                taskSet.insert(move(currentTask)); //изменение числа решений задачи
            }
        }
        else if(command == "STUD_STAT"){
            string name;
            cin >> name;
            id = studentNameSet.find(StudentName(name))->id;
            cout << students[id].tasks->tasks << " " << students[id].score->score << "\n";
        }
        else if (command == "STUDS_BY_TASKS"){
            for(const auto &i : studentTaskSet){
                cout << students[i.id].name->name << " " << students[i.id].tasks->tasks << "\n";
            }
        }
        else if (command == "STUDS_BY_BALLS"){
            for(const auto &i : studentScoreSet){
                cout << students[i.id].name->name << " " << students[i.id].score->score << "\n";
            }
        }
        else if (command == "STUDS_MORE_TASKS"){
            int tasksNumber;
            cin >> tasksNumber;
            for(auto i = studentTaskSet.lower_bound(tasksNumber); i != studentTaskSet.end(); ++i){
                cout << students[i->id].name->name << " " << students[i->id].tasks->tasks << "\n";
            }
        }
        else if (command == "STUDS_MORE_BALLS"){
            int scoreNumber;
            cin >> scoreNumber;
            for(auto i = studentScoreSet.lower_bound(scoreNumber); i != studentScoreSet.end(); ++i){
                cout << students[i->id].name->name << " " << students[i->id].score->score << "\n";
            }
        }
        else if (command == "TASKS_BY_SOLUTIONS"){
            for(const auto &i : taskSet){
                cout << i.number+1 << " " << i.soulutions << "\n";
            }
        }
        else if (command == "EXIT"){
            return 0;
        }
    }
}