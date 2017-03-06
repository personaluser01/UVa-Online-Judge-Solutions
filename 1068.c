/*
 * 1068. Air Conditioning Machinery
 * TOPIC: backtracking
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 21
#define enc(x,y,z,dir) ((x) | ((y)<<5) | ((z)<<10) | ((dir)<<15))
#define BIT(k) (1ULL << (k))
#define MASK(k) (BIT(k)-1ULL)
#define Q (BIT(21))
#define vc(x,y,z) (1<=(x)&&(x)<=m&&1<=(y)&&(y)<=n&&1<=(z)&&(z)<=p)
#define X(u) ((u)&31)
#define Y(u) (((u)>>5)&31)
#define Z(u) (((u)>>10)&31)
#define oo 0xfffffffful
enum { xm, xp, ym, yp, zm, zp };
typedef unsigned int state;
/*
 * -x: 0
 * +x: 1
 * -y: 2
 * +y: 3
 * -z: 4
 * +z: 5
 */

typedef unsigned long long u64;
int m,n,p,seen[Q],yes,used[W][W][W],indeed,best,DX,DY,DZ;
int dx[] = {-3,-3,-3,-3,-2,-2,-2,-2,    3,3,3,3,2,2,2,2, 		 -1, 0, 1, 0,-2, 0, 2, 0,   -1, 0, 1, 0,-2, 0, 2, 0,   -1,0, 1, 0,-2, 0, 2, 0,   -1,0,1,0,-2,0,2,0};
int dy[] = {-1, 0, 1, 0, -2, 0, 2,0,    -1,0,1,0,-2,0,2,0,       -3,-3,-3,-3,-2,-2,-2,-2,     3,3,3,3,2,2,2,2, 		   0,-1, 0, 1, 0,-2, 0, 2,    0,-1,0,1,0,-2,0,2};
int dz[] = {0, -1, 0, 1, 0,-2, 0, 2,    0,-1,0,1,0,-2,0,2,        0,-1, 0, 1, 0,-2, 0, 2,     0, -1, 0, 1, 0,-2, 0, 2,  -3,-3,-3,-3,-2,-2,-2,-2,  3,3,3,3,2,2,2,2};
int dt[] = {ym,zm,yp,zp,ym,zm,yp,zp,   ym,zm,yp,zp,ym,zm,yp,zp,  xm,zm,xp,zp,xm,zm,xp,zp,   xm,zm,xp,zp,xm,zm,xp,zp,   xm,ym,xp,yp,xm,ym,xp,yp,  xm,ym,xp,yp,xm,ym,xp,yp};


void fill_region( int x, int y, int z, int k ) {
	int nx = x+dx[k], ny = y+dy[k], nz = z+dz[k],
		sx,sy,sz,cx,cy,cz;
	if ( nx == x ) sx = 0; else if ( nx < x ) sx = -1; else sx = 1;
	if ( ny == y ) sy = 0; else if ( ny < y ) sy = -1; else sy = 1;
	if ( nz == z ) sz = 0; else if ( nz < z ) sz = -1; else sz = 1;
	if ( k/16 == 0 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cx != nx+sx; cx += sx )
			used[cx][cy][cz] = indeed;
		for ( cx -= sx ;(!sy || cy != ny+sy) && (!sz || cz != nz+sz);  cy += sy, cz += sz )
			used[cx][cy][cz] = indeed;
	}
	else if ( k/16 == 1 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cy != ny+sy; cy += sy )
			used[cx][cy][cz] = indeed;
		for ( cy -= sy ;(!sx || cx != nx+sx) && (!sz || cz != nz+sz);  cx += sx, cz += sz )
			used[cx][cy][cz] = indeed;
	}
	else {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cz != nz+sz; cz += sz )
			used[cx][cy][cz] = indeed;
		for ( cz -= sz ;(!sy || cy != ny+sy) && (!sx || cx != nx+sx);  cy += sy, cx += sx )
			used[cx][cy][cz] = indeed;
	}
}

