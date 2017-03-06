/*
 * 12247. 
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.util.regex.*;

class Main {
    public static void main( String [] args ) throws Exception {
        new Main().go();
    }
    boolean isGood( int []a, int []b, int [][]c ) {
        int k;
        for ( int i = 0; i < 6; ++i )
            for ( int j = 0; j < 6; ++j ) {
                k = 0;
                for ( int l = 0; l < 3; ++l )
                    if ( a[c[i][l]] > b[c[j][l]] )
                        if ( (++k) >= 2 )
                            return false;
            }
        return true;
    }
    void go() throws Exception {
        int []a = new int[3];
        int []b = new int[3];
        int [][]c = new int[6][3];
        int i,j,k;
        String s[] = {"012","021","102","120","201","210"};
        for ( i = 0; i < 6; ++i )
            for ( j = 0; j < 3; ++j )
                c[i][j] = s[i].charAt(j)-'0';
        Scanner scan = new Scanner(System.in);
        while ( true ) {
            boolean []used = new boolean[54];
            for ( i = 0; i < 3; ++i ) 
                used[a[i] = scan.nextInt()] = true;
            for ( i = 0; i < 2; ++i )
                used[b[i] = scan.nextInt()] = true;
            if ( a[0] == 0 && a[1] == 0 && a[2] == 0 && b[0] == 0 && b[1] == 0 ) break ;
            for ( k = 1; k < 53; ++k )
                if ( !used[k] ) {
                    b[2] = k;
                    if ( isGood(a,b,c) ) break ;
                }
            if ( k == 53 )
                System.out.println("-1");
            else 
                System.out.println(k);
        }
    }
};

