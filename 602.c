/*
 * 602. What Day Is It?
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
typedef struct { int d,m,y,w; } cell;
#define Q (1 << 14)

int month,days,year,
	lim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *nm[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"},
	 *wdays[7] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
cell r[Q],*ptr;

void display( cell *c ) {
	printf("%s %d, %d is %s\n",nm[c->m],c->d,c->y,wdays[c->w]);
}

int gregory( int y ) {
		/*
	if ( y % 4 )
		return 0;
	else if ( y % 100 )
		return 1;
	else if ( (y % 400) == 0 )
		return 1;
	else return 0;
	*/
		return ((!(y%4) && y%100) || !(y%400));
}

void cp( cell *dst, cell *src ) {
	dst->d = src->d, dst->m = src->m, dst->y = src->y, dst->w = src->w;
}

int julain_leap( int y ) { return !(y%4); }

int is_leap( int y ) {
	if ( y <= 1752 )
		return julain_leap(y);
	return gregory(y);
}

void prev( cell *c ) {
	c->w = (c->w+6) % 7;
	/*
	if ( c->d == 15 && c->m == 9 && c->y == 1582 ) {
		c->d = 4;
		return ;
	}
	*/
	if ( c->d == 14 && c->m == 8 && c->y == 1752 ) {
		c->d = 2;
		return ;
	}
	if ( c->d == 1 && c->m == 2 ) {
		c->m = (c->m+11) % 12;
		if ( is_leap(c->y) )
			c->d = 29;
		else c->d = 28;
	}
	else {
		if ( (--c->d) == 0 )
			c->d = lim[c->m = (c->m+11)%12];
		if ( c->d == 31 && c->m == 11 )
			--c->y;
	}
}

void next( cell *c ) {
	c->w = (c->w+1) % 7;
	/*
	if ( c->d == 4 && c->m == 9 && c->y == 1582 ) {
		c->d = 15;
		return ;
	}
	*/
	if ( c->d == 2 && c->m == 8 && c->y == 1752 ) {
		c->d = 14;
		return ;
	}
	if ( c->m == 1 && c->d == 29 ) {
		c->m = 2, c->d = 1;
		return ;
	}
	if ( c->m == 1 && c->d == 28 ) {
		if ( is_leap(c->y) )
			c->d = 29;
		else c->d = 1, c->m = 2;
	}
	else {
		if ( (++c->d) == lim[c->m]+1 )
			c->d = 1, c->m = (c->m+1) % 12;
		if ( c->d == 1 && c->m == 0 )
			++c->y;
	}
}

int invalid_date( cell *c ) {
	if ( c->y <= -1 ) return 1;
	if ( c->m <= -1 ) return 1;
	if ( c->d <= 0 ) return 1;
	/*
	if ( c->y == 1582 && c->m == 9 ) 
		return 5 <= c->d && c->d <= 14;
		*/
	if ( c->y == 1752 && c->m == 8 )
		return 3 <= c->d && c->d <= 13;
	if ( c->m == 1 ) 
		return (c->d >= 29 && !is_leap(c->y))||is_leap(c->y) && c->d >= 30;
	return !(0 <= c->m && c->m <= 11 && 1 <= c->d && c->d <= lim[c->m]);
}

cell G,NY;

int cmp ( cell *a, cell *b ) {
	if ( a->y == b->y ) {
		if ( a->m == b->m ) {
			if ( a->d == b->d )
				return 0;
			return a->d < b->d ? -1 : 1;
		}
		return a->m < b->m ? -1 : 1;
	}
	return a->y < b->y ? -1 : 1;
}

void f( cell *c ) {
	cell e;
	int days,leap_years,y,k;
	if ( cmp(c,&NY) <= 0 ) {
		for ( cp(&e,&NY); cmp(&e,c); prev(&e) );
		assert( 0 == cmp(&e,c) );
		c->w = e.w;
		return ;
	}
	if ( c->y-NY.y <= 2 ) {
		for ( cp(&e,&NY); cmp(&e,c) < 0; next(&e) );
		assert( 0 == cmp(&e,c) );
		c->w = e.w;
		return ;
	}
	k = (c->y-1-1756)/4;
	leap_years = k+1, y = c->y-1756-leap_years;
	days = 366*leap_years + y*365;
	e.w = (NY.w+days) % 7;
	e.d = 1, e.m = 0, e.y = c->y-1;
	for ( ;cmp(&e,c); next(&e) );
	c->w = e.w;
}

int main() {
	cell c,e;
	int i,high,low,mid;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	G.y = 1752, G.d = 14, G.m = 8, G.w = 3;
	for ( cp(&NY,&G); !(NY.m == 11 && NY.d == 31 && NY.y == 1755); next(&NY) );
	next(&NY);
	e.d = 1, e.m = 0, e.y = 0, f(&e);
	for ( ptr = r, cp(ptr++,&e); ptr-r < Q; cp(ptr++,&e) )
		for ( i = 500; i--; next(&e) );
	while ( 3 == scanf("%d %d %d",&month,&days,&year) && !(month==0&&days==0&&year==0) ) {
		c.d = days, c.m = --month, c.y = year;
		if ( invalid_date(&c) ) {
			printf("%d/%d/%d is an invalid date.\n",month+1,days,year);
			continue ;
		}
		/*printf("Received date: "), display(&c);*/
		for ( low = 0, high = Q; low+1 < high; ) {
			mid = (low+high)/2;
			cmp(r+mid,&c)<0?(low=mid):(high=mid);
		}
		assert( cmp(r+high,&c) >= 0 );
		for ( cp(&e,r+high); cmp(&e,&c); prev(&e) );
		c.w = e.w;
		assert( c.m >= 0 && c.m <= 11 && c.w >= 0 && c.w <= 6 );
		printf("%s %d, %d is a %s\n",nm[c.m],c.d,c.y,wdays[c.w]);
	}
	return 0;
}

