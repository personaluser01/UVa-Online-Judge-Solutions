/*
 * 645. File Mapping
 * TOPIC: output formatting, recursion
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	final int N = 0x400;
	String []s = new String[N];
	int n,m;
	boolean []isDir,isEnd;;
	public static void main ( String [] args ) throws Exception { new Main().go(); }
	boolean readInput() throws Exception {
		for ( n=0; !(s[n]=scan.next()).equals("*") && !s[n].equals("#"); ++n );
	//	for ( int i = 0; i < n; ++i )
	//		System.out.println(s[i]);
		return n>0;
	}
	class Dir {
		int i,j;
		String nm;
		Dir( int i, int j, String s ) {
			this.i = i; this.j = j; this.nm = s;
		}
	}
	String indent( int levels ) {
		StringBuilder sb = new StringBuilder();
		for ( int k = levels*6, i = 0; i < k; ++i )
			if ( 0 == (i%6) )
				sb.append("|");
			else sb.append(' ');
		return sb.toString();
	}
	void f( Dir cur, int OFFSET ) {
		int i,j,k,l,left = cur.i, right = cur.j;
		StringBuilder sb;
		if ( left > right ) return ;
		Set<String> w = new TreeSet<String>();
		Queue<Dir> q = new LinkedList<Dir>();
		for ( i = left; i <= right; i = j ) {
			for ( j = i; j <= right && !isDir[j]; ++j )
				if ( !isEnd[j] ) w.add(s[j]);
			if ( j <= right ) {
				for ( l = 1, k = j+1; k <= right; ++k )
					if ( isEnd[k] && (--l == 0) ) break ;
					else if ( isDir[k] ) ++l;
				assert k <= right;
				assert isEnd[k];
				q.add(new Dir(j+1,k,s[j]));
				j = k+1;
			}
		}
		System.out.println(indent(OFFSET)+cur.nm);
		for (;!q.isEmpty();) {
			Dir d = (Dir)q.poll();
			f(d,OFFSET+1);
		}
		String sh = indent(OFFSET);
		for ( Iterator<String> it = w.iterator(); it.hasNext(); System.out.println(sh+it.next()) );
	}
	void go() throws Exception {
		int i,j,k,cs = 0;
		for (;readInput();) {
			isDir = new boolean[n];
			isEnd = new boolean[n];
			for ( i = 0; i < n; ++i ) {
				isDir[i] = s[i].charAt(0)=='d';
				isEnd[i] = s[i].charAt(0)==']';
			}
			if ( cs >= 1 ) System.out.println("");
			System.out.println("DATA SET "+(++cs)+":");
			f(new Dir(0,n-1,"ROOT"),0);
		}
	}
};

