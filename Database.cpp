#include "Database.h"


bool Database::LoadFromFile(const char *filename)
{
	if (filename == nullptr)
	{
		cout << "Choose name: " << filename << endl;
		system("pause");
		exit(1);
	}

    ifstream FileDB(filename);

    if (!FileDB.is_open())
    {
        cout << "Unable to open input file: " << filename << endl;
		system("pause");
		exit(1);
    }

    int empl_type, id, age, salary;
    string f_name, l_name, department, line;
    Employee *empl;
    Manager *mang;
	int i = 0;

    while (getline(FileDB, line))//счит. построчно
    {
        if (!ParseInfo(line, empl_type, id, f_name, l_name, age, department, salary))
        {
            cout << "Wrong data on line " << i + 1 << endl;
            i++;
            continue;
        }

        if (find(ID.begin(), ID.end(), id) != ID.end())
        {
            cout << "Error ! Line: " << i + 1 << "\nEmployee with (" << id << ")" << " exist !" << endl;
            i++;
            continue;
        }

        if (empl_type == 0)
        {
            empl = new Employee(f_name, l_name, age, id);
            empl->SetDepartment(department);
            empl->SetSalary(salary);
            ID.push_back(id);
            employees.push_back(empl);
        }
        if (empl_type == 1)
        {
            mang = new Manager(f_name, l_name, age, id);
            mang->SetDepartment(department);
            mang->SetSalary(salary);
            employees.push_back(mang);
			ID.push_back(id);
        }
        i++;
    }

    FileDB.close();
    return true;
}

bool Database::ParseInfo(string line, int &type, int &id, string &f_name, string &l_name, int &age, string &department, int &salary)
{
    int begin = 0, count = 0/*для проверки на верное колич. элем. в файле*/, i = 0;
    string buffer;

    for (i ; i < line.length(); i++)
    {
        if (count == 7) 
		{
            return true;
        }

        if (line[i] == ';')
        {
            buffer = line.substr(begin, i - begin);

            if (buffer.length() == 0) 
			{
                return false;
            }

            switch (count)
            {
                case 0: //empl_type
                    if (buffer.find_first_not_of("0123456789") != string::npos) //проверка на символы между цифр, пример: "20О2" 
					{
                        return false;
                    }
                    type = stoi(buffer);
                    break;
                
                case 1: //id
                    if (buffer.find_first_not_of("0123456789") != string::npos) 
					{
                        return false;
                    }
                    id = stoi(buffer);
                    break;
                
                case 2: //f_name
                    f_name = buffer;
                    break;
                
                case 3: //l_name
                    l_name = buffer;
                    break;
                
                case 4: //age
                    if (buffer.find_first_not_of("0123456789") != string::npos) 
					{
                        return false;
                    }
                    age = stoi(buffer);
                    break;
                
                case 5: //department
                    department = buffer;
                    break;
            }
            count++;
			begin = i + 1;
        }
        if (i == line.length() - 1 && count == 6)//для последнего элемента (salary)
        {
            buffer = line.substr(begin, i - begin + 1);

            if (buffer.length() == 0 || buffer.find_first_not_of("0123456789") != string::npos) 
			{
                return false;
            }

            salary = stoi(buffer);
            count++;
        }
    }

    if (count < 7) 
	{
		cout << "Bad .csv file " << endl;
        return false;
    }

    return true;
}

void Database::ArrangeSubordinates()
{
	vector<Person *>::iterator iter = employees.begin();

    for (iter; iter != employees.end(); iter++)
    {
        if (typeid(**iter) == typeid(Manager))//Manager
        {
			vector<Person*>::iterator iter_ = employees.begin();

            for (iter_; iter_ != employees.end(); iter_++)
            {
				if ((typeid(**iter_) == typeid(Employee))
					&&(dynamic_cast<Manager*>(*iter)->GetDepartment()
					== dynamic_cast<Employee*>(*iter_)->GetDepartment()))
				{
					dynamic_cast<Manager*>(*iter)->AddSubordinate(*iter_);
				}
            }
        }
    }
}

Person* Database::HireEmployee(Person *p)
{
    if (p == nullptr) 
	{
        return nullptr;
    }

    employees.push_back(p);

    return employees.back();
}

bool Database::FireEmployee(int id)
{
	vector<Person*>::iterator iter = employees.begin();

	for (iter; iter != employees.end(); iter++)
	{
		if (dynamic_cast<Employee*>(*iter)->GetId() == id) 
		{
			break;
		}
	}

	if (iter == employees.end())//Если не найден id 
	{
		return false;
	}

	if (typeid(**iter) == typeid(Employee))//Employee
	{
		vector<Person*>::iterator iter_ = employees.begin();

		for (iter_; iter_ != employees.end(); iter_++)
		{
			if (typeid(**iter_) == typeid(Manager) 
				&& dynamic_cast<Manager*>(*iter_)->GetDepartment() 
				== dynamic_cast<Employee*>(*iter)->GetDepartment())
			{
				dynamic_cast<Manager*>(*iter_)->RemoveSubordinate(id);
			}
		}
	}
	employees.erase(iter);
	return true;
}

void Database::DisplayDepartmentEmployees(string _department)
{
	vector<Person*>::iterator iter = employees.begin();

    for (iter; iter != employees.end(); iter++)
	{
        if (dynamic_cast<Employee*>(*iter)->GetDepartment() == _department) 
		{
            (*iter)->Display(true);
        }
    }
}

void Database::DisplayAll()
{
	vector<Person*>::iterator iter = employees.begin();

    for (iter; iter != employees.end(); iter++)
	{
        (*iter)->Display(true);
    }
}

