/*
 * 10691. Subway
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#define tol 1e-9
#define pi (2*acos(0.00))
#define N (1 << 10)
typedef long double ld;
typedef struct { ld x[2]; int id; } segment;
typedef unsigned int event;
#define SH 9
#define enc(t,i) ((t)|((i)<<1))
#define Q (1 << (SH+3))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
segment s[N];
#define DBG 0
#if DBG
#define D(x) (x)
#else
#define D(x) ()
#endif

int cmp( const void *X, const void *Y ) {
	segment *x = (segment *)X,
			*y = (segment *)Y;
	if ( fabs(x->x[0]-y->x[0]) < tol ) {
		if ( fabs(x->x[1]-y->x[1]) < tol )
			return 0;
		return x->x[1]<y->x[1]?-1:1;
	}
	return x->x[0] < y->x[0] ? -1 : 1;
}

int is_less( event a, event b ) { 
	ld diff = fabs(s[a>>1].x[a&1]-s[b>>1].x[b&1]);
	if ( diff > tol )
		return s[a>>1].x[a&1] < s[b>>1].x[b&1];
	return (!(a&1))&&(b&1);
}

ld get_angle( ld a, ld b, ld c, ld d ) {
	ld L = sqrt((a*a+b*b)*(c*c+d*d)),
	   co = (a*c+b*d)/L,
	   si = (a*d-b*c)/L;
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

ld x[N],y[N];
int pos[Q],cnt,n,m,d,yes,nailed[N],in_queue[N],alias[N][2],inheap[Q];
unsigned int heap[Q];

void heap_push( event e ) {
	int i,j;
	if ( inheap[e] != yes )
		heap[pos[e] = cnt++] = e, inheap[e] = yes;
	for ( j = pos[e]; j; j = i ) {
		i = (j-1)>>1;
		if ( is_less(heap[i],heap[j]) ) break ;
		xchg(pos[heap[i]],pos[heap[j]]);
		xchg(heap[i],heap[j]);
	}
}

void heap_pop( event *e ) {
	int i,j;
	if ( e ) 
		*e = *heap;
	inheap[*heap] = 0;
	if ( --cnt )
		pos[heap[0] = heap[cnt]] = 0;
	for ( j = 0;; ) {
		i = j, j <<= 1, ++j;
		if ( j > cnt-1 ) break ;
		if ( j+1 < cnt && is_less(heap[j+1],heap[j]) ) ++j;
		if ( is_less(heap[j],heap[i]) )
			xchg(pos[heap[i]],pos[heap[j]]), xchg(heap[i],heap[j]);
		else break ;
	}
}

long double f( ld x ) {
	return x*180.0/pi;
}

int main() {
	int i,j,k,ts,t,l,res,ok,shift,ax,sz;
	ld L,phi,ang,left,right,prev;
	event u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && 2 == scanf("%d %d",&n,&d); ) {
		ax = n+n+n+n+n+n;
		for ( m = 0, i = 0; i < n; ++i ) {
			scanf("%Lf %Lf",x+i,y+i);
			L = x[i]*x[i] + y[i]*y[i];
			if ( L <= d*d ) continue ;
			phi = asin(sqrt((d*d)/L));
			assert( phi >= 0 );
			assert( phi <= pi/2 );
			ang = get_angle(1,0,x[i],y[i]);
			assert( -pi <= ang && ang <= pi );
			left = ang-phi, right = ang+phi;
			s[m].x[0] = left, s[m].x[1] = right, s[m].id = k = t = m++;
			s[m].x[0] = left+2*pi, s[m].x[1] = right+2*pi, s[m].id = l = t = m++;
			/*s[m].x[0] = left-2*pi, s[m].x[1] = right-2*pi, s[m].id = t = m++;*/
			alias[k][0] = l, alias[k][1] = t;
			alias[l][0] = k, alias[l][1] = t;
			alias[t][0] = k, alias[t][1] = l;
		}
		if ( !m ) {
			puts("0");
			continue ;
		}
		qsort(s,m,sizeof *s,cmp);
		for ( shift = 0; shift <= m/2; ++shift ) {
			ok = 1, cnt = 0, ++yes;
			for ( i = shift; i < m; heap_push(enc(0,i)), ++i );
			for ( l = 0, res = 0; cnt; ) {
				heap_pop(&u);
				if ( 0 == (u & 1) ) {
					heap_push(u^1);
					in_queue[s[u>>1].id] = yes;
					continue ;
				}
				if ( nailed[s[u>>1].id] == yes ) {
					in_queue[s[u>>1].id] = 0;
					continue ;
				}
				for ( k = 0, ++res, j = 0; j < m; ++j )
					if ( in_queue[j] == yes && nailed[j] != yes ) {
						nailed[j] = yes;
						nailed[alias[j][0]] = nailed[alias[j][1]] = yes;
						++k;
					}
				if ( !k ) --res;
				if ( res >= ax ) goto nx;
				in_queue[s[u>>1].id] = 0;
			}
			for ( i = 0; i < m && ok; ++i )
				if ( nailed[i] != yes )
					ok = 0;
			if ( ok && ax > res ) ax = res;
			nx: continue ;
		}
		printf("%d\n",ax);
	}
	return 0;
}

