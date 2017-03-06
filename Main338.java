/*
 * 338. Long Multiplication
 * TOPIC: ad hoc, formatting, tedious, discipline
 * status: Accepted
 */

import java.io.*;
import java.util.*;
import java.util.regex.Pattern;

/**
 * Created by sj on 09/01/17.
 */
public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/" + "338" + "/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/" + "338" + "/src/out02.txt")));
        new Main().go();
    }

    private int mult( char x, char y, int carry ) {
        int a = x-'0', b = y-'0';
        return a*b+carry;
    }

    boolean digitUpsideOf( int i, final int j, final char [][]c ) {
        for ( int k = i-1; k >= 0; --k )
            if ( c[k][j] != '$' )
                return true ;
        return false ;
    }
    boolean digitBelowOf( int i, final int j, final char [][]c ) {
        for ( int k = i+1; k < c.length; ++k )
            if ( c[k][j] != '$' )
                return true ;
        return false ;
    }

    boolean superfluousZeroes( int row, int j0, int j1, char [][]c ) {
        for ( int t = j0; t <= j1; ++t )
            if ( c[row][t] != '$' && c[row][t] != '0' )
                return false ;
        return true ;
    }
    void go() throws Exception {
        java.util.regex.Pattern pattern = Pattern.compile("[1-9]\\d*");
        java.util.regex.Matcher matcher;
        String s;
        String []x = new String[2];
        int n = 0x80;
        char [][]c = new char[n][n];
        int i,j,k,l,t,w,carry,activeRows,row;
        while ( (s = br.readLine()) != null ) {
            Scanner scan = new Scanner(s);
            x[0] = scan.next();
            if ( !scan.hasNext() ) break ;
            x[1] = scan.next();
            for ( i = 0; i < 2; ++i ) {
                matcher = pattern.matcher(x[i]);
                if ( !matcher.find() ) x[i] = "0";
                else x[i] = matcher.group();
            }
            for ( i = 0; i < n; ++i )
                for ( j = 0; j < n; ++j )
                    c[i][j] = '$';
            for ( i = 0; i <= 1; ++i )
                for ( j = n-1, k = x[i].length(); k-->0; c[i][j--]=x[i].charAt(k) );
            for ( j = n-1, k = 0; k < x[0].length() || k < x[1].length(); c[i][j--] = '-', ++k );
            for ( ++i, t = n-1, k = x[1].length(); k-->0; ++i, --t ) {
                for ( carry = 0, j = t, l = x[0].length(); l-->0; --j ) {
                    w = mult(x[1].charAt(k),x[0].charAt(l),carry);
                    c[i][j] = (char)((w%10)+'0');
                    carry = w/10;
                }
                if ( carry > 0 ) {
                    assert carry <= 9;
                    c[i][j--] = (char)(carry+'0');
                }
            }
            l = i++;
            for ( carry = 0, t = n-1; t > j; --t ) {
                for ( w = 0, k = 3; k <= i-2; ++k )
                    w += (c[k][t]=='$'?0:(c[k][t]-'0'));
                w += carry;
                c[i][t] = (char)((w%10)+'0');
                carry = w/10;
            }
            if ( carry > 0 ) {
                assert carry <= 9;
                c[i][t--] = (char)(carry+'0');
            }
            for ( j = n-1; j > t; c[l][j--] = '-' );
            for ( row = 0; row < 3; ++row, bw.write("\n") ) {
                for ( j = t+1; j < n && c[row][j] == '$'; ++j, bw.write(" ") );
                for (;j < n && c[row][j] != '$'; bw.write(c[row][j++]) );
            }
            for ( activeRows = 0, k = 3; k <= i-2; ++k )
                if ( !superfluousZeroes(k,t+1,n-1,c) ) ++activeRows;
            if ( activeRows <= 1 ) {
                for ( ++row, j = t+1; j < n && (c[i][j] == '$' || c[i][j] == '0'); c[i][j++] = '$' );
                if ( j == n )
                    c[i][n-1] = '0';
                for ( j = t+1; j < n && c[i][j] == '$'; bw.write(" "), ++j );
                for ( ;j < n && '0' <= c[i][j] && c[i][j] <= '9'; bw.write(c[i][j++]) );
                bw.write("\n");
            }
            else {
                for ( k = 3; k <= i-2; ++k ) {
                    if ( superfluousZeroes(k,t+1,n-1,c) ) continue ;
                    for ( j = t+1; j < n && (c[k][j] == '$' || c[k][j] == '0'); ++j, bw.write(" ") );
                    for ( ;j < n && '0'<=c[k][j] && c[k][j]<='9'; bw.write(c[k][j++]) );
                    bw.write("\n");
                }
                for ( j = t+1; j < n; bw.write(c[l][j++]) );
                bw.write("\n");
                for ( j = t+1; j < n && (c[i][j] == '$' || c[i][j] == '0'); bw.write(" "), ++j );
                for ( ;j < n && '0' <= c[i][j] && c[i][j] <= '9'; bw.write(c[i][j++]) );
                bw.write("\n");
            }
            bw.write("\n");
        }
        bw.flush();
    }
}

