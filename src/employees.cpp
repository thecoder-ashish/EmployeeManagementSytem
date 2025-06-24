#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

class Employee{
private:
    int id, salary;
    string name, department;

public:
    // constructor 
    Employee(int id, string n, string d, int s) : id(id), name(n), department(d), salary(s) {}

    // Getter
    int getID() const{
        return id;
    }
    int getSalary() const{
        return salary;
    }
    string getName() const{
        return name;
    }
    string getDepartment() const{
        return department;
    }

    // Setter
    void setSalary(int sal) {
        salary = sal;
    }
    void setName(string n) {
        name = n;
    }
    void setDepartement(string dep) {
        department = dep;
    }


    // methods to be used

    // display details of an employee
    void displayEmployee() const{
        cout << "ID: " << id <<endl;
        cout << "Name: " << name <<endl;
        cout << "Department: " << department <<endl;
        cout << "Salary: Rs " << salary <<endl<<endl;
    }

    // update existing employee
    void updateEmpData(string n, string depart, int sal){
        name=n;
        department=depart;
        salary=sal;

        cout << "Data of emp id " << id << " is updated\n" ;
    }
    
};


// Utility fucntions

// Functions to take inputs
int takeID(){
    int id;
    cin >> id;
    return id;
}
int takeSalary(){
    int sal;
    cin >> sal;
    return sal;
}
string takeName(){
    string name;
    cin.ignore(); // will be used after some int input everytime
    getline(cin, name);
    return name;
}
string takeDepartment(){
    string dep;
    getline(cin, dep); // will be used after takeName() so no cin.ignore() req
    return dep;
}

// Check if the user exist - this will be used by other functions and methods
// it is not of bool type or Employee type for their lack of functionality
Employee* empExist(vector<Employee> &emps, int id){
    for(auto &e : emps){
        if (e.getID()==id){
            return &e;
        }
    }
    return nullptr;
}

// Quick function to print the emp not found message
void empNotFoundMsg(int id){ cout << "Employee with ID " << id << " not found.\n"; }



// All the performable operations
// 1 - Display all employees
void displayAll(vector<Employee> &emps){
    for (const auto &e : emps){
        e.displayEmployee();
    }
}
// 2 - Search and employee
void searchEmp(vector<Employee> &emps){
    cout << "Enter employee id to be searched: ";
    int id = takeID();
    Employee* empPtr = empExist(emps, id);
    if (empPtr) {
        cout << "Employee found here are the details:-\n";
        empPtr->displayEmployee();
    } else {
        empNotFoundMsg(id);
    }
}

// 3 - Add employee
void addEmps(vector<Employee> &emps){
    int n;
    cout << "Enter number of employees you want to add: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "Enter the employee id: ";
        int id = takeID();
        cout << "Enter the employee name: ";
        string n = takeName();
        cout << "Enter the employee department: ";
        string dep = takeDepartment();
        cout << "Enter the employee salary: ";
        int sal = takeSalary();

        emps.push_back(Employee(id, n, dep, sal));
    }
    cout << "\nAll employees added!\n";
}

// 4 - Update an employee detail
void updateEmp(vector<Employee> &emps){
    cout << "Enter employee id to be updated: ";
    int id = takeID();

    Employee* empPtr = empExist(emps, id);
    if (empPtr){
        cout << "Enter the updated name: ";
        string n = takeName();
        
        cout << "Enter the updated department: ";
        string dep = takeDepartment();

        cout << "Enter the updated salary: ";
        int sal = takeSalary();

        empPtr->updateEmpData(n, dep, sal);
    } else {
        empNotFoundMsg(id);
    }
    
}

// 5 - Removing an employee by searching id
void deleteEmp(vector<Employee> &emps){
    cout << "Enter id of the employee to be deleted: ";
    int id = takeID();
    if (empExist(emps,id)){
        emps.erase(
            remove_if(emps.begin(), emps.end(), [id](const Employee &e){ return e.getID() == id; }),
            emps.end()
        );
        cout << "Data of employee with id " << id << " is deleted";
    } else {
        empNotFoundMsg(id);
    }
}

