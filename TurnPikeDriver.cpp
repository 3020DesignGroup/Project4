//TurnPikeDriver.cpp
//Wyatt Emery
//Talon Marquard
//Project 4 - TurnPike Reconstruction
//COSC 3020 Spring 2016


#include"RandomUtilities.h"
#include"winTimer.h"
#include"TurnPike.h"
#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include<algorithm>
#include<list>

using namespace std;

bool getInput(vector<int>& points, list<int>& distances);

void randBuildPoints(vector<int>& points, list<int>& distances, int size);

void fileBuildPoints(vector<int>& points, list<int>& distances, ifstream& infile);

list<int> getDistances(vector<int> points);

template<typename T>
void print(const T vals)
{
    cout << "Point\tPosition" << endl;
    int i = 0;
    auto itBegin = vals.begin();
    while (itBegin != vals.end())
    {
        cout << i + 1 << ":\t" << *itBegin << endl;
        i++;
        itBegin++;
    }
}


vector<int> mirror(vector<int> vals)
{
    vector<int> ret = vals;
    for (int i = 0; i < vals.size(); i++)
    {
        vals[i] = vals.back() - vals[i];
    }
    for (int i = 0; i < vals.size(); i++)
    {
        ret[i] = vals[vals.size() - 1 - i];
    }
    
    return ret;
}

int main()
{
    string input;
    Timer timer;
    list<int> distances;
    vector<int> points;
    bool going = getInput(points, distances);
    while (!going)
    {
        going = getInput(points, distances);
    }

    TurnPike TP(distances);
    cout << "Distances are: " << endl;
    print(distances);

    timer.start();
    TP.reconstruct();
    timer.stop();

    sort(points.begin(), points.end());

    cout << "Original points are : " << endl;
    print(points);
    cout << "Mirrored Points are : " << endl;
    print(mirror(points));
    cout << "Reconstructed Points are : " << endl;
    print(TP.getPoints());
    cout << "\npoints were found in " << timer() << " seconds" << endl << endl;
    cout << "original points ";

    vector<int> mirroredPoints;
    if (points == TP.getPoints() || mirror(points) == TP.getPoints()) cout << "Match ";
    else cout << "Don't match ";
    cout << "reconstructed points" << endl;
    return 0;
}

bool getInput(vector<int>& points, list<int>& distances)
{

    string filename;
    ifstream infile;
    string option;

    //prompt for random or file entry.
    cout << "Enter r for random creation of Jobs. Enter f for input via external file: ";
    cin >> option;
    if (option == "r")
    {
        //prompt for size and other desired values
        int size = 0;
        cout << "please enter desired size: ";
        cin >> size;

        randBuildPoints(points, distances, size);
        cout << size << "points were created and distances were found" << endl;

        return true;
    }

    // fill the graph by file input
    else if (option == "f")
    {
        //prompt for file
        cout << "enter filename: ";
        cin >> filename;

        //open file
        infile.open(filename);
        if (!(infile.is_open()))
        {
            cerr << "File not found!" << endl << endl;
            return false;
        }

        fileBuildPoints(points, distances, infile);
        return true;
    }
    else
    {
        cerr << "unrecognized input. Please enter \"r\" or \"f\"" << endl << endl;
        return false;
    }
    return true;
}



void randBuildPoints(vector<int>& points, list<int>& distances, int size)
{
    int point = 0;
    points.push_back(point);
    for (int i = 0; i < size - 1; i++)
    {
        point = randInt(1, size*size);
        points.push_back(point);
    }

    distances = getDistances(points);
}

void fileBuildPoints(vector<int>& points, list<int>& distances, ifstream& infile)
{
    int point = 0;
    points.push_back(point);

    while (infile >> point)
    {
        points.push_back(point);
    }
    distances = getDistances(points);
}

list<int> getDistances(vector<int> points)
{
    vector<int> distances;
    sort(points.begin(), points.end());
    for (int i = 0; i < points.size(); i++)
    {
        for (int k = i + 1; k < points.size(); k++)
        {
            distances.push_back(points[k] - points[i]);
        }
    }
    sort(distances.begin(), distances.end());
    list<int> ret(distances.begin(), distances.end());
    return ret;
}

