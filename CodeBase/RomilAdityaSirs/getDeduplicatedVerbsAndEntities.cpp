#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

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

	ifstream tweetFile("tweetsDeduplicatedWithNumbers.txt");

	while(getline(tweetFile,line))
	{
		getline(tweetFile,line);

		int lineNum = atoi(line.substr(0,line.find(',')).c_str());
		
		for(int i=0;i<entities[lineNum-1].size();i++)
		{
			cout<<entities[lineNum-1][i]<<",";
		}
		cout<<endl;
		
	}

	return 0;
}
