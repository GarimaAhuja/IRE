//numEntities representing a cluster = 4
//numVerbs = 2
//at max

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<vector>
#include<map>
#include<iterator>
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

vector<string> getIntersection(vector<string> v1, vector<string> v2, int maxSize)
{
	vector<string> answer;
	map<string,int> entityFreq;
	map<int,vector<string> > inverse;

	for(int i=0;i<v1.size();i++)
	{
		if(entityFreq.find(v1[i])==entityFreq.end())
			entityFreq.insert(std::pair<string,int>(v1[i],1));
		else
			entityFreq[v1[i]]++;
	}
	for(int i=0;i<v2.size();i++)
	{
		if(entityFreq.find(v2[i])==entityFreq.end())
			entityFreq.insert(std::pair<string,int>(v2[i],1));
		else
			entityFreq[v2[i]]++;
	}

	for(map<string,int>::iterator it=entityFreq.begin();it!=entityFreq.end();it++)
	{
		if(inverse.find(it->second)==inverse.end())
		{
			vector<string> curr;
			curr.push_back(it->first);
			inverse.insert(std::pair<int,vector<string> >(it->second,curr));
		}
		else
		{
			inverse[it->second].push_back(it->first);
		}
	}
	int count=0;
	for(map<int, vector<string> >::reverse_iterator itm=inverse.rbegin();itm!=inverse.rend();itm++)
	{
		for(int i=0;i<itm->second.size();i++)
		{
			answer.push_back(itm->second[i]);
			count++;
			if(count>=maxSize)
				break;
		}
		if(count>=maxSize)
			break;
	}

	return answer;
}

