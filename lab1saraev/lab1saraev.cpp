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

bool check_string(const string& input) 
{
    return !input.empty();
}
string check_strings(string& string_data) 
{
    do 
    {
        cin >> string_data;
        if (not check_string(string_data)) 
        {
            cout << "Enter string format output" << endl;
        }
    } while (check_string(string_data));
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
        cout << "Enter a integer data type greater than 0" << endl;
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
        cout << "Enter a double data type greater than 0" << endl;
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
        cout << "Enter a boolean data type greater than 0" << endl;
        cin >> bool_data;
    }
    return bool_data;
}


pipe add_pipe() 
{
    pipe new_pipe;
    cout << " Enter the pipe name: ";
    check_strings(new_pipe.name);
    cout << " Enter the length of the pipe: ";
    check_double(new_pipe.length);
    cout << " Enter the diameter of the pipe: ";
    check_int(new_pipe.diameter);
    cout << " Enter the repair of the pipe: ";
    check_bool(new_pipe.repair);
    cout << "" << endl;
    return new_pipe;
}

void output_pipe(pipe new_pipe) 
{
    if (new_pipe.name == "no") 
    {
        cout << " No new pipe " << endl;
    }
    else 
    {
        cout << " Info of pipes " << endl;
        cout << " 1. Name: " << "" << new_pipe.name << endl;
        cout << " 2. Length: " << "" << new_pipe.length << endl;
        cout << " 3. Diameter: " << "" << new_pipe.diameter << endl;
        cout << " 4. Repair: " << "" << new_pipe.repair << endl;
    }
}

void edit_pipe(pipe new_pipe)
{
    if (new_pipe.name == "no") 
    {
        cout << " No new pipe " << endl;
    }
    else 
    {
        cout << " Editing the under repair attribute " << endl;
        check_bool(new_pipe.repair);
    }
}

void save_pipe(ofstream& fout, const pipe& pipe)
{
    if (pipe.name != "no")
    {
        fout << " Info of pipes " << endl;
        fout << pipe.name << endl;
        fout << pipe.length << endl;
        fout << pipe.diameter << endl;
        fout << pipe.repair << endl;
    }
    
}

void load_pipe(ifstream& fin, pipe& pipe)
{
    fin >> pipe.name;
    fin >> pipe.length;
    fin >> pipe.diameter;
    fin >> pipe.repair;
}

cs add_cs()
{
    cs new_cs;
    int workshops_in_operation;
    cout << " Enter the cs name: ";
    check_strings(new_cs.name);
    cout << " Enter the workshops of the cs: ";
    check_int(new_cs.workshops);
    cout << " Enter the workshops_in_operation of the cs: ";
    check_int(new_cs.workshops_in_operation);
    do 
    {
        cin >> workshops_in_operation;
        check_int(workshops_in_operation);
    } while (workshops_in_operation > new_cs.workshops);
    new_cs.workshops_in_operation = workshops_in_operation;
    cout << " Enter the effcoef of the cs: ";
    check_double(new_cs.effcoef);
    cout << "" << endl;
    return new_cs;
}

void output_cs(cs new_cs)
{
    if (new_cs.name == "no")
    {
        cout << " No new station " << endl;
    }
    else
    {
        cout << " Info of station " << endl;
        cout << " 1. Name: " << "" << new_cs.name << endl;
        cout << " 2. Workshops: " << "" << new_cs.workshops << endl;
        cout << " 3. Workshops_in_operation: " << "" << new_cs.workshops_in_operation << endl;
        cout << " 4. Effcoef: " << "" << new_cs.effcoef << endl;
    }
}

void edit_cs(cs new_cs)
{
    if (new_cs.name == "no")
    {
        cout << " No new station " << endl;
    }
    else
    {
        int workshops_in_operation
        cout << " Editing the number of workshops " << endl;
        do
        {
            cin >> workshops_in_operation;
            check_int(workshops_in_operation);
        } while (workshops_in_operation > new_cs.workshops);
        new_cs.workshops_in_operation = workshops_in_operation;
    }
}

void save_cs(ofstream& fout, const cs& cs)
{
    if (cs.name != "no")
    {
        fout << " Info of station " << endl;
        fout << cs.name << endl;
        fout << cs.workshops << endl;
        fout << cs.workshops_in_operation << endl;
        fout << cs.effcoef << endl;
    }
}

void load_cs(ifstream& fin, cs& cs)
{
    fin >> cs.name;
    fin >> cs.workshops;
    fin >> cs.workshops_in_operation;
    fin >> cs.effcoef;
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
            if (line == " Info of pipes ")
            {
                load_pipe(fin, pipe);
                flag = 1;
            }
            else if (line == " Info of station ")
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
            return false;
            break;
        }
    }

}