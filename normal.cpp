#include <iostream>

using namespace std;

bool fdl[100][100];					//fdl[i][j] represents attribute j+1 is on LHS of fd no. i
bool fdr[100][100];

bool fdlt[100][100];				//temporary sets
bool fdrt[100][100];

int checkvis(bool *vis , int s)						//gets if all reachable					#works
{
	for(int i=0 ; i<s ; i++)
	{
		if(vis[i] == 0)
			return 0;
	}
	return 1;
}

bool equl(bool *b1 , bool *b2 , int n)				//true if b1 = b2
{
	for(int i=0 ; i<n ; i++)
	{
		if(b1[i]!=b2[i])
			return false;
	}
	
	return true;
}

void cop(bool *src , bool *dest , int n)							//copies source visibility matrix into dest. one...
{
	for(int i=0 ; i<n ; i++)
		dest[i] = src[i];
	
}

void cop_d(bool **fdl , bool **fdr , bool **fdlt , bool **fdrt , int n , int m)								//copies fdl into fdlt and fdr into fdrt
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			fdlt[i][j] = fdl[i][j];
			fdrt[i][j] = fdr[i][j];
		}
	}
}

bool* closure(bool **fdl , bool **fdr , int *list , int s , int n , int m)						//gets closure of fd set and returns vis
{
	bool *vis = new bool[n];
	bool *temp = new bool[n];
	for(int i=0 ; i<n ; i++)
		vis[i] = 0;
	for(int i=0 ; i<s ; i++)
		vis[list[i]] = 1;
	
	cop(vis , temp , n);
	
	do
	{
		for(int i=0 ; i<m ; i++)
		{
			for(int j=0 ; j<n ; j++)
			{
				bool flg = 0;
				if(fdl[i][j] == 1)
				{	
					if(temp[j] == 1)
						continue;
					else
					{
						flg = 1;
						break;
					}
				}
				if(flg == 1)
					break;
				
				for(int j=0 ; j<n ; j++)
					if(fdr[i][j] == 1)
						temp[j] = 1;
			}
		}
	}while(!equl(vis , temp , n));
	
	return vis;
	
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

bool equiv(bool **fdl , bool **fdr , bool **fdlt , bool **fdrt , int n , int m)				//full equivalence check  ->  finished working 'z' state		true if equivalent
{
	bool *v1 = new bool[n];
	bool *v2 = new bool[n];

	int *list = new int[n];
	bool fl = 1;

	for(int i=0 ; i<n ; i++)
	{
		list[0] = i;
		v1 = closure(fdl , fdr , list , 1 , n , m);
		v2 = closure(fdlt , fdrt , list , 1 , n , m);
		fl = equl(v1 , v2 , n);
		if(!fl)
			break;
	}
	if(!fl)																						//after checking reach of all attributes , if discrepancy
		return false;

	//get for all lhs

	int in = 0;
	fl = 1;
	for(int i = 0 ; i<m ; i++)
	{
		in = 0;
		for(int j=0 ; j<n ; j++)
			if(fdl[i][j] == 1)
				list[in++] = j;

		v1 = closure(fdl , fdr , list , in , n , m);
		v2 = closure(fdlt , fdrt , list , in , n , m);
		fl = equl(v1 , v2 , n);
		if(!fl)
			break;
	}
	if(!fl)
		return false;

	return true;
}

void mincov(bool **fdl , bool **fdr , int n , int m)									//does brute min cover and puts minimum cover fd set into fdl and fdr
{
	bool **fdlt = new bool*[n];          //declare graph

  	for(int i = 0 ; i<n ; i++)       //declare graph
  		fdlt[i] = new bool[n];

    bool **fdrt = new bool*[n];          //declare graph

    for(int i = 0 ; i<n ; i++)       //declare graph
    	fdrt[i] = new bool[n];

    cop_d(fdl , fdr , fdlt , fdrt , n , m);
    int cnt = 0;
    bool fin = 0;
    do   													//repeatedly removes all possible attributes and checks for equivalence over all fds and breaks when no change at all possible any more
    {
    	fin = 0;
    	for(int i=0 ; i<m ; i++)
    	{
    		cnt = 0;
    		for(int k=0 ; k<n ; k++)
    		{
    			int cmp = cnt;
	    		for(int j=0 ; j<n ; j++)
    			{
		    		if(fdl[i][j] == 1)
    				{
    					if(cmp == 0)
		    			{
		    				fdlt[i][j] = 0;					//remove i from fdlt[i]
    						break;
    					}
    					else
    						cmp--;
    				}
    			}

    			if(cmp > 0)
    				break;

    			bool k =equiv(fdl , fdr , fdlt , fdrt , n , m);
    			if(k)
	    		{
		    		cop_d(fdlt , fdrt , fdl , fdr , n , m);						//if equivalent , change
	    			fin = 1;
	    			break;
	    		}
    			else
		    		cop_d(fdl , fdr , fdlt , fdrt , n , m);						//else revert
		    	cnt++;
		    }
	    }
	}while(fin);

	//fdl and fdr have min cover fd sets

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