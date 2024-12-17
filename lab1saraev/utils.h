#pragma once

#include <unordered_map>
#include "pipe.h"
#include "station.h"
#include <vector>

void LogInput(const std::string& input);

void AddPipe(std::unordered_map<int, Pipe>& pipes);
void AddStation(std::unordered_map<int, Station>& stations);

template<typename T>
void ViewAll(const std::unordered_map<int, T>& object);

void EditStatusPipe(unordered_map<int, Pipe>& pipes, int id);
void EditStatusStation(std::unordered_map<int, Station>& stations);

template<typename T>
void DeleteOblect(std::unordered_map<int, T>& object, const std::string& type_of_object);

void SaveData(const std::unordered_map<int, Pipe>& pipes, const std::unordered_map<int, Station>& stations);
void LoadData(std::unordered_map<int, Pipe>& pipes, std::unordered_map<int, Station>& stations);

void WorkWithPipes(unordered_map<int, Pipe>& pipes);
void WorkWithStations(unordered_map<int, Station>& stations);

vector<int> SearchAndEditPipes(std::unordered_map<int, Pipe>& pipes);

template<typename T>
std::vector<int> SearchObjectsByName(const std::unordered_map<int, T>& object, const std::string& type_of_object);

template<typename T>
void EditStatus(std::unordered_map<int, T>& object, const std::string& type_of_object);


std::vector<int> SearchPipesByStatus(const unordered_map<int, Pipe>& pipes);
void EditSomePipes(unordered_map<int, Pipe>& pipes, const std::vector<int>& ids);
void EditAllPipes(std::unordered_map<int, Pipe>& pipes, const std::vector<int>& ids);
void EditSpecificPipes(std::unordered_map<int, Pipe>& pipes, const std::vector<int>& ids);

std::vector<int> SearchAndEditStations(unordered_map<int, Station>& stations);

std::vector<int> SearchStationsByUnusedWorkshops(const std::unordered_map<int, Station>& stations);

void AddActiveWorkshopToStations(unordered_map<int, Station>& stations, const vector<int>& ids);
void RemoveActiveWorkshopFromStations(unordered_map<int, Station>& stations, const vector<int>& ids);
