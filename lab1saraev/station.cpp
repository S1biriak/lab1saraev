#include "station.h"
#include <limits>
#include "utils.h"

using namespace std;

int Station::max_id = 0;

Station::Station() {

}

void Station::reset_max_id()
{
    max_id = 0;
}


int Station::getId() const {
    return id;
}

void Station::AddStation() {
    id = ++max_id;

    cout << "Enter the name of the station (Positive value): ";
    getline(cin >> ws, name);
    LogInput(name);

    cout << "Enter the number of workshops (Positive value): ";

    while (!(cin >> workshops) || workshops <= 0) {
        cout << "Invalid value. Enter a positive number: ";
        LogInput("Error: " + std::to_string(workshops));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    LogInput(std::to_string(workshops));

    cout << "Enter the number of Active workshops: ";

    while (!(cin >> activeworkshops) || activeworkshops <= 0 || activeworkshops > workshops) {
        cout << "Invalid value. Enter a number from 0 to " << workshops << ": ";
        LogInput("Error: " + std::to_string(activeworkshops));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    LogInput(std::to_string(activeworkshops));


    cout << "Enter the efficiency of workshop: ";

    while (!(cin >> station_efficiency) || station_efficiency <= 0 || station_efficiency > 100) {
        cout << "Invalid value. Enter a positive number < 100%: ";
        LogInput("Error: " + std::to_string(station_efficiency));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    LogInput(std::to_string(station_efficiency));

    float unused_percentage = 100.0f * (workshops - activeworkshops) / workshops;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void Station::EditStatus() {
    cout << "The current number of Active workshops:" << activeworkshops << endl;
    cout << "Select an action: " << endl;
    cout << "1. Start the workshop" << endl;
    cout << "2. Stop the workshop" << endl;
    cout << "Enter the number (1 or 2): ";

    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Incorrect choice. Enter '1' to start or '2' to stop the workshop: ";
        LogInput("Error: " + std::to_string(choice));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (choice == 1) {
        if (activeworkshops < workshops) {
            activeworkshops++;
            cout << "The workshop is running. The current number of active workshops: " << activeworkshops << "/" << workshops << endl;
        }
        else {
            cout << "It is impossible to start a new workshop. All workshops are already working. The current number of active workshops: " << activeworkshops << "/" << workshops << endl;
        }
    }
    else if (choice == 2) {
        if (activeworkshops > 0) {
            activeworkshops--;
            cout << "The workshop is stopped. The current number of active workshops: " << activeworkshops << "/" << workshops << endl;
        }
        else {
            cout << "All workshops have already been stopped. The current number of active workshops: " << activeworkshops << "/" << workshops << endl;
        }
    }
}



void Station::view() const {

    cout << "Information about the station:" << endl;
    cout << "Id: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Number of workshops: " << workshops << endl;
    cout << "Number of active workshops: " << activeworkshops << endl;
    if (workshops != 0) {
        float unused_percentage = 100.0f * (workshops - activeworkshops) / workshops;
        cout << "Percentage of unused workshops: " << unused_percentage << "%" << endl;
    }
    else {
        cout << "No workshops available." << endl;
    }

    cout << "Efficiency: " << station_efficiency << "%" << endl;

}


void Station::SaveStation(ofstream& outFile) const {
    outFile << "STATION" << endl;
    outFile << id << endl;
    outFile << name << endl;
    outFile << workshops << endl;
    outFile << activeworkshops << endl;
    outFile << station_efficiency << endl;
}

void Station::LoadStation(ifstream& inFile) {
    inFile >> id;
    inFile.ignore();
    getline(inFile, name);
    inFile >> workshops;
    inFile >> activeworkshops;
    inFile >> station_efficiency;
    inFile.ignore();


    if (id > max_id) {
        max_id = id;
    }
}

