/*
 * 10186. Euro Cup 2000
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 21
enum { LOSS, TIE, WIN };
enum { IN, OUT };

int max( int x, int y ) {
	if ( x < y )
		return y;
	return x;
}

int min( int x, int  y ) {
	if ( x < y )
		return x;
	return y;
}

char nm[N][0x400];
unsigned int M;
int n,cs,games,g[2][N][N],
	nx[N][N],goals[2][N],score[N],
	pelit,outcome[N],
	x[N],y[N],worst[N],best[N];

typedef struct {
	int score,id;
}team;

team c[N];

void swp( team *a, team *b ) {
	int tmp;
	tmp = a->id, a->id = b->id, b->id = tmp;
	tmp = a->score, a->score = b->score, b->score = tmp;
}

void model_it() {
	int i,j,k,left,right;
	for ( i = 0; i < n; ++i )
		c[i].id = i, c[i].score = score[i];
	for ( k = 0; k < pelit; ++k ) {
		i = x[k], j = y[k];
		if ( outcome[k] == LOSS ) 
			c[j].score += 3;
		else if ( outcome[k] == TIE )
			c[j].score += 1, c[i].score += 1;
		else c[i].score += 3;
	}
	for ( j = 1; j;)
		for ( j = i = 0; i < n-1; ++i )
			if ( c[i].score < c[i+1].score )
				++j, swp(c+i,c+i+1);
	for ( i = j = 0; i < n; i = j ) {
		for (;j < n && c[j].score == c[i].score; ++j );
		left = i, right = j-1;
		for ( k = left; k <= right; ++k ) {
			best[c[k].id] = min(best[c[k].id],left);
			worst[c[k].id] = max(worst[c[k].id],right);
		}
	}
}

int which_team( char *a ) {
	int i;
	for ( i = 0; i < n; ++i )
		if ( strcmp(a,nm[i]) == 0 )
			return i;
	assert( 0 );
}

int main() {
	int i,j,k,ti,tj,t;
	char a[0x400],b[0x400];
	unsigned int u,v;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( 1 == scanf("%d",&n) && n > 0 && printf("Group #%d\n",++cs) ) {
		for ( i = 0; i < n; scanf("%s",nm[i++]) );
		for ( i = 0; i < n; ++i )
			for ( score[i] = 0, goals[IN][i] = goals[OUT][i] = 0, j = 0; j < n; ++j )
				nx[i][j] = -1;
		for ( t = 0; t <= 1; ++t )
			for ( i = 0; i < n; ++i )
				for ( j = 0; j < n; ++j )
					g[t][i][j] = -1;
		for ( scanf("%d",&games), k = 0; k < games; ++k ) {
			scanf("%s %s %d %d",a,b,&i,&j);
			ti = which_team(a), tj = which_team(b);
			assert( (++nx[ti][tj]) <= 1 );
			assert( (++nx[tj][ti]) <= 1 );
			assert( ti != tj );
			t = nx[ti][tj];
			goals[IN][ti] += j, goals[IN][tj] += i;
			goals[OUT][ti] += i, goals[OUT][tj] += j;
			if ( i == j ) {
				g[t][ti][tj] = g[t][tj][ti] = TIE;
				++score[ti], ++score[tj];
				continue ;
			}
			if ( i > j ) {
				g[t][ti][tj] = WIN, g[t][tj][ti] = LOSS;
				score[ti] += 3;
				continue ;
			}
			g[t][ti][tj] = LOSS, g[t][tj][ti] = WIN;
			score[tj] += 3;
		}
		for ( pelit = 0, i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				for ( t = nx[i][j]; (++t) <= 1; x[pelit] = i, y[pelit] = j, ++pelit );
		assert( pelit <= 10 );
		for ( i = 0; i < n; ++i )
			best[i] = 2*n, worst[i] = -1;
		for ( M = 1, k = 0; k < pelit; M *= 3, ++k );
		for ( u = 0; u < M; ++u ) {
			for ( v = u, i = 0; i < pelit; outcome[i++] = (v%3), v /= 3 );
			model_it();
		}
		for ( i = 0; i < n; ++i )
			printf("%s %d-%d\n",nm[i],best[i]+1,worst[i]+1);
		putchar('\n');
	}
	return 0;
}
