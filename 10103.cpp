/*
 * 10103. Karpovich Blocks
 * TOPIC: dfs
 * status: Accepted
 */
#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SZ 0x10
#define Q 0x400
#define vc(x,y,z) (0<=min(x,min(y,z))&&max(x,max(y,z))<n)
typedef unsigned long long u64;
using namespace std;
enum { R=0, G=1, B=2, FREE_SPACE=3 };

const char *alph = "RGB";

int min( int x, int y ) { return x<y?x:y; }
int max( int x, int y ) { return x>y?x:y; }

int n,c[3][Q],len[3],seen[SZ][SZ][SZ],yes,the_other_color;
vector<int> sample;
set<u64> S;
char tmp[SZ][SZ][SZ],value[256],
	 dx[] = {0, 0, 0,0,-1,1},
	 dy[] = {-1,1, 0,0, 0,0},
	 dz[] = {0, 0,-1,1, 0,0};

char cube( int x, int y, int z ) { 
	switch ( tmp[x][y][z] ) {
		case 'R': return R;
		case 'G': return G;
		case 'B': return B;
		default:  return FREE_SPACE;
	}
}

void floodfill( int x, int y, int z, char col ) {
	int nx,ny,nz,i;
	assert( cube(x,y,z) == col );
	for ( seen[x][y][z] = yes, i = 0; i < 6; ++i )
		if ( vc(nx=x+dx[i],ny=y+dy[i],nz=z+dz[i]) )
			if ( seen[nx][ny][nz] != yes )
				if ( cube(nx,ny,nz) == col )
					floodfill(nx,ny,nz,col);
	c[col][len[col]++] = x|(y<<4)|(z<<8);
}

int can_remove( int t, int dir ) {
	int i,dist,x,y,z,nx,ny,nz;
	for ( dist = 1; dist <= n+n+n; ++dist ) 
		for ( i = 0; i < len[t]; ++i ) {
			x=(c[t][i]&0xf),y=((c[t][i]>>4)&0xf),z=c[t][i]>>8;
			nx = x+dx[dir]*dist, ny = y+dy[dir]*dist, nz = z+dz[dir]*dist;
			if ( vc(nx,ny,nz) && cube(nx,ny,nz) != t )
				return 0;
		}
	return 1;
}

int is_solution( int *p, int m ) {
	int i,x,y,z,all_out = 1;
	for ( i = 0; i < m; ++i ) {
		x = (p[i]&0xf), y = ((p[i]>>4)&0xf), z = (p[i]>>8);
		if ( x-n > n || y-n > n || z-n > n || -x > n || -y > n || -z > n )
			return 1;
		if ( vc(x,y,z) ) all_out = 0;
	}
	return all_out;
}

u64 fingerprint( int col, int *p ) {
	u64 u = 0;
	for ( int i = 0; i < (int)sample.size(); ++i )
		u |= (((u64)p[sample[i]])<<(12*i));
	return u;
}

int dfs( int col, int *p, int last_dir ) {
	int i,j,k,dir,x,y,z,nx,ny,nz,pos[0x400],*ptr;
	if ( is_solution(p,len[col]) )
		return 1;

	u64 u = fingerprint(col,p);

	if ( S.count(u) ) return 0;

	for ( S.insert(u), dir = 0; dir < 6; ++dir ) {

		if ( last_dir == (dir^1) ) continue ;

		for ( i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			nx=x+dx[dir], ny=y+dy[dir], nz=z+dz[dir];
			if ( vc(nx,ny,nz) && cube(nx,ny,nz) == the_other_color ) break ;
		}

		if ( i < len[col] ) continue ;

		for ( ptr = pos, i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			nx = x+dx[dir], ny = y+dy[dir], nz = z+dz[dir];
			*ptr++ = nx|(ny<<4)|(nz<<8);
		}

		for ( i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			tmp[x][y][z] = '.';
		}
		for ( i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			nx = x+dx[dir], ny = y+dy[dir], nz = z+dz[dir];
			tmp[nx][ny][nz] = alph[col];
		}
		if ( dfs(col,pos,dir) ) return 1;
		for ( i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			nx = x+dx[dir], ny = y+dy[dir], nz = z+dz[dir];
			tmp[nx][ny][nz] = '.';
		}
		for ( i = 0; i < len[col]; ++i ) {
			x=(p[i]&0xf), y=((p[i]>>4)&0xf), z=(p[i]>>8);
			tmp[x][y][z] = alph[col];
		}
	}
	return 0;
}

int main() {
	int i,j,k,t,l,dir,ok,K;
	char out[8],*ptr,LIM=5;
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	for ( i = R; i <= B; value[alph[i]] = i, ++i );
	for (;1 == scanf("%d",&n) && n;) {
		for ( k = 0; k < n; ++k )
			for ( j = 0; j < n; ++j )
				scanf("%s",tmp[k][j]);
		for ( k = R; k <= B; len[k++] = 0 );
		for ( ++yes, t = 0, i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < n; ++k )
					if ( seen[i][j][k] != yes ) 
						floodfill(i,j,k,cube(i,j,k)), ++t;
		assert( t <= 3 );
		0 && printf("t = %d\n",t);
		0 && printf("%d %d %d vs %d\n",len[R],len[G],len[B],n*n*n);
		assert( len[R]+len[G]+len[B] == n*n*n );
		for ( l = -1, t = R; t <= B && l == -1; ++t ) 
			for ( dir = 0; dir < 6 && l == -1; ++dir )
				if ( can_remove(t,dir) ) 
					l = t, K = dir;
		if ( l == -1 ) {
			NO: puts("NO");
			continue ;
		}
		ptr = out, *ptr++ = alph[l];
		for ( i = 0; i < n; ++i )
			for ( j = 0; j < n; ++j )
				for ( k = 0; k < n; ++k )
					if ( cube(i,j,k) == l )
						tmp[i][j][k] = '.';
		0 && printf("This one can be removed first: %c, in the direction (%d,%d,%d)\n",out[0],dx[K],dy[K],dz[K]);
		for ( ok = 0, t = R; t <= B && !ok; ++t )
			if ( t != l ) {
				the_other_color = R+G+B-t-l;
				sample.clear(), S.clear();
				for ( i = 0; i < LIM; ++i )
					sample.push_back(abs(rand()%len[t]));
				ok |= dfs(t,c[t],6);
				break ;
			}
		if ( !ok ) { printf("%c\n",alph[l]); continue; };
		puts("RGB");
		/*
		if ( ok ) *ptr++ = alph[--t], *ptr++ = alph[the_other_color], *ptr = '\0';
		else *ptr = '\0';
		for ( j = 1; j; )
			for ( i = j = 0; i < ptr-out-1; ++i )
				if ( value[out[i]] > value[out[i+1]] )
					k = out[i], out[i] = out[i+1], out[i+1] = k, ++j;
		puts(out);
		*/
	}
	return 0;
}

