#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sys/time.h> 
#include <iostream>
#include "../dis.h"
#define NUUM 2000000
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
double vec[1000][1000] ;
bool flag[NUUM];
int stack[NUUM],top=0;
int cand[NUUM];
int ppnum;
double alpha;
ofstream out1;
double time1,ddt;
void readq(){ //re-read the file
	readm();
	for(int i=0;i<num;i++)flag[i]=0;	
	ifstream ain1;
	ain1.open("cand.txt", ifstream::in);	
	ain1>>ddt;
	ain1>>pnum;
	ppnum=pnum;
	for(int i=0;i<pnum;i++)
		ain1>>cand[i];
	ain1.close();
	ain1.open("dim.txt", ifstream::in);	
	double q;
	ain1>>q>>time1;
	pnum=(int)q;
//	out1<<"dis "<<ddt<<" build_Time "<<time1<<endl;
	ain1.close();
	ain1.open("vec.txt", ifstream::in);	
	for(int i=0;i<pnum;i++){
		ain1>>vec[i][0];
		for(int j=0;j<pnum;j++)	ain1>>vec[i][j+1];
	}	
	ain1.close();
}

double dis1(int i,int j){
	double sum=0;
	for(int k=0;k<ppnum;k++)
		sum+=pow(dis(cand[k],j)*vec[i][k+1],2)*0.01;
	return pow(sum,0.5);
}

void swap(int k,int j){
	double p;
	for(int i=0;i<=pnum;i++){
		p=vec[k][i];
		vec[k][i]=vec[j][i];
		vec[j][i]=p;
	}
}
void work(){
	int app[10];
	for(int i=0;i<pnum/15;i++){
		for(int j=0;j<pnum;j++)
			if(vec[i][0]<vec[j][0]) swap(i,j);
	}	
	pnum/=30;
	int ttt=pnum;
	top=0;
	for(int i=0;i<pnum;i++){
		
		double tmp=0;
		int k=0;
		for(int j=0;j<num;j++)
		if(flag[j]==0||i<ttt*1.5) 
		{
			double tt=dis1(i,j);
			if(tt>tmp){
				tmp=tt;
				k=j;
			}
		}
		if(flag[k]==0){
			stack[top++]=k;
			flag[k]=1;
		}
		else pnum++;
		cout<<i<<" "<<k<<" temp: "<<tmp<<endl;
		if(i>=ttt*3) break;
	}
	cout<<pnum<<" "<<top<<endl;
}

void opo(){	
	out1<<top<<endl;
	for(int i=0;i<top;i++){
		out1<<stack[i]<<" ";		
	}	
	out1<<endl;	
	
}
int main(){
	struct timeval start, end1;
	out1.open("../pivotpca.txt");
	readq();
	gettimeofday(&start, NULL);
	work();				
	opo();
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time: "<<time1+ddt+(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001<<" s"<<endl;
	out1.close();
}

