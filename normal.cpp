#include <iostream>

using namespace std;

/*bool fdl[100][100];					//fdl[i][j] represents attribute j+1 is on LHS of fd no. i
bool fdr[100][100];

bool fdlt[100][100];				//temporary sets
bool fdrt[100][100];*/

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

void erase(bool *v , int n)											//erases v of size n to all zeros
{
	for(int i=0 ; i<n ; i++)
		v[i] = 0;
}

void mrg(bool *src , bool *dest , int n)							//merges source and dest into dest and puts src = 0
{
	/*cout<<"into merge func. : before , source array = ";
	for(int i=0 ; i<n ; i++)
		cout<<src[i]<<" , ";
	cout<<"\n\n\n";*/
	for(int i=0 ; i<n ; i++)
	{
		if(src[i] == 1)
			dest[i] = 1;
	}
	/*cout<<"into merge func. : dest array = ";
	for(int i=0 ; i<n ; i++)
		cout<<dest[i]<<" , ";
	cout<<"\n\n\n";*/
	erase(src , n);
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

void print(bool **fdl , bool **fdr , int n , int m)
{
	cout<<"\n\nprinting : \n";

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
}

void samchk(bool **fdl , bool **fdr , int n , int m)					//merges together similar fds
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=i+1 ; j<m ; j++)
		{
			if(equl(fdl[i] , fdl[j] , n))
			{
				cout<<"in merge : for i = "<<i<<" , j = "<<j<<endl;
				mrg(fdr[j] , fdr[i] , n);
				erase(fdl[j] , n);
				//erase(fdr[j] , n);
				cout<<"after merge : ";
				print(fdl , fdr , n , m);
			}
		}
	}
}

/*void print(bool **fdl , bool **fdr , int n , int m)
{
	cout<<"\n\nprinting : \n";

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
}*/

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
		//copy temp into vis

		cop(temp , vis , n);

		for(int i=0 ; i<m ; i++)
		{
			bool flg = 0;
			for(int j=0 ; j<n ; j++)
			{
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
			}
			if(flg == 1)
				continue;
				
			for(int kj=0 ; kj<n ; kj++)
				if(fdr[i][kj] == 1)
					temp[kj] = 1;

		}
		/*cout<<"atka";
		int hk = 0;
		cout<<"\n\nvis : ";
		for(int p =0 ; p<n ; p++)
			cout<<vis[p]<<" , ";
		cout<<"\n\ntemp : ";
		for(int p =0 ; p<n ; p++)
			cout<<temp[p]<<" , ";

		cout<<"for the current fd set : "<<endl;

		print(fdl , fdr , n , m);

		cout<<endl<<endl;

		cout<<"for list : ";

		for(int i=0 ; i<s ; i++)
			cout<<list[i]<<" , ";
		cout<<endl;

		cin>>hk;*/


	}while(!equl(vis , temp , n));

	/*cout<<"\n\nvis : ";
	for(int p =0 ; p<n ; p++)
		cout<<vis[p]<<" , ";
	cout<<"\n\n\n";*/
	
	return vis;
	
}

