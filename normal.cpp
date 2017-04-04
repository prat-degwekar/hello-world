#include <iostream>

using namespace std;

bool fdl[100][100];					//fdl[i][j] represents attribute j+1 is on LHS of fd no. i
bool fdr[100][100];

int checkvis(bool *vis , int s)						//gets if all reachable					#works
{
	for(int i=0 ; i<s ; i++)
	{
		if(vis[i] == 0)
			return 0;
	}
	return 1;
}

int reach(int *list , int s , int n , int m)		//s is size of list of attributes , n is no. of attr. , m is no. of fds			returns 1 if all reachable from <list>
{													//gives reachability of all attrs. in <list> together			#works
	bool *vis = new bool[n];
	for(int i=0 ; i<n ; i++)
		vis[i] = 0;
	for(int i=0 ; i<s ; i++)
		vis[list[i]] = 1;

	//check
	int fl=0;
	/*for(int i=0 ; i<n ; i++)
	{
		if(vis[i] == 0)
		{
			fl = 1;
			break;
		}
	}
	if(fl == 0)
		return 1;*/

	int k = checkvis(vis , n);
	if(k == 1)
		return 1;

	//main algo

	for(int i=0 ; i<m ; i++)
	{
		int flf = 0;
		for(int j=0 ; j<n ; j++)
		{
			if(fdl[i][j] == 1)
			{
				if(vis[j] == 1)
					continue;
				else
				{
					flf = 1;
					break;
				}
			}
		}
		if(flf == 1)
		{
			flf = 0;
			continue;
		}

		for(int j=0 ; j<n ; j++)
		{
			if(fdr[i][j] == 1)
				vis[j] = 1;
		}

		int kk = checkvis(vis , n);
		if(kk == 1)
			return 1;

	}

	//main algo

	for(int i=0 ; i<n ; i++)
		cout<<vis[i]<<" ";

	int kk = checkvis(vis , n);
	if(kk == 1)
		return 1;

	return 0;
}

bool exist(int *list , int s , int e)				//1 if e exists in <list> of length s
{
	for(int i=0 ; i<s ; i++)
	{
		if(list[i] == e)
			return 1;
	}
	return 0;
}

void gensubs(int *list , int s , int n)
{
	for(int i=0 ; i<n ; i++)
	{
		if(!exist(list , s , i))
		{
			//add i and check
			list[s] = i;
			int r = reach(list , s+1 , n , m);
			if(r == 1)
			{
				//set this as candidate key and print , return , whatever...
				//return
			}
		}
	}
}

void ckeycheck(int n , int m)					//what all min need to be there				#works
{
	int fl=0;

	int *list = new int[n];

	for(int i=0 ; i<n ; i++)
		list[i] = 0;

	int ind = 0;

	for(int i=0 ; i<n ; i++)
	{
		for(int j=0 ; j<m ; j++)
		{
			if(fdr[j][i] == 1)
			{
				fl=1;
				break;
			}
		}
		if(fl==0)
		{
			list[ind++] = i;
			//cout<<(i+1)<<endl;
		}
		fl=0;
	}
	
	//print current list here
	//end brack

	if(reach(list , ind , n , m) == 1)
	{
		cout<<"candidate key found!!\n\n";
		return;
	}

	//length = ind ++

	//generate l+1 subs

}

int main()
{
	int n=0;
	cout<<"enter number of attributes : ";
	cin>>n;
	for(int i=0 ; i<100 ; i++)
		for(int j=0 ; j<100 ; j++)
			fdl[i][j] = fdr[i][j] = 0;


	int m=0;
	cout<<"enter number of fds : ";
	cin>>m;
	for(int i=0 ; i<m ; i++)
	{
		cout<<"enter fd numbers on lhs separated by space, end with -1 : ";
		int k=0;
		cin>>k;
		while(k!=-1)
		{
			fdl[i][k-1] = 1;
			cin>>k;
		}

		cout<<"enter fd numbers on rhs separated by space, end with -1 : ";
		k=0;
		cin>>k;
		while(k!=-1)
		{
			fdr[i][k-1] = 1;
			cin>>k;
		}

	}

	//print fd
	for(int i=0 ; i<m ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			if(fdl[i][j] == 1)
				cout<<(j+1)<<".";
		}
		cout<<"  -->  ";
		for(int j=0 ; j<n ; j++)
		{
			if(fdr[i][j] == 1)
				cout<<(j+1)<<".";
		}
		cout<<endl;
	}

	//finish print fd

	cout<<"candidate key attributes are : ";
	ckeycheck(n,m);

	int list[3] = {0,2,2};
	cout<<"\n"<<reach(list , 2 , n , m)<<endl;
	
	return 0;
}