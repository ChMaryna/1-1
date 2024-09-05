#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_EMPLOYEES = 100;

struct Employee {
    char lastName[50];
    char firstName[50];
    char phoneNumber[15];
    double salary;
};

void addEmployee(Employee employees[], int& count) {
    if (count >= MAX_EMPLOYEES) {
        cout << "��������� ����������� ������� �����������." << endl;
        return;
    }

    cout << "������ �������: ";
    cin >> employees[count].lastName;
    cout << "������ ��'�: ";
    cin >> employees[count].firstName;
    cout << "������ ����� �������� (������ +38 *** *** ****): ";
    cin >> employees[count].phoneNumber;
    cout << "������ ��������: ";
    cin >> employees[count].salary;

    count++;
}

void displayEmployees(Employee employees[], int count) {
    cout << left << "�������\t" << "��'�\t" << "�������\t" << "��������" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << employees[i].lastName << "\t\t"
            << employees[i].firstName << "\t\t"
            << employees[i].phoneNumber << "\t\t"
            << employees[i].salary << endl;
    }
}

void sortEmployees(Employee employees[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(employees[i].lastName, employees[j].lastName) > 0) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    cout << "����������� ���������� �� �������." << endl;
}

void searchByLastName(Employee employees[], int count) {
    char searchName[50];
    cout << "������ ������� ��� ������: ";
    cin >> searchName;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].lastName, searchName) == 0) {
            cout << "�������� �����������: " << employees[i].firstName << " " << employees[i].lastName
                << " �� ��������� " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "����������� � ����� �������� �� ��������." << endl;
    }
}

void searchBySalaryRange(Employee employees[], int count) {
    double minSalary, maxSalary;
    cout << "������ �������� ��������: ";
    cin >> minSalary;
    cout << "������ ����������� ��������: ";
    cin >> maxSalary;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (employees[i].salary >= minSalary && employees[i].salary <= maxSalary) {
            cout << "�������� �����������: " << employees[i].firstName << " " << employees[i].lastName
                << " �� ��������� " << employees[i].salary << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "����������� � ����� ������� ������� �� ��������." << endl;
    }
}

void saveToFile(Employee employees[], int count, const char* filename) {
    ofstream file(filename, ios::binary);

    if (!file) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        file.write(employees[i].lastName, sizeof(employees[i].lastName));
        file.write(employees[i].firstName, sizeof(employees[i].firstName));
        file.write(employees[i].phoneNumber, sizeof(employees[i].phoneNumber));
        file.write(reinterpret_cast<const char*>(&employees[i].salary), sizeof(employees[i].salary));
    }
    file.close();
    cout << "��� ������ �������� � ����." << endl;
}

void loadFromFile(Employee employees[], int& count, const char* filename) {
    ifstream file(filename, ios::binary);

    if (!file) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        file.read(employees[i].lastName, sizeof(employees[i].lastName));
        file.read(employees[i].firstName, sizeof(employees[i].firstName));
        file.read(employees[i].phoneNumber, sizeof(employees[i].phoneNumber));
        file.read(reinterpret_cast<char*>(&employees[i].salary), sizeof(employees[i].salary));
    }
    file.close();
    cout << "��� ������ ���������� �� �����." << endl;
}

void deleteEmployee(Employee employees[], int& count) {
    char lastName[50];
    cout << "������ ������� ��� ���������: ";
    cin >> lastName;

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].lastName, lastName) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < count - 1; i++) {
            employees[i] = employees[i + 1];
        }
        count--;
        cout << "����������� ��������." << endl;
    }
    else {
        cout << "����������� � ����� �������� �� ��������." << endl;
    }
}

void menu() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    const char* filename = "employees.dat";

    int choice;
    do {
        cout << "\n����:\n"
            << "1. ������ �����������\n"
            << "2. �������� ��� �����������\n"
            << "3. ����� �� �������\n"
            << "4. ����� �� �������� �������\n"
            << "5. ���������� �� ��������\n"
            << "6. �������� �����������\n"
            << "7. �������� � ����\n"
            << "8. ����������� � �����\n"
            << "0. �����\n"
            << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee(employees, count);
            break;
        case 2:
            displayEmployees(employees, count);
            break;
        case 3:
            searchByLastName(employees, count);
            break;
        case 4:
            searchBySalaryRange(employees, count);
            break;
        case 5:
            sortEmployees(employees, count);
            break;
        case 6:
            deleteEmployee(employees, count);
            break;
        case 7:
            saveToFile(employees, count, filename);
            break;
        case 8:
            loadFromFile(employees, count, filename);
            break;
        case 0:
            cout << "����� �� ��������." << endl;
            break;
        default:
            cout << "������������ ����. �������� ������." << endl;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "");
    menu();
    return 0;
}   `