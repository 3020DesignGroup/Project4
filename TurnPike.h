//TurnPike.h
//Wyatt Emery
//Talon Marquard
//Project 4
//COSC 3020
//Spring 2016

using namespace std;

#include<vector>
#include<list>
#include<algorithm>
#include <iostream>
#include <cmath>
#include<set>
class TurnPike
{
public:
	explicit TurnPike(list<int> distances);
	void reconstruct();
	vector<int> getPoints() const;
private:
	multiset<int> _distances;
	vector<int> _points;
	bool place(vector<int> & x, multiset<int> d, int n, int left, int right);
	bool turnpike(vector<int> & x, multiset<int> d, int n);
};


TurnPike::TurnPike(list<int> distances)
{

    multiset<int> distancesS(distances.begin(), distances.end());
    _distances = distancesS;
}

void TurnPike::reconstruct()
{
    bool found = false;
    int i = _distances.size();
    int n = ((sqrt(8 * i + 1) + 1) / 2);
    _points.resize(n);
    found = turnpike(_points, _distances, n);
    if (found == false)
    {
        cout << "error!!!!!!!!!" << endl << endl;
    }
}

vector<int> TurnPike::getPoints() const
{
	return _points;
}
bool TurnPike::turnpike(vector<int> & points, multiset<int> d, int n)
{
	points[0] = 0;
	points[n - 1] = *d.rbegin();
	d.erase(*d.rbegin());
    /*auto it = d.find(points[n - 1] - points[n - 2]);
    if (it != d.end())
    {*/
        /*d.erase(it);*/
        return place(points, d, n, 1, n - 2);
 //   }
	//else
	//{
	//	return false;
	//}
}
//bool TurnPike::place(vector<int> & x, list<int> d, int n, int left, int right)
//{
//	//cout << "right == " << right << "  left == " << left << "size of d == " << d.size() << endl << endl;
//
//	bool found = false;
//	if (d.empty())
//	{
//		return true;
//	}
//	int dmax = d.back();
//	vector<int> check;
//	int temp = 0;
//	for (int i = 0; i < x.size(); i++)
//	{
//		if (i >= 1 && (i < left || i > right))
//		{
//			//cout << "ahjkahjkghklahjkag" << endl;
//			check.push_back(i);
//			//cout << "i == " << i << endl;
//		}
//	}
//
//	for each (int j in check)
//	{
//		temp = abs(x[j] - dmax);
//
//		list<int>::iterator it;
//		it = find(d.begin(), d.end(), temp);
//		if (it != d.end())
//		{
//			
//			cout << "temp == " << temp << endl;
//			x[right] = dmax;
//			int tempsize1 = d.size();
//			for each (int i in check)
//			{
//				d = remove1(d, abs(x[i] - dmax));
//			}
//			if (tempsize1 == d.size())
//			{
//				found = false;
//				x[right] = 0;
//			}
//			else
//			{
//				found = place(x, d, n, left, right - 1);
//				if (!found)
//				{
//					for each (int i in check)
//					{
//						d.push_back(abs(x[i] - dmax));
//					}
//					d.sort();
//				}
//			}
//		}
//	}
//	if (!found)
//	{
//		for each (int j in check)
//		{
//			temp = abs(x[n] - dmax - x[j]);
//			list<int>::iterator it;
//			it = find(d.begin(), d.end(), temp);
//			if (it != d.end())
//			{
//				x[left] = dmax;
//				int tempsize1 = d.size();
//				for each (int i in check)
//				{
//					d = remove1(d, abs(x[n] - dmax - x[i]));
//				}
//				if (tempsize1 == d.size())
//				{
//					found = false;
//					x[left] = 0;
//				}
//				else
//				{
//					found = place(x, d, n, left + 1, right);
//
//					if (!found)
//					{
//						for each (int i in check)
//						{
//							d.push_back(abs(x[n] - dmax - x[i]));
//						}
//						d.sort();
//					}
//				}
//			}
//		}
//	}
//	return found;
//	//return true;
//}

bool TurnPike::place(vector<int> & x, multiset<int> d, int n, int left, int right)
{
    int dmax = 0;
    bool found = false;

    if (d.empty()) 
    {
        return true;
    }

    dmax = *d.rbegin();

    bool valid = true;
    for (int i = 0; i < left; i++)
    {
        auto it = d.find(abs(x[i] - dmax));
        if (it == d.end())
        {
            valid = false;
        }
    }
    
    for (int i = right + 1; i < n; i++)
    {
        auto it = d.find(abs(x[i] - dmax));
        if (it == d.end())
        {
            valid = false;
        }
    }


    if (valid)
    {
        x[right] = dmax;
        for (int i = 0; i < left; i++)
        {
            auto it = d.find(abs(x[i] - dmax));
            if (it != d.end())
            d.erase(it);
        }
        for (int i = right + 1; i < n; i++)
        {
            auto it = d.find(abs(x[i] - dmax));
            if (it != d.end())
            d.erase(it);
        }

        found = place(x, d, n, left, right - 1);
        if (!found)
        {
            for (int i = 0; i < left; i++)
            {
                d.insert(abs(x[i] - dmax));
            }
            for (int i = right + 1; i < n; i++)
            {
                d.insert(abs(x[i] - dmax));
            }
        }
    }
//-------------------------------------------------------------------


    valid = true;
    for (int i = 0; i < left; i++)
    {
        auto it = d.find(abs(x[n - 1] - dmax - x[i]));
        if (it == d.end())
        {
            valid = false;
        }
    }
    for (int i = right + 1; i < n; i++)
    {
        auto it = d.find(abs(x[n - 1] - dmax - x[i]));
        if (it == d.end())
        {
            valid = false;
        }
    }
    
    if (!found && valid)
    {
        x[left] = x[n - 1] - dmax;
        for (int i = 0; i < left; i++)
        {
            auto it = d.find(abs(x[n - 1] - dmax - x[i]));
            if (it != d.end())
            d.erase(it);
        }
        for (int i = right + 1; i < n; i++)
        {
            auto it = d.find(abs(x[n - 1] - dmax - x[i]));
            if(it != d.end())
            d.erase(it);
        }

        found = place(x, d, n, left + 1, right);
        if (!found)
        {
            for (int i = 0; i < left; i++)
            {
                d.insert(abs(x[n - 1] - dmax - x[i]));
            }
            for (int i = right + 1; i < n; i++)
            {
                d.insert(abs(x[n - 1] - dmax - x[i]));
            }
        }
    }
  

    return found;

}

