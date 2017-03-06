/*
 * 172. Calculator Language
 */
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#define N 32
#define FG (ptr = fgets(buff,sizeof(buff),stdin))
#include <stack>
#include <queue>
#include <vector>
using namespace std;

int val[2][N],t;
char buff[0x400],*ptr;

void remove_spaces() {
	char tmp[0x400],*qtr = tmp,*str;
	for (;*ptr && *ptr != '\n'; ++ptr )
		if ( !isspace(*ptr) )
			*qtr++ = *ptr;
	for ( ptr = buff, str = tmp; str < qtr; *ptr++ = *str++ );
	*ptr = '\0';, ptr = buff;
}

int perform( int x, int y, char ch ) {
	if ( ch == '+' )
		return x+y;
	if ( ch == '-' )
		return x-y;
	if ( ch == '*' )
		return x*y;
	assert( ch == '/' );
	assert( y );
	return x/y;
}

int get_num() {
	int n = 0;
	while ( *ptr && *ptr != '\n' && isdigit(*ptr) )
		n = 10*n + *ptr++ - '0';
	return n;
}

int eval() {
	stack<int> v;
	stack<char> op;
	char ch;
	int i,j,k;

	for ( v.push(0);; ) {
		if ( isdigit(*ptr) ) {
			k = get_num();
			v.push(k);
		}
		else if ( isupper(*ptr) ) {
			k = val[t^1][*ptr-'A'];
			v.push(k);
		}
		else if ( *ptr == '(' ) {
			++ptr, v.push(eval());
			assert( *ptr++ == ')' );
		}
		else {
			assert( *ptr == '+' || *ptr == '-' ||\
					*ptr == '*' || *ptr == '/' );
			op.push(*ptr++);
		}
	}
	while ( !op.empty() ) {
		ch = op.top(), op.pop();
		j = v.top(), v.pop();
		i = v.top(), v.pop();
		v.push(perform(i,j,ch));
	}
	k = v.top(), v.pop();
	return k;
}

int main() {
	int i,j,k;
	vector<int> vec;
	for ( t = 0; FG; t ^= 1 ) {
		remove_spaces();
		for ( vec.clear(), parse(), i = 0; i < 26; ++i )
			if ( val[t][i] != UNDEF && val[t][i] != val[t^1][i] )
				vec.push(i);
		if ( vec.size() == 0 )
			puts("No Change");
		else if ( vec.size() == 1 ) 
			printf("%c = %d\n",vec[0]+'A',val[t][vec[0]]);
		else {
			for ( i = 0; i+1 < (int)vec.size(); ++i )
				printf("%c = %d, ",vec[i]+'A',val[t][vec[i]]);
			printf("%c = %d\n",vec[i],val[t][vec[i]]);
		}
	}
	return 0;
}

