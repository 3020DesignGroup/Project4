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

using namespace std;

bool getInput(vector<int>& points, vector<int>& distances);

void randBuildPoints(vector<int>& points, vector<int>& distances, int size);

void fileBuildPoints(vector<int>& points, vector<int>& distances, ifstream& infile);

vector<int> getDistances(vector<int> points);

void print(const vector<int>& points);

int main()
{
    string input;
    Timer timer;
    vector<int> distances;
    vector<int> points;
    bool going = getInput(points, distances);
    while (!going)
    {
        going = getInput(points, distances);
    }

    TurnPike TP(distances);
 
    timer.start();
    TP.reconstruct();
    timer.stop();

    cout << "Original points are : " << endl;
    print(points);
    cout << "Reconstructed Points are : " << endl;
    print(TP.getPoints());
    cout << "\npoints were found in " << timer() << " seconds" << endl << endl;
    return 0;
}

bool getInput(vector<int>& points, vector<int>& distances)
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



void randBuildPoints(vector<int>& points, vector<int>& distances, int size)
{
    int point = 0;
    points.push_back(point);
    for (int i = 0; i < size; i++)
    {
        point = randInt(1, size*size);
        points.push_back(point);
    }

    distances = getDistances(points);
}

void fileBuildPoints(vector<int>& points, vector<int>& distances, ifstream& infile)
{
    int point = 0;
    points.push_back(point);

    while (infile >> point)
    {
        points.push_back(point);
    }
    distances = getDistances(points);
}

vector<int> getDistances(vector<int> points)
{
    return points;
}

void print( const vector<int>& points)
{
    cout << "Point\tPosition" << endl;
    for (int i = 0; i < points.size(); i++)
    {
        cout << i + 1 << ":\t" << points[i] << endl;
    }
}