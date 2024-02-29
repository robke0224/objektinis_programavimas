#include "student.h"

void generateRandomGrades(vector<Student>& students, double hw) {
    for (int i = 0; i < students.size(); ++i) {
        // random pazymiukai
        students[i].grades.resize(static_cast<int>(hw));
        for (int j = 0; j < hw; ++j) {
            students[i].grades[j] = rand() % 10 + 1;
        }

        // random egzas
        students[i].exam_results = rand() % 10 + 1;

        // galutinio mediana arba vidurkis
        double total_grades = accumulate(students[i].grades.begin(), students[i].grades.end(), 0.0);
        students[i].final_avg = (total_grades / hw) * 0.4 + (students[i].exam_results) * 0.6;
        students[i].median = calculateMedian(students[i].grades);
    }
}

void generateRandomData(vector<Student>& students, double hw) {
    string first_names[] = {"Jonas", "Emanuelis", "Mikas", "Adomas", "Vilius", "Lukas", "Tomas", "Kasparas", "Benas", "Edas"};
    string last_names[] = {"Pavardukas", "Pavardelis", "Pavardytelis", "Pavardenis", "Pavardziukas", "Pavv", "Pavardaitis", "Pavardis", "Pavpav", "Pavardeliukas"};

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

double calculateMedian(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int size = arr.size();
    if (size % 2 != 0)
        return arr[size / 2];
    else
        return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
}

void readDataFromFile(vector<Student>& students, double& hw, int N) {
    try {
        ifstream file;
        file.open("studentai10000.txt");

        if (!file) {
            throw runtime_error("Nepavyko atidaryti failo");
        }
      string line;
      getline(file, line);

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
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

void enterDataManually(vector<Student>& students, double hw) {
    try {
        for (int i = 0; i < students.size(); ++i) {
            cout << "Iveskite " << i + 1 << " mokinio varda ir pavarde: ";
            cin >> students[i].name >> students[i].sur;

            students[i].grades.resize(static_cast<int>(hw));
            double total_grades = 0.0;

            for (int j = 0; j < hw; ++j) {
                cout << "Iveskite mokinio pazymius uz " << j + 1 << " namu darbus: ";
                while (!(cin >> students[i].grades[j])|| students[i].grades[j] < 1 || students[i].grades[j] > 10){
                    if (!(cin >> students[i].grades[j])) {
                        cout << "Klaida. Iveskite skaiciu." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else if (students[i].grades[j] < 1 || students[i].grades[j] > 10) {
                        cout << "Klaida. Skaicius privalo buti intervale nuo 1 iki 10." << endl;
                        cin.clear();
                        cin.ignore();
                    }
                } ;
                total_grades += students[i].grades[j];
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}


