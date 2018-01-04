#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream ifile;
	int ig,net,module,padoff,g;
	ifile.open("ibm01.net");
	if(ifile.fail())
	{
		cout<<"\n No file";
	}
	else
	{
		ifile>>ig>>net>>module>>padoff>>g;
	}
	cout<<ig<<net<<module<<padoff<<g;
return 0;
}
	
