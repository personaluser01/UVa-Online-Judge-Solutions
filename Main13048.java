/*
 * 13048. Burger Stand
 * TOPIC: trivial
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static final int N = 0x40;
	String s;
	char []c;
	int n;

	public static void main( String [] args ) throws Exception {
		new Main().go();
	}

	boolean goodSpot( int pos ) {
		if ( c[pos] == 'D' || c[pos] == 'B' || c[pos] == 'S' ) return false ;
		if ( pos+1 < n && c[pos+1] == 'B' ) return false ;
		if ( pos+2 < n && c[pos+2] == 'B' ) return false ;
		if ( pos+1 < n && c[pos+1] == 'S' ) return false ;
		if ( pos-1 >= 0 && c[pos-1] == 'S' ) return false ;
		return true ;
	}

	void go() throws Exception {
		int i,j,k,ts = Integer.parseInt(br.readLine()),cs = 0,ans = 0;
		for ( ;ts-->0; ) {
			n = (s = br.readLine()).length();
			c = s.toCharArray();
			for ( ans = 0, i = 0; i < n; ++i )
				if ( goodSpot(i) ) ++ans;
			bw.write("Case "+(++cs)+": "+ans+"\n");
		}
		bw.flush();
	}
};