bool reach(bool **fdl , bool **fdr , bool *vis , int n , int m)		//true if bool has full reachability
{																			//gives reachability of all attrs. in <list> together			#works
	bool *temp = new bool[n];
	for(int i=0 ; i<n ; i++)
		temp[i] = 0;
	/*for(int i=0 ; i<s ; i++)
		vis[list[i]] = 1;*/

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

	/*for(int i=0 ; i<m ; i++)
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

	/*for(int i=0 ; i<n ; i++)
		cout<<vis[i]<<" ";*/

	cop(vis , temp , n);
	
	do
	{
		//copy temp into vis

		cop(temp , vis , n);

		for(int i=0 ; i<m ; i++)
		{
			bool flg = 0;
			for(int j=0 ; j<n ; j++)
			{
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
			}
			if(flg == 1)
				continue;
				
			for(int kj=0 ; kj<n ; kj++)
				if(fdr[i][kj] == 1)
					temp[kj] = 1;

		}
		/*cout<<"atka";
		int hk = 0;
		cout<<"\n\nvis : ";
		for(int p =0 ; p<n ; p++)
			cout<<vis[p]<<" , ";
		cout<<"\n\ntemp : ";
		for(int p =0 ; p<n ; p++)
			cout<<temp[p]<<" , ";

		cout<<"for the current fd set : "<<endl;

		print(fdl , fdr , n , m);

		cout<<endl<<endl;

		cout<<"for list : ";

		for(int i=0 ; i<s ; i++)
			cout<<list[i]<<" , ";
		cout<<endl;

		cin>>hk;*/


	}while(!equl(vis , temp , n));

	/*cout<<"\n\nvis : ";
	for(int p =0 ; p<n ; p++)
		cout<<vis[p]<<" , ";
	cout<<"\n\n\n";*/
	
	//return vis;

	bool kk = checkvis(vis , n);
	if(kk)
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

int nos(bool *v , int n)																//returns no. of 1's in v
{
	int count = 0;
	for(int i=0 ; i<n ; i++)
	{
		if(v[i] == 1)
			count++;
	}
	return count;
}

bool* binary(bool *vis , bool **fdl , bool **fdr , int n , int m , int lev , bool *min , int mn)
{
    if(lev < 1)
    {
    	//return vis;
    	bool *tt = new bool[n];
    	cop(vis , tt , n);
    	bool k = reach(fdl , fdr , tt , n , m);
    	if(!k)
    	{
    		/*cout<<"k is false ... \n vis = ";
    		for(int i=0 ; i<n ; i++)
    			cout<<vis[i]<<" ";
    		cout<<"\n\n";*/
    		return vis;
    	}
    	int h = nos(vis , n);
    	/*cout<<"k is true ...\n\nvis = ";
    	for(int i=0 ; i<n ; i++)
    		cout<<vis[i]<<" ";*/
    	int pp = nos(min , n);
    	/*cout<<"\nh = "<<h<<" , pp = "<<pp<<endl;;
    	cout<<" h = "<<h<<" mn = "<<mn<<endl;*/
    	if(h < pp)
    	{
    		//cout<<" inside for h = "<<h<<" , mn = "<<mn<<" pp = "<<pp<<endl<<endl;
    		mn = h;
    		cop(vis , min , n);
    		//cout<<"copied\nmn = "<<mn<<"\n";
    		//return temp;
    	}
    } //printf("%s\n",A);    // Assume A is a global variable
    else
    {
        vis[lev-1] = 0;
        binary(vis , fdl , fdr , n , m , lev-1 , min , mn);
        vis[lev-1] = 1;
        binary(vis , fdl , fdr , n , m , lev-1 , min , mn);
    }
    /*cout<<"all print : ";
    for(int i=0 ; i<n ; i++)
    		cout<<vis[i]<<" ";
    cout<<"\n\n";*/
    return vis;
}

bool* gensubs(bool **fdl , bool **fdr , int n , int m)					//returns candidate key as bool array
{
	/*for(int i=0 ; i<n ; i++)
	{
		if(!exist(list , s , i))
		{
			//add i and check
			list[s] = i;
			int r = reach(fdl , fdr , list , s+1 , n , m);
			if(r == 1)
			{
				//set this as candidate key and print , return , whatever...
				//return
			}
		}
	}*/

	bool *vis = new bool[n];
	bool *temp = new bool[n];
	for(int i=0 ; i<n ; i++)
	{
		vis[i] = 0;
		temp[i] = 1;
	}

	//code to gen all bin strings of size n

	bool *kk = binary(vis , fdl , fdr , n , m , n , temp , n+1);

	cout<<"\n\ntemp : ";

	for(int i=0 ; i<n ; i++)
	{
		if(temp[i] == 1)
			cout<<" "<<(i+1)<<" ";
	}
	cout<<"\n\n";

	/*cout<<"vis : ";

	for(int i=0 ; i<n ; i++)
	{
		if(vis[i] == 1)
			cout<<" "<<(i+1)<<" ";
	}
	cout<<"\n\n";

	cout<<"kk : ";

	for(int i=0 ; i<n ; i++)
	{
		if(kk[i] == 1)
			cout<<" "<<(i+1)<<" ";
	}
	cout<<"\n\n";*/
	
	//fin code

	/*if(reach(fdl , fdr , vis , n , m))
		return vis;*/

	return temp;
}

void ckeycheck(bool **fdl , bool **fdr , int n , int m)					//what all min need to be there				#works
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

	/*if(reach(fdl , fdr , list , ind , n , m) == 1)
	{
		cout<<"candidate key found!!\n\n";
		return;
	}*/

	//length = ind ++

	//generate l+1 subs

}

