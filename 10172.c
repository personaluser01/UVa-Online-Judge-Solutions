/*
 * 10172. Lonesome Cargo Distributor
 * status: Accepted
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define S 0x80
#define Q 0x80
#define NX(k) (k+1)

int ts,n,capacity,B,stack[S],*top,
	q[N][1 << 14],head[N],tail[N],sz[N];

void enq( int t, int id ) { q[t][tail[t]] = id, ++sz[t], tail[t] = NX(tail[t]); }
int deq( int t ) {
	int r = q[t][head[t]];
	head[t] = NX(head[t]), --sz[t];
	return r;
}

int main() {
	int i,j,k,l,t,total,ax;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d %d %d",&n,&capacity,&B); ) {
		for(total=0,i=0;i<n;++i)
			for(scanf("%d",&l),total+=l,head[i]=tail[i]=sz[i]=0;l--&&scanf("%d",&k);enq(i,--k));
		for(ax=0,top=stack,i=0;total;i=(i+1)%n) {
			for(;sz[i]<B&&top>stack;((k=*top--)==i?--total:enq(i,k)),++ax);
			for(;top>stack&&*top==i; --top, --total, ++ax );
			for(;sz[i]&&top-stack<capacity;*++top=deq(i),++ax);
			if(total)ax+=2;
		}
		printf("%d\n",ax);
	}
	return 0;
}
