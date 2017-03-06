/*
 * 12968. In the Airport
 * TOPIC: simulation, maths
 * status: Acepted
 */
import java.io.*;
import java.util.*;

class Main {
	final int N = 0x400, oo = (1<<29);
	Scanner scan = new Scanner(System.in);
	int n,m,k;
	public static void main( String [] args ) throws Exception {
		new Main().go();
	};
	void go() throws Exception {
		int i,j,ts,cs = 0,l;
		long[]c = new long[N],cakes,drinks;
		long w,best_drink,best_cake,total;
		for ( ts = scan.nextInt(); ts-->0; ) {
			n = scan.nextInt();
			m = scan.nextInt();
			k = scan.nextInt();
			cakes = new long[m];
			drinks = new long[k];
			for ( total = 0, l = 0, i = 0; i < m; ++i )
				total += (c[l++] = cakes[i] = scan.nextInt());
			for ( i = 0; i < k; ++i )
				total += (c[l++] = drinks[i] = scan.nextInt());
			for ( i = 0; i < n-m-k; ++i )
				total += (c[l++] = scan.nextInt());
			for ( best_cake = cakes[0], i = 1; i < m; ++i )
				if ( Math.abs(best_cake*n-total) > Math.abs(cakes[i]*n-total) || Math.abs(best_cake*n-total) == Math.abs(cakes[i]*n-total) && best_cake>cakes[i] )
					best_cake = cakes[i];
			for ( best_drink = drinks[0], i = 1; i < k; ++i )
				if ( Math.abs(best_drink*n-total)>Math.abs(drinks[i]*n-total) || Math.abs(best_drink*n-total)==Math.abs(drinks[i]*n-total) && best_drink>drinks[i] )
					best_drink = drinks[i];
			System.out.println("Case #"+(++cs)+": "+best_cake+" "+best_drink);
		};
	};
};