bool equiv(bool **fdl , bool **fdr , bool **fdlt , bool **fdrt , int n , int m)				//full equivalence check  ->  finished working 'z' state		true if equivalent
{
	bool *v1 = new bool[n];
	bool *v2 = new bool[n];

	int *list = new int[n];
	bool fl = 1;

	cout<<"here at least..."<<endl<<endl;

	for(int i=0 ; i<n ; i++)
	{
		list[0] = i;
		v1 = closure(fdl , fdr , list , 1 , n , m);
		v2 = closure(fdlt , fdrt , list , 1 , n , m);
		fl = equl(v1 , v2 , n);
		//cout<<"for list var : "<<i<<" , fl = "<<fl<<" , for fdlt and fdrt : \n\n";
		//print(fdlt , fdrt , n , m);
		/*cout<<"in single attribute closure : for i = "<<i<<endl;

		cout<<"for temp fd set : ";
		print(fdlt , fdrt , n , m);
		cout<<"\nv1 : ";

		for(int j=0 ; j<n ; j++)
			cout<<v1[j]<<" , ";
		cout<<"\n\nv2 : ";

		for(int j=0 ; j<n ; j++)
			cout<<v2[j]<<" , ";
		cout<<"\n\nfl = "<<fl<<endl<<endl<<endl;*/
		if(!fl)
			break;
	}

	//cout<<"found fl actually...\n\n";

	if(!fl)																						//after checking reach of all attributes , if discrepancy
		return false;

	//get for all lhs

	//cout<<"in mid -> checked all closures of indi attributes...\n\n\n";

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

/*bool equiv(bool **fdl , bool **fdr , bool **fdlt , bool **fdrt , int n , int m)
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=0 ; j<n ; j++)
			if(fdlt[i][j] == 1)
				cout<<(j+1)<<" . ";

		cout<<"  -->  ";
		for(int j=0 ; j<n ; j++)
			if(fdrt[i][j] == 1)
				cout<<(j+1)<<" . ";

		cout<<endl;
	}
	cout<<"\n\n\n";
	return true;
}
*/

void mincov(bool **fdl , bool **fdr , int n , int m)									//does brute min cover and puts minimum cover fd set into fdl and fdrt					##works##
{			
	bool **fdlt = new bool*[m];          //declare graph

  	for(int i = 0 ; i<n ; i++)       //declare graph
  		fdlt[i] = new bool[n];

    bool **fdrt = new bool*[m];          //declare graph

    for(int i = 0 ; i<n ; i++)       //declare graph
    	fdrt[i] = new bool[n];

    cop_d(fdl , fdr , fdlt , fdrt , n , m);
    int cnt = 0;
    bool fin = 0;
    do   													//repeatedly removes all possible attributes and checks for equivalence over all fds and breaks when no change at all possible any more -> on LHS
    {
    	fin = 0;
    	for(int i=0 ; i<m ; i++)
    	{
    		cnt = 0;
    		if(nos(fdl[i] , n) <= 1)
    			continue;
    		for(int k=0 ; k<n ; k++)
    		{
    			int cmp = cnt;
    			bool laf = 0;
	    		for(int j=0 ; j<n ; j++)
    			{
		    		if(fdl[i][j] == 1)
    				{
    					if(cmp == 0)
		    			{
		    				fdlt[i][j] = 0;					//remove i from fdlt[i]
		    				laf = 1;
    						break;
    					}
    					else
    						cmp--;
    				}
    			}

    			if(laf == 0)
    			{
    				cout<<"check break at cmp = "<<cmp<<endl;
    				break;
    			}

    			bool chk = equiv(fdl , fdr , fdlt , fdrt , n , m);
    			if(chk)
	    		{
		    		cop_d(fdlt , fdrt , fdl , fdr , n , m);						//if equivalent , change
	    			fin = 1;
	    			break;
	    		}
    			else
		    		cop_d(fdl , fdr , fdlt , fdrt , n , m);						//else revert
		    	cnt++;
		    	cout<<"count = "<<cnt<<endl;
		    }
	    }
	}while(fin);

	//fdl and fdr have min cover fd sets

	cout<<"after lhs : set is : ";
	print(fdl , fdr , n , m);


	do   													//repeatedly removes all possible attributes and checks for equivalence over all fds and breaks when no change at all possible any more -> on RHS
    {
    	fin = 0;
    	for(int i=0 ; i<m ; i++)
    	{
    		cnt = 0;
    		/*if(nos(fdr[i] , n) <= 1)
    			continue;*/
    		for(int k=0 ; k<n ; k++)
    		{
    			int cmp = cnt;
    			bool laf = 0;
	    		for(int j=0 ; j<n ; j++)
    			{
		    		if(fdr[i][j] == 1)
    				{
    					if(cmp == 0)
		    			{
		    				fdrt[i][j] = 0;					//remove i from fdlt[i]
		    				laf = 1;
    						break;
    					}
    					else
    						cmp--;
    				}
    			}

    			if(laf == 0)
    			{
    				cout<<"check break at cmp = "<<cmp<<endl;
    				break;
    			}

    			bool chk = equiv(fdl , fdr , fdlt , fdrt , n , m);
    			if(chk)
	    		{
		    		cop_d(fdlt , fdrt , fdl , fdr , n , m);						//if equivalent , change
	    			fin = 1;
	    			break;
	    		}
    			else
		    		cop_d(fdl , fdr , fdlt , fdrt , n , m);						//else revert
		    	cnt++;
		    	cout<<"count = "<<cnt<<endl;
		    }
	    }
	}while(fin);

}

bool allz(bool *v , int n)																//true if all zero
{
	for(int i=0 ; i<n ; i++)
		if(v[i] == 1)
			return false;

	return true;
}

void delit(bool **fdl , bool **fdr , int n , int &m)									//deletes empty fds and updates m
{
	for(int i=0 ; i<m ; i++)
	{
		if(allz(fdl[i] , n) || allz(fdr[i] , n))
		{
			for(int k=i ; k<(m-1) ; k++)
			{
				cop(fdl[i+1] , fdl[i] , n);
				cop(fdr[i+1] , fdr[i] , n);
			}
			m--;
			i--;
		}
	}

	cout<<"\n\ndelited : \n";
	print(fdl , fdr , n , m);
}

void init(bool **fd , int n , int m)													//initialize fd of size m x n
{
	for(int  i=0 ; i<m ; i++)
		for(int j=0 ; j<n ; j++)
			fd[i][j] = 0;
}

void foolchk(bool **fdl , bool **fdr , int n , int &m)									//checks for left = right
{
	for(int i=0 ; i<m ; i++)
	{
		if(equl(fdl[i] , fdr[i] , n))
		{
			erase(fdl[i] , n);
			erase(fdr[i] , n);
		}
	}

	cout<<"before deliting m = "<<m<<" and state : "<<endl;

	print(fdl , fdr , n , m);

	delit(fdl , fdr , n , m);
}

void filter(bool **fdl , bool **fdr , int n , int &m)									//filters if same attribute on left and right of fd
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			if(fdl[i][j] == fdr[i][j])
			{
				fdl[i][j] = 0;
				fdr[i][j] = 0;
			}
		}
	}

	delit(fdl , fdr , n , m);
}

