#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
int main()
{
	map< vector<string>,vector<int> > clusters;

	vector< vector<string> > stuff;
	
	vector<string> tweets;

	ifstream entityFile("entitiesDeduplicated.txt");
	ifstream verbFile("verbsDeduplicated.txt");
	ifstream tweetFile("tweetsDeduplicated.txt");

	string line;
	
	while(getline(tweetFile,line))
	{
		tweets.push_back(line);
	}

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
		curr.push_back("dummy_garima");
		stuff.push_back(curr);
	}

	int i=0;
	while(getline(verbFile,line))
	{
		while(line.size()>0)
		{
			string temp=line.substr(0,line.find(","));
			if(find(stuff[i].begin(),stuff[i].end(),temp)==stuff[i].end())
			{
				stuff[i].push_back(temp);
			}
			line=line.substr(line.find(",")+1);
		}
		i++;
	}

	for(i=0;i<stuff.size();i++)
	{
		if(clusters.find(stuff[i])==clusters.end())
		{
			vector<int> curr;
			curr.push_back(i+1);
			clusters.insert(std::pair< vector<string>,vector <int> >(stuff[i],curr));
		}
		else
		{
			clusters[stuff[i]].push_back(i+1);
		}
	}

	int count=1;
	for(map<vector<string>,vector<int> >::iterator it=clusters.begin();it!=clusters.end();it++)
	{
		for(i=0;i<it->first.size();i++)
		{
			if(it->first[i].compare("dummy_garima")==0)
			{
				cout<<endl;
			}
			else
			{
				cout<<it->first[i]<<",";
			}
		}
		cout<<endl;
		//cout<<tweets[it->second[0]-1]<<endl;
		cout<<count<<","<<endl;
		count++;

	}



	return 0;
}
