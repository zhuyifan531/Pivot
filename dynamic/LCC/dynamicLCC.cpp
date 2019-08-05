#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h> 
#define NUUM 2000000
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
int ppa[NUUM][2];
int MaxI[NUUM][2];
double loc[NUUM][30];
double MaxD[NUUM][3];
double contribution[NUUM];
int stack[NUUM],top=0,ptop=0;
int num,dim;
double mm;
int pnum=0;
double alpha;
double rat=0;
ifstream ain1;
void readm(){ //re-read the file
	srand((int)time(0)); 
	cout<<"Input pnum : ";
	cin>>pnum;
	cout<<"Input alpha: ";
	cin>>alpha;
	ain1.open("LA.txt", ifstream::in);	
	int q;
	ain1>>dim>>num>>q;
	for(int i=0;i<num;i++){
		for(int j=0;j<dim;j++)
			ain1>>loc[i][j];		
	}
	
	ain1.close();
	ptop=5000;
	if (num<ptop) ptop=num;
	mm=15000;
	for(int j=0;j<ptop;j++){
		MaxD[j][0]=-1;	
		MaxD[j][1]=-1;	
	}
	for(int i=0;i<ptop;i++){
		int p=rand()%num;
		ppa[i][0]=p;
		p=rand()%num;
		ppa[i][1]=p;
		if(ppa[i][0]==ppa[i][1]) i--;			
	} 
}
double dis(int i,int j){
	double sum=0;
	for(int k=0;k<dim;k++) sum+=pow(loc[i][k]-loc[j][k],2);
	return pow(sum,0.5);
}
double ddis(int i,int j){
	return abs(dis(ppa[i][0],j)-dis(ppa[i][1],j));
}
int check(int k){
	int i;
	for(i=0;i<top;i++){
		if(dis(k,stack[i])<mm*alpha) {	
			return 1;
		}	
	}	
	return 0;
}

void slim(){
	top=0;
	for(int i=0;i<num;i++)
	if(check(i)==0)
	{
		stack[top++]=i;
		cout<<top<<" "<<i<<endl; 
		contribution[top-1]=0;
		for(int j=0;j<ptop;j++){
			double tt=ddis(j,i);
			MaxD[j][2]=tt;
			if(tt>MaxD[j][0])
			contribution[top-1]+=tt-MaxD[j][0];
		}
		int flag=0;
		int temp=top-1;
		if(top>pnum){			
			for(int j=0;j<pnum;j++)if(contribution[j]<contribution[temp]) temp=j;
			if(temp==top-1) flag=1;
		}
		if(flag==0){
			stack[temp]=i;
			for(int j=0;j<ptop;j++){
				double tt=MaxD[j][2];
				if(tt>MaxD[j][0]){					
					MaxD[j][1]=MaxD[j][0];
					MaxD[j][0]=tt;
				}
				else if(tt>MaxD[j][1]){
					MaxD[j][1]=tt;					
				}				
			}
			cout<<"changing"<<endl;
		}
		if(top>pnum) top=pnum;
		for(int i=0;i<top;i++){
			cout<<stack[i]<<" ";	
		}
		cout<<endl;
	}
}

void op(){
	ofstream out1;
	out1.open("dynamicsss_lcc_ans.txt");
	out1<<top<<endl;
	for(int i=0;i<top;i++){
		out1<<stack[i]<<" ";	
	}
	out1<<endl;
	out1.close();		
}

int main(){
	readm();
	slim();
	op();
}

