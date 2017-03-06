/*
 * 272. TeX Quotes
 * status: Accepted
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FG (ptr = fgets(buff,sizeof(buff),stdin))

char buff[1<<21],*ptr,t;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for(;FG;putchar(*ptr))
		for(;*ptr&&*ptr!='\n';++ptr)
			*ptr=='"'?printf(t?"\'\'":"``"),t^=1:putchar(*ptr);
	return 0;
}
