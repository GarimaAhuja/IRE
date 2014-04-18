#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
float getJacardSim(vector<string> v1,vector<string> v2)
{
	int intersect=0;
	for(int i=0;i<v1.size();i++)
	{
		for(int j=0;j<v2.size();j++)
		{
			if(v1[i].compare(v2[j])==0)
			{
				intersect++;
			}
		}
	}
	float sim=0;
	if((v1.size()+v2.size()-intersect)>0)
		sim = (1.0*intersect)/(v1.size()+v2.size()-intersect);

	return sim;
}
int main()
{
	vector< vector<string> > entities;
	vector< vector<string> > verbs;

	ifstream entityFile("entities.txt");
	ifstream verbFile("verbs.txt");

	string line;

	while(getline(entityFile,line))
	{
		vector<string> curr;
		while(line.size()>0)
		{
			string temp=line.substr(0,line.find(","));
			if(find(curr.begin(),curr.end(),temp)==curr.end())
			{
				curr.push_back(temp);
			}
			line=line.substr(line.find(",")+1);
		}
		entities.push_back(curr);
	}
	
	while(getline(verbFile,line))
	{
		vector<string> curr;
		while(line.size()>0)
		{
			string temp=line.substr(0,line.find(","));
			if(find(curr.begin(),curr.end(),temp)==curr.end())
			{
				curr.push_back(temp);
			}
			line=line.substr(line.find(",")+1);
		}
		verbs.push_back(curr);
	}

	for(int i=0;i<100000;i++)
	{
		for(int j=i+1;j<100000;j++)
		{
			float vSim=getJacardSim(verbs[i],verbs[j]);
			float eSim=getJacardSim(entities[i],entities[j]);

			float lambda=.7;

			float sim=lambda*eSim + (1-lambda)*vSim;

			if(sim>=.8)
				cout<<i+1<<","<<j+1<<":"<<sim<<endl; 
		}
	}

	return 0;
}
