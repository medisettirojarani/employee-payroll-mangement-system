#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>
using namespace std;

class Employee
{
private:
    int id;
    char name[50];
    char department[50];
    char designation[50];

    double basicSalary;
    double hra;
    double da;
    double allowance;
    double pf;
    double tax;
    int performanceRating;

public:

    // Constructor
    Employee()
    {
        id = 0;
        strcpy(name, "");
        strcpy(department, "");
        strcpy(designation, "");

        basicSalary = 0;
        hra = 0;
        da = 0;
        allowance = 0;
        pf = 0;
        tax = 0;
        performanceRating = 0;
    }

    // Input employee details
    void input()
    {
        cout << "\nEnter Employee ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Employee Name: ";
        cin.getline(name, 50);

        cout << "Enter Department: ";
        cin.getline(department, 50);

        cout << "Enter Designation: ";
        cin.getline(designation, 50);

        cout << "Enter Basic Salary: ";
        cin >> basicSalary;

        cout << "Enter HRA: ";
        cin >> hra;

        cout << "Enter DA: ";
        cin >> da;

        cout << "Enter Other Allowance: ";
        cin >> allowance;

        cout << "Enter PF Deduction: ";
        cin >> pf;

        cout << "Enter Tax Deduction: ";
        cin >> tax;

        do
        {
            cout << "Enter Performance Rating (1-5): ";
            cin >> performanceRating;

            if (performanceRating < 1 || performanceRating > 5)
            {
                cout << "Invalid rating! Enter between 1 and 5.\n";
            }

        } while (performanceRating < 1 || performanceRating > 5);
    }

    // Get employee ID
    int getID()
    {
        return id;
    }

    // Calculate performance bonus
    double calculateBonus()
    {
        double percentage = 0;

        switch (performanceRating)
        {
        case 5:
            percentage = 20;
            break;

        case 4:
            percentage = 15;
            break;

        case 3:
            percentage = 10;
            break;

        case 2:
            percentage = 5;
            break;

        case 1:
            percentage = 0;
            break;
        }

        return basicSalary * percentage / 100;
    }

    // Calculate gross salary
    double calculateGrossSalary()
    {
        return basicSalary + hra + da + allowance + calculateBonus();
    }

    // Calculate net salary
    double calculateNetSalary()
    {
        return calculateGrossSalary() - pf - tax;
    }

    // Display employee details
    void display()
    {
        cout << "\n---------------------------------------------";
        cout << "\nEmployee ID       : " << id;
        cout << "\nEmployee Name     : " << name;
        cout << "\nDepartment        : " << department;
        cout << "\nDesignation       : " << designation;
        cout << "\nBasic Salary      : Rs. " << fixed << setprecision(2)
             << basicSalary;
        cout << "\nHRA               : Rs. " << hra;
        cout << "\nDA                : Rs. " << da;
        cout << "\nOther Allowance   : Rs. " << allowance;
        cout << "\nPerformance Bonus : Rs. " << calculateBonus();
        cout << "\nPF Deduction      : Rs. " << pf;
        cout << "\nTax Deduction     : Rs. " << tax;
        cout << "\nGross Salary      : Rs. " << calculateGrossSalary();
        cout << "\nNet Salary        : Rs. " << calculateNetSalary();
        cout << "\nPerformance Rating: " << performanceRating << "/5";
        cout << "\n---------------------------------------------\n";
    }

    // Display salary slip
    void salarySlip()
    {
        cout << "\n\n=============================================";
        cout << "\n              SALARY SLIP";
        cout << "\n=============================================";

        cout << "\nEmployee ID       : " << id;
        cout << "\nEmployee Name     : " << name;
        cout << "\nDepartment        : " << department;
        cout << "\nDesignation       : " << designation;

        cout << "\n---------------------------------------------";

        cout << "\nBasic Salary      : Rs. " << fixed << setprecision(2)
             << basicSalary;

        cout << "\nHRA               : Rs. " << hra;
        cout << "\nDA                : Rs. " << da;
        cout << "\nOther Allowance   : Rs. " << allowance;
        cout << "\nPerformance Bonus : Rs. " << calculateBonus();

        cout << "\n---------------------------------------------";

        cout << "\nGross Salary      : Rs. " << calculateGrossSalary();

        cout << "\nPF Deduction      : Rs. " << pf;
        cout << "\nTax Deduction     : Rs. " << tax;

        cout << "\n---------------------------------------------";

        cout << "\nNet Salary        : Rs. " << calculateNetSalary();

        cout << "\n=============================================\n";
    }

    // Update employee details
    void update()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nEnter New Employee Name: ";
        cin.getline(name, 50);

        cout << "Enter New Department: ";
        cin.getline(department, 50);

        cout << "Enter New Designation: ";
        cin.getline(designation, 50);

        cout << "Enter New Basic Salary: ";
        cin >> basicSalary;

