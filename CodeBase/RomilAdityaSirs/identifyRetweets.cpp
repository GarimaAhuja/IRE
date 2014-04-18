#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;
int main()
{
	map<string, vector<int> > tweets;

	int i=1;
	ifstream tweetFile("tweets.txt");

	string line;

	while(getline(tweetFile,line))
	{
		if(tweets.find(line)==tweets.end())
		{
			vector<int> curr;
			curr.push_back(i);
			tweets.insert(std::pair<string, vector<int> >(line,curr));
		}
		else
		{
			tweets[line].push_back(i);
		}
		i++;
	}

	for(map<string,vector<int> >::iterator it=tweets.begin();it!=tweets.end();it++)
	{
		cout<<it->first<<endl;
	}


	return 0;	
}
