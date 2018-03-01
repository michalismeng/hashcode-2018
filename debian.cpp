#include <bits/stdc++.h>
#define I64 long long
#define MAX_N 10005
#define CARRY dist(people[r].a,people[r].b,people[r].x,people[r].y);
#define TOT_TIME max(people[r].s,t + dist(x,y,people[r].a,people[r].b))-t + carry_time;
using namespace std;

I64 R,C,F,N,B,T;

typedef struct
{
	I64 a,b,x,y,s,f;
}ride;

ride people[MAX_N];
char complete[MAX_N];

typedef struct{
	I64 id,end_time,x,y;
}car;

bool operator<(const car& a,const car& b)
{
	return a.end_time > b.end_time;//min???
}

priority_queue<car> Q;

I64 dist(I64 x1,I64 y1,I64 x2,I64 y2)
{
	return abs(x1-x2)+abs(y1-y2);
}

double cost(I64 x,I64 y,I64 t,I64 r)
{
	I64 points = 0;
	I64 carry_time = dist(people[r].a,people[r].b,people[r].x,people[r].y);
	//if on time
	I64 finish_time = max(people[r].s,t + dist(x,y,people[r].a,people[r].b)) + carry_time;
	if(finish_time > people[r].f || finish_time > T)
		return 0;
	if(t + dist(x,y,people[r].a,people[r].b) <= people[r].s)//?
		points += B;
	points += carry_time;
	I64 total_time = finish_time - t;
	//printf("points = %lld,tot_time = %lld,finish_time = %lld\n",points,total_time,finish_time);
	return ((double)points)/((double)total_time);
}

I64 find_ride(car v)
{
	I64 a;
	I64 r = -1;
	double score = 0.;
	for(a = 0;a < N;a++){
		if(complete[a] == 0){
			double tmp = cost(v.x,v.y,v.end_time,a);
			//printf("cost = %lf\n",tmp);
			if(tmp > score){
				r = a;
				score = tmp;
			}
		}
	}
	return r;
}

vector<I64> res[MAX_N];

int main(void)
{
	I64 a,b;
	scanf("%lld%lld%lld%lld%lld%lld",&R,&C,&F,&N,&B,&T);
	for(a = 0;a < N;a++){
		ride r;
		scanf("%lld%lld%lld%lld%lld%lld",&r.a,&r.b,&r.x,&r.y,&r.s,&r.f);
		people[a] = r;
	}
	//push cars from start
	for(a = 0;a < F;a++){
		car tmp;
		tmp.end_time = tmp.x = tmp.y = 0;
		tmp.id = a;
		Q.push(tmp);
	}
	while(!Q.empty()){
		car v = Q.top();
		Q.pop();
		I64 r = find_ride(v);
		//printf("r = %lld\n",r);
		if(r != -1){
			complete[r] = 1;
			res[v.id].push_back(r);
			//push_new
			I64 carry_time = dist(people[r].a,people[r].b,people[r].x,people[r].y);
			v.end_time = max(people[r].s,v.end_time + dist(v.x,v.y,people[r].a,people[r].b))-v.end_time + carry_time;
			v.x = people[r].x;
			v.y = people[r].y;
			Q.push(v);
		}
	}
	//print result
	for(a = 0;a < F;a++){
		printf("%lld",res[a].size());
		for(b = 0;b < res[a].size();b++)
			printf(" %lld",res[a][b]);
		putchar('\n');
	}
	return 0;
}