void clear_region( int x, int y, int z, int k ) {
	int nx = x+dx[k], ny = y+dy[k], nz = z+dz[k],
		sx,sy,sz,cx,cy,cz;
	if ( nx == x ) sx = 0; else if ( nx < x ) sx = -1; else sx = 1;
	if ( ny == y ) sy = 0; else if ( ny < y ) sy = -1; else sy = 1;
	if ( nz == z ) sz = 0; else if ( nz < z ) sz = -1; else sz = 1;
	if ( k/16 == 0 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cx != nx+sx; cx += sx )
			used[cx][cy][cz] = 0;
		for ( cx -= sx ;(!sy || cy != ny+sy) && (!sz || cz != nz+sz);  cy += sy, cz += sz )
			used[cx][cy][cz] = 0;
	}
	else if ( k/16 == 1 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cy != ny+sy; cy += sy )
			used[cx][cy][cz] = 0;
		for ( cy -= sy ;(!sx || cx != nx+sx) && (!sz || cz != nz+sz);  cx += sx, cz += sz )
			used[cx][cy][cz] = 0;
	}
	else {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cz != nz+sz; cz += sz )
			used[cx][cy][cz] = 0;
		for ( cz -= sz ;(!sy || cy != ny+sy) && (!sx || cx != nx+sx);  cy += sy, cx += sx )
			used[cx][cy][cz] = 0;
	}
}

int impermeable( int x, int y, int z, int k ) {
	int nx = x+dx[k], ny = y+dy[k], nz = z+dz[k],
		sx,sy,sz,cx,cy,cz;
	if ( nx == x ) sx = 0; else if ( nx < x ) sx = -1; else sx = 1;
	if ( ny == y ) sy = 0; else if ( ny < y ) sy = -1; else sy = 1;
	if ( nz == z ) sz = 0; else if ( nz < z ) sz = -1; else sz = 1;
	if ( k/16 == 0 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cx != nx+sx; cx += sx )
			if ( used[cx][cy][cz] == indeed ) 
				return 1;
		for ( cx -= sx ;(!sy || cy != ny+sy) && (!sz || cz != nz+sz);  cy += sy, cz += sz )
			if ( used[cx][cy][cz] == indeed ) 
				return 1;
		return 0;
	}
	else if ( k/16 == 1 ) {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cy != ny+sy; cy += sy )
			if ( used[cx][cy][cz] == indeed )
				return 1;
		for ( cy -= sy ;(!sx || cx != nx+sx) && (!sz || cz != nz+sz);  cx += sx, cz += sz )
			if ( used[cx][cy][cz] == indeed )
				return 1;
		return 0;
	}
	else {
		for ( cx = x+sx, cy = y+sy, cz = z+sz; cz != nz+sz; cz += sz )
			if ( used[cx][cy][cz] == indeed )
				return 1;
		for ( cz -= sz ;(!sy || cy != ny+sy) && (!sx || cx != nx+sx);  cy += sy, cx += sx )
			if ( used[cx][cy][cz] == indeed )
				return 1;
		return 0;
	}
}

void f( const state dst, state u, int cost ) {
	int dir,x,y,z,l,nx,ny,nz;
	if ( u == dst && best > cost ) best = cost;
	if ( DX == X(u) && DY == Y(u) && DZ == Z(u) || cost >= 7 ) return ;
	for ( x=X(u),y=Y(u),z=Z(u),dir=(u>>15), l = dir*8; l < (dir+1)*8 && cost < best; ++l ) {
		if ( !vc(nx=x+dx[l],ny=y+dy[l],nz=z+dz[l]) || impermeable(x,y,z,l) ) continue ;
	   	fill_region(x,y,z,l);
		f(dst,enc(nx,ny,nz,dt[l]),cost+1);
		clear_region(x,y,z,l);
	}
}

int conv( char *s ) {
	if ( 0 == strcmp(s,"-x") ) return xm;
	if ( 0 == strcmp(s,"+x") ) return xp;
	if ( 0 == strcmp(s,"-y") ) return ym;
	if ( 0 == strcmp(s,"+y") ) return yp;
	if ( 0 == strcmp(s,"-z") ) return zm;
	if ( 0 == strcmp(s,"+z") ) return zp;
	assert( 0 );
}

int main() {
	int i,j,k,t,ix,iy,iz,ox,oy,oz,cs = 0;
	char idir[0x10],odir[0x10];
#ifndef ONLINE_JUDGE
	freopen("1068.in","r",stdin);
#endif
	while ( 3 == scanf("%d %d %d",&m,&n,&p) ) {
		scanf("%d %d %d %s",&ix,&iy,&iz,idir);
		t = conv(idir);
		if ( t == xp )
			--ix;
		else if ( t == xm )
			++ix;
		else if ( t == yp )
			--iy;
		else if ( t == ym )
			++iy;
		else if ( t == zp )
			--iz;
		else ++iz;
		scanf("%d %d %d %s",&ox,&oy,&oz,odir), DX = ox, DY = oy, DZ = oz;
		printf("Case %d: ",++cs);
		best = 7, ++indeed, f(enc(ox,oy,oz,conv(odir)),enc(ix,iy,iz,t),0);
		if ( best == 7 )
			puts("Impossible");
		else printf("%d\n",best);
	}
	return 0;
}

