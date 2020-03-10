#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int64MultiArray.h"
#include <iostream>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>
using namespace std;

int arrx[100],arry[100],count1;
turtlesim::Pose pos;
void Calback(const std_msgs::Int64MultiArray::ConstPtr & array)
{
	int i=0;
	printf("PID1 %ld\n",array->data.size());
	if(count1==0)
	for(vector<long int>::const_iterator it = array->data.begin(); it < array->data.end(); it+=2)
	{
		arry[i]=*it;
		arrx[i]=*(it+1);
		arrx[i+1]=-1;
		i++;
		if(array->data.size()>0)
			count1=1;
	}

}
void Callback2(const turtlesim::Pose::ConstPtr & position)
{
	printf("yoooooooooooooooooooooo00000000000000000000000\n");
	pos.x=position->x;
	pos.y=position->y;
	pos.theta=position->theta;
	pos.linear_velocity=position->linear_velocity;
	pos.angular_velocity=position->angular_velocity;
}
int main(int agrc,char **agrv)
{
	int count2=0;
	printf("PID 2\n");
	arrx[0]=-1;
	ros::init(agrc,agrv,"PID");
	ros::NodeHandle n;
	
	ros::Subscriber sub = n.subscribe("array",0,Calback);
	while(arrx[0]==-1)
		ros::spinOnce();
	printf("PID 2");
	//system("rosrun turtlesim turtlesim_node");
	for(int i=0;i<100;i++)
	{
		count2=i;
		if(arrx[i]==-1)
		{
			printf("PID %d\n",arrx[i]);
			break;
		}
		printf("PID %d %d\n",arrx[i],arry[i]);
	}
	system("rosservice call turtle1/teleport_absolute 0.748404 10.521768 0.0");
	//ros::shutdown();
	//sub.shutdown();
	//ros::init(agrc,agrv,"PID1");
	float error_angle=3.142/100;
	float error_linear=0.1;
	//ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
	//ros::NodeHandle k;
	ros::Subscriber sub1= n.subscribe("turtle1/pose",0,Callback2);
	ros::Rate rate(1);
	geometry_msgs::Twist cammand;
	//cammand.angular.z=3*3.142/4.0;
	ros::Rate loop_rate(100);
	rate.sleep();
	//ros::publisher pub1 =n.advertise<turtlesim::Pose>("displaypath",1);
	//pub.publish(cammand);
	
	//while(1)
	//{	printf("1  ");
	//	ros::spinOnce();
	//	printf("%lf\n",pos.theta);
	//	if(abs(pos.theta-3*3.142/4.0)<error_angle)
	//		break;
	//}
	//cammand.angular.z=0;
	//cammand.linear.x=9;
	//pub.publish(cammand);
	//while(1)
	//{	printf("2\n");
	//	ros::spinOnce();
	//	if(pos.x-0.8<0)
	//		break;
	//}
	//cammand.angular.z=-3*3.2/4.0;
	//cammand.linear.x=0;
	//pub.publish(cammand);	
	//while(1)
	//{	printf("3\n");
	//	ros::spinOnce();
	//	if(abs(pos.theta)<error_angle)

	//		break;
	//}
	
	float current_angle,current_positionx,current_positiony;
	current_angle=pos.theta;
	current_positionx=pos.x;
	current_positiony=11.08889-pos.y;
	for(int i=0;i<count2;1)
	{
		ros::spinOnce();
		printf("%d %d %f %f %d %d \n",i,count2,pos.x,pos.y,arrx[i],arry[i]);

		float theta=float(atan(((arry[i])/50.0-current_positiony)/(arrx[i]/50.0-current_positionx)))+current_angle;
		if (theta>3.142/2)
			theta=theta-3.142;
		if (theta<-3.142/2)
			theta=theta+3.142;
		//if(abs(arrx[i]/50.0-current_positionx)<0.01)
		//if(abs(theta)<2.0)
		cammand.angular.z=-8*theta;
		printf("%f",theta);
		
		cammand.linear.x=2*sqrt(pow(((arry[i])/50.0-current_positiony),2)+pow((arrx[i]/50.0-current_positionx),2));
		pub.publish(cammand);
		//while(1)
		//pub1.publish(pos);
		printf("4\n");
		
		if(abs((pos.x-(arrx[i]/50.0))< error_linear) && (abs(11.08889-pos.y-(arry[i]/50.0)) < error_linear))
		{
			printf("Trueeeeeeeeeeeeeeeeeeee\n");
			i++;
		}
		
		current_angle=pos.theta;
		current_positionx=pos.x;
		current_positiony=11.08889-pos.y;
		loop_rate.sleep();
	}

}