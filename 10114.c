/*
 * 10114. Loansome Car Buyer
 * status: Accepted
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define N 0x80
typedef long long i64;

int n,m;
long double payment,loan,d[N],value;

int main() {
	int i,j,k;
	long double w,debt;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;1==scanf("%d",&n)&&n>= 0;) {
		scanf("%Lf %Lf %d",&payment,&loan,&m);
		for(k=-1,i=0;i<m;d[k]=w,++i)
			for(scanf("%d %Lf",&j,&w);j!=++k;d[k]=d[k-1]);
		for(;++k<=n;d[k]=d[k-1]);
		value=(loan+payment)*(1-d[0]);
		payment=loan/n;
		debt=loan;
		for(k=1;k<=n&&debt>=value;debt-=payment,value*=(1-d[k++]));
			/*printf("value %Lf and debt %Lf\n",value,debt);*/
		--k, printf("%d month%s\n",k,k==1?"":"s");
	}
	return 0;
}
