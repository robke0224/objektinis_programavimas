#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <numeric>
#include <limits>

using namespace std;

struct Student {
    string name, sur;
    double final_avg, median;
    vector<int> grades;
    int exam_results;
};

double calculateMedian(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int size = arr.size();
    if (size % 2 != 0)
        return arr[size / 2];
    else
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
}

bool compareByName(const Student& a, const Student& b) {
    return stoi(a.name.substr(6,1)) < stoi(b.name.substr(6,1));
}

bool compareBySurname(const Student& a, const Student& b) {
    return stoi(a.sur.substr(7,1)) < stoi(b.sur.substr(7,1));
}

bool compareByMedian(const Student& a, const Student& b) {
    return a.median < b.median;
}

bool compareByAvg(const Student& a, const Student& b) {
    return a.final_avg < b.final_avg;
}

void readDataFromFile(vector<Student>& students, double& hw, int N) {
    ifstream file;
    file.open("studentai10000.txt");

    if (!file) {
        cout << "Error opening the file" << endl;
        return;
    }

    string line;
    getline(file, line); // prasoka pirma eil

    int count = 0;
    while (getline(file, line) && count < N) {
        istringstream iss(line);
        Student student;
        iss >> student.name >> student.sur;
        int grade;
        while (iss >> grade) {
            student.grades.push_back(grade);
        }
        student.exam_results = student.grades.back();
        student.grades.pop_back();
        double finalAvg = 0.0;
        double median = 0.0;
        if (!student.grades.empty()) {
            finalAvg = accumulate(student.grades.begin(), student.grades.end(), 0.0) / student.grades.size();
            sort(student.grades.begin(), student.grades.end());
            int size = student.grades.size();
            if (size % 2 != 0)
                median = student.grades[size / 2];
            else
                median = (student.grades[size / 2 - 1] + student.grades[size / 2]) / 2.0;
        }
        student.final_avg = finalAvg;
        student.median = median;
        students.push_back(student);
        count++;
    }

    file.close();

    char sortChoice;
    cout << "Sort by (N)ame, (S)urname, (M)edian or (A)verage: ";
    cin >> sortChoice;
    switch (sortChoice){
        case 'N':
        case 'n':
            sort(students.begin(), students.end(), compareByName);
            break;
        case 'S':
        case 's':
            sort (students.begin(), students.end(), compareBySurname);
            break;
        case 'M':
        case 'm':
            sort (students.begin(), students.end(), compareByMedian);
            break;
        case 'A':
        case 'a':
            sort (students.begin(), students.end(), compareByAvg);
            break;
        default:
            cout << "Invalid choice. Data will be displayed unsorted." << endl;
            break;
    }
}

