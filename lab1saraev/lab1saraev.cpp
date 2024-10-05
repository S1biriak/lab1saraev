#include <iostream>
#include <string>

using namespace std;

struct pipe 
{
	string name;
	double length;
	int diameter;
	bool repair;
};

struct compressor_station 
{
	string name;
	int workshops;
	int workshops_in_operation;
	int effcoef;
};

int main()
{
    cout << "" << endl;
    cout << " ----------- MENU ---------- " << endl;
    cout << "" << endl;
    cout << " 1. Add gas pipe " << endl;
    cout << " 2. Add compression station " << endl;
    cout << " 3. All components view " << endl;
    cout << " 4. Edit gas pipe " << endl;
    cout << " 5. Edit compression station " << endl;
    cout << " 6. Save to file " << endl;
    cout << " 7. Upload from file " << endl;
    cout << " 0. EXIT " << endl;
    cout << "" << endl;
    cout << " --------------------------- " << endl;
    cout << "" << endl;
}