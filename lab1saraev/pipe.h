#pragma once

#include <string>
#include <iostream>
#include <fstream>



class Pipe {

private:
    int id;
    static int max_id;

public:
    std::string name;
    float length = 0.0;
    int diameter = 0;
    bool inrepair = false;

    static void reset_max_id();
    Pipe();

    int getId() const;
    void AddPipe();
    void EditStatus();
    void SavePipe(std::ofstream& outFile) const;
    void LoadPipe(std::ifstream& inFile);
    void view() const;

};