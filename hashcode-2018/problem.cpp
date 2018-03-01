#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

#define I64 long long int

using namespace std;

I64 cur_time, rows, cols,
	car_count, ride_count, bonus, steps;

struct point
{
	I64 x, y;
};

struct ride
{
	I64 score, t_start, t_finish;
	point start, end;
};

struct car
{
	point pos;
	vector <I64> assigned_rides;
};

struct car_end_time
{
	I64 car_index, ride_index, end_time;
	bool operator< (car_end_time b) const { return end_time > b.end_time; }
};

I64 dist(point &a, point &b) { return abs(a.x - b.x) + abs(a.y - b.y); };

double heuristic(car &car, ride &ride)
{
	return 0;
}

vector<ride> rides;
vector<car> cars;
priority_queue<car_end_time> car_end_times;

vector<bool> is_ride_removed;

int main()
{
	freopen("a_example.in", "r", stdin);
	scanf("%lld %lld %lld %lld %lld %lld", &rows, &cols, 
					&car_count, &ride_count, &bonus, &steps);

	for (int i = 0; i < ride_count; i++)
	{
		ride temp;
		temp.score = 0;
		is_ride_removed.push_back(false);
		scanf("%lld %lld %lld %lld %lld %lld", &temp.start.x, &temp.start.y,
			&temp.end.x, &temp.end.y, &temp.t_start, &temp.t_finish);

		rides.push_back(temp);

	}

	for (int i = 0; i < car_count; i++)
	{
		car temp;
		temp.pos.x = temp.pos.y = 0;
		cars.push_back(temp);
	}
		

	// initial heuristic assignment
	for (int i = 0; i < car_count; i++)
	{
		I64 best_ride_id, best_ride_score = -1, tmp;
		
		// check rides
		for (int r = 0; r < ride_count; r++)
		{
			if (is_ride_removed[r]) continue;

			tmp = heuristic(cars[i], rides[r]);
			if (tmp == 0) continue; //TODO CHECK FOR EPSILON;

			if (best_ride_score < tmp)
			{
				best_ride_id = r;
				best_ride_score = tmp;
			}
		}

		// assign ride
		is_ride_removed[best_ride_id] = true;

	}

	system("PAUSE");
	return 0;
}