bool lossless(bool *key , bool **fdl , bool **fdr , int n , int m)						//true if lossless join , false -> lossed join , add key...
{
	bool k = false;
	for(int i=0 ; i<m ; i++)
	{
		bool fl=0;
		for(int j=0 ; j<n ; j++)
		{
			if(fdl[i][j] == 0 && key[j] == 1)
				fl = 1;
			if(fl == 1)
				break;
		}
		if(fl == 0)
		{
			k = true;
			break;
		}
	}

	return k;
}

void create_table(bool **fdl , bool **fdr , bool **table , int n , int m)				//returns filled tabel based on normal fd set
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			if(fdl[i][j] == 1)
				table[i][j] = 1;
			if(fdr[i][j] == 1)
				table[i][j] = 1;
		}
	}
}

void add_table(bool *key , bool **table , int n , int m)								//adds relation <key> to table
{
	for(int i=0 ; i<n ; i++)
	{
		if(key[i] == 1)
		{
			table[m][i] = 1;
		}
	}
}

void del_table(bool **table , int n , int &m)											//deletes useless table entries
{
	for(int i=0 ; i<m ; i++)
	{
		if(allz(table[i] , n))
		{
			for(int k=i ; k<(m-1) ; k++)
			{
				cop(table[i+1] , table[i] , n);
				//cop(fdr[i+1] , fdr[i] , n);
			}
			m--;
			i--;
		}
	}

	cout<<"\n\ndelited : \n";
}

