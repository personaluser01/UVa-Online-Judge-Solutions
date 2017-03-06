#include <stdio.h>
long long a,b,c;
int main(){
	for(;3==scanf("%lld %lld %lld",&a,&b,&c)&&(a||b||c);puts(a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a?"right":"wrong"));
	return 0;
}

