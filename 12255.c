/*
 * 12255. Underwater Snipers
 * TOPIC: geometry, binary search, sweepline, binary heap
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pi (2*acos(0.00))
#define DIM 3
#define N (1 << 15)
#define oo (1LL << 43)
typedef long long i64;
#define Q (2*N)
enum { OPENING, CLOSING };
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define tol 1e-9

double min( double x, double y ) { return x < y ? x:y; }

typedef struct { i64 x[DIM]; } cell;
typedef struct { i64 t; int id; char event_type; } event;

int cmp( const void *a, const void *b ) {
	event *p = (event *)a,
		  *q = (event *)b;
	if ( p->t == q->t ) {
		if ( p->event_type == q->event_type ) return 0;
		return p->event_type==OPENING?-1:1;
	}
	return p->t<q->t?-1:1;
}

int ts,cs,heap[Q],pos[N],cnt,*head,*tail,q[Q],inq[N],yes;
i64 K,n,d,h_plus,snipers;
cell c[N];
event e[Q];

void push( int x ) {
	int i,j;
	if ( inq[x] != yes ) pos[heap[cnt]=x] = cnt, ++cnt, inq[x] = yes;
	for(j=pos[x];j&&cmp(e+heap[i=(j-1)>>1],e+heap[j])>0;bubble,j=i);
}

int pop() {
	int x = *heap,i,j;
	if ( (inq[x]=0,--cnt) ) pos[heap[0]=heap[cnt]]=0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && cmp(e+heap[j+1],e+heap[j]) < 0 ) ++j;
		if ( cmp(e+heap[i],e+heap[j]) <= 0 ) break ;
	}
	return x;
}

void update_key( int x, i64 val ) { e[x].t = val, push(x); }

int f( i64 M ) {
	double leg;
	int i,j,k,a,b,nails = 0;

	if ( M < 0 ) return 0;

	for ( ++yes, cnt = 0, j = 0, i = 0; i < n; ++i ) {
		if ( c[i].x[1]-K+M > d ) return 0;
		assert( c[i].x[1]-K+M >= 0 );
		assert( c[i].x[1]-K+M <= d );
		leg = d*sin(acos((c[i].x[1]-K+M)/(d+.00)));
		e[a=j].t = (i64)ceil(c[i].x[0]-leg),  e[j].event_type = OPENING, e[j].id = (j++)/2;
		e[b=j].t = (i64)floor(c[i].x[0]+leg), e[j].event_type = CLOSING, e[j].id = (j++)/2;
		0 && printf("[M = %lld] %lld %lld\n",M,e[a].t,e[b].t);
		if ( e[a].t > e[b].t ) { 0&&printf("With M = %lld an empty segment\n",M); return 0;}
		push(a);
	}
	for ( head=tail=q; cnt>0;) 
		if ( e[i=pop()].event_type==OPENING ) *tail++ = (i^1), push(i^1);
		else 
			for( ++nails; head < tail;) {
				update_key(j=*head++,-oo);
				assert( pop() == j );
			}
	return nails <= snipers;
}

int main() {
	int i,j,k,ok,l;
	i64 low,high,mid;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		printf("Case %d: ",++cs),ok=1,scanf("%lld %lld %lld %lld",&K,&n,&snipers,&d);
		for ( h_plus = -oo, i = 0; i < n; ++i ) {
			scanf("%lld %lld",c[i].x,c[i].x+1);
			assert( c[i].x[1] >= K );
			if ( h_plus > c[i].x[1]-d )
				h_plus = c[i].x[1]-d, l = i;
			if ( c[i].x[1]-d>K ) ok = 0;
		}
		if(!ok||h_plus>K) {bad_news: puts("IMPOSSIBLE");continue;}
		if ( !f(low=0) ) goto bad_news; 
		assert( !f(K-h_plus+1) );
		for(low=0,high=K-h_plus+1;low+1<high;f(mid=(low+high)/2)?(low=mid):(high=mid));
		printf("%lld\n",low);
	}
	return 0;
}


