/*
 * 11488. Hyper-Prefix Sets
 * TOPIC: trie, dp, neat
 * status: Accepted
 */
import java.util.*;
import java.io.*;

class Main {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static final int N = (1<<22), MAXLEN = 208;

	int []t = new int[N], depth = new int[N], card = new int[N], id = new int[N];
	byte []cnt = new byte[N];
	int n,ans;

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	enum Color {
		WHITE, GRAY, BLACK
	}

	class Cell {
		Cell []son = new Cell[2];
		Cell p = null;
		Color col;
		int depth = 0, card = 0;
		Cell transit( char ch ) {
			return son[(int)(ch-'0')];
		}
		boolean isLeaf() {
			return son[0] == null && son[1] == null;
		}
		Cell( Cell p, int depth ) {
			this.p = p;
			this.depth = depth;
			this.col = Color.WHITE;
			this.card = 0;
		}
		void addSon( char ch ) {
			this.son[ch-'0'] = new Cell(this,depth+1);
		}
	}

	void push( Cell root, char []c ) {
		Cell x = root;
		for ( int i = 0; i < c.length; x = x.transit(c[i++]) ) 
			if ( x.transit(c[i]) == null ) 
				x.addSon(c[i]);
		++x.card;
	}

	void dfs( Cell x ) {
		if ( x.col == Color.WHITE ) {
			x.col = Color.GRAY;
			for ( int i = 0; i < 2; ++i )
				if ( x.son[i] != null ) {
					dfs(x.son[i]);
					x.card += x.son[i].card;
				}
			x.col = Color.BLACK;
			ans = Math.max(ans,x.depth*x.card);
		}
	}

	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(br.readLine()),x,y,px,w;
		String s;
		for(;ts-->0;) {
			n = Integer.parseInt(br.readLine());
			Cell root = new Cell(null,0);
			for ( i = 0; i < n; ++i ) 
				push(root,(s = br.readLine()).toCharArray());
			ans = 0; dfs(root);
			bw.write(ans+"\n");
		}
		bw.flush();
	}
};


