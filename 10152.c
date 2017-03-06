/*
 * 10152. Shell Sort
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x100
#define L 0x100
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))

int ts,n,place[N],c[N];
char nm[N][L],name[N][L];

void rev( int k ) {
	int i,j;
	for ( i = 0, j = k-2; i < j; ++i, --j )
		xchg(c[i],c[j]), xchg(place[c[i]],place[c[j]]);
	for ( i = 0, j = k-1; i < j; ++i, --j )
		xchg(c[i],c[j]), xchg(place[c[i]],place[c[j]]);
}

int main() {
	int i,j,k,m,M,l;
	char tmp[0x400];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( scanf("%d",&ts); ts-- && scanf("%d\n",&n); putchar('\n') ) {
		for ( i = 0; i < n; ++i ) 
			fgets(nm[i],sizeof(nm[i]),stdin);
		for ( i = 0; i < n; ++i ) {
			fgets(tmp,sizeof(tmp),stdin);
			for ( j = 0; j < n; ++j )
				if ( strcmp(nm[j],tmp) == 0 ) {
					place[c[j] = i] = j;
					goto nx;
				}
			assert( 0 );
			nx: continue ;
		}
		for ( i = 0; i < n; ++i )
			strcpy(name[i],nm[place[i]]);
		for ( ;;) {
			for ( j = 0, k = 0; k < n; ++k )
				if ( c[k] != k && ++j );
			if ( !j ) break ;
			for ( M = -(1<<29),i = 0; i < n; i = j+1 ) {
				for ( j = i; j+1 < n && c[j+1] > c[j]; ++j );
				if ( j+1 < n ) {
					for ( l = j+1; l < n && c[l] < c[j]; ++l )
						if ( M < c[l] )
							M = c[k = l];
				}
			}
			printf("%s",name[c[k]]);
			rev(k+1);
		}
	}
	return 0;
}
