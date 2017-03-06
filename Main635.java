/*
 * 635. Solitaire Clock
 * TOPIC: ad hoc, simulation
 * status: Accepted
 */

/**
 * Created by sj on 13/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    int []c = new int[52];

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/635/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/635/src/out02.txt")));
        new Main().go();
    }

    int find( String s ) {
        switch ( s ) {
            case "J": return 0;
            case "A": return 10;
            case "Q": return 11;
            case "K": return 12;
            case "T": return 9;
            default: return Integer.parseInt(s)-1;
        }
    }

    boolean successfulGame( final int offset ) {
		int i,j,k;
		Map<Integer,Deque<Integer>> m = new TreeMap<>();
		for ( i = 0; i < 13; ++i ) {
			Deque<Integer> d;
			m.put(i,d = new ArrayDeque<>());
			for ( j = i*4; j < i*4+4; ++j ) {
				k = (j+offset)%52;
				d.addFirst(c[k]);
			}
		}
		boolean flag;
		k = 12;
		do {
			flag = false ;
			Deque<Integer> d = m.get(k);
			if ( !d.isEmpty() ) {
				flag = true ;
				k = d.pollFirst();
			}
		} while ( flag );
		for ( i = 0; i < 13; ++i )
			if ( !m.get(i).isEmpty() )
				return false ;
		return true ;
    }

    void go() throws Exception {
        int i,j,k;
        String []s = new String[52];
        for ( ;!(s[0] = scan.next()).equals("0"); ) {
            for ( i = 1; i < 52; s[i++] = scan.next() );
            for ( i = 0; i < 52; ++i )
                c[i] = find(s[i]);
            for ( k = 0, i = 0; i < 52; ++i )
                if ( successfulGame(i) ) ++k;
            bw.write(k+"\n");
        }
        bw.flush();
    }
}
