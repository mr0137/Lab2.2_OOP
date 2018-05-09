#include "Employee.h"

Employee::Employee(const Employee &e)
{
	if (this == &e || &e == nullptr)
	{
		return;
	}

    *this = e;
}

Employee& Employee::operator=(const Employee &e)
{
	if (this == &e || &e == nullptr)
	{
		return *this;
	}
  
    id = e.id;
    f_name = e.f_name;
    l_name = e.l_name;
    age = e.age;
    department = e.department;
    salary = e.salary;

    return *this;
}

void Employee::SetSalary(int salary_)
{
    salary = salary_;
}

int Employee::GetSalary()
{
	return salary;
}

void Employee::SetDepartment(string dept)
{
    department = dept;
}

void Employee::SetId(int n)
{
    id = n;
}

int Employee::GetId()
{
    return id;
}

string Employee::Getf_name()
{
	return f_name;
}

string Employee::Getl_name()
{
	return l_name;
}

int Employee::Getage()
{
	return age;
}

string Employee::GetDepartment()
{
    return department;
}

void Employee::Display(bool subordinates)
{
    if (subordinates)
    {
		printf("Employee type: Employee\n id: %d;\n Name: %s %s;\n Age: %d;\n Salary: %d;\n Department: %s;\n\n"
			, id, f_name.c_str(), l_name.c_str(), age, salary, department.c_str());
        return;
    }

	printf("\tEmployee type: Employee\n\t id: %d;\n\t Name: %s %s;\n\t Age: %d;\n\t Salary: %d;\n\t Department: %s;\n\n"
		, id, f_name.c_str(), l_name.c_str(), age, salary, department.c_str());
}