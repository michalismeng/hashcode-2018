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
	I64 total_time = finish_time - carry_time - t;
	//printf("points = %lld,tot_time = %lld,finish_time = %lld\n",points,total_time,finish_time);
	return ((double)points)/((double)total_time);
}
double best_score;
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
	best_score = score;
	return r;
}

vector<I64> res[MAX_N];
vector<car> same_end;

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
		same_end.clear();
		car v = Q.top(),v2;
		Q.pop();
		same_end.push_back(v);
		while(!Q.empty() && (v2 = Q.top()).end_time== v.end_time){
			same_end.push_back(v2);
			Q.pop();
		}
		
		for(b = 0;b < same_end.size();b++){
			double same_end_score = 0;
			I64 id;
			for(a = 0;a < same_end.size();a++){
				I64 r = find_ride(same_end[a]);
				if(best_score > same_end_score){
					same_end_score = best_score;	
					id = a;
				}
			}
			I64 r = find_ride(same_end[id]);
			v = *(same_end.begin()+id);
			same_end.erase(same_end.begin()+id);
			if(r != -1){
				complete[r] = 1;
				res[v.id].push_back(r);
				//push_new
				I64 carry_time = dist(people[r].a,people[r].b,people[r].x,people[r].y);
				v.end_time = max(people[r].s,v.end_time + dist(v.x,v.y,people[r].a,people[r].b)) + carry_time;
				v.x = people[r].x;
				v.y = people[r].y;
				Q.push(v);
			}
		}
		//printf("r = %lld\n",r);
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
