//TurnPike.h
//Wyatt Emery
//Talon Marquard
//Project 4
//COSC 3020
//Spring 2016

using namespace std;

#include<vector>


class TurnPike
{
public:
    explicit TurnPike(vector<int> distances);
    void reconstruct();
    vector<int> getPoints() const;
private:
    vector<int> _distances;
    vector<int> _points;

};


TurnPike::TurnPike(vector<int> distances) : _distances(distances)
{
}

void TurnPike::reconstruct()
{
    _points = _distances;
}

vector<int> TurnPike::getPoints() const
{
    return _points;
}
