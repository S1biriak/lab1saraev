#include <iostream>
#include <limits>
#include <fstream>
#include "utils.h"
#include <algorithm>

void LogInput(const std::string& input) {
    std::ofstream logFile("log.txt", std::ios_base::app);
    if (logFile.is_open()) {
        logFile << input << std::endl;
    }
}

void AddPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    p.AddPipe();
    pipes.emplace(p.getId(), p);
}

void AddStation(unordered_map<int, Station>& stations) {
    Station s;
    s.AddStation();
    stations.emplace(s.getId(), s);
}

template<typename T>
void ViewAll(const std::unordered_map<int, T>& object) {
    if (object.empty()) {
        cout << "No objects available." << endl;
    }
    else {
        for (const auto& pair : object) {
            pair.second.view();
            cout << endl; 
        }
    }
}


template<typename T>
void EditStatus(std::unordered_map<int, T>& object, const std::string& type_of_object) {
    if (object.empty()) {
        cout << type_of_object << "was not found." << endl;
        return;
    }

    cout << "Enter ID" << type_of_object << " for editing: ";
    int id;
    cin >> id;
    LogInput(std::to_string(id));

    auto it = object.find(id);
    if (it != object.end()) {
        it->second.EditStatus();
    }
    else {
        cout << type_of_object << " with ID " << id << " not found." << endl;
    }
}


template<typename T>
void DeleteOblect(std::unordered_map<int, T>& object, const std::string& type_of_object) {
    if (object.empty()) {
        cout << type_of_object << " was not found.." << std::endl;
        return;
    }

    cout << "1. Delete specific " << type_of_object << endl;
    cout << "2. Delete all " << type_of_object << endl;
    cout << "Select an action: ";

    int choice;
    cin >> choice;
    LogInput(std::to_string(choice));

    switch (choice) {
    case 1: {
        cout << "Enter ID to delete: ";
        int id;
        cin >> id;
        if (object.erase(id)) {
            cout << type_of_object << " with ID " << id << " has been deleted." << endl;
        }
        else {
            cout << type_of_object << " with ID " << id << " not found." << endl;
        }
        break;
    }
    case 2:
        object.clear();
        T::reset_max_id();
        cout << "All " << type_of_object << " have been deleted." << endl;
        break;
    default:
        cout << "Invalid choice. Returning to menu." << endl;
    }
}


template<typename T>
std::vector<int> SearchObjectsByName(const std::unordered_map<int, T>& objects, const std::string& type_of_object) {

    std::vector<int> ids;

    while (true) {

        if (objects.empty()) {
            cout << "No " << type_of_object << " available." << endl;
            return ids;
        }

        cout << "Enter name ('exit' to return): ";
        string name;
        getline(cin >> ws, name);
        LogInput(name);

        if (name == "exit") {
            break;
        }

        bool search = false;
        for (const auto& [id, obj] : objects) {
            if (obj.name.find(name) != std::string::npos) {
                obj.view();
                ids.push_back(id);
                search = true;
            }
        }

        if (search) {
            break;
        }
        else {
            cout << type_of_object << " with the name \"" << name << "\" were not found." << endl;
        }
    }

    return ids;

}



void SaveData(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Station>& stations) {

    cout << "Enter the file name for saving data: ";
    string filename;
    cin >> filename;
    LogInput(filename);

    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& pair : pipes) {
            pair.second.SavePipe(outFile);
        }

        for (const auto& pair : stations) {
            pair.second.SaveStation(outFile);
        }
        outFile.close();
        cout << "The data has been successfully saved to a file." << endl;
    }
    else {
        cout << "Error, try again." << endl;
    }
}



void LoadData(unordered_map<int, Pipe>& pipes, unordered_map<int, Station>& stations) {
    cout << "Enter the file name for loading data: ";
    string filename;
    cin >> filename;
    LogInput(filename);

    ifstream inFile(filename);


    if (inFile.is_open()) {
        string line;
        pipes.clear();
        stations.clear();

        while (getline(inFile, line)) {
            if (line == "PIPE") {
                Pipe p;
                p.LoadPipe(inFile);
                pipes.emplace(p.getId(), p);

            }
            else if (line == "STATION") {
                Station s;
                s.LoadStation(inFile);
                stations.emplace(s.getId(), s);
            }


        }

        inFile.close();
        cout << "The data has been uploaded successfully." << endl;
    }
    else {
        cout << "Error, try again." << endl;
    }
}


