/*
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define N 0x400
#define FG (ptr = fgets(buff,sizeof(buff),stdin))

int empty( char *ptr ) {
	while ( *ptr && *ptr != '\n' )
		if ( !isspace(*ptr) )
			return 0;
	return 1;
}

char buff[0x400],*ptr;
int ts,f[32];

typedef struct cell {
	struct cell *para;
	char plate[0x20],tm_of_day[0x20],dir[0x10];
	int km,charge;
} cell;

cell c[N],res[N];
int m,n;

int cmp( const void *a, const void *b ) {
	cell *x = (cell *)a,
		 *y = (cell *)b;
	int t = strcmp(x->tm_of_day,y->tm_of_day),
		r = strcmp(x->plate,y->plate);
	if ( !r ) {
		if ( !t ) {
			return strcmp(x->dir,y->dir);
		}
		return t;
	}
	return r;
}

int same_day( char *s, char *t ) {
	return strncmp(s,t,5) == 0;
}

int when_began( char *s ) {
	int m,d,h,mi;
	sscanf(s,"%d:%d:%d:%d",&m,&d,&h,&mi);
	/*
	int hr = 10*(s[6]-'0')+(s[7]-'0'),
		mi = 10*(s[8]-'0')+(s[9]-'0');
	return hr;
	*/
	return h;
}

int main() {
	int i,j,k;
	char tmp[0x400],direction[0x400];
	cell *nc;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts--; ) {
		for ( i = 0; i < 24; ++i ) 
			scanf("%d\n",f+i);
		for ( n = 0; FG && !empty(ptr); ++n )  {
			sscanf(buff,"%s %s %s %d",c[n].plate,c[n].tm_of_day,c[n].dir,&c[n].km), c[n].para = NULL, c[n].charge = -1;
			for ( i = 0; c[n].dir[i]; c[n].dir[i] = tolower(c[n].dir[i]), ++i );
		}
		qsort(c,n,sizeof *c,cmp);
		for ( i = 0; i < n; ) {
			if ( c[i].para||strcmp(c[i].dir,"enter") != 0 ) {
				++i;
				continue ;
			}
			for ( j = i+1; j <= i+1; ++j )
				if ( strcmp(c[j].plate,c[i].plate) == 0 ) {
					if ( 1 )
						if ( strcmp(c[j].dir,"exit") == 0 && !c[j].para ) 
							if ( 1 ) {
								c[j].para = c+i, c[i].para = c+j;
								i = j+1;
								goto nx;
							}
				}
				else break ;
			++i;
			nx: continue ;
		}
		for ( i = 0; i < n; ++i )
			if ( nc = c[i].para ) {
				k = abs(nc->km - c[i].km);
				if ( c[i].dir[1] == 'n' )
					c[i].charge = 100 + f[when_began(c[i].tm_of_day)]*k;
				else
					c[i].charge = 100 + f[when_began(nc->tm_of_day)]*k;
				c[i].para = nc->para = NULL;
			}
		for ( m = 0, i = 0; i < n; ++i )
			if ( c[i].charge != -1 ) {
				strcpy(res[m].plate,c[i].plate);
				res[m].charge = c[i].charge, c[i].charge = -1;
				for ( j = i+1; j < n; ++j ) 
					if ( strcmp(c[j].plate,c[i].plate) != 0 ) 
						break ;
					else if ( c[j].charge != -1 )
						res[m].charge += c[j].charge, c[j].charge = -1;
				++m;
			}
		qsort(res,m,sizeof *res,cmp);
		for ( i = 0; i < m; ++i ) {
			res[i].charge += 200;
			printf("%s $%d.%02d\n",res[i].plate,res[i].charge/100,res[i].charge%100);
		}
		if ( ts ) putchar('\n');
	}
	return 0;
}
