/*
 * 1636. Headshoot
 * TOPIC: probability, conditional
 * status: Accepted
 */
import java.io.*;
import java.util.*;

class Main {
	Scanner scan = new Scanner(System.in);
	String s;
	char []c;
	int n,T;
	int []cnt = new int[4];
	double []p = new double[4];
	double rightAway, afterRotation;
	public static void main( String [] args ) throws Exception { new Main().go(); }
	void go() throws Exception {
		int i,j,k;
		for (;scan.hasNext();) {
			n=(s=scan.next()).length();
			c=s.toCharArray();
			for ( i = 0; i < 4; cnt[i++] = 0 );
			for ( i = 0; i < n; ++i ) 
				++cnt[((c[i]-'0')<<1)+(c[(i+1)%n]-'0')];
			T = cnt[0]+cnt[1]+cnt[2]+cnt[3];
			for ( i = 0; i < 4; ++i )
				p[i] = ((double)cnt[i])/T;
			rightAway = p[0]/(p[0]+p[2]);
			afterRotation = p[0]+p[1];
			if ( rightAway == afterRotation ) {
				System.out.println("EQUAL");
				continue ;
			}
			if ( rightAway > afterRotation ) {
				System.out.println("SHOOT");
				continue ;
			}
			System.out.println("ROTATE");
		}
	}
};

