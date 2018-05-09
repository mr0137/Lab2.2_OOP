#include "Database.h"

int main()
{
    Database db;
    db.LoadFromFile("Data.csv");
    db.ArrangeSubordinates();
    db.DisplayAll();
    cout << "------------------------------" << endl;
    db.DisplayDepartmentEmployees("IT");
    cout << "------------------------------" << endl;
    db.FireEmployee(2);
    db.DisplayAll();
	cout << "------------------------------" << endl;
	vector<Person*> rs = db.SQL("department", "lt", "IT");
	db.ShowRecordSet(rs);
	rs.clear();

	rs = db.SQL("age", "lt", "62");
	db.ShowRecordSet(rs);
	rs.clear();

	rs = db.SQL("id", "lt", "3");
	db.ShowRecordSet(rs);
	rs.clear();

	system("pause");
	return 0;
}