void WorkWithPipes(unordered_map<int, Pipe>& pipes) {
    while (true) {
        cout << " Pipe Menu: " << endl;
        cout << " 1. Search pipes " << endl;
        cout << " 2. View all pipes " << endl;
        cout << " 3. Edit pipe/pipes " << endl;
        cout << " 4. Delete a pipe " << endl;
        cout << " 5. Return to main menu " << endl;
        cout << " Select an action: ";

        int choice = 0;
        LogInput(std::to_string(choice));

        if (!(cin >> choice)) {
            cout << " Invalid choice. Please try again." << endl;
            LogInput(" Error: " + std::to_string(choice));
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        vector<int> ids;

        switch (choice) {
        case 1:
            SearchAndEditPipes(pipes);
            break;
        case 2:
            ViewAll(pipes);
            break;
        case 3:
            ids = SearchAndEditPipes(pipes);
            EditSomePipes(pipes, ids);
            break;
        case 4:
            DeleteOblect(pipes, "pipe");
            break;
        case 5:
            return;
        default:
            cout << " Invalid choice. Please try again." << endl;
            break;
        }
    }
}

vector<int> SearchAndEditPipes(unordered_map<int, Pipe>& pipes) {
    vector<int> ids;

    if (pipes.empty()) {
        cout << " No pipes available." << endl;
        return ids;
    }

    cout << " Search pipes by:" << endl;
    cout << " 1. Name" << endl;
    cout << " 2. Status (In repair / Running)" << endl;
    cout << " 3. Return to main menu" << endl;
    cout << " Select an action: ";

    int choice;
    while (true) {


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
            ids = SearchObjectsByName(pipes, "pipe");
            return ids;
        case 2:
            ids = SearchPipesByStatus(pipes);
            return ids;
        case 3:
            return ids;
        default:
            cout << " Invalid choice. Please try again." << endl;
        }


    }

    return ids;
}


std::vector<int> SearchPipesByStatus(const unordered_map<int, Pipe>& pipes) {
    std::vector<int> ids;

    if (pipes.empty()) {
        cout << " No pipes available." << endl;
        return ids;
    }

    cout << " Enter status (1 - In repair, 0 - Running): ";

    int status;
    while (!(cin >> status) || (status != 0 && status != 1)) {
        cout << " Invalid value. Enter 1 or 0 ( 1 - In repairing, 0 - Running): ";
        LogInput("Error: " + std::to_string(status));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool search = false;

    for (const auto& pair : pipes) {
        if (pair.second.inrepair == status) {
            pair.second.view();
            ids.push_back(pair.first);
            search = true;
        }
    }

    if (!search) {
        cout << " Pipes with the status \"" << (status ? "In repairing" : "Running") << "\" were not found." << endl;
    }

    return ids;
}


void EditSomePipes(unordered_map<int, Pipe>& pipes, const std::vector<int>& ids) {
    if (ids.empty()) {
        cout << " No pipes available." << endl;
        return;
    }

    cout << " 1. Edit all" << endl;
    cout << " 2. Select specific pipes" << endl;
    cout << " 3. Return to previous menu" << endl;
    cout << " Enter your choice: ";

    int choice;
    while (true) {


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
            EditAllPipes(pipes, ids);
            break;
        case 2:
            EditSpecificPipes(pipes, ids);
            break;
        case 3:
            return;
        default:
            cout << " Invalid choice. Try again." << endl;
        }
    }

}

void EditAllPipes(std::unordered_map<int, Pipe>& pipes, const std::vector<int>& ids) {
    if (ids.empty()) {
        cout << " No pipes available." << endl;
        return;
    }

    cout << " Enter the new status for all selected pipes (1 - In repair, 0 - Running): ";
    int new_status;
    while (!(cin >> new_status) || (new_status != 0 && new_status != 1)) {
        cout << " Invalid value. Enter 1 or 0 (1 - In repair, 0 - Running): ";
        LogInput("Error: " + std::to_string(new_status));
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    for (int id : ids) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            it->second.inrepair = new_status;
        }
        else {
            cout << " Pipe with ID " << id << " not found." << endl;
        }
    }

    cout << " All selected pipes have been edited." << endl;
}


