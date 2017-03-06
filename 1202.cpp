/*
 * 1202. Finding Nemo
 * TOPIC: Dijkstra, coordinate compression
 * status:
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <set>
#include <map>
#include <vector>
#define N 5001
#define oo (1<<29)
#define vc(x,y) (0<=(x)&&(x)<H&&0<=(y)&&(y)<W)
#define NDEBUG
using namespace std;

int m,n,doors,walls,sx,sy,H,W,A[N],B[N],d[N][N],
	dx[N][2],dy[N][2],wx[N][2],wy[N][2];
set<double> X,Y;
vector<double> XX,YY;
double x[N][2],y[N][2],
	   xx[N][2],yy[N][2];

int getrank( vector<double> &v, double x ) {
	int i,j,k,n=v.size();
	if ( !v.size() ) return -1;
	if ( v[0]>=x ) return 0;
	if ( v[n-1]<x ) return n;
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2]<x?(i=k):(j=k));
	assert( v[i] < x );
	assert( v[j] >= x );
	return j;
}

bool empty( int l, int r ) { return l >= r; }

vector<pair<int,int> > dr[N],dc[N],wr[N],wc[N],
					   ddr[N],ddc[N],wwr[N],wwc[N];
set<pair<int,pair<int,int> > > s;

void find_union( const vector<pair<int,int> > &v, vector<pair<int,int> > &u ) {
	int i,j,k,left,right;
	for ( u.clear(), left = (1<<29), right = -(1<<29), i = 0; i < (int)v.size(); ++i ) {
		if ( v[i].first > right ) {
			if ( !empty(left,right) ) u.push_back(make_pair(left,right));
			left = v[i].first, right = v[i].second;
			continue ;
		}
		if ( v[i].second > right )
			right = v[i].second;
	}
	if ( !empty(left,right) ) u.push_back(make_pair(left,right));
}

bool inside( const pair<int,int> v, int x ) { return v.first <= x && x <= v.second; }
bool sinside( const pair<int,int> v, int x ) { return v.first < x && x < v.second; }

int on_horiz( const vector<pair<int,int> > &v, int x, int y ) {
	int i,j,k,n = v.size();
	if ( !n ) return -1;
	if ( v[n-1].second < y ) return -1;
	if ( y < v[0].first ) return -1; 
	assert( v[0].first <= y );
	if(inside(v[0],y)) return 0;
	if (inside(v[n-1],y)) return n-1;
	assert( v[n-1].first > y );
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2].first<=y?(i=k):(j=k));
	return inside(v[i],y)?i:-1;
}

int on_verti( const vector<pair<int,int> > &v, int x, int y ) {
	int i,j,k,n = v.size();
	if ( !n ) return -1;
	if ( v[n-1].second < x ) return -1;
	if ( x < v[0].first ) return -1; 
	assert( v[0].first <= x );
	if(inside(v[0],x)) return 0;
	if (inside(v[n-1],x)) return n-1;
	assert( v[n-1].first > x );
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2].first<=x?(i=k):(j=k));
	return inside(v[i],x)?i:-1;
}

int on_horiz_wall( const vector<pair<int,int> > &v, int x, int y ) {
	int i,j,k,n = v.size();
	if ( !n ) return -1;
	if ( v[n-1].second <= y ) return -1;
	if ( y <= v[0].first ) return -1; 
	assert( v[0].first < y );
	if(sinside(v[0],y)) return 0;
	if (sinside(v[n-1],y)) return n-1;
	if ( v[n-1].first == y ) return -1;
	assert( v[n-1].first > y );
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2].first<=y?(i=k):(j=k));
	return sinside(v[i],y)?i:-1;
}

int on_verti_wall( const vector<pair<int,int> > &v, int x, int y ) {
	int i,j,k,n = v.size();
	if ( !n ) return -1;
	if ( v[n-1].second <= x ) return -1;
	if ( x <= v[0].first ) return -1; 
	assert( v[0].first < x );
	if(sinside(v[0],x)) return 0;
	if (sinside(v[n-1],x)) return n-1;
	if ( v[n-1].first == x ) return -1;
	assert( v[n-1].first > x );
	for(i=0,j=n-1;i+1<j;v[k=(i+j)/2].first<=x?(i=k):(j=k));
	return sinside(v[i],x)?i:-1;
}

int is_door( int x, int y ) { return (on_horiz_wall(ddr[x],x,y)!=-1||on_verti_wall(ddc[y],x,y)!=-1)?1:0; }

bool on_same_door( int x, int y, int p, int q ) {
	int a = on_horiz_wall(ddr[x],x,y),
		b = on_horiz_wall(ddr[p],p,q),
		c = on_verti_wall(ddc[y],x,y),
		d = on_verti_wall(ddc[q],p,q);
	return (a!=-1&&a==b)||(c!=-1&&c==d);
}

map<int,double> mx,my;
set<double> V;

int main() {
	int i,j,k,direction,l,weight,dweight;
	double lx,ly,len,prev;
	bool t;
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	for(;2 == scanf("%d %d",&walls,&doors) && (doors+1||walls+1); ) {
		X.clear(), Y.clear(), X.insert(0), Y.insert(0);
		for ( i = 0; i < walls; ++i ) {
			scanf("%lf %lf %d %lf",&lx,&ly,&direction,&len);
			X.insert(lx), Y.insert(ly), X.insert(lx+(1-direction)*len), Y.insert(ly+direction*len);
			x[i][0]=lx,y[i][0]=ly,x[i][1]=(lx+(1-direction)*len),y[i][1]=(ly+direction*len);
		}
		for ( i = 0; i < doors; ++i ) {
			scanf("%lf %lf %d",&lx,&ly,&direction);
			X.insert(lx), Y.insert(ly), X.insert(lx+(1-direction)), Y.insert(ly+direction);
			xx[i][0]=lx,yy[i][0]=ly,xx[i][1]=(lx+(1-direction)),yy[i][1]=(ly+direction);
		}
		scanf("%lf %lf",&lx,&ly), X.insert(lx), Y.insert(ly);

		X.insert(-oo), X.insert(+oo), Y.insert(-oo), Y.insert(+oo);

		prev = -oo, V.clear();
		for ( set<double>::iterator it = X.begin(); it != X.end(); ++it ) 
			V.insert((prev+*it)/2), prev = *it, V.insert(*it);
		XX = vector<double>(V.begin(),V.end());
		X = set<double>(V.begin(),V.end());

		prev = -oo, V.clear();
		for ( set<double>::iterator it = Y.begin(); it != Y.end(); ++it ) 
			V.insert((prev+*it)/2), prev = *it, V.insert(*it);
		YY = vector<double>(V.begin(),V.end());
		Y = set<double>(V.begin(),V.end());

		mx.clear(), my.clear(); k =0;
		for ( set<double>::iterator it = X.begin(); it != X.end(); ++it )
			mx[k++] = *it;
		k = 0;
		for ( set<double>::iterator it = Y.begin(); it != Y.end(); ++it )
			my[k++] = *it;
		sx = getrank(XX,lx), sy = getrank(YY,ly);
		H = XX.size(), W = YY.size();
		for ( i = 0; i <= H; ++i ) dr[i].clear(), wr[i].clear();
		for ( j = 0; j <= W; ++j ) dc[j].clear(), wc[j].clear();
		for ( i = 0; i < walls; ++i ) {
			for ( j = 0; j <= 1; ++j )
				wx[i][j] = getrank(XX,x[i][j]), wy[i][j] = getrank(YY,y[i][j]);
			if ( wx[i][0] == wx[i][1] )
				wr[wx[i][0]].push_back(make_pair(wy[i][0],wy[i][1]));
			else 
				wc[wy[i][0]].push_back(make_pair(wx[i][0],wx[i][1]));
		}
		for ( i = 0; i < doors; ++i ) {
			for ( j = 0; j <= 1; ++j )
				dx[i][j] = getrank(XX,xx[i][j]), dy[i][j] = getrank(YY,yy[i][j]);
			if ( dx[i][0] == dx[i][1] )
				dr[dx[i][0]].push_back(make_pair(dy[i][0],dy[i][1]));
			else 
				dc[dy[i][0]].push_back(make_pair(dx[i][0],dx[i][1]));
		}
		for ( i = 0; i <= H; ++i ) {
			sort(wr[i].begin(),wr[i].end()),sort(dr[i].begin(),dr[i].end());
			find_union(wr[i],wwr[i]), find_union(dr[i],ddr[i]);
		}
		for ( j = 0; j <= W; ++j ) {
			sort(wc[j].begin(),wc[j].end()),sort(dc[j].begin(),dc[j].end());
			find_union(wc[j],wwc[j]), find_union(dc[j],ddc[j]);
		}
		for ( s.clear(), i = 0; i <= H; ++i )
			for ( j = 0; j <= W; ++j )
				d[i][j] = +oo;
		i = getrank(XX,0), j = getrank(YY,0);
		for ( s.insert(make_pair(d[i][j]=is_door(i,j),make_pair(i,j))); !s.empty(); ) {
			set<pair<int,pair<int,int> > >::iterator it = s.begin();
			s.erase(*it), weight = it->first, i = it->second.first, j = it->second.second;
			// printf("(%.2lf,%.2lf) weight = %d\n",mx[i],my[j],weight);
			for ( l =-1; l <= 1; ++l )
				for ( k = -1; k <= 1; ++k )
					if (abs(l)+abs(k)==1&&vc(i+l,j+k)) {
						if ( on_same_door(i,j,i+l,j+k) ) continue ;
						dweight = is_door(i+l,j+k);
						t = is_door(i+l,j+k);
						if ( !t && (on_horiz(wwr[i+l],i+l,j+k)!=-1||on_verti(wwc[j+k],i+l,j+k)!=-1) ) continue ;
						if ( d[i+l][j+k]>d[i][j]+dweight ) 
							s.insert(make_pair(d[i+l][j+k]=d[i][j]+dweight,make_pair(i+l,j+k)));
					}
		}
		printf("%d\n",d[sx][sy]<+oo?d[sx][sy]:-1);
	}
	return 0;
}


