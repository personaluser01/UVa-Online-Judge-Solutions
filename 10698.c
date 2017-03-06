/*
 * 10698. Football Sort
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#define N 0x20
#define L 0x20

int n,games;
char buff[0x400],*ptr,cname[N][L];

int get_id( char *s ) {
	int i;
	for ( i = 0; i < n; ++i )
		if ( strcmp(s,cname[i]) == 0 )
			return i;
	return -1;
}

typedef struct { int a,ax,g,id,played;}cell;

cell c[N];

int cmp( const void *x, const void *y ) {
	cell *xx = (cell *)x,
		 *yy = (cell *)y;
	if ( xx->ax == yy->ax ) {
		if ( xx->g-xx->a == yy->g-yy->a ) {
			if ( xx->g == yy->g ) {
				return strcasecmp(cname[xx->id],cname[yy->id]);
			}
			return xx->g > yy->g ? -1 : 1;
		}
		return xx->g-xx->a > yy->g-yy->a ? -1 : 1;
	}
	return xx->ax > yy->ax ? -1 : 1;
}

int rank( cell *xx, cell *yy ) {
	if ( xx->ax == yy->ax ) {
		if ( xx->g-xx->a == yy->g-yy->a ) {
			if ( xx->g == yy->g ) 
				return 0;
			return xx->g > yy->g ? -1 : 1;
		}
		return xx->g-xx->a > yy->g-yy->a ? -1 : 1;
	}
	return xx->ax > yy->ax ? -1 : 1;
}

int main() {
	int i,j,k,x,y,cs = 0,l;
	char hometeam[L],awayteam[L],s[L];
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for (;sscanf(FG,"%d %d",&n,&games)==2 && (n||games);) {
		if ( ++cs > 1 ) putchar('\n');
		for ( i = 0; i < n; sscanf(FG,"%[A-Za-z-]",cname[i++]) );
		for ( i = 0; i < n; ++i )
			c[i].a = c[i].g = c[i].ax = 0, c[i].id = i, c[i].played = 0;
		for ( k = 0; k < games; ++k ) {
			sscanf(FG,"%[A-Za-z-] %d - %d %[A-Za-z-]",hometeam,&x,&y,awayteam); 
			i = get_id(hometeam), j = get_id(awayteam);
			/*printf("home %s %d - %d away %s\n",hometeam,x,y,awayteam);*/
			c[i].g += x, c[j].g += y, c[i].a += y, c[j].a += x;
			++c[i].played, ++c[j].played;
			if ( x == y ) 
				c[i].ax += 1, c[j].ax += 1;
			else if ( x > y ) 
				c[i].ax += 3, c[j].ax += 0;
			else 
				c[j].ax += 3, c[i].ax += 0;
		}
		qsort(c,n,sizeof *c,cmp);
		for ( k = 1, i = 0; i < n; i = j, ++k ) {
			for ( j = i+1; j < n && 0 == rank(c+i,c+j); ++j );
			printf("%2d.%16s%4d%4d%4d%4d%4d%7s\n",k,cname[c[i].id],c[i].ax,c[i].played,c[i].g,c[i].a,c[i].g-c[i].a,c[i].played?sprintf(s,"%7.2lf",(c[i].ax+0.00)/(c[i].played*3)*100),s:"N/A");
			for ( l = i+1; l < j; ++l, ++k )
				printf("   %16s%4d%4d%4d%4d%4d%7s\n",cname[c[l].id],c[l].ax,c[l].played,c[l].g,c[l].a,c[l].g-c[l].a,c[l].played?sprintf(s,"%7.2lf",(c[l].ax+0.00)/(c[l].played*3)*100),s:"N/A");
		}
	}
	return 0;
}