int main()
{
	int maxE=4;
	int maxV=2;
	int currLevel=9;
	int nextLevel=10;
	int targetClusters=156;

	while(currLevel<=11)
	{
		//cluster attributes
		vector<vector<string> > clusterE;
		vector<vector<string> > clusterV;
		vector<vector<string> > newE;
		vector<vector<string> > newV;
		vector<string> finalTweets;

		map<string, vector<int> > entityToClusters;
		
		//point attributes
		vector<string> tweets;
		vector<vector<string> > entities;
		vector<vector<string> > verbs;
			
		char inputfilename[50];
		sprintf(inputfilename,"level%d.txt",currLevel);
		ifstream inputFile(inputfilename);

		string line,curr;
		for(int i=0;i<targetClusters;i++)
		{
			getline(inputFile,line);
			vector<string> currE;
			while(line.find(",")!=-1)
			{
				curr=line.substr(0,line.find(","));
				currE.push_back(curr);
				line=line.substr(line.find(",")+1);
			}
			clusterE.push_back(currE);
			entities.push_back(currE);
			
			getline(inputFile,line);
			vector<string> currV;
			while(line.find(",")!=-1)
			{
				curr=line.substr(0,line.find(","));
				currV.push_back(curr);
				line=line.substr(line.find(",")+1);
			}
			clusterV.push_back(currV);
			verbs.push_back(currV);

			getline(inputFile,line);
			finalTweets.push_back("");
			tweets.push_back(line);
			
			vector<string> e;
			vector<string> v; 

			newE.push_back(e);
			newV.push_back(v);
		}
		while(getline(inputFile,line))
		{
			vector<string> currE;
			while(line.find(",")!=-1)
			{
				curr=line.substr(0,line.find(","));
				currE.push_back(curr);
				line=line.substr(line.find(",")+1);
			}
			entities.push_back(currE);
			
			getline(inputFile,line);
			vector<string> currV;
			while(line.find(",")!=-1)
			{
				curr=line.substr(0,line.find(","));
				currV.push_back(curr);
				line=line.substr(line.find(",")+1);
			}
			verbs.push_back(currV);

			getline(inputFile,line);
			tweets.push_back(line);

		}

		for(int i=0;i<clusterE.size();i++)
		{
			for(int j=0;j<clusterE[i].size();j++)
			{
				if(entityToClusters.find(clusterE[i][j])==entityToClusters.end())
				{
					vector<int> curr;
					curr.push_back(i);
					entityToClusters.insert(std::pair<string,vector<int> >(clusterE[i][j],curr));
				}
				else
				{
					entityToClusters[clusterE[i][j]].push_back(i);
				}
			}
		}

		cout<<"Level: "<<currLevel<<endl;

		for(int i=0;i<5;i++)
		{
			//assign to clusters
			for(int j=0;j<tweets.size();j++)
			{
				float sim=0;
				float maxSim=0;
				int maxSimK=-1;


				for(int k=0;k<entities[j].size();k++)
				{
					for(int l=0;l<entityToClusters[entities[j][k]].size();l++)
					{
						sim=0.7*getJacardSim(clusterE[entityToClusters[entities[j][k]][l]],entities[j])+0.3*getJacardSim(clusterV[entityToClusters[entities[j][k]][l]],verbs[j]);
						if(maxSim<sim)
						{
							maxSim=sim;
							maxSimK=entityToClusters[entities[j][k]][l];
						}
					}
				}
				if(maxSimK==-1)
					continue;
				for(int l=0;l<entities[j].size();l++)
				{
					newE[maxSimK].push_back(entities[j][l]);
				}
				for(int l=0;l<verbs[j].size();l++)
				{
					newV[maxSimK].push_back(verbs[j][l]);
				}
				if(j%1000==0)
					cout<<"j: "<<j<<endl;
			}

			//recalculate centroids
			for(int k=0;k<clusterE.size();k++)
			{
				if(newE[k].size()==0&&newV[k].size()==0)
					continue;

				vector<string> finalE= getIntersection(clusterE[k],newE[k],4);
				vector<string> finalV= getIntersection(clusterV[k],newV[k],2);

				vector<string> e;
				vector<string> v; 

				clusterE[k]=finalE;
				clusterV[k]=finalV;

				newE[k]=e;
				newV[k]=v;

			}

			//LSH again
			for(int j=0;j<clusterE.size();j++)
			{
				for(int k=0;k<clusterE[j].size();k++)
				{
					if(entityToClusters.find(clusterE[j][k])==entityToClusters.end())
					{
						vector<int> curr;
						curr.push_back(j);
						entityToClusters.insert(std::pair<string,vector<int> >(clusterE[j][k],curr));
					}
					else
					{
						entityToClusters[clusterE[j][k]].push_back(j);
					}
				}
			}
			cout<<"i: "<<i<<endl;
		}

		//assign to clusters
		for(int j=0;j<tweets.size();j++)
		{
			float sim=0;
			float maxSim=0;
			int maxSimK=-1;

			for(int k=0;k<entities[j].size();k++)
			{
				for(int l=0;l<entityToClusters[entities[j][k]].size();l++)
				{
					sim=0.7*getJacardSim(clusterE[entityToClusters[entities[j][k]][l]],entities[j])+0.3*getJacardSim(clusterV[entityToClusters[entities[j][k]][l]],verbs[j]);
					if(maxSim<sim)
					{
						maxSim=sim;
						maxSimK=entityToClusters[entities[j][k]][l];
					}
				}
			}

			if(maxSimK==-1)
				continue;
			
			finalTweets[maxSimK]+=tweets[j];
		}

		//write output to file
		char outputfilename[50];
		sprintf(outputfilename,"level%d.txt",nextLevel);
		ofstream outputFile(outputfilename);

		for(int k=0;k<clusterE.size();k++)
		{
			for(int l=0;l<clusterE[k].size();l++)
			{
				outputFile<<clusterE[k][l]<<",";
			}
			outputFile<<endl;
			
			for(int l=0;l<clusterV[k].size();l++)
			{
				outputFile<<clusterV[k][l]<<",";
			}
			outputFile<<endl;

			outputFile<<finalTweets[k]<<endl;
		}

		currLevel++;
		nextLevel++;
		targetClusters/=2;
	}
	

	return 0;
}