void EditSpecificPipes(std::unordered_map<int, Pipe>& pipes, const std::vector<int>& ids) {

    cout << " Enter the ID of a pipe you want to edit (or -7 to finish): ";

    int id;
    while (true) {
        cin >> id;
        LogInput(std::to_string(id));
        if (id == -7) {
            break;
        }
        if (std::find(ids.begin(), ids.end(), id) != ids.end()) {
            EditStatus(pipes, "pipe");
        }
        else {
            cout << " Pipe with ID " << id << " is not in the search results. Please enter a valid ID." << endl;
        }
        cout << " Enter another ID (or -7 to finish): ";
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << " Editing of selected pipes completed." << endl;

}

void AddActiveWorkshopToStations(unordered_map<int, Station>& stations, const vector<int>& ids) {
    for (int id : ids) {
        auto it = stations.find(id);
        if (it != stations.end()) {
            if (it->second.activeworkshops < it->second.workshops) {
                it->second.activeworkshops++;
            }
            else {
                cout << " Station ID " << id << " already has all workshops active." << endl;
            }
        }
    }
    cout << " Added 1 active workshop." << endl;
}

void RemoveActiveWorkshopFromStations(unordered_map<int, Station>& stations, const vector<int>& ids) {
    for (int id : ids) {
        auto it = stations.find(id);
        if (it != stations.end()) {
            if (it->second.activeworkshops > 0) {
                it->second.activeworkshops--;
            }
            else {
                cout << " Station ID " << id << " has no active workshops to remove." << endl;
            }
        }
    }
    cout << " Removed 1 active workshop." << endl;
}


void EditSomeStations(unordered_map<int, Station>& stations, const vector<int>& ids) {

    if (ids.empty()) {
        cout << " No stations to edit." << endl;
        return;
    }

    cout << " 1. Add 1 active workshop to all found stations" << endl;
    cout << " 2. Remove 1 active workshop from all found stations" << endl;
    cout << " 3. Return to previous menu" << endl;
    cout << " Enter your choice: ";

    int choice;
    while (true) {
        if (!(cin >> choice)) {
            cout << " Incorrect input. Please enter 1, 2, or 3." << endl;
            LogInput("Error: " + std::to_string(choice));
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            AddActiveWorkshopToStations(stations, ids);
            return;
        case 2:
            RemoveActiveWorkshopFromStations(stations, ids);
            return;
        case 3:
            return;
        default:
            cout << " Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    }

}


void WorkWithStations(unordered_map<int, Station>& stations) {
    while (true) {
        cout << " Station Menu:" << endl;
        cout << " 1. Search stations" << endl;
        cout << " 2. View all stations" << endl;
        cout << " 3. Edit stations" << endl;
        cout << " 4. Delete a station" << endl;
        cout << " 5. Return to main menu" << endl;
        cout << " Enter the number: ";

        int choice;

        if (!(cin >> choice)) {
            cout << " Invalid choice. Please try again." << endl;
            LogInput("Error: " + std::to_string(choice));
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        LogInput(std::to_string(choice));

        vector<int> ids;

        switch (choice) {
        case 1:
            SearchAndEditStations(stations);
            break;
        case 2:
            ViewAll(stations);
            break;
        case 3:
            ids = SearchAndEditStations(stations);
            EditSomeStations(stations, ids);
            break;
        case 4:
            DeleteOblect(stations, "station");
            break;
        case 5:
            return;
        default:
            cout << " Invalid choice. Please try again." << endl;
            break;
        }
    }
}


vector<int> SearchAndEditStations(unordered_map<int, Station>& stations) {

    vector<int> ids;

    if (stations.empty()) {
        cout << " No stations available." << endl;
        return ids;
    }

    cout << " Search stations by:" << endl;
    cout << " 1. Name" << endl;
    cout << " 2. Number of workshops" << endl;
    cout << " 3. Return to main menu" << endl;
    cout << " Select an action: ";

    int choice;
    while (true) {


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
            ids = SearchObjectsByName(stations, "station");
            return ids;
            break;
        case 2:
            ids = SearchStationsByUnusedWorkshops(stations);
            return ids;
            break;
        case 3:
            return ids;

        }
    }

    return ids;
}


vector<int> SearchStationsByUnusedWorkshops(const std::unordered_map<int, Station>& stations) {

    vector<int> ids;

    if (stations.empty()) {
        cout << " No stations." << endl;
        return ids;
    }

    cout << " Enter the percentage of unused workshops: ";

    float percentage;
    while (!(cin >> percentage) || percentage < 0 || percentage > 100) {
        cout << " Incorrect input. Please enter a number betwwen 0 - 100: ";
        LogInput("Error: " + std::to_string(percentage));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    LogInput(std::to_string(percentage));

    bool search = false;
    for (const auto& pair : stations) {

        float unused_percentage = 100.0f * (pair.second.workshops - pair.second.activeworkshops) / pair.second.workshops;

        if (unused_percentage >= percentage) {
            pair.second.view();
            ids.push_back(pair.first);
            search = true;
        }
    }

    if (!search) {
        cout << " Stations with a percentage of unused workshops >= " << percentage << "% were not found." << endl;
    }

    return ids;
}
