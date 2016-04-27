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
};


TurnPike::TurnPike(list<int> distances) : _distances(distances)
{
	// sort the distances before the call to the other functions
	bool found = false;
	vector<int> x;
	int i = distances.size();
	int n = i*(i - 1) / 2;
	x.resize(n + 1);
	found = turnpike(x, distances, n);

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
	x[n-1] = d.back();
	d.pop_back();
	list<int>::iterator it;
	int temp = x[n] - x[n - 1];
	it = find(d.begin(), d.end(), temp);
	if (it != d.end())
	{
		d.remove(temp);
		return place(x, d, n, 2, n - 2);
	}
	else
	{
		return false;
	}

}
bool place(vector<int> & x, list<int> d, int n, int left, int right)
{
	
	bool found = false;
	if (d.empty())
	{
		return true;
	}
	int dmax = d.back();
	d.pop_back();
	
	for (int j = 1; j < left && j > right && j <= n; j++) //this may need revision. 
	{
		int temp = x[j] - dmax;
		list<int>::iterator it;
		it = find(d.begin(), d.end(), temp);
		if (it != d.end())
		{
			x[right] = dmax;
			for (int i = 1; i < left && i > right && i <= n; i++) //this may need revision. 
			{
				d.remove(abs(x[i] - dmax));
			}
			found = place(x, d, n, left, right - 1);

			if (!found)
			{
				for (int i = 1; i < left && i > right && i <= n; i++) //this may need revision. 
				{
					d.push_back(abs(x[i] - dmax));
				}
				//sort d again.
				//sort(d.begin(), d.end());
				d.sort();
			}
		}
		temp = abs(x[n] - dmax - x[j]);
		it = find(d.begin(), d.end(), temp);
		if (!found && (it != d.end()))
		{
			for (int j = 1; j < left && j > right && j <= n; j++) //this may need revision. 
			{
				x[left] = x[n] - dmax;
				for (int i = 1; i < left && i > right && i <= n; i++) //this may need revision. 
				{
					d.remove(abs(x[n] - dmax - x[j]));
				}
				found = place(x, d, n, left + 1, right);
				if (!found)
				{
					for (int i = 1; i < left && i > right && i <= n; i++) //this may need revision. 
					{
						d.push_back(abs(x[n] - dmax - x[j]));
					}
					//sort
					//sort(d.begin(), d.end());
					d.sort();
				}

			}
		}
	}
	return found;
}