// 6 - Custom sort method to sort according to id (joining date) or salary
// Oldest -> newest
// or, highest salary -> least salary
void sortEmps(vector<Employee>& emps){
    int by;
    while (true){
        cout << "How do you want to sort the employees? (1 - by salary, 2 - by joining date or id)";
        cin >> by;
        
        if (by==1){ // sort by salary
            sort(emps.begin(), emps.end(), [](const Employee& e1, const Employee& e2){
                return e1.getSalary() > e2.getSalary();
            });
            
            cout << "Employees sorted by descending order of salary\n";
            break;
        } else if (by==2) { // sort by joining date (emp id)
            sort(emps.begin(), emps.end(), [](const Employee& e1, const Employee& e2){
                return e1.getID() < e2.getID();
            });
            cout << "Employees sorted by accending order of joining date\n";
            break;
        } else {
            cout << "\tInvalid sorting type\n";
        }
    }
}

// 7 - Save changes
void saveChanges(vector<Employee> &emps){
    ofstream out("../data/employees.csv");
    if (out){
        for (const auto &e : emps){
            int id = e.getID();
            string n = e.getName();
            string dep = e.getDepartment();
            int sal = e.getSalary();

            out << id << ',' << n << ',' << dep << ',' << sal << endl ;
        }
        cout << "All the changes are saved!\n";
    } else {
        cout << "Unable to save changes - cant open the file ../data/employees.csv";
    }
}


// Saving file data
void saveData(vector<Employee> &emps){
    ofstream out("../data/employees.csv");
    if (out){
        for (const auto &e : emps){
            out << e.getID() << ',' << e.getName() << ',' << e.getDepartment() << ',' << e.getSalary() << '\n';
        }
        out.close();
        cout << "Data saved successfully!!\n";
    } else{
        cout << "!!! Cant open the ../data/employees.csv !!!";
    }
}

// Loading file data
void loadData(vector<Employee> &emps){
    ifstream in("../data/employees.csv");
    if (in){
        string line;
        while (getline(in, line)){
            stringstream word(line);

            int id, sal;
            string n, dep;
            char comma; // to pass the delimiter comma

            word >> id >> comma;
            getline(word, n, ',');
            getline(word, dep, ',');
            word >> sal;

            emps.push_back(Employee(id, n, dep, sal));
        }
        in.close();
    } else {
        cout << "../data/employees.csv file doesn't exist.";
    }
}

// Main interaction ui
void ui(vector<Employee> &emps){
    while (true){
        cout << "\n\t\tWELCOME TO EMPLOYEE MANAGEMENT SYSTEM\n";
        cout << "Please enter what operation you want to perform\n";
        cout << "1 - Display all employees\n";
        cout << "2 - Search employee\n";
        cout << "3 - Add employees\n";
        cout << "4 - Update an employee\n";
        cout << "5 - Delete an employee\n";
        cout << "6 - Sort Employees\n";
        cout << "7 - Save all changes\n";
        cout << "8 - Exit the program\n";

        int choice;
        cin >> choice;

        switch (choice){
            case 1:
                displayAll(emps);
                break;
            case 2:
                searchEmp(emps);
                break;
            case 3:
                addEmps(emps);
                break;
            case 4:
                updateEmp(emps);
                break;
            case 5:
                deleteEmp(emps);
                break;
            case 6:
                sortEmps(emps);
                break;
            case 7:
                saveChanges(emps);
                break;
            case 8:
                cout << "\t\tExiting the program!!";
                return;
            default:
                cout << "\t!!! Invalid input !!!\n";
                break;
        }
    }
}


int main() {
    vector<Employee> employees;
    loadData(employees);

    ui(employees);
    return 0;
}