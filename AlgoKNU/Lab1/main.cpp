#include <iostream>
#include <vector>
#include <string>
#include "IdealHashTable.h"
using namespace std;

class Employee
{
	string name;
	string surname;
	string department;

public:
	Employee() = default;
	Employee(string name, string surname)
	{
		this->name = name;
		this->surname = surname;
	}
	void SetDepartment(string name)
	{
		this->department = name;
	}

	string GetName()
	{
		return this->name;
	}
	string GetSurname()
	{
		return this->surname;
	}
	string GetDepartmentName()
	{
		return this->department;
	}

	static size_t GetKey(string surname)
	{
		size_t hash = 0;
		size_t prime = 29;
		for (register size_t i = 0; i < surname.size(); i++)
		{
			hash = hash * prime + (tolower(surname[i]) - 'a' + 1);
			hash %= (size_t)1e9 + 7;
		}
		return hash;
	}
};
class Department
{
	string name;
	size_t employee_count;
	string enterprise;
	spaceIdealHashTable::IdealHashTable<Employee> employee_table;
	vector<string> employee_keyfield;
public:
	Department() = default;
	Department(string name, vector<Employee> employees)
	{
		this->name = name;
		this->employee_count = employees.size();
		vector<pair<size_t, Employee>> tmp;
		employee_keyfield.reserve(employee_count);
		tmp.reserve(employee_count);
		for (size_t i = 0; i < employees.size(); i++)
		{
			employees[i].SetDepartment(this->name);
			tmp.push_back(pair<size_t, Employee>(Employee::GetKey(employees[i].GetSurname()), employees[i]));
			employee_keyfield.push_back(employees[i].GetSurname());
		}
		employee_table = spaceIdealHashTable::IdealHashTable<Employee>(tmp);
	}
	void SetEnterprise(string name)
	{
		this->enterprise = name;
	}

	string GetName()
	{
		return this->name;
	}
	size_t GetEmployeeCount()
	{
		return this->employee_count;
	}
	string GetEnterpriseName()
	{
		return this->enterprise;
	}
	vector<string> GetAllEmployees()
	{
		return this->employee_keyfield;
	}
	bool ExistingEmployee(string surname)
	{
		size_t hash = Employee::GetKey(surname);
		return employee_table.Exist(hash);
	}
	Employee GetEmployee(string surname)
	{
		size_t hash = Employee::GetKey(surname);
		return employee_table.Find(hash);
	}

	static size_t GetKey(string name)
	{
		size_t hash = 0;
		size_t prime = 29;
		for (register size_t i = 0; i < name.size(); i++)
		{
			hash = hash * prime + (tolower(name[i]) - 'a' + 1);
			hash %= (size_t)1e9 + 7;
		}
		return hash;
	}
};
class Enterprise
{
	string name;
	size_t department_count;
	spaceIdealHashTable::IdealHashTable<Department> department_table;
	vector<string> department_keyfield;
public:
	Enterprise() = default;
	Enterprise(string name, vector<Department> departments)
	{
		this->name = name;
		this->department_count = departments.size();
		vector<pair<size_t, Department>> tmp;
		tmp.reserve(department_count);
		this->department_keyfield.reserve(department_count);
		for (size_t i = 0; i < departments.size(); i++)
		{
			departments[i].SetEnterprise(this->name);
			tmp.push_back(pair<size_t, Department>(Department::GetKey(departments[i].GetName()), departments[i]));
			department_keyfield.push_back(departments[i].GetName());
		}
		this->department_table = spaceIdealHashTable::IdealHashTable<Department>(tmp);
	}

