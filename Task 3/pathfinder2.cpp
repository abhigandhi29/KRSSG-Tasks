#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include<math.h>
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;
using namespace cv;

int dist(Point point1,Point point2)
{
	return((point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y));
}
int check(Mat a,int i,int j)
{
	for(int a1=-5;a1<11;a1++)	
	for(int b=-5;b<11;b++)
	{
		if(i+a1<0 || j+b<0 || i+a1>=a.rows || j+b>=a.cols)
			return(0);
		if(a.at<uchar>(i+a1,j+b)>200)
			return(0); 
	}
	return(1);	
}
int draw(Mat c,Point point1,Point point2)
{
	printf("a %Lf\n", (sqrtl(dist(point1,point2))));
	if((sqrtl(dist(point1,point2)))!=0)
	for(int i=0;1;i++)
	{
		
		c.at<Vec3b>(point1.x+i*(point2.x-point1.x)/(sqrtl(dist(point1,point2))),point1.y+i*(point2.y-point1.y)/(sqrtl(dist(point1,point2))))[1]=255;
		if(i==int(sqrtl(dist(point1,point2))))
			break;
	}
	namedWindow("IMAGE1",WINDOW_NORMAL);
	imshow("IMAGE1",c);
	waitKey(1);

}
int draw1(Mat c,Point point1,Point point2)
{
	printf("a %Lf\n", (sqrtl(dist(point1,point2))));
	if((sqrtl(dist(point1,point2)))!=0)
	for(int i=0;1;i++)
	{
		c.at<Vec3b>(point1.x+i*(point2.x-point1.x)/(sqrtl(dist(point1,point2))),point1.y+i*(point2.y-point1.y)/(sqrtl(dist(point1,point2))))[1]=255;
		if(i==int(sqrtl(dist(point1,point2))))
			break;
	}
	namedWindow("IMAGE2",WINDOW_NORMAL);
	imshow("IMAGE2",c);
	waitKey(1);
	
}
int redraw(Mat c,Point point1,Point point2)
{
	printf("b %Lf\n", (sqrtl(dist(point1,point2))));
	if((sqrtl(dist(point1,point2)))!=0)
	for(int i=0;i<5;i++)
	{
		c.at<Vec3b>(point1.x+i*(point2.x-point1.x)/(sqrtl(dist(point1,point2))),point1.y+i*(point2.y-point1.y)/(sqrtl(dist(point1,point2))))[0]=0;
	}
	namedWindow("IMAGE1",WINDOW_NORMAL);
	imshow("IMAGE1",c);
	waitKey(50);
}