void enterDataManually(vector<Student>& students, double hw) {
    for (int i = 0; i < students.size(); ++i) {
        cout << "Enter " << i + 1 << " student's name and surname: ";
        cin >> students[i].name >> students[i].sur;

        students[i].grades.resize(static_cast<int>(hw));
        double total_grades = 0.0;

        for (int j = 0; j < hw; ++j) {
            cout << "Enter student's grades for " << j + 1 << " homework: ";
            while (!(cin >> students[i].grades[j])|| students[i].grades[j] < 1 || students[i].grades[j] > 10){
                if (!(cin >> students[i].grades[j])) {
                    cout << "Error: Please enter a number." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else if (students[i].grades[j] < 1 || students[i].grades[j] > 10) {
                    cout << "Error: Grade must be between 1 and 10." << endl;
                    cin.clear();
                    cin.ignore();
                }
            } ;
            total_grades += students[i].grades[j];
        }

        students[i].final_avg = total_grades / hw;
        students[i].median = calculateMedian(students[i].grades);

        do {
            cout << "Enter " << i + 1 << " student's exam grade: ";
            if (!(cin >> students[i].exam_results)) {
                cout << "Error: Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else if (students[i].exam_results < 1 || students[i].exam_results > 10) {
                cout << "Error: Grade must be between 1 and 10." << endl;
            }
        } while (cin.fail() || students[i].exam_results < 1 || students[i].exam_results > 10);

        students[i].final_avg = 0.4 * students[i].final_avg + 0.6 * students[i].exam_results;
    }
}

void generateRandomGrades(vector<Student>& students, double hw) {
    for (int i = 0; i < students.size(); ++i) {
        // Generate random grades
        students[i].grades.resize(static_cast<int>(hw));
        for (int j = 0; j < hw; ++j) {
            if (!(cin >> students[i].grades[j])) {
                cout << "Error: Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Generate random exam result
        do {
            if (!(cin >> students[i].exam_results)) {
                cout << "Error: Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (cin.fail() || students[i].exam_results < 1 || students[i].exam_results > 10);

        // Calculate final average and median
        double total_grades = accumulate(students[i].grades.begin(), students[i].grades.end(), 0.0);
        students[i].final_avg = (total_grades / hw) * 0.4 + (students[i].exam_results) * 0.6;
        students[i].median = calculateMedian(students[i].grades);
    }
}



void generateRandomData(vector<Student>& students, double hw) {
    string first_names[] = {"Jonas", "Ema", "Mikas", "Greta", "Vilius", "Sofija", "Tomas", "Eva", "Benas", "Izabelė"};
    string last_names[] = {"Pavardukas", "Pavardelis", "Pavardyte", "Pavardenis", "Pavardenaite", "Pavardyte", "Pavardaite", "Pavardis", "Pavpav", "Pavardeliukas"};

    for (int i = 0; i < students.size(); ++i) {
        students[i].name = first_names[rand() % 10];
        students[i].sur = last_names[rand() % 10];

        students[i].grades.resize(static_cast<int>(hw));
        double total_grades = 0.0;

        for (int j = 0; j < hw; ++j) {
            students[i].grades[j] = rand() % 10 + 1;
            total_grades += students[i].grades[j];
        }

        students[i].final_avg = total_grades / hw;
        students[i].median = calculateMedian(students[i].grades);

        students[i].exam_results = rand() % 10 + 1;

        students[i].final_avg = 0.4 * students[i].final_avg + 0.6 * students[i].exam_results;
    }
}

int main() {
    int s;
    double hw;

    char choice;
    vector<Student> students;

    do {
        cout << "Menu:" << endl;
        cout << "1. Enter data manually" << endl;
        cout << "2. Enter names and surnames manually and then generate random grades" << endl;
        cout << "3. Generate random names, surnames, and grades" << endl;
        cout << "4. Read data from file and print data on screen" << endl;
        cout << "5. Read data from file and create a file for results" << endl;
        cout << "6. End the program" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
         case '1': {
                 cout << "How many students in a group? ";
                 while (!(cin >> s)) {
                cout << "Error: Please enter a valid number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
                students.resize(s);

                 cout << "How much homework? ";
                 while (!(cin >> hw)) {
                cout << "Error: Please enter a valid number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                 }

    enterDataManually(students, hw);
    cout << "Data entered manually successfully." << endl;

    char displayChoice;
    cout << "Do you want to see the final average (A) or the median (M)? ";
    cin >> displayChoice;

    if (!(displayChoice == 'A' || displayChoice == 'a' || displayChoice == 'M' || displayChoice == 'm')) {
        cout << "Error: Invalid choice. Please enter 'A' or 'M'." << endl;
        break;
    }

    cout << left << setw(20) << "Name" << setw(20) << "Surname";
    if (displayChoice == 'A' || displayChoice == 'a')
        cout << setw(20) << "Final Average";
    else if (displayChoice == 'M' || displayChoice == 'm')
        cout << setw(20) << "Median";
    cout << endl;

    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < students.size(); i++) {
        cout << left << setw(20) << students[i].name << setw(20) << students[i].sur;
        if (displayChoice == 'A' || displayChoice == 'a')
            cout << setw(20) << fixed << setprecision(2) << students[i].final_avg;
        else if (displayChoice == 'M' || displayChoice == 'm')
            cout << setw(20) << fixed << setprecision(2) << students[i].median;
        cout << endl;
    }
    break;
}

            case '2': {
                cout << "How many students in a group? ";
                cin >> s;
                students.resize(s);

                cout << "How much homework? ";
                cin >> hw;

                // Only enter names and surnames manually
                for (int i = 0; i < students.size(); ++i) {
                    cout << "Enter " << i + 1 << " student's name and surname: ";
                    cin >> students[i].name >> students[i].sur;
                }

                // Generate random grades
                generateRandomGrades(students, hw);

                char displayChoice;
                cout << "Do you want to see the final average (A) or the median (M)? ";
                cin >> displayChoice;

                cout << left << setw(20) << "Name" << setw(20) << "Surname";
                if (displayChoice == 'A' || displayChoice == 'a')
                    cout << setw(20) << "Final Average";
                else if (displayChoice == 'M' || displayChoice == 'm')
                    cout << setw(20) << "Median";
                cout << endl;

                cout << "------------------------------------------------------------" << endl;
                for (int i = 0; i < students.size(); i++) {
                    cout << left << setw(20) << students[i].name << setw(20) << students[i].sur;
                    if (displayChoice == 'A' || displayChoice == 'a')
                        cout << setw(20) << fixed << setprecision(2) << students[i].final_avg;
                    else if (displayChoice == 'M' || displayChoice == 'm')
                        cout << setw(20) << fixed << setprecision(2) << students[i].median;
                    cout << endl;
                }
                break;
            }
            case '3': {
                cout << "How many students in a group?";
                 while (!(cin >> s)) {
                 cout << "Error: Please enter a valid number." << endl;
                 cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
                }
              students.resize(s);

            cout << "How much homework? ";
            while (!(cin >> hw)) {
            cout << "Error: Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
               }

                generateRandomData(students, hw);
                cout << "Random data generated successfully." << endl;

                char displayChoice;
                cout << "Do you want to see the final average (A) or the median (M)? ";
                cin >> displayChoice;

                cout << left << setw(20) << "Name" << setw(20) << "Surname";
                if (displayChoice == 'A' || displayChoice == 'a')
                    cout << setw(20) << "Final Average";
                else if(displayChoice == 'M' || displayChoice == 'm')
                    cout << setw(20) << "Median";
                cout << endl;

                cout << "------------------------------------------------------------" << endl;
                for (int i = 0; i < students.size(); i++) {
                    cout << left << setw(20) << students[i].name << setw(20) << students[i].sur;
                    if (displayChoice == 'A' || displayChoice == 'a'){
                        cout << setw(20) << fixed << setprecision(2) << students[i].final_avg;
                    }
                    else{
                        cout << setw(20) << fixed << setprecision(2) << students[i].median;
                    }
                    cout << endl;
                }
                break;
            }
            case '4': {
                int N;
                cout << "Enter how many data entries you want to read: ";
                cin >> N;

                readDataFromFile(students, hw, N);

                char displayChoice;
                cout << "Do you want to see the final average (A) or the median (M)? ";
                cin >> displayChoice;

                cout << left << setw(20) << "Name" << setw(20) << "Surname";
                if (displayChoice == 'A' || displayChoice == 'a')
                    cout << setw(20) << "Final Average";
                else if (displayChoice == 'M' || displayChoice == 'm')
                    cout << setw(20) << "Median";
                cout << endl;

                cout << "------------------------------------------------------------" << endl;
                for (int i = 0; i < students.size(); i++) {
                    cout << left << setw(20) << students[i].name << setw(20) << students[i].sur;
                    if (displayChoice == 'A' || displayChoice == 'a')
                        cout << setw(20) << fixed << setprecision(2) << students[i].final_avg;
                    else if (displayChoice == 'M' || displayChoice == 'm')
                        cout << setw(20) << fixed << setprecision(2) << students[i].median;
                    cout << endl;
                }
                break;
            }
            case '5':{
                ofstream out_file ("results.txt");
                if (!out_file){
                    cout << "error opening the file" << endl;
                }
                int N;
                cout << "Enter how many data entries you want to read: ";
                cin >> N;

                readDataFromFile(students, hw, N);

                char displayChoice;
                cout << "Do you want to see the final average (A) or the median (M)? ";
                cin >> displayChoice;

                out_file << left << setw(20) << "Name" << setw(20) << "Surname";
                if (displayChoice == 'A' || displayChoice == 'a')
                    out_file << setw(20) << "Final Average";
                else if (displayChoice == 'M' || displayChoice == 'm')
                    out_file << setw(20) << "Median";
                out_file << endl;

                out_file << "------------------------------------------------------------" << endl;
                for (int i = 0; i < students.size(); i++) {
                    out_file << left << setw(20) << students[i].name << setw(20) << students[i].sur;
                    if (displayChoice == 'A' || displayChoice == 'a')
                        out_file << setw(20) << fixed << setprecision(2) << students[i].final_avg;
                    else if (displayChoice == 'M' || displayChoice == 'm')
                        out_file << setw(20) << fixed << setprecision(2) << students[i].median;
                    out_file << endl;
                }
                break;

            }
            case '6': {
                cout << "Ending the program." << endl;
                break;
            }
            default:
                cout << "Invalid option. Please choose again." << endl;
        }
    } while (choice != '6');

    return 0;
}