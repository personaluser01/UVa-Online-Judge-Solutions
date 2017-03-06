/*
 * 10032. Tug of War
 * status: Accepted
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define W 0x200

int n,c[N],total,m,z[N/2][W*N/2],yes,eps,w;
unsigned int *headj,*headk,*tailj,*tailk,qj[N/2*W*N/2],qk[N/2*W*N/2],
			   *sj,*sk,*ptrj,*ptrk;

int main() {
	int ts,i,j,k;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d",&n);) {
		for ( total = 0, m=(n>>1),i=0;i<n;scanf("%d",c+i),total+=c[i++]);
		headj = tailj = qj, headk = tailk = qk;
		for ( z[*tailj++=0][*tailk++=0]=++yes, i=0; i<n; ++i ) {
			for ( sj = tailj, sk = tailk, ptrj = headj, ptrk = headk; ptrj < sj; ++ptrj, ++ptrk )
				if ( (*ptrj)+1 <= m && (*ptrk)+c[i] <= total && z[(*ptrj)+1][(*ptrk)+c[i]] != yes ) 
					*tailj++=(*ptrj)+1,*tailk++=(*ptrk)+c[i];
			for ( ptrj = sj, ptrk = sk; ptrj < tailj; z[*ptrj][*ptrk] = yes, ++ptrj, ++ptrk );
		}
		for ( eps = (1<<29), k = 0; k <= total; ++k )
			if ( (z[m][k]==yes||z[m][total-k]==yes) && abs(k-total+k) < eps )
				eps = abs(2*k-total), w = k;
		if ( w > total-w ) w = total-w;
		printf("%d %d\n",w,total-w);
		if ( ts ) putchar('\n');
	}
	return 0;
}
