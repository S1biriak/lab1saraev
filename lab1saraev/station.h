#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Station {

private:
    int id;
    static int max_id;

public:

    std::string name;
    int workshops = 0;
    int activeworkshops = 0;
    float station_efficiency = 0.0;

    Station();

    static void reset_max_id();

    int getId() const;
    void AddStation();
    void EditStatus();
    void SaveStation(std::ofstream& outFile) const;
    void LoadStation(std::ifstream& inFile);
    void view() const;
};