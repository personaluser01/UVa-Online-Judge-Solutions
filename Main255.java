/*
 * 255. Correct Move
 * status: Accepted
 * TOPIC: simulation, easy
 */
import java.io.*;
import java.util.*;

class Main {
	static boolean validCell( int x, int y ) {
		return 0 <= x && x < 8 && 0 <= y && y < 8;
	}
	public static void main( String [] args ) throws Exception {
		Main m = new Main();
		m.doIt();
	}
	void doIt() {
		boolean allowed,hasOptions,encounter;
		int i,j,k,q,nq,kx,ky,qx,qy,nqx,nqy,len,l;
		int []x = new int[64],y = new int[64],dx = {-1,0,1,0},dy = {0,1,0,-1};
		int [][]id = new int[8][8];
		for ( i = 0; i < 8; ++i )
			for ( j = 0; j < 8; ++j ) {
				k = (i*8+j);
				id[i][j] = k;
				x[k] = i; y[k] = j;
			}
		String s;
		StringTokenizer st;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		try {
			while ( (s = br.readLine()) != null ) {
				boolean [][]reachable = new boolean[8][8];
				st = new StringTokenizer(s);
				k = Integer.parseInt(st.nextToken());
				kx = x[k]; ky = y[k];
				q = Integer.parseInt(st.nextToken());
				qx = x[q]; qy = y[q];
				nq = Integer.parseInt(st.nextToken());
				nqx = x[nq]; nqy = y[nq];
				if ( q == k ) {
					System.out.println("Illegal state");
					continue ;
				}
				if ( nq == k || !((nqx==qx||nqy==qy) && nq != q) ) {
					System.out.println("Illegal move");
					continue ;
				}
				len = (nqx-qx + nqy-qy);
				if ( len < 0 ) len = -len;
				assert( len != 0 );
				if ( nqx != qx ) {
					assert( nqy == qy );
					if ( nqx > qx )
						j = 2;
					else j = 0;
				}
				else {
					assert( nqy-qy == len );
					if ( nqy > qy )
						j = 1;
					else j = 3;
				}
				encounter = false;
				for ( l = 1; l <= len && !encounter; ++l ) 
					if ( qx+dx[j]*l == kx && qy+dy[j]*l == ky )
						encounter = true;
				assert( qx+dx[j]*len == nqx && qy+dy[j]*len == nqy );
				if ( encounter ) {
					System.out.println("Illegal move");
					continue ;
				}
				allowed = true;
				for ( i = 0; i < 4 && allowed; ++i ) 
					if ( Main.validCell(kx+dx[i],ky+dy[i]) && kx+dx[i] == nqx && ky+dy[i] == nqy )
						allowed = false;
				if ( !allowed ) {
					System.out.println("Move not allowed");
					continue ;
				}
				hasOptions = false;
				for ( i = 0; i < 8; ++i )
					for ( j = 0; j < 8; ++j )
						reachable[i][j] = false;
				for ( i = 0; i < 4; ++i )
					if ( validCell(nqx+dx[i],nqy+dy[i]) )
						reachable[nqx+dx[i]][nqy+dy[i]] = true;

				for ( i = 0; i < 4 && !hasOptions; ++i ) 
					if ( Main.validCell(kx+dx[i],ky+dy[i]) && (kx+dx[i] != nqx || ky+dy[i] != nqy) && !reachable[kx+dx[i]][ky+dy[i]] )
						hasOptions = true;
				if ( !hasOptions ) 
					System.out.println("Stop");
				else 
					System.out.println("Continue");
			}
		}
		catch ( IOException e ) {
			System.out.println(e.toString());
		}
	}
};

