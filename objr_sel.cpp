#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iostream>
#include <sys/time.h> 
#define NUUM 2000000
#define rand() ((rand()%10000)*10000+rand()%10000)
using namespace std;
struct timeval start, end1;
double loc[NUUM][30];
int pivot[NUUM],cnt[NUUM],fa[NUUM];
double rec[NUUM],dist[NUUM];
int stack[NUUM],top=0;
int best_p[300],s_p[300],stop;
int num,dim,eva;
double mm,mxd=100000000;
double best_min=10000000,s_min=10000000;
int pnum=0,ptype;
double beta=0.4;
ifstream ain1;
double alpha=3;
void readm(){ //re-read the file
	cout<< "input pnum : ";
	cin>>pnum;
	ain1.open("LA.txt", ifstream::in);	
	ain1>>dim>>num>>ptype;
	for(int i=0;i<num;i++){
		for(int j=0;j<dim;j++)
			ain1>>loc[i][j];
		cnt[i]=0;
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
	cout<<"mindis "<<mxd<<" "<<mm<<endl;
}
double objr(double alpha){
	double sum=0;
	double dd=num*1.0/top;
	for(int i=0;i<top;i++)
		for(int j=i+1;j<top;j++){
			double max=0,q,p;
			p=dis(stack[i],stack[j]); 
			for(int k=0;k<stop;k++){
				q=abs(dis(s_p[k],stack[i])-dis(s_p[k],stack[j]));
				if(q>max) max=q;				
			} 	
		 	sum+=cnt[i]/dd*cnt[j]/dd*pow(1-max/p,alpha);
		}
	return sum;
}
void op(int i){
	ofstream out1;

	char tmpf1[20];
	if(i>=0)sprintf(tmpf1, "pivotobj%d.txt", i);
	else sprintf(tmpf1, "pivotobj.txt");
	string tmpf(tmpf1);
	cout<<tmpf<<endl;
	out1.open(tmpf);
	out1<<pnum<<endl;
	for(int i=0;i<pnum;i++)out1<<s_p[i]<<" ";	
	out1<<endl;	
	gettimeofday(&end1, NULL);//记录下系统当前时间给end，此时程序结束。
	out1<<"time "<<(end1.tv_sec - start.tv_sec)+ (end1.tv_usec - start.tv_usec)*0.000001 <<" s"<<endl;
	out1.close();		
}
void exp(){
	stop=1;
	double min=1000000;
	int pos=-1;
	s_p[0]=stack[rand()%top];
	for(int j=0;j<top;j++){
			s_p[stop-1]=stack[j];
			double tt=objr(alpha);
			if(tt<min-0.00000001){
				pos=j;
				min=tt;
			}
		}
	s_p[0]=stack[pos];
	stop=1;
	int i=50,fgg;
	while(i--){
		cout<<"doing : "<<50-i<<endl;
		for(int j=0;j<stop;j++){
			cout<<s_p[j]<<" ";
		}
		cout<<" ans= "<<objr(alpha)<<endl;
		stop++;
		min=1000000;
		pos=-1;
		for(int j=0;j<top;j++){
			s_p[stop-1]=stack[j];
			double tt=objr(alpha);
			if(tt<min-0.00000001){
				pos=j;
				min=tt;
			}
		}
		
		cout<<" pos "<<pos<<" top "<<top<<endl;
		cout<<" min "<<min<<endl;
		
		if(pos==-1) break;
		if(stop<=pnum) continue;
		stop--;
		s_p[stop]=stack[pos];
		min=objr(alpha);
		cout<<"value : "<<min<<endl;
		pos=stop;
		for(int j=0;j<stop;j++){
			int q=s_p[j];
			s_p[j]=s_p[stop];
			double tt=objr(alpha);
			if(tt<min-0.00000001){
				min=tt;
				pos=j;
			}
			s_p[j]=q;
		} 
		if(pos==stop) break;
		s_p[pos]=s_p[stop];
		cout<<"finish : "<<50-i<<" value : "<<min<<endl;
	}
	stop=pnum;
	s_min=objr(alpha);
		
}

int main(){
	srand(time(0));
	readm();
	
	for(int k=0;k<5;k++){
		gettimeofday(&start, NULL);
		gen();		
		cout<<endl<<"======ittr "<<k<<"====="<<endl;
		exp();
		op(k);
		cout<<"tmp _ ans "<<s_min<<endl;
		stop=pnum;

		if(s_min<best_min-0.00000001){
			for(int j=0;j<pnum;j++){
				best_p[j]=s_p[j];
			}
			best_min=s_min;
		}
	}
	for(int j=0;j<pnum;j++){
		s_p[j]=best_p[j];
	}
	op(-1);

	
}
