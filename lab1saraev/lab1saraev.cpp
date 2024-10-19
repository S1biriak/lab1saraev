#include <iostream>
#include <string>

using namespace std;

struct pipe 
{
	string name="no";
	double length;
	int diameter;
	bool repair;
};

struct compressor_station 
{
	string name="no";
	int workshops;
	int workshops_in_operation;
	int effcoef;
};

pipe add_pipe() 
{
    pipe new_pipe;
    cout << " Enter the pipe name " << endl;
    cin >> new_pipe.name;
    cout << " Enter the length of the pipe " << endl;
    cin >> new_pipe.length;
    cout << " Enter the diameter of the pipe " << endl;
    cin >> new_pipe.diameter;
    cout << " Ennter the repair of the pipe " << endl;
    cin >> new_pipe.repair;
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
        cout << " Info of pipes" << endl;
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
        cout << " Editing the under repair attribute " << endl;;
        cin >> new_pipe.repair;
    }
}

cs add_cs()
{
    cs new_cs;
    cout << " Enter the cs name " << endl;
    cin >> new_cs.name;
    cout << " Enter the count shop of the cs " << endl;
    cin >> new_cs.count_shop;
    cout << " Enter the count workshop of the cs " << endl;
    cin >> new_cs.count_workshop;
    cout << " Enter the perfomance of the cs " << endl;
    cin >> new_cs.perfomance;
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
        cout << " 2. Count shop: " << "" << new_cs.count_shop << endl;
        cout << " 3. Count workshop: " << "" << new_cs.count_workshop << endl;
        cout << " 4. Perfomance: " << "" << new_cs.perfomance << endl;
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
        cout << " Editing the number of workshops " << endl;;
        cin >> new_cs.count_workshop;
    }
}
int main()
{
    pipe new_pipe;
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
        cout << " Enter the number " << endl;
        
        cin >> number;
        switch (number)
        {
        case 1:
            cout << " 1. Add gas pipe " << endl;
            new_pipe = add_pipe();
            output_pipe(new_pipe);
            break;
        case 2:
            cout << " 2. Add compression station " << endl;
            break;
        case 3:
            cout << " 3. All components view " << endl;
            break;
        case 4:
            cout << " 4. Edit gas pipe " << endl;
            break;
        case 5:
            cout << " 5. Edit compression station " << endl;
            break;
        case 6:
            cout << " 6. Save to file " << endl;
            break;
        case 7:
            cout << " 7. Upload from file " << endl;
            break;
        case 0:
            return false;
            break;
        }
    }
    
}