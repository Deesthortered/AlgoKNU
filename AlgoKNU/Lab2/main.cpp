#include <iostream>
#include <vector>
#include "Red_Black_Tree.h"
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

	friend bool operator< (Employee &a, Employee &b)
	{
		return a.surname < b.surname;
	}
};
class Department
{
	string name;
	size_t employee_count;
	string enterprise;
	spaceRed_Black_Tree::Red_Black_Tree<Employee> employee_tree;
public:
	Department() = default;
	Department(string name, vector<Employee> employees)
	{
		this->name = name;
		this->employee_count = employees.size();
		for (size_t i = 0; i < employees.size(); i++)
			employee_tree.Insert(employees[i]);
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
		vector<string> res;
		for (size_t i = 0; i < employee_count; i++)
			res.push_back(employee_tree.FindByIndex(i).GetSurname());
		return res;
	}
	bool ExistingEmployee(string surname)
	{
		Employee tmp("", surname);
		tmp = employee_tree.Find(tmp);
		if (tmp.GetName() == "") return false;
		return true;
	}
	Employee GetEmployee(string surname)
	{
		return employee_tree.Find(Employee("", surname));
	}

	friend bool operator< (Department &a, Department &b)
	{
		return a.name < b.name;
	}
};
class Enterprise
{
	string name;
	size_t department_count;
	spaceRed_Black_Tree::Red_Black_Tree<Department> department_tree;
public:
	Enterprise() = default;
	Enterprise(string name, vector<Department> departments)
	{
		this->name = name;
		this->department_count = departments.size();
		for (size_t i = 0; i < departments.size(); i++)
			department_tree.Insert(departments[i]);
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
		vector<string> res;
		for (size_t i = 0; i < department_count; i++)
			res.push_back(department_tree.FindByIndex(i).GetName());
		return res;
	}
	bool ExistingDepartment(string name)
	{
		Department tmp(name, {});
		tmp = department_tree.Find(tmp);
		if (tmp.GetName() == "") return false;
		return true;
	}
	Department GetDeparment(string name)
	{
		return department_tree.Find(Department(name, {}));
	}
	bool ExistingEmployee(string surname)
	{
		for (size_t i = 0; i < department_count; i++)
			if (department_tree.FindByIndex(i).ExistingEmployee(surname)) 
				return true;
		return false;
	}
	Employee GetEmployee(string surname)
	{
		for (size_t i = 0; i < department_count; i++)
		{
			if (department_tree.FindByIndex(i).ExistingEmployee(surname))
				return department_tree.FindByIndex(i).GetEmployee(surname);
		}
		throw "Employee is not existing";
		return Employee();
	}
	vector<string> GetAllDepartments()
	{
		vector<string> res;
		for (size_t i = 0; i < department_count; i++)
			res.push_back(department_tree.FindByIndex(i).GetName());
		return res;
	}
	vector<string> GetAllEmployees()
	{
		vector<string> res, s;
		for (size_t i = 0; i < department_count; i++)
		{
			s = department_tree.FindByIndex(i).GetAllEmployees();
			res.insert(res.end(), s.begin(), s.end());
		}
		return res;
	}
};


int main()
{
	
	system("pause");
	return 0;
}