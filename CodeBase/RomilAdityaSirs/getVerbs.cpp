#include<vector>
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream tweetFile("taggedTweets.txt");
	string line;

	while(getline(tweetFile,line))
	{
		string currEntity;
		line+=" ";

		//detect entity
		while(line.find(' ')!=-1)
		{
			string tweetWord=line.substr(0,line.find(' '));

			//processing here
			if(tweetWord.find("VB")!=-1)
			{
				currEntity=tweetWord.substr(0,tweetWord.find('/'));
				
				for(int i=0;i<currEntity.size();i++)
				{
					if(currEntity[i]>='A'&&currEntity[i]<='Z')
					{
						currEntity[i]-='A';
						currEntity[i]+='a';
					}
				}
				
				cout<<currEntity<<",";
			}

			line=line.substr(line.find(' ')+1);
		}
		cout<<endl;

	}

	return 0;
}
