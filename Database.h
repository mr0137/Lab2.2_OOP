#pragma once

#include "Manager.h"


class Database
{
public:
    Database() {};
    ~Database() {}; // no need in destructor

    // creates “flat” database
    bool LoadFromFile(const char *filename);

    // arranges "flat" database after loading from the file
    void ArrangeSubordinates();

    // hire a new employee
    Person* HireEmployee(Person *p);

    void DisplayDepartmentEmployees(string _department);    

    // fire the employee
    bool FireEmployee(int id);

    void DisplayAll();

    // Add here whatever you need

	vector<Person*> SQL(const char*, const char*, const char*);

	void CreateTemp(vector<Person*>::iterator , const char* cond, const char* value, int field_);

	void ShowRecordSet(vector<Person*> rs);

private:
    vector<Person*> employees; 
	vector<Person*> temp;

    vector<int> ID;
    bool ParseInfo(string line, int &type, int &id, string &f_name, string &l_name, int &age, string &department, int &salary);
};