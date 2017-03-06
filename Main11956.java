/*
 * 11956. Brainfuck
 * TOPIC: ad hoc
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 100;
	int ts,cs;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String s;
	public static void main( String [] args ) throws Exception { new Main().go(); };
	void go() throws Exception {
		int i,j,k;
		int []u;
		for ( ts = Integer.parseInt(br.readLine()); ts-->0; ) {
			s = br.readLine();
			System.out.print("Case "+(++cs)+":");
			i = 0; u = new int[N];;
			for ( char c: s.toCharArray() ) 
				switch ( c ) {
					case '>': ++i; i %= N; break ;
					case '<': --i; i += N; i %= N; break ;
					case '+': ++u[i]; u[i] &= 0xff; break ;
					case '-': --u[i]; u[i] += (1<<8); u[i] &= 0xff; break ;
					default: break ;
				};
			for ( i = 0; i < N; ++i )
				System.out.printf(" %02X",u[i]);
			System.out.println("");
		};
	};
};