        cout << "Enter New HRA: ";
        cin >> hra;

        cout << "Enter New DA: ";
        cin >> da;

        cout << "Enter New Other Allowance: ";
        cin >> allowance;

        cout << "Enter New PF Deduction: ";
        cin >> pf;

        cout << "Enter New Tax Deduction: ";
        cin >> tax;

        do
        {
            cout << "Enter New Performance Rating (1-5): ";
            cin >> performanceRating;

            if (performanceRating < 1 || performanceRating > 5)
            {
                cout << "Invalid rating! Enter between 1 and 5.\n";
            }

        } while (performanceRating < 1 || performanceRating > 5);

        cout << "\nEmployee details updated successfully!\n";
    }
};


// Check whether employee ID already exists
bool employeeExists(int id)
{
    Employee emp;
    ifstream file("employees.dat", ios::binary);

    while (file.read((char *)&emp, sizeof(emp)))
    {
        if (emp.getID() == id)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


// Add employee
void addEmployee()
{
    Employee emp;

    cout << "\n========== ADD EMPLOYEE ==========\n";

    emp.input();

    if (employeeExists(emp.getID()))
    {
        cout << "\nEmployee ID already exists!\n";
        return;
    }

    ofstream file("employees.dat", ios::binary | ios::app);

    if (!file)
    {
        cout << "\nError opening file!\n";
        return;
    }

    file.write((char *)&emp, sizeof(emp));

    file.close();

    cout << "\nEmployee added successfully!\n";
}


// Display all employees
void displayAllEmployees()
{
    Employee emp;

    ifstream file("employees.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    bool found = false;

    cout << "\n========== ALL EMPLOYEES ==========\n";

    while (file.read((char *)&emp, sizeof(emp)))
    {
        emp.display();
        found = true;
    }

    file.close();

    if (!found)
    {
        cout << "\nNo employee records found!\n";
    }
}


// Search employee
void searchEmployee()
{
    int id;
    Employee emp;

    cout << "\nEnter Employee ID to search: ";
    cin >> id;

    ifstream file("employees.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    bool found = false;

    while (file.read((char *)&emp, sizeof(emp)))
    {
        if (emp.getID() == id)
        {
            cout << "\nEmployee Found!\n";
            emp.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nEmployee not found!\n";
    }
}


// Update employee
void updateEmployee()
{
    int id;
    Employee emp;

    cout << "\nEnter Employee ID to update: ";
    cin >> id;

    fstream file("employees.dat",
                 ios::binary | ios::in | ios::out);

    if (!file)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    bool found = false;

    while (file.read((char *)&emp, sizeof(emp)))
    {
        if (emp.getID() == id)
        {
            emp.update();

            long position = -static_cast<long>(sizeof(emp));

            file.seekp(position, ios::cur);

            file.write((char *)&emp, sizeof(emp));

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nEmployee not found!\n";
    }
}


// Delete employee
void deleteEmployee()
{
    int id;
    Employee emp;

    cout << "\nEnter Employee ID to delete: ";
    cin >> id;

    ifstream inputFile("employees.dat", ios::binary);

    if (!inputFile)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    ofstream tempFile("temp.dat", ios::binary);

    bool found = false;

    while (inputFile.read((char *)&emp, sizeof(emp)))
    {
        if (emp.getID() == id)
        {
            found = true;
        }
        else
        {
            tempFile.write((char *)&emp, sizeof(emp));
        }
    }

    inputFile.close();
    tempFile.close();

    remove("employees.dat");
    rename("temp.dat", "employees.dat");

    if (found)
    {
        cout << "\nEmployee deleted successfully!\n";
    }
    else
    {
        cout << "\nEmployee not found!\n";
    }
}


// Generate salary slip
void generateSalarySlip()
{
    int id;
    Employee emp;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    ifstream file("employees.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo employee records found!\n";
        return;
    }

    bool found = false;

    while (file.read((char *)&emp, sizeof(emp)))
    {
        if (emp.getID() == id)
        {
            emp.salarySlip();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nEmployee not found!\n";
    }
}


// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n\n=============================================";
        cout << "\n        EMPLOYEE PAYROLL SYSTEM";
        cout << "\n=============================================";

        cout << "\n1. Add Employee";
        cout << "\n2. Display All Employees";
        cout << "\n3. Search Employee";
        cout << "\n4. Update Employee";
        cout << "\n5. Delete Employee";
        cout << "\n6. Generate Salary Slip";
        cout << "\n7. Exit";

        cout << "\n=============================================";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addEmployee();
            break;

        case 2:
            displayAllEmployees();
            break;

        case 3:
            searchEmployee();
            break;

        case 4:
            updateEmployee();
            break;

        case 5:
            deleteEmployee();
            break;

        case 6:
            generateSalarySlip();
            break;

        case 7:
            cout << "\nThank you for using Employee Payroll System!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}