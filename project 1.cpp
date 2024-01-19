#include <iostream>
#include <iomanip>  //Library for "stew" function that makes the schedule alligned 
#include <climits> //Library for the highest, lowest value
#include <algorithm> //Library for Transform function
using namespace std;

int main() {
    const int MAX_ROWS = 20;
    int ROWS = 4;
    const int COLS = 5;
    string Names[MAX_ROWS] = { "Noura", "Aziz", "Deem", "Omar" };
    string Days[COLS] = { "SUN", "MON", "TUE", "WED", "THU" };
    int Numbers[MAX_ROWS][COLS] =
    { {8, 7, 7, 5, 9},
      {9, 9, 10, 12, 5},
      {6, 10, 11, 10, 9},
      {8, 11, 5, 8, 12} };

    // Display the initial table
    cout << setw(8) << " ";
    for (int j = 0; j < COLS; j++) {
        cout << setw(7) << Days[j];
    }
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << setw(7) << Names[i];
        for (int j = 0; j < COLS; j++) {
            cout << setw(7) << Numbers[i][j];
        }
        cout << endl;
    }
        // Modify working hours less than 6 to be 6
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            if (Numbers[i][j] < 6) {
                Numbers[i][j] = 6;
                cout << "The hours for " << Names[i] << " on " << Days[j] << " were changed to be 6" << endl;
            }
        }
    }

    // Display the table after modification
    cout << setw(8) << " ";
    for (int j = 0; j < COLS; j++) {
        cout << setw(7) << Days[j];
    }
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        cout << setw(7) << Names[i];
        for (int j = 0; j < COLS; j++) {
            cout << setw(7) << Numbers[i][j];
        }
        cout << endl;
    }

    // Find the day with the highest and lowest total working hours
    int highest_Total_Hours = 0;
    int day_highest_Total_Hours = 0;

    int lowest_Total_Hours = INT_MAX; 
    int day_lowest_Total_Hours = 0;

    for (int j = 0; j < COLS; j++) {
        int Total_Hours = 0;
        for (int i = 0; i < ROWS; i++) {
            Total_Hours += Numbers[i][j];
        }
        
        if (Total_Hours > highest_Total_Hours) {
            highest_Total_Hours = Total_Hours;
            day_highest_Total_Hours = j;
        }

        if (Total_Hours < lowest_Total_Hours) {
            lowest_Total_Hours = Total_Hours;
            day_lowest_Total_Hours = j;
        }
    }

    // Print the day of the week with the highest and lowest total working hours
    cout << "The day with the highest total working hours: " << Days[day_highest_Total_Hours] << endl;
    cout << "The day with the lowest total working hours: " << Days[day_lowest_Total_Hours] << endl;
    cout << "------------------------------------------------------------------" << endl;

    while (true) {
        cout << "\nChoose one of the following options:" << endl;
        cout << "1. Add a new Employee." << endl;
        cout << "2. Enquire about an Employee." << endl;
        cout << "3. Exit." << endl;

        char choice;
        cin >> choice;

        switch (choice) {

        case '1': {
            // Add a new employee
            string newEmployeeName;
            int newEmployeeHours[COLS];

            cout << "Enter the Employee name: ";
            cin >> newEmployeeName;

            cout << "Enter the working hours of the week: ";
            for (int j = 0; j < COLS; j++) {
                cin >> newEmployeeHours[j];
            }

            // Add the new employee to the arrays
            if (ROWS < MAX_ROWS) {
                Names[ROWS] = newEmployeeName;
                for (int j = 0; j < COLS; j++) {
                    Numbers[ROWS][j] = newEmployeeHours[j];
                }
                ROWS++;

                // Display the table after adding the new employee
                cout << "\nNew Entry Added." << endl;
                cout << setw(8) << " ";
                for (int j = 0; j < COLS; j++) {
                    cout << setw(7) << Days[j];
                }
                cout << endl;

                for (int i = 0; i < ROWS; i++) {
                    cout << setw(7) << Names[i];
                    for (int j = 0; j < COLS; j++) {
                        cout << setw(7) << Numbers[i][j];
                    }
                    cout << endl;
                }
                cout << "------------------------------------------------------------------" << endl;
            }
            break;
        }

        case '2': {  
    // Enquiring about an employee
    string employeeNameToInquire;
    cout << "Enter the name of an employee: ";
    cin >> employeeNameToInquire;

    // Convert the input name to lowercase to compare it with the names in the names array
    transform(employeeNameToInquire.begin(), employeeNameToInquire.end(), employeeNameToInquire.begin(), ::tolower);

    // Search for the employee in the names array (case insensitive)
    int employeeIndex = -1;
    for (int i = 0; i < ROWS; i++) {
        string currentName = Names[i];
    // Convert the input name to lowercase to compare it with the names in the names array
        transform(currentName.begin(), currentName.end(), currentName.begin(), ::tolower);
        
        if (employeeNameToInquire == currentName) {
            employeeIndex = i;
            break;
        }
    }

    if (employeeIndex != -1) {

        // How many weekly working hours has the employee worked
        int weeklyWorkingHours = 0;
        for (int j = 0; j < COLS; j++) {
            weeklyWorkingHours += Numbers[employeeIndex][j];
        }
        cout << employeeNameToInquire<<" has worked " << weeklyWorkingHours << " hours in the week." << endl;

        // The day of the week does the employee have the highest number of working hours
        int maxHours = 0;
        int maxDayIndex = 0;
        for (int j = 0; j < COLS; j++) {
            if (Numbers[employeeIndex][j] > maxHours) {
                maxHours = Numbers[employeeIndex][j];
                maxDayIndex = j;
            }
        }
        cout << "The day that "<<employeeNameToInquire<<" has the highest working hours is " << Days[maxDayIndex] << endl;

        // Calculate the employee’s salary
        int regularHourlyRate = 100;
        int overtimeHourlyRate = 200;
        int regularHoursPerDay = 9;  // 9 hours is regular working hours per day
        int overtimeThreshold = 9;   // More than 9 are considered overtime

        int totalRegularHours = 0;
        int totalOvertimeHours = 0;

        // Calculate total regular and overtime hours
        for (int j = 0; j < COLS; j++) {
        totalRegularHours += min(regularHoursPerDay, Numbers[employeeIndex][j]);
        totalOvertimeHours += max(0, Numbers[employeeIndex][j] - regularHoursPerDay);
        }

        // Calculate the employee’s salary
        int salary = (totalRegularHours * regularHourlyRate) + (totalOvertimeHours * overtimeHourlyRate);
        cout << employeeNameToInquire << " Salary: " << salary << " SAR in the week." << endl;

        } else {
        // Employee not found in the names array
        cout << "Sorry, the employee does not exist." << endl;
        }

        cout << "------------------------------------------------------------------" << endl;
        break;
        }

        case '3':
            cout << "Thank you for using our system." << endl;
            return 0;

        default:
            cout << "Invalid option. Please choose again." << endl;
        }
    }

    return 0;
}
