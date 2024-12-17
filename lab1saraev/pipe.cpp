#include "pipe.h"
#include <limits>
#include "utils.h"

using namespace std;

int Pipe::max_id = 0;

Pipe::Pipe() {

}

void Pipe::reset_max_id()
{
    max_id = 0;
}


int Pipe::getId() const {
    return id;
}

void Pipe::AddPipe() {
    id = ++max_id;
    cout << "Enter the name of the pipe: ";
    getline(cin >> ws, name);
    LogInput(name);

    cout << "Enter the length of the pipe (positive value): ";
    while (!(cin >> length) || length <= 0) {
        cout << "Invalid value. Enter a positive number: ";
        LogInput("Error: " + std::to_string(length));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    LogInput(std::to_string(length));


    cout << "Enter the diameter of the pipe: ";
    while (!(cin >> diameter) || diameter <= 0) {
        cout << "Invalid value. Enter a positive number: ";
        LogInput("Error: " + std::to_string(diameter));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    LogInput(std::to_string(diameter));

    inrepair = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Pipe::EditStatus() {
    if (name.empty()) {
        cout << "Pipe was not found.";
        return;
    }

    cout << "The current status of the pipe: " << (inrepair ? "In repairing" : "Running") << endl;
    cout << "Enter a new status ( 1 - In repairing, 0 - Running): ";
    while (!(cin >> inrepair) || (inrepair != 0 && inrepair != 1)) {
        cout << "Invalid value. Enter 1 or 0 ( 1 - In repairing, 0 - Running): ";
        LogInput("Error: " + std::to_string(inrepair));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Pipe::view() const {
    cout << "Information about the pipe:" << endl;
    cout << "Id: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Length: " << length << endl;
    cout << "Diameter: " << diameter << endl;
    cout << "Status: " << (inrepair ? "In repairing" : "Running") << endl;
}

void Pipe::SavePipe(ofstream& outFile) const {
    outFile << "PIPE" << endl;
    outFile << id << endl;
    outFile << name << endl;
    outFile << length << endl;
    outFile << diameter << endl;
    outFile << inrepair << endl;
}

void Pipe::LoadPipe(ifstream& inFile) {
    inFile >> id;
    inFile.ignore();
    getline(inFile, name);
    inFile >> length;
    inFile >> diameter;
    inFile >> inrepair;
    inFile.ignore();

    if (id > max_id) {
        max_id = id;
    }
}