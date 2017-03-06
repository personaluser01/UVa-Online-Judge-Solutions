/*
 * 13035. Another Combination Problem
 * TOPIC: combinatorics
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	static final long MOD = 1000000007L, INV = 166666668L;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	int n;

	public static void main( String ... args ) throws Exception {
		new Main().go();
	}

	void go() throws Exception {
		int i,j,k,cs = 0,ts = Integer.parseInt(br.readLine());
		for (;ts-->0; ) {
			n = Integer.parseInt(br.readLine());
			bw.write("Case "+(++cs)+": ");
			n += 2;
			long []x = {n,n-1,n-2};
			long res = INV;
			for ( long t: x ) {
				res *= t;
				res %= MOD;
			}
			res *= 2; res %= MOD;
			bw.write(res+"\n");
		}
		bw.flush();
	}
};

