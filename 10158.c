/*
 * 10158. War
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10002

int rank[N],p[N],e[N],n;

void make_set( int x ) { rank[x] = 1, p[x] = x, e[x] = 0; }
int find( int x ) { return p[x]=(p[x]==x)?x:find(p[x]); }
void link( int x, int y ) {
	assert( find(x) == x && find(y) == y );
	if ( !e[x] ) e[x] = e[y];
	if ( !e[y] ) e[y] = e[x];
	if ( rank[x] > rank[y] ) {
		p[y] = x;
	}
	else {
		p[x] = y;
		if ( rank[x] == rank[y] ) ++rank[y];
	}
}
void merge( int x, int y ) {
	link(find(x),find(y));
}

int F( int x ) {
	return e[x]=(p[x]==x)?e[x]:F(find(x));
}

int are_enemies(int,int);
int are_friends(int,int);
int can_be_friends(int,int);
int can_be_enemies(int,int);
int set_friends(int,int);
int set_enemies(int,int);

int are_enemies( int x, int y ) {
	if ( x == y )
		return 0;
	if (!F(x)||!F(y))
		return 0;
	return are_friends(F(x),y)||are_friends(F(y),x);
}

int are_friends( int x, int y ) {
	return find(x)==find(y);
}

int can_be_friends( int x, int y ) {
	if ( are_enemies(x,y) )
		return 0;
	if ( are_friends(x,y) )
		return 1;
	if ( F(x) && F(y) ) {
		if ( are_enemies(F(x),F(y)) )
			return 0;
	}
	return 1;
}

int can_be_enemies( int x, int y ) {
	if ( are_friends(x,y) )
		return 0;
	if ( are_enemies(x,y) )
		return 1;
	if ( F(x) && F(y) ) {
		if ( are_friends(F(x),F(y)) )
			return 0;
	}
	return 1;
}

int set_friends( int x, int y ) {
	int ex,ey;
	if ( !can_be_friends(x,y) )
		return 0;
	ex = F(x), ey = F(y);
	merge(x,y);
	if ( ex && ey ) 
		merge(ex,ey);
	return 1;
}

int set_enemies( int x, int y ) {
	if ( !can_be_enemies(x,y) )
		return 0;
	if ( !F(x) )
		e[find(x)] = find(y);
	if ( !F(y) )
		e[find(y)] = find(x);
	set_friends(F(x),y);
	set_friends(F(y),x);
	return 1;
}

int main() {
	int x,y,op;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d",&n);
	for ( x = 1; x <= n; make_set(x++) );
	while ( 3 == scanf("%d %d %d",&op,&x,&y) ) {
		if ( op == 0 && x == 0 && y == 0 )
			break ;
		++x, ++y;
		if ( op == 1 ) {
			if ( !set_friends(x,y) )
				puts("-1");
		}
		else if ( op == 2 ) {
			if ( !set_enemies(x,y) )
				puts("-1");
		}
		else if ( op == 3 ) {
			puts(are_friends(x,y) ? "1":"0");
		}
		else {
			puts(are_enemies(x,y) ? "1":"0");
		}
	}
	return 0;
}

