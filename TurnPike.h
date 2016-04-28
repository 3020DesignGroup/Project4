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

class TurnPike
{
public:
	explicit TurnPike(list<int> distances);
	void reconstruct();
	list<int> getPoints() const;
private:
	list<int> _distances;
	list<int> _points;
	bool place(vector<int> & x, list<int> d, int n, int left, int right);
	bool turnpike(vector<int> & x, list<int> d, int n);
	list<int> remove1(list<int> d, int x);
};


TurnPike::TurnPike(list<int> distances) : _distances(distances)
{
	// sort the distances before the call to the other functions
	bool found = false;
	vector<int> x;
	int i = distances.size();
	//cout << "probelmsdfasd  asg " << i << endl;
	int n = (sqrt(8 * i + 1) + 1) / 2;
	x.resize(n + 1);
	found = turnpike(x, distances, n);
	if (found == false)
	{
		cout << "error!!!!!!!!!" << endl << endl;
	}
	list<int> ret(x.begin(), x.end());
	_distances = ret;
}

void TurnPike::reconstruct()
{
	_points = _distances;
}

list<int> TurnPike::getPoints() const
{
	return _points;
}
bool TurnPike::turnpike(vector<int> & x, list<int> d, int n)
{
	x[1] = 0;
	x[n] = d.back();
	d.pop_back();
	x[n - 1] = d.back();
	d.pop_back();
	list<int>::iterator it;
	int temp = x[n] - x[n - 1];
	it = find(d.begin(), d.end(), temp);
	if (it != d.end())
	{
		d = remove1(d, temp);
		return place(x, d, n, 2, n - 2);
	}
	else
	{
		return false;
	}

	//return true;
}
bool TurnPike::place(vector<int> & x, list<int> d, int n, int left, int right)
{
	//cout << "right == " << right << "  left == " << left << "size of d == " << d.size() << endl << endl;

	bool found = false;
	if (d.empty())
	{
		return true;
	}
	int dmax = d.back();
	vector<int> check;
	int temp = 0;
	for (int i = 0; i < x.size(); i++)
	{
		if (i >= 1 && (i < left || i > right))
		{
			//cout << "ahjkahjkghklahjkag" << endl;
			check.push_back(i);
			//cout << "i == " << i << endl;
		}
	}

	for each (int j in check)
	{
		temp = abs(x[j] - dmax);

		list<int>::iterator it;
		it = find(d.begin(), d.end(), temp);
		if (it != d.end())
		{
			
			cout << "temp == " << temp << endl;
			x[right] = dmax;
			int tempsize1 = d.size();
			for each (int i in check)
			{
				d = remove1(d, abs(x[i] - dmax));
			}
			if (tempsize1 == d.size())
			{
				found = false;
				x[right] = 0;
			}
			else
			{
				found = place(x, d, n, left, right - 1);
				if (!found)
				{
					for each (int i in check)
					{
						d.push_back(abs(x[i] - dmax));
					}
					d.sort();
				}
			}
		}
	}
	if (!found)
	{
		for each (int j in check)
		{
			temp = abs(x[n] - dmax - x[j]);
			list<int>::iterator it;
			it = find(d.begin(), d.end(), temp);
			if (it != d.end())
			{
				x[left] = dmax;
				int tempsize1 = d.size();
				for each (int i in check)
				{
					d = remove1(d, abs(x[n] - dmax - x[i]));
				}
				if (tempsize1 == d.size())
				{
					found = false;
					x[left] = 0;
				}
				else
				{
					found = place(x, d, n, left + 1, right);

					if (!found)
					{
						for each (int i in check)
						{
							d.push_back(abs(x[n] - dmax - x[i]));
						}
						d.sort();
					}
				}
			}
		}
	}
	return found;
	//return true;
}


list<int> TurnPike::remove1(list<int> d, int x)
{
	list<int> removed;
	bool check = false;
	for each (int j in d)
	{
		if ((j == x) && check == false)
		{
			check = true;
		}
		else
		{
			removed.push_back(j);
		}
	}
	return removed;
}

