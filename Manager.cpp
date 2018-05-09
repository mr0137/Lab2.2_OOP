#include "Manager.h"

Manager::Manager(const Manager &m)
{
	if (this == &m || &m == nullptr)
	{
		return;
	}

    *this = m;
}

Manager& Manager::operator=(const Manager &m)
{
	if (this == &m || &m == nullptr)
	{
		return *this;
	}

    id = m.id;
    f_name = m.f_name;
    l_name = m.l_name;
    age = m.age;
    department = m.department;
    salary = m.salary;
    subordinates = m.subordinates;

    return *this;
}

Person* Manager::AddSubordinate(Person *p)
{
    if (p == nullptr) 
	{
        return nullptr;
    }

	list<Person*>::iterator iter = subordinates.begin();

    for (iter; iter != subordinates.end(); iter++)
    {
        if (dynamic_cast<Employee*>(*iter)->GetId() == dynamic_cast<Employee*>(p)->GetId()) 
		{
            return nullptr;
        }
    }

    if (dynamic_cast<Employee*>(p)->GetDepartment() != this->GetDepartment()) 
	{
        dynamic_cast<Employee*>(p)->SetDepartment(this->GetDepartment());
    }

    subordinates.push_back(p);

    return p;
}

bool Manager::RemoveSubordinate(int id)
{
    if (id <= 0 || id > subordinates.size()) 
	{
        return false;
    }

    list<Person*>::iterator iter = subordinates.begin();

    for (iter ; iter != subordinates.end(); iter++)
    {
        if (dynamic_cast<Employee*>(*iter)->GetId() == id)
        {
            subordinates.erase(iter);
            break;
        }
    }

    return true;
}

void Manager::Display(bool subordinates)
{
	printf("Employee type: Manager\n id: %d;\n Name: %s %s;\n Age: %d;\n Salary: %d;\n Department: %s;\n\n"
		, id, f_name.c_str(), l_name.c_str(), age, salary, department.c_str());

    if (subordinates)
    {
        printf("Subordinates: \n\n");
        DisplaySubordinates();
    }
    else 
	{
        cout << endl;
    }
}

void Manager::DisplaySubordinates()
{
    if (subordinates.empty())
    {
		printf("\t\t None");
        return;
    }

	list <Person*>::iterator iter = subordinates.begin();

    for(iter; iter != subordinates.end(); iter++) 
	{
        (*iter)->Display(false);
    }
}