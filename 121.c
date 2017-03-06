/*
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tol 1e-7
#define pi (2*acos(0.0))
enum { GRID, SKEW };

double n[2],a,b;
char *Pat[] = {"grid","skew"};

int main() {
	int mm,nn,t,
		max_so_far,pattern,
		rows,cols,pipes;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	while ( 2 == scanf("%lf %lf",n,n+1) ) {
		mm = (int)(0[n]+tol), nn = (int)(1[n]+tol);
		/*
		 * grid pattern
		 */
		max_so_far = mm*nn, pattern = GRID;
		/*
		 * Skew Pattern 1
		 */
		for ( t = 0; t <= 1; ++t ) {
			a = n[t], b = n[t^1];
			cols = (int)(a+tol), rows = (int)(b/cos(pi/6)+tol);
			if ( !(rows & 1) ) {
				pipes = (rows/2)*(cols+cols-1);
			}
			else {
				pipes = ((rows+1)/2)*cols + ((rows-1)/2)*(cols-1);
			}
			if ( pipes > max_so_far )
				max_so_far = pipes, pattern = SKEW;

			if ( cols+0.5 > n[t] )
				continue ;

			pipes = cols*rows;
			if ( pipes > max_so_far )
				max_so_far = pipes, pattern = SKEW;
		}
		printf("%d %s\n",max_so_far,Pat[pattern]);
	}
	return 0;
}

