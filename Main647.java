/*
 * 647. Chutes and Ladders
 * TOPIC: simulation, medium
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
	public static void main( String [] args ) throws Exception { new Main().go(); }
	class Player {
		public int pos;
		public boolean missATurn;
		Player( int pos, boolean t ) {
			this.pos = pos;
			this.missATurn = t;
		}
	}
	void go() throws Exception {
		Scanner scan = new Scanner(System.in);
		int []g = new int[0x80];
		int []c = new int[0x400];
		int i,j,k,n = 0,m,K,L,winner;
		int []left  = new int[0x400];
		int []right = new int[0x400];
		int []e = new int[0x400];
		int []idx = new int[0x400];
		boolean []isLose;
		boolean []oneMore;
		boolean []isChute;
		boolean []isLadder;
		for (;(c[n]=scan.nextInt())!=0; ++n );
		for (;(m=scan.nextInt())!=0;) {
			Player []p = new Player[m];
			for ( i = 0; i < m; ++i )
				p[i] = new Player(0,false);
			isLose = new boolean[0x80];
			oneMore = new boolean[0x80];
			isChute = new boolean[0x80];
			isLadder = new boolean[0x80];
			for ( K = 0; (left[K] = scan.nextInt()) != 0; right[K++] = scan.nextInt() );
			scan.nextInt();
			for ( i = 0; i < K; ++i ) {
				if ( left[i] > right[i] ) {
					isChute[left[i]] = true;
					idx[left[i]] = i;
				}
				else {
					isLadder[left[i]] = true;
					idx[left[i]] = i;
				}
			}
			for ( L = 0; (e[L] = scan.nextInt()) != 0; ++L )
				if ( e[L] > 0 )
					oneMore[e[L]] = true;
				else isLose[-e[L]] = true;
			winner = -1;
			for ( j = i = 0; i < n && winner == -1; ) {
				if ( p[j].missATurn ) {
					p[j].missATurn = false;
					++j; j %= m;
					continue ;
				}
				k = p[j].pos+c[i];
				if ( k > 100 ) {
					++j; j %= m; ++i;
					continue ;
				}
				if ( k == 100 ) {
					winner = j;
					break ;
				}
				p[j].pos = k;
				if ( isLose[k] ) {
					p[j].missATurn = true;
					++j; j %= m; ++i;
					continue ;
				}
				if ( isChute[k]||isLadder[k] ) {
					p[j].pos = right[idx[k]];
					++j; j %= m; ++i;
					continue ;
				}
				if ( oneMore[k] ) {
					++i; continue ;
				}
				++j; j %= m; ++i;
			}
			System.out.println(winner+1);
		}
	}
};

