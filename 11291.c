/*
 * 11291. Smeech
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
#define FG (ptr=fgets(buff,sizeof(buff),stdin))
char buff[0x4000],*ptr;
void skip_space() {	while ( isspace(*ptr) && *ptr != '\n' && *ptr ) ++ptr; }
int empty( char *p ) { return *p=='(' && *(p+1)==')' && (*(p+2)=='\n'||*(p+2)=='\0'); }

long double f() {
	long double p,x,y;
	int cn;
	skip_space();
	if ( *ptr == '(' ) {
		++ptr, sscanf(ptr,"%Lf%n",&p,&cn), ptr += cn, x = f(), y = f();
		/*printf("Read this %.1Lf\n",p);*/
		skip_space();
		assert( *ptr++ == ')' );
		return p*(x+y)+(1-p)*(x-y);
	}
	sscanf(ptr,"%Lf%n",&x,&cn), ptr += cn;
	/*printf("Read this %d\n",x);*/
	return x;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	while ( FG && !empty(ptr) && printf("%.2Lf\n",f()) );
	return 0;
}

