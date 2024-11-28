#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct pipe 
{
	string name="no";
	double length;
	int diameter;
	bool repair;
};

struct cs 
{
	string name="no";
	int workshops;
	int workshops_in_operation;
	double effcoef;
};

bool valid_string(const string& input) 
{
    return !input.empty();
}
string check_strings(string& string_data) 
{
    do 
    {
        getline(cin, string_data);
        if (!valid_string(string_data))
        {
            cout << "" << endl;
            cout << " Please enter a valid string: ";
        }
    } while (!valid_string(string_data));
    return string_data;
}
int check_int(int& int_data)
{
    cin >> int_data;
    while (cin.fail() || cin.peek() != '\n' || int_data <= 0)
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "" << endl;
        cout << " Please enter a integer data type greater than 0: ";
        cin >> int_data;
    }
    return int_data;
}
double check_double(double& double_data)
{
    cin >> double_data;
    while (cin.fail() || cin.peek() != '\n' || double_data <= 0)
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "" << endl;
        cout << " Please enter a double data type greater than 0: ";
        cin >> double_data;
    }
    return double_data;
}
bool check_bool(bool& bool_data)
{
    cin >> bool_data;
    while (cin.fail() || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "" << endl;
        cout << " Enter 1 (yes) or 0 (no): ";
        cin >> bool_data;
    }
    return bool_data;
}


pipe add_pipe() 
{
    pipe new_pipe;
    cout << " Enter the pipe name: ";
    cin.ignore();
    check_strings(new_pipe.name);
    cout << " Enter the pipe length (in km): ";
    check_double(new_pipe.length);
    cout << " Enter the pipe diameter (in cm): ";
    check_int(new_pipe.diameter);
    cout << " Pipe under repair? (yes/no): ";
    check_bool(new_pipe.repair);
    cout << "" << endl;
    return new_pipe;
}

void output_pipe(pipe& new_pipe) 
{
    if (new_pipe.name == "no") 
    {
        cout << " No pipe information " << endl;
    }
    else 
    {
        cout << " Pipe Information " << endl;
        cout << " 1. Name: " << "" << new_pipe.name << endl;
        cout << " 2. Length: " << "" << new_pipe.length << endl;
        cout << " 3. Diameter: " << "" << new_pipe.diameter << endl;
        cout << " 4. Repair: " << "" << new_pipe.repair << endl;
    }
}

void edit_pipe(pipe& new_pipe)
{
    if (new_pipe.name == "no") 
    {
        cout << " No pipe to edit " << endl;
    }
    else 
    {
        cout << " Pipe under repair? (yes/no): ";
        check_bool(new_pipe.repair);
    }
}

void save_pipe(ofstream& fout, const pipe& pipe)
{
    if (pipe.name != "no")
    {
        fout << " Pipe Information " << endl;
        fout << pipe.name << endl;
        fout << pipe.length << endl;
        fout << pipe.diameter << endl;
        fout << pipe.repair << endl;
    }
    
}

void load_pipe(ifstream& fin, pipe& pipe)
{
    getline(fin, pipe.name);
    fin >> pipe.length;
    fin >> pipe.diameter;
    fin >> pipe.repair;
    fin.ignore();
}

cs add_cs()
{
    cs new_cs;

    cout << " Enter the cs name: ";
    cin.ignore();
    check_strings(new_cs.name);
    cout << " Enter the total number of workshops: ";
    check_int(new_cs.workshops);
    cout << " Enter the number of workshops in operation: ";
    check_int(new_cs.workshops_in_operation);
    while (new_cs.workshops_in_operation > new_cs.workshops)
    {
        cout << " Workshops in operation cannot exceed total workshops. Try again: ";
        check_int(new_cs.workshops_in_operation);
    }
    cout << " Enter the station efficiency (0-100): ";
    check_double(new_cs.effcoef);
    while (new_cs.effcoef > 100)
    {
        cout << " Efficiency must be between 0 and 100. Try again: ";
        check_double(new_cs.effcoef);
    }
    return new_cs;
}

void output_cs(cs& new_cs)
{
    if (new_cs.name == "no")
    {
        cout << "" << endl;
        cout << " No station information " << endl;
    }
    else
    {
        cout << "" << endl;
        cout << " Compression Station Information: " << endl;
        cout << " 1. Name: " << "" << new_cs.name << endl;
        cout << " 2. Workshops: " << "" << new_cs.workshops << endl;
        cout << " 3. Workshops in operation: " << "" << new_cs.workshops_in_operation << endl;
        cout << " 4. Efficiency: " << "" << new_cs.effcoef << "%" << endl;
    }
}

void edit_cs(cs& new_cs)
{
    if (new_cs.name == "no")
    {
        cout << " No station to edit " << endl;
    }
    else
    {
        do 
        {
            cout << " Enter the number of workshops in operation: ";
            check_int(new_cs.workshops_in_operation);
            if (new_cs.workshops_in_operation > new_cs.workshops) 
            {
                cout << " Workshops in operation cannot exceed total workshops.\n";
            }
        } while (new_cs.workshops_in_operation > new_cs.workshops);
    }
}

void save_cs(ofstream& fout, const cs& cs)
{
    if (cs.name != "no")
    {
        fout << " Compression Station Information " << endl;
        fout << cs.name << endl;
        fout << cs.workshops << endl;
        fout << cs.workshops_in_operation << endl;
        fout << cs.effcoef << endl;
    }
}

void load_cs(ifstream& fin, cs& cs)
{
    getline(fin, cs.name);
    fin >> cs.workshops;
    fin >> cs.workshops_in_operation;
    fin >> cs.effcoef;
    fin.ignore();
}

void save(const pipe& pipe, const cs& cs)
{
    ofstream fout("info.txt");
    save_pipe(fout, pipe);
    save_cs(fout, cs);
    fout.close();
}

void load(pipe& pipe, cs& cs)
{
    ifstream fin("info.txt");
    string line;
    int flag = 0;
    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            if (line == " Pipe Information ")
            {
                load_pipe(fin, pipe);
                flag = 1;
            }
            else if (line == " Compression Station Information ")
            {
                load_cs(fin, cs);
                flag = 1;
            }
            if (flag == 0) cout << " No info in file" << endl;
        }
        fin.close();
    }
}


int main()
{
    pipe new_pipe;
    cs new_cs;
    int number;
    while (true) 
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
        cout << " Enter the number: ";
        cin >> number;
        cout << "" << endl;

        switch (number)
        {
        case 1:
            cout << " 1. Add gas pipe " << endl;
            new_pipe = add_pipe();
            output_pipe(new_pipe);
            break;
        case 2:
            cout << " 2. Add compression station " << endl;
            new_cs = add_cs();
            output_cs(new_cs);
            break;
        case 3:
            cout << " 3. All components view " << endl;
            cout << "" << endl;
            output_pipe(new_pipe);
            output_cs(new_cs);
            break;
        case 4:
            cout << " 4. Edit gas pipe " << endl;
            edit_pipe(new_pipe);
            break;
        case 5:
            cout << " 5. Edit compression station " << endl;
            edit_cs(new_cs);
            break;
        case 6:
            cout << " 6. Save to file " << endl;
            save(new_pipe, new_cs);
            break;
        case 7:
            cout << " 7. Upload from file " << endl;
            load(new_pipe, new_cs);
            break;
        case 0:
            cout << "End command" << endl;
            return 0;
        default:
            cout << " Invalid choice. Please try again." << endl;
        }
    }

}