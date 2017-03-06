/*
 * 11355. Cool Points
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
#define N 0x100
#define tol 1e-11
#define pi (2*acos(0.00))
#define Q (N<<2)
#define enc(i,t) ((t)|((i)<<1))
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]), xchg(heap[i],heap[j]))
#define SQ(x) ((x)*(x))
typedef struct { long double x,y; } cell;
typedef unsigned int state;
#define DBG(x) (1)
long double min( long double x, long double y ) { return x < y ? x : y; }
long double max( long double x, long double y ) { return x > y ? x : y; }
long double Norm( long double x ) {
	for (;x < -pi; x += 2*pi );
	for (;x > pi; x -= 2*pi );
	assert( -pi <= x );
	assert( x <= pi );
	return x;
}

long double 
get_angle( long double a, long double b, long double c, long double d ) {
	long double L = sqrt((SQ(a)+SQ(b))*(SQ(c)+SQ(d))),
		 		si = (a*d-b*c)/L,
				co = (a*c+b*d)/L;
	DBG(printf("L = %.2Lf\n",L));
	if ( fabs(si) < tol && fabs(co-1) < tol )
		return 0;
	if ( fabs(si) < tol && fabs(co+1) < tol )
		return pi;
	if ( fabs(si-1) < tol )
		return pi/2;
	if ( fabs(si+1) < tol )
		return -pi/2;
	if ( co >= 0 && si >= 0 )
		return asin(si);
	if ( co >= 0 && si <= 0 )
		return asin(si);
	if ( co <= 0 && si >= 0 )
		return acos(co);
	return -pi+acos(-co);
}

int ts,cs,n,pos[Q],cnt,in_queue,seen[Q],yes;
long double R,phi[Q][2],first_phi,last_phi,A[Q];
cell c[Q][2];
state heap[Q],alias[Q];

int is_less( state u, state v ) {
	if ( fabs(phi[u>>1][u&1]-phi[v>>1][v&1]) < tol ) 
		return (u&1)<(v&1);
	return phi[u>>1][u&1] < phi[v>>1][v&1];
}

void heap_push( state e ) {
	int i,j;
	if ( pos[e] < 0 ) {
		pos[heap[cnt] = e] = cnt; 
		++cnt;
	}
	for ( j = pos[e]; j && !is_less(heap[i=(j-1)>>1],heap[j]); bubble, j = i );
}

void heap_pop( state *e ) {
	int i,j;
	if ( e ) *e = *heap;
	pos[*heap] = -1;
	if ( --cnt )
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0;; bubble ) {
		if ( (i = j, j <<= 1, ++j) > cnt-1 ) break ;
		if ( j < cnt-1 && is_less(heap[j+1],heap[j]) && ++j );
		if ( is_less(heap[i],heap[j]) )
			break ;
	}
}

long double Rnd( long double x ) {
	int d = (int)(1000*x+tol);
	if ( (d%10) <= 4 ) {
		return (d+.00)/1000.00;
	}
	else {
		for (;(d % 10); ++d );
		return (d+0.00)/1000.00;
	}
}

void swp( cell *a, cell *b ) {
	long double t;
	t = a->x, a->x = b->x, b->x = t;
	t = a->y, a->y = b->y, b->y = t;
}

typedef struct {
	long double a,b;
	int id;
} seg;

seg s[N];

int cmp_seg( const void *x, const void *y ) {
	seg *s = (seg *)x,
		*t = (seg *)y;
	if ( fabs(s->a-t->a) < tol ) {
		if ( fabs(s->b-t->b) < tol )
			return s->id-t->id;
		return s->b < t->b ? -1 : 1;
	}
	return s->a < t->a ? -1 : 1;
}

int main() {
	int i,j,k,t,l,shift,processed,st,sz,opening;
	long double ang,ax,w,diff,acc,prev,
		 left,right,limit;
	cell tmp;
	state u,v,u0,uu;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		scanf("%d %Lf",&n,&R);
		if ( !n ) {
			printf("Case %d: 100.00%%\n",++cs);
			continue ;
		}
		for ( i = 0; i < n; ++i ) {
			for ( t = 0; t <= 1; ++t ) {
				scanf("%Lf %Lf",&c[i][t].x,&c[i][t].y);
				/*c[i][t].x /= R, c[i][t].y /= R;*/
			}
			ang = get_angle(c[i][0].x,c[i][0].y,c[i][1].x,c[i][1].y);
			if ( fabs(A[i] = ang) < tol ) {
				phi[i][0] = phi[i][1] = get_angle(1,0,c[i][0].x,c[i][0].y);
				continue ;
			}
			if ( ang < 0 )
				swp(&c[i][0],&c[i][1]), ang = -ang;
			A[i] = ang;
			phi[i][0] = get_angle(1,0,c[i][0].x,c[i][0].y);
			phi[i][1] = phi[i][0]+A[i];
			diff = phi[i][1] - phi[i][0];
			assert( 0 <= diff );
			assert( diff < pi );
		}
		for ( i = n; i < 2*n; ++i )
			for ( t = 0; t <= 1; ++t ) {
				c[i][t] = c[i-n][t];
				phi[i][t] = phi[i-n][t]+2*pi;
				alias[enc(i,t)] = alias[enc(i-n,t)] = enc(i-n,t);
				A[i] = A[i-n];
			}
		for ( i = 2*n; i < 3*n; ++i ) {
			for ( t = 0; t <= 1; ++t ) {
				c[i][t] = c[i-2*n][t];
				phi[i][t] = phi[i-2*n][t]-2*pi;
				A[i] = A[i-2*n];
				alias[enc(i,t)] = enc(i-2*n,t);
			}
		}
		for ( i = 0; i < 3*n; ++i )
			s[i].a = phi[i][0], s[i].b = phi[i][1], s[i].id = (i%n);
		qsort(s,3*n,sizeof *s,cmp_seg);
		for ( w = 0, i = 0; i < 3*n; ++i ) {
			limit = s[i].a+2*pi, acc = 0;
			left = s[i].a, right = s[i].b;
			for ( j = i+1; j < 3*n && !(fabs(right-limit)<tol||right>limit); ++j )
				if ( right < s[j].a ) {
					acc += right-left;
					left = s[j].a, right = min(s[j].b,limit);
				}
				else {
					right = max(right,s[j].b);
					right = min(right,limit);
				}
			acc += (right-left);
			acc = min(acc,2*pi);
			w = max(acc,w);
		}
		/*
		for ( w = 0, shift = 0; shift < 3*n && ++yes; ++shift ) {
			for ( cnt = 0, processed = 0, i = 0; i < 3*n; ++i )
				for ( t = 0; t <= 1; ++t ) pos[enc(i,t)] = -1;
			for ( acc = 0, i = shift; i < 3*n; heap_push(enc(i,0)), ++i );
			for ( sz = 0, ax = 0, st = 0; cnt && processed < n; ) {
				heap_pop(&u);
				DBG(printf("Event (%.2Lf,%.2Lf) with angle %.2Lf\n",c[u>>1][u&1].x,c[u>>1][u&1].y,phi[u>>1][u&1]*180/pi));
				if ( !(u&1) ) {
					if ( seen[alias[u]>>1] == yes )
						continue ;
					DBG(printf("++Opening event (%.2Lf,%.2Lf), %.2Lf degrees\n",c[u>>1][0].x,c[u>>1][0].y,phi[u>>1][0]*180/pi));
					(!sz++)?((st++)?(ax+=(phi[u>>1][0]-last_phi)):(u0=u)):1;
					heap_push(u^1), seen[alias[u]>>1] = yes;
				}
				else {
					DBG(printf("--Closing event (%.2Lf,%.2Lf), %.2Lf degrees\n",c[u>>1][1].x,c[u>>1][1].y,phi[u>>1][1]*180/pi));
					if ( ++processed && !--sz )
						last_phi = phi[u>>1][1];
				}
				if ( u != u0 ) {
					assert(fabs(phi[u>>1][u&1]-prev)<tol||phi[u>>1][u&1]>prev);
					acc += (phi[u>>1][u&1]-prev);
				}
				prev = phi[u>>1][u&1], uu = u;
			}
			ax += max(0,2*pi-acc);
			if ( processed == n ) {
				DBG(printf("ax = %.2Lf\n",ax*180/pi));
				w = max(w,acc);
			}
		}
		w = min(2*pi,w);
		*/
		printf("Case %d: %.2Lf%%\n",++cs,((2*pi-w)/(2*pi))*100+tol);
	}
	return 0;
}

