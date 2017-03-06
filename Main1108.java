/*
 * 1108. Mining Your Own Business
 * TOPIC: graphs, articulation points, dfs
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int MAXN = (1<<18), MAXE = 2*MAXN, WHITE = 0, GREY = 1, BLACK = 2, oo = (1<<29);
	int m,n,E,yes;
	long w,usedn;
	int []last = new int[MAXN], next = new int[MAXE], to = new int[MAXE], p = new int[MAXN], used = new int[MAXN], deg = new int[MAXN];
	int []height = new int[MAXN], depth = new int[MAXN], color = new int[MAXN];
	boolean []isArticulationPoint = new boolean[MAXN];
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void addArcs( int x, int y ) {
		int i = E++, j = E++;
		to[i] = y; next[i] = last[x]; last[x] = i;
		to[j] = x; next[j] = last[y]; last[y] = j;
		n = Math.max(n,x+1);
		n = Math.max(n,y+1);
		used[x] = used[y] = yes;
		++deg[x]; ++deg[y];
	}
	void dfs( int x, int d ) {
		int i,y,son = 0;
		assert color[x] == WHITE;
		// System.out.println((x+1)+" of depth "+d);
		for ( color[x] = GREY, height[x]=depth[x]=d, i = last[x]; i>=0 && (y=to[i])>=0; i = next[i] ) 
			if ( color[y] == WHITE ) {
				++son; p[y] = x; dfs(y,1+d);
				height[x] = Math.min(height[x],height[y]);
				// if ( deg[x] >= 2 && height[y] > depth[x] )
				if ( (x==0 && son>1) || (x!=0&&height[y]>=depth[x]) )
					isArticulationPoint[x] = true ;
			}
			else if ( color[y] == GREY && p[x] != y )
				height[x] = Math.min(height[x],depth[y]);
		/*
		if ( isArticulationPoint[x] )
			System.out.println((x+1)+" is articulation point");
		*/
		color[x] = BLACK;
	}
	Set<Integer> adjCutPoint;
	void floodfill( int x ) {
		int i,y;
		assert color[x] == WHITE;
		for ( color[x] = GREY, ++w, i = last[x]; i >= 0 && (y=to[i]) >= 0; i = next[i] )
			if ( color[y] == WHITE && !isArticulationPoint[y] ) 
				floodfill(y);
			else if ( isArticulationPoint[y] ) adjCutPoint.add(y);
		color[x] = BLACK;
	}
	void go() throws Exception {
		int i,j,k,l,t,cs = 0;
		long ax,ans,bx;
		boolean ok;
		for (;(m=scan.nextInt())!=0 && ++yes>=1;) {
			for ( i = 0; i < MAXN; deg[i] = 0, last[i++] = -1 );
			System.out.printf("Case %d: ",++cs);
			for ( n = 0, E = 0, l = 0; l < m; addArcs(i,j), ++l ) { i = scan.nextInt()-1; j = scan.nextInt()-1; }
			for ( i = 0; i < n; p[i] = -1, color[i] = WHITE, isArticulationPoint[i++] = false );
			for ( i = 0; i < n; ++i )
				if ( color[i] == WHITE && used[i] == yes ) dfs(i,0);
			for ( usedn=0, i = 0; i < n; ++i )
				if ( used[i] == yes ) ++usedn;
			for ( i = 0; i < n; color[i++] = WHITE );
			for ( ans = 0, bx = 1L, ax = 1L, ok = false, k = 0, i = 0; i < n; ++i )
				if ( color[i] == WHITE && used[i] == yes && !isArticulationPoint[i] ) {
						adjCutPoint = new HashSet<Integer>();
						w = 0; floodfill(i);
						if ( adjCutPoint.size() == 1 ) {
							ax *= w; ++k; ok = true;
						}
						/*
						else if ( adjCutPoint.size() == 0 ) {
							if ( w == 1 ) continue ;
							ans += 2;
							bx *= (w*(w-1))/2;
						}*/
				}
			if ( !ok ) { k = 2; ax = (usedn*(usedn-1))/2; }
			System.out.println((k+ans)+" "+(ax*bx));
		}
	}
};

