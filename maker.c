#include <stdio.h>
#include <stdlib.h>
#define N 50
#define R 31

char *s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int n,m[N][N],left[N];

int main() {
	int i,j,k,l,t,ts = 200;
	for ( t = 0; t < ts; ++t ) {
		n = 1+(rand()%9);
		for ( i = 0; i < n; ++i )
			for ( j = i+1; j < n; ++j )
				m[i][j] = m[j][i] = rand() % R;
		for ( i = 0; i < n; ++i )
			for ( left[i] = 0, j = 0; j < n; ++j )
				left[i] += m[i][j];
		printf("%d\n",n);
		for ( i = 0; i < n; ++i ) {
			printf("%c %d %d %d ",s[i],rand()%13,-1,left[i]);
			for ( j = 0; j < n; ++j )
				printf("%d ",m[i][j]);
			puts("");
		}
	}
	puts("-1");
	return 0;
}

