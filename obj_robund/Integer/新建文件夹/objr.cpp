#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iostream>
#define NUUM 2000000
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
double loc[NUUM][30];
int pivot[NUUM],cnt[NUUM],fa[NUUM];
double rec[NUUM],dist[NUUM];
int stack[NUUM],top=0;
int num,dim,eva;
double mm,mxd=100000000;
int pnum=0;
int ptype;
double beta=0.4;
ifstream ain1;
string fils;
string tmpf;
void readm(){ //re-read the file
cout<<"input algo: ";


	cin>>fils;
	ain1.open("../integer.txt", ifstream::in);	
	
	ain1>>dim>>num>>ptype;
	for(int i=0;i<num;i++){
		for(int j=0;j<dim;j++)
			ain1>>loc[i][j];
		cnt[i]=0;
	}
	ain1.close();
	mm=15000;
}

void readn(){ //re-read the file
	tmpf="../pivot"+fils+".txt";
	ain1.open(tmpf, ifstream::in);	
	ain1>>pnum;
	for(int i=0;i<pnum;i++){
		ain1>>pivot[i];			
	}
	ain1.close();
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


void gen(){
	int tpn=(int)pow(num,beta);
	double bou;
	stack[0]=rand()%num;
	top=1;
	double tmp=0;
	for(int i=0;i<num;i++){
		dist[i]=dis(stack[0],i);		
		fa[i]=0;
		cnt[i]=0; 
	}
	for(int i=0;i<num;i++)if(dist[i]>tmp) tmp=dist[i];
	bou=pow(tmp,beta);
	
	while (tmp>2*bou&&tpn>top){		
		int maxi=0;
		double max=0,q;
		for(int i=0;i<num;i++)
			if(dist[i]>max){
				maxi=i;
				max=dist[i];
			}
		stack[top++]=maxi;
		for(int i=0;i<num;i++){
			q=dis(maxi,i);
			if(q<dist[i]){
				dist[i]=q;
				fa[i]=top-1;
			}			
		}		
		tmp=max;	
	}
	for(int i=0;i<num;i++) cnt[fa[i]]++;		
	mxd=tmp;
	cout<<"mindis "<<bou<<"tmp "<<tmp<<endl<<"maxnum "<<tpn<<" top "<<top<<endl;
//	cout<<"mindis "<<mxd<<" "<<mm<<endl;
}
double objr(){
	double sum=0;
	double dd=num*1.0/top;
	for(int i=0;i<top;i++)
		for(int j=i+1;j<top;j++)
		if (dis(stack[i],stack[j])>=1.2*mxd){
			double max=0,q; 
			for(int k=0;k<pnum;k++){
				q=abs(dis(pivot[k],stack[i])-dis(pivot[k],stack[j]));
				if(q>max) max=q;				
			} 
			if(max>mxd) continue;
		 	sum+=cnt[i]/dd*cnt[j]/dd;
		}		
	return sum;
}
double objr1(double qq){
	double sum=0;
	double dd=num*1.0/top;
	for(int i=0;i<top;i++)
		for(int j=i+1;j<top;j++)
		{
			double max=0,q,p; 
			p=dis(stack[i],stack[j]);
			for(int k=0;k<pnum;k++){
				q=abs(dis(pivot[k],stack[i])-dis(pivot[k],stack[j]));
				if(q>max) max=q;				
			} 		
		 	sum+=cnt[i]/dd*cnt[j]/dd*pow(1-max/p,qq);
		}		
	return sum;
}
void op(){
	ofstream out1;
	tmpf="../objr_"+fils+".txt";
	out1.open(tmpf);
	double sum=0;
	for(int i=0;i<5;i++){
		gen();
		double q=objr();
		sum+=q;
		out1<<"obj "<<i<<" = "<<q<<endl;		
	}	
	
	out1<<sum/5<<endl;	
	out1<<"======"<<endl;
	sum=0;
	for(int i=0;i<5;i++){
		gen();
		double q=objr1(2);
		sum+=q;
		out1<<"obj "<<i<<" = "<<q<<endl;		
	}		
	out1<<sum/5<<endl;	
	out1<<"======"<<endl;
	sum=0;
	for(int i=0;i<5;i++){
		gen();
		double q=objr1(3);
		sum+=q;
		out1<<"obj "<<i<<" = "<<q<<endl;		
	}		
	out1<<sum/5<<endl;	
	out1<<"======"<<endl;
	sum=0;
	for(int i=0;i<5;i++){
		gen();
		double q=objr1(4);
		sum+=q;
		out1<<"obj "<<i<<" = "<<q<<endl;		
	}		
	out1<<sum/5<<endl;	
	out1<<"======"<<endl;
	out1.close();	
	
}
int main(){
	
	readm();
	readn(); 	
	op();
	char ch;
	cin>>ch;
}
