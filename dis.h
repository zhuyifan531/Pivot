#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sys/time.h> 
#define NUUM 2000000
#define PairA 2000
#define CandA 300
#define FILENAME "../LA.txt" 
using namespace std;

double loc[NUUM][30];
int dim;
int pnum=0,num;
int ptype=0;
double mm;
void readm(){ //re-read the file
	srand((int)time(0)); 
	ifstream ain1;
	cout<<"Input pnum : ";
	cin>>pnum;
	ain1.open(FILENAME, ifstream::in);	
	ain1>>dim>>num>>ptype;
	for(int i=0;i<num;i++){
		for(int j=0;j<dim;j++)
			ain1>>loc[i][j];		
	}
	ain1.close();
	mm=15000;
}

double dis(int i,int j){
	if(ptype==2){
		double sum=0;
		for(int k=0;k<dim;k++) sum+=pow(loc[i][k]-loc[j][k],2);
		return pow(sum,0.5);	
	}
	if(ptype==0){
		double max=0,p;
		for(int k=0;k<dim;k++) 
		{
			p=abs(loc[i][k]-loc[j][k]);
			if(p>max) max=p;
		}
		return max;	
	}	
}
