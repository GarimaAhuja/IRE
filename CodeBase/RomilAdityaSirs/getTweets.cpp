#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	ifstream tweetFile("tweets.tsv");

	string line;

	while(getline(tweetFile,line))
	{
		for(int i=0;i<8;i++)
		{
			line=line.substr(line.find('\t')+1);
		}
		cout<<line.substr(0,line.find('\t'))<<endl;
	}

	return 0;
}
