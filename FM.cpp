/* Program to implemenet the Fiduccia-Mattheyeses Algorithm */


//The Header File section//
#include<iostream>
#include<vector>
#include<list>
#include<cstring>
#include<fstream>
using namespace std;
ifstream ifile; //File Pointer to read the input
int bucket1[100],bucket2[100];

//The Class to represent the vertex structure 
class node{
	public:	
		int no;		
		string name;
		int part;
		bool lock;
		int tgain;
		int fgain;
		int gp;
		node() //Constructor to initialize the code
		{
			no=0;
			name='\0';
			part=1;
			lock=false; //All nodes are unlocked in the beginning
		}
};


int main()
{
	
	int n,ig,pin,nets,modules,pado;
	string nname,lname;
	int temp1,temp2,maxgain1=0,maxgain2=0;
	int p1=0,p2=0;
	float ratio,ratio1;
	int ics=0;
	ifile.open("ibm01.net"); //Reading of the input ibm benchmarks//
	if(ifile.fail())
	{
		cout<<"\n No file";
	}
	else
	{
		ifile>>ig>>pin>>nets>>modules>>pado;
	}
	n=modules;
	cout<<pin<<"\n"<<n;
	node n1[n];
	
	/* The function for initail partitioning */
	for(int i=0;i<n;i++)
	{
		n1[i].no=i;	
		ifile>>nname;
		if(nname=="s"||nname=="1"||nname=="l")
		{
			n1[i].name=" ";			
			continue;
		}
		else
			n1[i].name=nname;
	if(n1[i].no==0)
	{
		n1[i].part=1;
		p1++;
	}
	else if(n1[i].no==1)
	{
		n1[i].part=2;
		p2++;
	}
	else
	{
		if(p1>=p2)
		{
			n1[i].part=2;
			p2++;
		}	
		else
		{
			n1[i].part=1;
			p1++;
		}
	}
}
	ratio= (float)p1/(p1+p2);
	//ifile.open("ibm01.net");
	//ifile>>ig>>pin>>nets>>modules>>pado;
	std::vector <std::list<string> > node_list(n);
	for(int i=0;i<n;i++)
	{
		do{			
			ifile>>lname;
			if(lname=="s"||lname=="1"||lname=="l")			
				continue;
			else
				node_list[i].push_back(lname);
		}while(lname=="l");
	}

	/*
	node_list[0].push_back(n1[1].no);
	node_list[0].push_back(n1[2].no);
	
	node_list[1].push_back(n1[0].no);
	node_list[1].push_back(n1[3].no);
	
	node_list[2].push_back(n1[0].no);
	node_list[3].push_back(n1[1].no);
	
	node_list[4].push_back(n1[3].no);
*/	
	// Displaying the Graph connections//
	cout<<"\n GRAPH INFORMATION";
	std::vector<std::list<int> >::iterator i;
	int c=0;

	for (std::vector<std::list<string> >::iterator i=node_list.begin(); i !=node_list.end(); ++i)
	{
		cout<<"\n The vertices connected to"<<c<<"are";
		std::list<string> li=*i;
		 for(std::list<string>::iterator it = li.begin(); it!= li.end(); ++it)
		 {
			if(*it=="\0")				
				continue;
			else		 	
				cout<<*it<<" ";
		}
		cout<<endl;
		c++;
	}

/* Displays the node inforamtion*/
	
	cout<<"\n NODE INFORMATION";	
	for(int i=0;i<n;i++)
	{
		
		if(!n1[i].name.compare(" "))
			continue;
		else
			{
				cout<<"\n Node Number"<<n1[i].no;
				cout<<"\n Node Name"<<n1[i].name;
				cout<<"\n Node Partition"<<n1[i].part;
			}
	
	}
/* Function to calculate the initial cutsize*/

	for(int i=0;i<n;i++)
	{
		if(n1[i].part==2&&n1[i+1].part==1)
		{			
			ics++;
			n1[i].fgain=1;
			n1[i].tgain=0;
			n1[i+1].fgain=0;
			n1[i+1].tgain=1;
		}
	}
	for(int i=0;i<p1;i++)
	{		
		temp1=maxgain1;
		temp2=maxgain2;		
		if(n1[i].part==1)
		{
			maxgain1=n1[i].fgain-n1[i].tgain;
			if(maxgain1<=temp1)
				continue;
			else
			{
				temp1=0;
				n1[i].gp=temp1;
			}
		}
			
		else
		{
			maxgain2=n1[i].fgain-n1[i].tgain;
			if(maxgain2>=temp2)
			
				continue;
			else
			{
				n1[i].gp=maxgain2;	
				temp2=maxgain2;
			}
		}
	}
	cout<<"\n Maximum gain of partition1 is: "<<maxgain1<<" "<<"Maximum gain of partition 2 is: "<<maxgain2<<endl;
	cout<<"\n The initial cutsize is"<<ics<<endl;
	
	
	 /* FM algorithm */ 
	for(int i=0;i<n;i++)
	{
		while(n1[i].lock=false)
		{
			if((n1[i].gp==temp2)&&(n1[i].part==2))
			{
				n1[i].part=1;
				n1[i].gp=0;
				p2--;
				n1[i].lock=true;
			}
			else
				n1[i].lock=true;
		}
		
	}
	ratio1= (float)p1/(p1+p2);
	cout<<"\n The ratio is"<<ratio1;
	ifile.close();
	return 0;
}

		
