//TurnPike.h
//Wyatt Emery
//Talon Marquard
//Project 4
//COSC 3020
//Spring 2016

using namespace std;

#include<vector>
#include<list>

class TurnPike
{
public:
    explicit TurnPike(list<int> distances);
    void reconstruct();
    vector<int> getPoints() const;
private:
    list<int> _distances;
    vector<int> _points;

};


TurnPike::TurnPike(list<int> distances) : _distances(distances)
{
}

void TurnPike::reconstruct()
{
    
}

vector<int> TurnPike::getPoints() const
{
    return _points;
}
