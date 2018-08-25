#include "../include/Vehicle.hpp"
 vector <State> Vehicle::nextStates(State* n)//vector<Vehicle::State>
{
	
	vector<State> next;
	State t;
	float alpha,beta,r,d=0.5; //alpha=steering angle, beta = turning angle, r=turning radius, d= distanced travelled

	for(alpha=-BOT_MAX_ALPHA; alpha<=BOT_MAX_ALPHA; alpha+=BOT_MAX_ALPHA/2)
	{
		beta= (d/BOT_L)*tan(alpha*PI/180);

		if(abs(beta)>0.001)
		{
			r=d/beta;
			t.x=n->x - sin(n->theta)*r + sin(n->theta+beta)*r;
			t.y=n->y + cos(n->theta)*r - cos(n->theta+beta)*r;
			t.theta=fmod(n->theta+beta,2*PI);
			if(t.theta<0)
				t.theta+=2*PI;
		}
		else
		{
			t.x=n->x + d*cos(n->theta); // if turning radius is very small we assume that the back tire has moved straight
			t.y=n->y + d*sin(n->theta);
			t.theta=n->theta;
		}
		t.gx=(int)(t.x*10);
		t.gy=(int)(t.y*10);
		t.steer_angle=alpha;
		t.parent=n;

		if(t.gx>=0&&t.gx<1000&&t.gy>=0&&t.gy<1000)//change upperbound according to the map size
		{	
			next.push_back(t);
			// cout<<" Next states of "<<n.gx<<","<<n.gy<<","<<n.theta<<" "<<t.gx<<","<<t.gy<<","<<t.theta<<endl;
		}
		//printf("%f,%f,%f\n",t.x,t.y,t.theta);
	}
	return next;		
}
