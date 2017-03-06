int main()
{
		int num;

		while (cin>>num)
		{
				if (num==0)
				{
						cout<<"0"<<endl;
						continue;
				}
				if (num==1)
				{
						cout<<"1"<<endl;
						continue;
				}
				if (num==2)
				{
						cout<<"3"<<endl;
						continue;
				}
				if (num==3)
				{
						cout<<"5"<<endl;
						continue;
				}

				BigNum n(num);
				BigNum count(3);
				BigNum numadd(3);
				BigNum total(5);
				BigNum power(4);
				while (count<n || count==n)
				{
						if (count+numadd>n)
						{
								BigNum d=n-count;
								d*=power;
								total+=d;
						}
						else
						{
								BigNum d=numadd*power;
								total+=d;
						}

						power*=2;
						count+=numadd;
						++numadd;

				}
				cout<<total<<endl;
		}
		return 0;
} 
