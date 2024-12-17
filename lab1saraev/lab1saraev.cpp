#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>
#include <fstream>
#include "pipe.h"
#include "station.h"
#include "utils.h"

using namespace std;

int main() {

    unordered_map<int, Pipe> pipes;
    unordered_map<int, Station> stations;

    while (true) 
    {
        cout << "" << endl;
        cout << " ----------- MENU ---------- " << endl;
        cout << "" << endl;
        cout << " 1. Add gas pipe " << endl;
        cout << " 2. Add compression station " << endl;
        cout << " 3. All components view " << endl;
        cout << " 4. Work with pipes" << endl;
        cout << " 5. Work with stations" << endl;
        cout << " 6. Save the components" << endl;
        cout << " 7. Load the components" << endl;
        cout << " 0. EXIT " << endl;
        cout << "" << endl;
        cout << " --------------------------- " << endl;
        cout << "" << endl;
        cout << " Enter the number: " << endl;

        int choice;
        if (!(cin >> choice)) {
            cout << " Invalid choice. Please try again." << endl;
            LogInput("Error: " + std::to_string(choice));
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        LogInput(std::to_string(choice));

        switch (choice) {
        case 1:
            AddPipe(pipes);
            break;
        case 2:
            AddStation(stations);
            break;
        case 3:
            ViewAll(pipes);
            ViewAll(stations);
            break;
        case 4:
            WorkWithPipes(pipes);
            break;
        case 5:
            WorkWithStations(stations);
            break;
        case 6:
            SaveData(pipes, stations);
            break;
        case 7:
            LoadData(pipes, stations);
            break;
        case 0:
            cout << " End command" << endl;
            return 0;
        default:
            cout << " Invalid choice. Please try again." << endl;
            break;
        }
    }
}