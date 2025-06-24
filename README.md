# Employee Management System (C++)

A simple command-line Employee Management System written in C++ using STL containers and file I/O.

## Features

- Add new employees
- Display all employees
- Search for an employee by ID
- Update employee details
- Delete an employee
- Sort employees by salary or joining date (ID)
- Save and load employee data from a CSV file (`employees.csv`)

## How It Works

- Employee data is stored in a `vector<Employee>`.
- Data is persisted in a CSV file (`employees.csv`) in the same directory.
- All operations are performed via a text-based menu.

## Usage

### Compile

```sh
g++ -o employee_mgmt stlEmployee.cpp
```
For static build (dll(s) not required
)
```sh
g++ -static -o employee_mgmt.exe stlEmployee.cpp
```
### Run

```sh
./employee_mgmt
```

### Menu Options

1. Display all employees
2. Search employee
3. Add employees
4. Update an employee
5. Delete an employee
6. Sort Employees
7. Save all changes
8. Exit the program

## File Format

The `employees.csv` file uses the following format:

```
id,name,department,salary
```

Example:

```
1,John Doe,HR,50000
2,Jane Smith,IT,60000
```

## Requirements

- C++11 or later
- Standard C++ STL

## Notes

- Data is only saved to `employees.csv` when you choose the "Save all changes" option.
- On startup, the program loads existing data from `employees.csv` if it exists.

---