void rep_table(bool **table , int n , int &m)											//removes repetetive table entries
{
	for(int i=0 ; i<m ; i++)
	{
		for(int j=i+1 ; j<m ; j++)
		{
			if(equl(table[i] , table[j] , n))
			{
				cout<<"in merge : for i = "<<i<<" , j = "<<j<<endl;
				mrg(table[j] , table[i] , n);
				erase(table[j] , n);
				//erase(fdr[j] , n);
				cout<<"after merge : ";
				//print(fdl , fdr , n , m);
			}
		}
	}

	del_table(table , n , m);
}

int main()
{
	int n=0;
	cout<<"enter number of attributes : ";
	cin>>n;

	int m=0;
	cout<<"enter number of fds : ";
	cin>>m;

	bool **fdl = new bool*[m];          //declare graph

    for(int i = 0 ; i<n ; i++)       	//declare graph
      	fdl[i] = new bool[n];

    //cout<<"segged\n\n";

    bool **fdr = new bool*[m];          //declare graph

    for(int i = 0 ; i<n ; i++)       	//declare graph
      	fdr[i] = new bool[n];

    //cout<<"segged agn\n\n";

    init(fdl , n , m);

    //cout<<"segged\n\n";

    init(fdr , n , m);

    //cout<<"segged agn\n\n\n";

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

	bool *key = new bool[n];

	for(int i=0 ; i<n ; i++)
		key[i] = 0;

	key = gensubs(fdl , fdr , n , m);
	/*cout<<"enter key : ";
	int jk = 0;
	cin>>jk;
	while(jk!= -1)
	{
		key[jk-1] = 1;
		cin>>jk;
	}

	//print fd

	print(fdl , fdr , n , m);

	cout<<"key is : ";

	for(int i=0 ; i<n ; i++)
		if(key[i] == 1)
			cout<<(i+1)<<" . ";
	cout<<"\n\n";

	//finish print fd

	/*cout<<"candidate key attributes are : ";
	ckeycheck(n,m);

	int list[3] = {0,2,2};
	cout<<"\n"<<reach(list , 2 , n , m)<<endl;*/

	/*filter(fdl , fdr , n , m);

	mincov(fdl , fdr , n , m);

	cout<<"AFTER MINCOV\n\n\n";

	print(fdl , fdr , n , m);

	samchk(fdl , fdr , n , m);

	cout<<"\n\nAFTER SAMCHK\n\n";

	print(fdl , fdr , n , m);

	delit(fdl , fdr , n , m);

	foolchk(fdl , fdr , n , m);

	print(fdl , fdr , n , m);
	
	cout<<"\n\n m = "<<m<<endl<<endl<<endl;

	bool **table = new bool*[m+1];          //declare graph

    for(int i = 0 ; i<n ; i++)       	//declare graph
      	table[i] = new bool[n];

	create_table(fdl , fdr , table , n , m);			//table created

	//get / find key here

	bool lk = lossless(key , fdl , fdr , n , m);
	if(!lk)
		add_table(key , table , n , m++);

	rep_table(table , n , m);

	//print table

	cout<<"tables are : \n";

	for(int i=0 ; i<m ; i++)
	{
		cout<<(i+1)<<" : ";
		for(int j=0 ; j<n ; j++)
		{
			if(table[i][j] == 1)
				cout<<" "<<(j+1)<<" ";
		}
		cout<<endl;
	}*/

	//print table

	return 0;
}