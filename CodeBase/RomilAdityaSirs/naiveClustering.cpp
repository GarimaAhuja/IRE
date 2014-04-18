#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
int main()
{
	ifstream entityFile("entities.txt");

	string line;

	vector<vector<string> > entities;
	map< string,vector<int> > clusters;

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

	for(int i=0;i<100000;i++)
	{
		for(int j=0;j<entities[i].size();j++)
		{
			if(clusters.find(entities[i][j])==clusters.end())
			{
				vector<int> curr;
				curr.push_back(i+1);

				clusters.insert(std::pair<string, vector<int> >(entities[i][j],curr));
			}
			else
			{
				clusters[entities[i][j]].push_back(i+1);
			}
		}
	}

	for(map<string,vector<int> >::iterator it=clusters.begin();it!=clusters.end();it++)
	{
		cout<<it->first<<":";
		for(int i=0;i<it->second.size();i++)
			cout<<it->second[i]<<",";
		cout<<endl;
	}


	return 0;
}
