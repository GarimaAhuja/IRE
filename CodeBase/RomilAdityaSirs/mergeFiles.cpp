#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>

using namespace std;
int main()
{
	string line;
	int i=0;

	while(i<10)
	{
		char filename[10];

		sprintf(filename,"%d.txt",i);
		ifstream file(filename);

		while(getline(file,line))
		{
			cout<<line<<endl;
		}
		i++;
	}
	return 0;
}