vector<Person*> Database::SQL(const char *field, const char *cond, const char *value)
{
	if (field == nullptr || cond == nullptr || value == nullptr)
	{
		cout << "Bad value" << endl;
		exit(1);
	}
	printf("Selected by %s cond:(%s) value:(%s)\n ", field, cond, value);
	int field_;
	string buffer;
	buffer = value;

	/*
	field :
	error  == 0
	salary == 1
	id    ==  2
	age   ==  3
	*/

	if (!strcmp(field, "salary"))field_ = 1;
	else if (!strcmp(field, "id"))field_ = 2;
	else if (!strcmp(field, "age"))field_ = 3;
	else field_ = 0;

	//vector<Person*>::iterator rs = employees.begin()
	Employee *empl;
	vector<Person*>::iterator iter = employees.begin();
	if (!strcmp(field, "department"))
	{
		//для department не может быть меньше или больше по значению, только eq

		for (iter; iter != employees.end(); iter++)
		{
			if (!strcmp(dynamic_cast<Employee*>(*iter)->GetDepartment().c_str(), value))
			{
				empl = new Employee(dynamic_cast<Employee*>(*iter)->Getf_name(), dynamic_cast<Employee*>(*iter)->Getl_name(), dynamic_cast<Employee*>(*iter)->Getage(), dynamic_cast<Employee*>(*iter)->GetId());
				empl->SetDepartment(dynamic_cast<Employee*>(*iter)->GetDepartment());
				empl->SetSalary(dynamic_cast<Employee*>(*iter)->GetSalary());
				ID.push_back(dynamic_cast<Employee*>(*iter)->GetId());
				temp.push_back(empl);
			}
		}
		return temp;
	}

	if (field_ == 0 )
	{
		cout << "Bad cond or field" << endl;
		exit(1);
	}

	if (buffer.length() == 0 || buffer.find_first_not_of("0123456789") != string::npos)
	{
		cout << "Bad value" << endl;
		exit(1);
	}

	switch (field_)
	{
	case 1://salary
	{
		iter = employees.begin();
		for (iter; iter != employees.end(); iter++)
		{
			CreateTemp( iter, cond, value, field_);
		}
		break;
	}
	case 2://id
	{
		iter = employees.begin();
		for (iter; iter != employees.end(); iter++)
		{
			CreateTemp(iter, cond, value, field_);
		}
		break;
	}
	case 3://age
	{
		iter = employees.begin();
		for (iter; iter != employees.end(); iter++)
		{
			CreateTemp(iter, cond, value, field_);
		}
		break;
	}
	case 0://error
		cout << "Bad field" << endl;
		exit(1);
	}
	return temp;
}

void Database::CreateTemp(vector<Person*>::iterator iter, const char * cond, const char* value, int field_)
{
	Employee *empl;
	int temp_data;
	switch (field_) 
	{
	case 1: temp_data = dynamic_cast<Employee*>(*iter)->GetSalary();
		break;
	case 2: temp_data = dynamic_cast<Employee*>(*iter)->GetId();
		break;
	case 3: temp_data = dynamic_cast<Employee*>(*iter)->Getage();
		break;
	case 0:
		cout << "Bad field" << endl;
		exit(1);
	}
	
	if (!strcmp(cond, "gt"))
		if ( temp_data > atoi(value))
		{
			empl = new Employee(dynamic_cast<Employee*>(*iter)->Getf_name(), dynamic_cast<Employee*>(*iter)->Getl_name(), dynamic_cast<Employee*>(*iter)->Getage(), dynamic_cast<Employee*>(*iter)->GetId());
			empl->SetDepartment(dynamic_cast<Employee*>(*iter)->GetDepartment());
			empl->SetSalary(dynamic_cast<Employee*>(*iter)->GetSalary());
			ID.push_back(dynamic_cast<Employee*>(*iter)->GetId());
			temp.push_back(empl);
		}
	if (!strcmp(cond, "lt"))
		if ( temp_data < atoi(value))
		{
			empl = new Employee(dynamic_cast<Employee*>(*iter)->Getf_name(), dynamic_cast<Employee*>(*iter)->Getl_name(), dynamic_cast<Employee*>(*iter)->Getage(), dynamic_cast<Employee*>(*iter)->GetId());
			empl->SetDepartment(dynamic_cast<Employee*>(*iter)->GetDepartment());
			empl->SetSalary(dynamic_cast<Employee*>(*iter)->GetSalary());
			ID.push_back(dynamic_cast<Employee*>(*iter)->GetId());
			temp.push_back(empl);
		}
	if (!strcmp(cond, "eq"))
		if ( temp_data == atoi(value))
		{
			empl = new Employee(dynamic_cast<Employee*>(*iter)->Getf_name(), dynamic_cast<Employee*>(*iter)->Getl_name(), dynamic_cast<Employee*>(*iter)->Getage(), dynamic_cast<Employee*>(*iter)->GetId());
			empl->SetDepartment(dynamic_cast<Employee*>(*iter)->GetDepartment());
			empl->SetSalary(dynamic_cast<Employee*>(*iter)->GetSalary());
			ID.push_back(dynamic_cast<Employee*>(*iter)->GetId());
			temp.push_back(empl);

		}
}

void Database::ShowRecordSet(vector<Person*> rs)
{
	vector<Person*>::iterator iter = rs.begin();
	temp.clear();
	for (iter; iter != rs.end(); iter++)
	{
		(*iter)->Display(true);
	}
}