int main()
{
	srand(time(0));
	Mat a=imread("Image2.jpg",0);
	vector<Vec3f> circles;
	Mat b=a.clone();
	GaussianBlur( a, a, Size(9, 9), 2, 2 );
	HoughCircles(a,circles,CV_HOUGH_GRADIENT,1,a.rows/8,150,39,0,0);
	printf("%d\n",int(circles.size()));
	a.at<uchar>(circles[0][1],circles[0][0])=255;
	a.at<uchar>(circles[1][1],circles[1][0])=255;
	Mat c=imread("Image2.jpg",1);
	Mat d=c.clone();
	namedWindow("IMAGE",WINDOW_NORMAL);
	imshow("IMAGE",a);
	waitKey(0);
	Point initialpos,finalpos;
	if(c.at<Vec3b>(circles[0][1],circles[0][0])[1]<150)
	{
		initialpos=Point(circles[0][1],circles[0][0]);
		finalpos=Point(circles[1][1],circles[1][0]);
	}
	else
	{
		finalpos=Point(circles[0][1],circles[0][0]);
		initialpos=Point(circles[1][1],circles[1][0]);
	}
	vector<Point> begin;
	vector<Point> end; 
	begin.push_back(initialpos);
	end.push_back(finalpos);
	float starttotal[a.rows][a.cols],finaltotal[a.rows][a.cols];
	printf("1\n");
	int startpoints[a.rows][a.cols],finalpoints[a.rows][a.cols];
	printf("1\n");
	//float startweight[a.rows][a.cols],finalweight[a.rows][a.cols];
	printf("2\n");
	
	printf("2\n");
	//int connectedpoints[a.rows][a.cols];
	printf("1\n");

	//for(int i=0;i<a.rows;i++)
	//for(int j=0;j<a.cols;j++)
	//		connectedpoints[i][j]=0;
	//startweight[initialpos.x][initialpos.y]=0;
	//finalweight[finalpos.x][finalpos.y]=0;
	starttotal[initialpos.x][initialpos.y]=0;
	finaltotal[finalpos.x][finalpos.y]=0;
	startpoints[initialpos.x][initialpos.y]=-1;
	finalpoints[finalpos.x][finalpos.y]=-1;
	Point commonpoint;
	printf("1\n");
	int random,random1;
	while(1)
	{
		
		Point startconnect=initialpos,endconnect=finalpos;
		random=rand()%(a.rows*a.cols);
		random1=rand()%(a.rows*a.cols);
		//printf("%d\n",random);
		Point rand=Point(random/a.cols,random%a.cols);
		Point rand3=Point(random/a.cols,random%a.cols);
		Point rand1,rand2;
		int statusstart=1,statusfinal=1;
		for(int i=0;i<begin.size();i++)
		{
			if(dist(begin[i],rand)<dist(startconnect,rand))
				startconnect=begin[i];
		}
		for(int i=0;i<end.size();i++)
		{
			if(dist(end[i],rand)<dist(endconnect,rand))
				endconnect=end[i];
		}
		for(int i=0;i<5;i++)
		{
			printf("c %Lf\n", (sqrtl(dist(startconnect,rand))));
			statusstart=check(b,startconnect.x-i*((startconnect.x-rand.x)/(sqrtl(dist(startconnect,rand)))),startconnect.y-i*(startconnect.y-rand.y)/(sqrtl(dist(startconnect,rand))));
			if(statusstart==0)
			{
				rand1=Point(-1,-1);
				break;
			}
			rand1=Point(startconnect.x-i*((startconnect.x-rand.x)/(sqrtl(dist(startconnect,rand)))),startconnect.y-i*(startconnect.y-rand.y)/(sqrtl(dist(startconnect,rand))));
		}
		for(int i=0;i<5;i++)
		{
			printf("d %Lf\n", (sqrtl(dist(endconnect,rand3))));
			statusfinal=check(b,endconnect.x-i*((endconnect.x-rand3.x)/(sqrtl(dist(endconnect,rand3)))),endconnect.y-i*(endconnect.y-rand3.y)/(sqrtl(dist(endconnect,rand3))));
			if( statusfinal==0)
			{
				rand2=Point(-1,-1);
				break;
			}
			rand2=Point(endconnect.x-i*((endconnect.x-rand3.x)/(sqrtl(dist(endconnect,rand3)))),endconnect.y-i*(endconnect.y-rand3.y)/(sqrtl(dist(endconnect,rand3))));
		}
		
		if(statusstart==1)
		{
			//connectedpoints[startconnect.x][startconnect.y]++;
			//connectedpoints[rand1.x][rand1.y]++;
			startpoints[rand1.x][rand1.y]=(startconnect.x)*a.cols+startconnect.y;
			//startweight[rand1.x][rand1.y]=int(sqrtl(dist(startconnect,rand1),0.5);
			starttotal[rand1.x][rand1.y]=starttotal[startconnect.x][startconnect.y]+(sqrtl(dist(startconnect,rand1)));
			for(int i=0;i<begin.size();i++)
			{
				if(dist(rand1,begin[i])<500 )
				{
					if(starttotal[begin[i].x][begin[i].y]+(sqrtl(dist(rand1,begin[i])))<starttotal[rand1.x][rand1.y])
					{
						printf("yoooooooooooooooooooooooooooo\n");
						//redraw(c,rand1,Point(startpoints[begin[i].x][begin[i].y]/a.cols,startpoints[begin[i].x][begin[i].y]%a.cols));
						startpoints[rand1.x][rand1.y]=begin[i].x*a.cols+begin[i].y;
						starttotal[rand1.x][rand1.y]=starttotal[begin[i].x][begin[i].y]+(sqrtl(dist(rand1,begin[i])));
						
						//draw(c,rand1,begin[i]);
						startconnect=begin[i];
					}
				}
			} 
			begin.push_back(rand1);
			draw(c,startconnect,rand1);
		}
		printf("statusfinal=%d\n",statusfinal);
		if(statusfinal==1)
		{
			//connectedpoints[endconnect.x][endconnect.y]++;
			//connectedpoints[rand2.x][rand2.y]++;
			finalpoints[rand2.x][rand2.y]=endconnect.x*a.cols+endconnect.y;
			//finalweight[rand2.x][rand2.y]=int(sqrtl(dist(endconnect,rand2),0.5);
			finaltotal[rand2.x][rand2.y]=finaltotal[endconnect.x][endconnect.y]+(sqrtl(dist(endconnect,rand2)));
			for(int i=0;i<end.size();i++)
			{
				if(dist(rand2,end[i])<500)
				{
					if(finaltotal[end[i].x][end[i].y]+(sqrtl(dist(rand2,end[i])))<finaltotal[rand2.x][rand2.y])
					{
						printf("yoooooooooooooooooooooooooooo\n");
						finalpoints[rand2.x][rand2.y]=end[i].x*a.cols+end[i].y;
						finaltotal[rand2.x][rand2.y]=finaltotal[end[i].x][end[i].y]+(sqrtl(dist(rand2,end[i])));
						//redraw(c,end[i],Point(finalpoints[end[i].x][end[i].y]/a.cols,finalpoints[end[i].x][end[i].y]%a.cols));
						endconnect=end[i];
						//draw(c,rand2,end[i]);
					}	
				}
			}
			end.push_back(rand2);
			draw(c,endconnect,rand2);
		}
		int break1=0;
		//printf("size of begin=%d\n",begin.size());
		for(int i=0;i<end.size();i++)
		//for(int j=0;j<end.size();j++)
		{
			//printf("%d %d\n",begin[i].x,end[j].x);

			printf("%Lf\n",(sqrtl(dist(begin[begin.size()-1],end[i]))));
		if((dist(begin[begin.size()-1],end[i]))<100)	
		{
			printf("doneeeeeeeeeeeeee\n");
			startpoints[end[i].x][end[i].y]=begin[begin.size()-1].x*a.cols+begin[begin.size()-1].y;
			commonpoint=end[i];
			break1=1;
			draw(c,begin[begin.size()-1],end[i]);
		}
	}
	for(int i=0;i<begin.size();i++)
		//for(int j=0;j<end.size();j++)
		{
			//printf("%d %d\n",begin[i].x,end[j].x);

			printf("%Lf\n",(sqrtl(dist(begin[begin.size()-1],end[i]))));
		if((dist(end[end.size()-1],begin[i]))<100)	
		{
			printf("doneeeeeeeeeeeeee\n");
			startpoints[end[end.size()-1].x][end[end.size()-1].y]=begin[i].x*a.cols+begin[i].y;
			commonpoint=end[end.size()-1];
			break1=1;
			draw(c,begin[i],end[end.size()-1]);
		}
	}
	if(break1==1)
		break;

	}
	//for(int i=0;i<begin.size();i++)
	//{
	//	printf("values%d %d %d\n",begin[i].x,begin[i].y,startpoints[begin[i].x][begin[i].y]);
	//}
	Point pt1,pt2;
	pt1=commonpoint;
	pt2=commonpoint;
	while(1)
	{
		if(startpoints[pt1.x][pt1.y]!=-1)
		{
			printf("%d %d %d\n",pt1.x,pt1.y,startpoints[pt1.x][pt1.y]);
			draw1(d,pt1,Point(startpoints[pt1.x][pt1.y]/a.rows,startpoints[pt1.x][pt1.y]%a.rows));
			pt1=Point(startpoints[pt1.x][pt1.y]/a.rows,startpoints[pt1.x][pt1.y]%a.rows);
			
		}
		if(finalpoints[pt2.x][pt2.y]!=-1)	
		{	printf("hi %d %d %d\n",pt2.x,pt2.y,finalpoints[pt2.x][pt2.y]);
			draw1(d,pt2,Point(finalpoints[pt2.x][pt2.y]/a.rows,finalpoints[pt2.x][pt2.y]%a.rows));
			pt2=Point(finalpoints[pt2.x][pt2.y]/a.rows,finalpoints[pt2.x][pt2.y]%a.rows);
			
		}
		if(startpoints[pt1.x][pt1.y]==-1 && finalpoints[pt2.x][pt2.y]==-1)
		{
			break;
		}
	//c.at<Vec3b>(finalpos.x,finalpos.y)=0;
	}
	//vector<Point>
	//system("quit");
	namedWindow("IMAGE2",WINDOW_NORMAL);
	imshow("IMAGE2",d);
	waitKey(0);
}