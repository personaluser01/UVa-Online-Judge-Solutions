/*
 * 12506. Shortest Names
 * TOPIC: trie, bfs, dp
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400;
	int n;
	String []s;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	}
	class Cell {
		char ch;
		int depth;
		boolean isTerm,branches;
		Cell son,sib,p;
		Cell( char ch, boolean t ) { this.ch = ch; this.isTerm = t;	this.son = this.sib = this.p = null; }
	}
	void push( Cell root, char []s, int n ) {
		Cell x = root,y;
		for ( int i = 0; i < n; ++i, x = y ) {
			for ( y = x.son; y != null && y.ch != s[i]; y = y.sib );
			if ( y == null ) {
				y = new Cell(s[i],false);
				y.sib = x.son; x.son = y; y.p = x;
			}
		}
		x.isTerm = true;
	}
	void bfs( Cell root ) {
		Queue<Cell> q = new LinkedList<Cell>();
		Cell x,y;
		for ( root.depth = 0, q.add(root); !q.isEmpty(); ) 
			for ( x = (Cell)q.poll(), y = x.son; y != null; y.depth = x.depth+1, q.add(y), y = y.sib );
	}
	Queue<Cell> Q;
	void dfs( Cell x ) {
		if ( x.isTerm ) {
			Q.add(x);
			x.branches = false;
			return ;
		}
		int k = 0;
		for ( Cell y = x.son; y != null; ++k, dfs(y), y = y.sib );
		x.branches=(k>=2||k==1&&x.son.branches);
	}
	void go() throws Exception {
		int ts = scan.nextInt(),i,j,k,ans;
		for (;ts-->0;System.out.println(ans)) {
			s = new String[n = scan.nextInt()];
			Cell x,y,root = new Cell('$',false);
			for ( i = 0; i < n; ++i ) {
				s[i] = scan.next();
				push(root,s[i].toCharArray(),s[i].length());
			}
			Q = new LinkedList<Cell>();
			for ( bfs(root), dfs(root), ans = 0; !Q.isEmpty(); ) {
				x = (Cell)Q.poll();
				if ( x.branches ) continue ;
				if ( x.p != null && x.p.branches ) 
					ans += x.depth;
				else if ( x.p != null )
					Q.add(x.p);
			}
		}
	}
};