	string GetName()
	{
		return this->name;
	}
	size_t GetDepartmentCount()
	{
		return this->department_count;
	}
	vector<string> GetDepartmentNames()
	{
		return this->department_keyfield;
	}
	bool ExistingDepartment(string name)
	{
		size_t hash = Department::GetKey(name);
		return department_table.Exist(hash);
	}
	Department GetDeparment(string name)
	{
		size_t hash = Department::GetKey(name);
		if (!department_table.Exist(hash)) throw "Department is not existing";
		return department_table.Find(hash);
	}
	bool ExistingEmployee(string surname)
	{
		for (size_t i = 0; i < department_keyfield.size(); i++)
		{
			size_t hash = Department::GetKey(department_keyfield[i]);
			if (department_table.Find(hash).ExistingEmployee(surname)) return true;
		}
		return false;
	}
	Employee GetEmployee(string surname)
	{
		for (size_t i = 0; i < department_keyfield.size(); i++)
		{
			size_t hash = Department::GetKey(department_keyfield[i]);
			if (department_table.Find(hash).ExistingEmployee(surname)) 
				return department_table.Find(hash).GetEmployee(surname);
		}
		throw "Employee is not existing";
	}
	vector<string> GetAllDepartments()
	{
		return this->department_keyfield;
	}
	vector<string> GetAllEmployees()
	{
		vector<string> res;
		for (size_t i = 0; i < this->department_keyfield.size(); i++)
		{
			vector<string> s = department_table.Find(Department::GetKey(department_keyfield[i])).GetAllEmployees();
			res.insert(res.end(),  s.begin(), s.end());
		}
		return res;
	}
};

int main()
{
	vector<Employee> w1 = { Employee("Ivan", "Ivanov"), Employee("Petro", "Sidorov"), Employee("Sidor", "Petrovich") };
	vector<Employee> w2 = { Employee("Name", "NoName"), Employee("Vasilii", "Pirogov"), Employee("Igor", "Nikolaev") };
	vector<Department> deps = { Department("1 otdel razvedki", w1), Department("Seckretariat", w2) };
	Enterprise ent("Sharaskina kontora", deps);

	cout << " *** Enterprise info ***" << endl;
	cout << "Name:\t" << ent.GetName() << endl;
	cout << "Count of departments: " << ent.GetDepartmentCount() << endl;
	cout << "Departments: " << endl;
	vector<string> departments = ent.GetDepartmentNames();
	for (size_t i = 0; i < departments.size(); i++)
	{
		Department tmp_dep = ent.GetDeparment(departments[i]);
		cout << "\t Department name: " << tmp_dep.GetName() << endl;
		cout << "\t Enterprise: " << tmp_dep.GetEnterpriseName() << endl;
		cout << "\t Count of employee: " << tmp_dep.GetEmployeeCount() << endl;
		vector<string> employees = tmp_dep.GetAllEmployees();
		cout << "\t Employees: " << endl;
		for (size_t j = 0; j < employees.size(); j++)
		{
			if (!tmp_dep.ExistingEmployee(employees[i])) cout << "ERROR" << endl;
			Employee tmp_emp = tmp_dep.GetEmployee(employees[i]);
			cout << "\t\t Name:" << tmp_emp.GetName() << endl;
			cout << "\t\t Surname:" << tmp_emp.GetSurname() << endl;
			cout << "\t\t Department:" << tmp_emp.GetDepartmentName() << endl;
			cout << endl;
		}
		cout << endl;
	}
	cout << "All names:" << endl;
	vector<string> s = ent.GetAllEmployees();
	for (size_t i = 0; i < s.size(); i++)
		cout << s[i] << endl;

	system("pause");
	return 0;
}


/*
	Працівник
	1) Дізнатися ім'я та прізвище
	2) В якому підрозділі

	Підрозділ
	1) Дізнатися назву підрозділу
	2) Кількість працівників
	3) В якому підприємстві
	4) Імена всіх працівників
	5) Отримати данні працівника

	Підприємство
	1) Дізнатися назву підприємства
	2) Кількість підрозділів
	3) Отримати список підрозділів
	4) Знайти певний підрозділ
	5) Знайти певного працівника
	6) Отримати список всіх працівників певного підрозділу та всього підприємства
*/