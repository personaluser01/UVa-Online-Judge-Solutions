/*
 * 312. Crosswords (II)
 * TOPIC: ad hoc, text processing, bfs
 * status: Accepted
 */

/**
 * Created by sj on 11/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    final private static int N = 0x400, X = 3, Y = 5;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    int m,n,ord;
    int [][]g = new int[32][32], number = new int[32][32];
    char [][]res = new char[32*4][32*6];

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/312/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/312/src/out02.txt")));
        new Main().go();
    }

    boolean vc( int x, int y ) {
        return 0<=x && x<m && 0<=y && y<n;
    }

    boolean moreAhead( final int i, final int j ) {
        int k = j+1;
        for (;k<=n && g[i][k] == 1; ++k );
        return k<=n;
    }
    boolean moreAbove( final int i, final int j ) {
        int k = i-1;
        for (;k>=0 && g[k][j] == 1; --k );
        return k>=0;
    }
    boolean moreBefore( final int i, final int j ) {
        int k = j-1;
        for (;k >= 0 && g[i][k] == 1; --k );
        return k >= 0;
    }

    void fillHor( final int i, final int j ) {
        int x = X*i, y = Y*j, ny;
        for ( ny = y; ny < y+Y; ++ny )
            res[x][ny] = '+';
        res[x][ny] = '$';
    }
    void fillHor( final int i, final int j, final char ch ) {
        int x = X*i, y = Y*j, ny;
        for ( ny = y; ny < y+Y; ++ny )
            res[x][ny] = ch;
        res[x][ny] = '$';
    }
    void fillVer( final int i, final int j ) {
        int x = X*i, y = Y*j, nx;
        for ( nx = x; nx < x+X; ++nx )
            res[nx][y] = '+';
    }
    void fillVer( final int i, final int j, final char ch ) {
        int x = X*i, y = Y*j, nx;
        for ( nx = x; nx < x+X; ++nx )
            res[nx][y] = ch;
    }
    void fillCell( final int i, final int j, final char ch ) {
        int x = X*i, y = Y*j;
        for ( int nx = x+1; nx < x+X; ++nx )
            for ( int ny = y+1; ny < y+Y; ++ny )
                res[nx][ny] = ch;
    }

    void writeRow( final int i ) {
        for ( int j = 0; j < res[X*i].length; res[X*i][j++] = '#' );
        for ( int j = 0; j <= n; ++j ) {
            if (number[i][j] == -2) {
                fillCell(i, j,moreAhead(i,j)?' ':'$');
                if ( i>=1&&number[i-1][j]!=-2&&j>=1&&number[i][j-1]!=-2 ) {
                    fillHor(i,j,'+');
                    fillVer(i,j,'+');
                    continue ;
                }
                if ( i>=1&&number[i-1][j]!=-2 ) {
                    fillVer(i,j,moreAhead(i,j)?' ':'$');
                    fillHor(i,j,'+');
                    continue ;
                }
                if ( j>=1&&number[i][j-1]!=-2 ) {
                    fillHor(i,j,moreAhead(i,j)?' ':'$');
                    fillVer(i,j,'+');
                    continue ;
                }
                fillVer(i,j,moreAhead(i,j)?' ':'$');
                fillHor(i,j,moreAhead(i,j)?' ':'$');
                if ( i>=1&&j>=1&&number[i-1][j-1] != -2)
                    res[i*X][j*Y] = '+';
                continue ;
            }
            if ( number[i][j] == -1 ) {
                fillVer(i,j);
                fillHor(i,j);
                fillCell(i,j,g[i][j]==1?'+':' ');
                continue ;
            }
            assert number[i][j] >= 1;
            fillVer(i,j);
            fillHor(i,j);
            fillCell(i,j,' ');
            int xx = number[i][j];
            for ( int k = Y*j+3; k >= Y*j+1; --k ) {
                res[X*i+1][k] = (char)((xx%10)+'0');
                xx /= 10;
            }
        }
        int j;
        for ( j = res[X*i].length-1; j >= 0 && res[X*i][j] == '#'; --j );
        while ( j >= 0 && res[X*i][j] == '$' ) --j;
        for ( int t = 0; t < j; ++t )
            if ( res[X*i][t] == '$' )
                res[X * i][t] = ' ';
    }

    void preprocess() {
        int left = -1,right = n,up = -1,down = m,i,j,k;
        for ( j = 0; j < n; ++j ) {
            for (i = 0; i < m && g[i][j] == 1; ++i) ;
            if ( i == m ) left = i;
            else break ;
        }
        for ( j = n-1; j >= 0; --j ) {
            for ( i = 0; i < m && g[i][j] == 1; ++i );
            if ( i == m ) right = j;
            else break ;
        }
        for ( i = 0; i < m; ++i ) {
            for ( j = 0; j < n && g[i][j] == 1; ++j );
            if ( j == n ) up = i;
            else break ;
        }
        for ( i = m-1; i >= 0; --i ) {
            for ( j = 0; j < n && g[i][j] == 1; ++j );
            if ( j == n ) down = i;
            else break ;
        }
        int newm = (down-1)-(up+1)+1, newn = (right-1)-(left+1)+1, l,t;
        int[][]newg = new int[newm][newn];
        for ( l = 0, t = 0, i = up+1; i <= down-1; ++i, ++l )
            for ( t = 0, j = left+1; j <= right-1; ++j )
                newg[l][t++] = g[i][j];
        m = newm; n = newn;
        for ( i = 0; i < m; ++i )
            for ( j = 0; j < n; ++j )
                g[i][j] = newg[i][j];
    }

    void go() throws Exception {
        int i,j,k,di,dj;
        for ( String s; (s = br.readLine()) != null; ) {
            Scanner scan = new Scanner(s);
            m = scan.nextInt();
            n = scan.nextInt();
            if ( m == 0 && n == 0 ) break ;
            // read the matrix in
            for ( i = 0; i < m; ++i )
                for ( j = 0, scan = new Scanner(br.readLine()); j < n; g[i][j++] = scan.nextInt()) ;
            // preprocess();
            for ( i = 0; i <= m; ++i )
                for ( j = 0; j <= n; ++j )
                    number[i][j] = -1;
            // fill the border with black squares: only the right and bottom margins
            for ( i = 0; i <= m; ++i )
                for ( j = 0; j <= n; ++j )
                    if ( i == m || j == n ) {
                        g[i][j] = 1;
                        number[i][j] = -2;
                    }
            for ( i = 0; i < m; ++i )
                for ( j = 0; j < n; ++j )
                    if ( i == 0 || j == 0 )
                        if ( g[i][j] == 1 )
                            number[i][j] = -2;

            // assign numbers to numbered cells
            for ( ord = 0, i = 0; i < m; ++i )
                for ( j = 0; j < n; ++j ) {
                    if ( g[i][j] == 0 )
                        if ( (i==0||g[i-1][j]==1)&&(i+1<=m+1&&g[i+1][j]==0) || (j==0||g[i][j-1]==1)&&(j+1<=n+1&&g[i][j+1]==0) )
                            number[i][j] = ++ord;
                }
            // calculate phantom cells
            // phantom cell is a black cell on the edge OR a black cell with a phantom edge as its neighbor
            boolean flag;
            do {
                for ( flag = false, i = 0; i <= m; ++i )
                    for ( j = 0; j <= n; ++j )
                        if ( number[i][j] == -2 )
                            for ( di = i-1; di <= i+1; ++di )
                                for ( dj = j-1; dj <= j+1; ++dj )
                                    if ( Math.abs(di-i)+Math.abs(dj-j) == 1 )
                                        if ( vc(di,dj) && number[di][dj] != -2 && g[di][dj] == 1 ) {
                                            number[di][dj] = -2;
                                            flag = true ;
                                        }
            } while ( flag );
            for ( i = 0; i <= m; writeRow(i++) );
            for ( i = 0; i <= m; ++i )
                for ( k = X*i; k < X*i+X; ++k ) {
                    for ( j = 0; j < res[k].length && res[k][j] != '$'; ++j );
                    String t = new String(res[k],0,j);
                    if ( k <= X*m ) bw.write(t+"\n");
                }
            bw.write("\n");
        }
        bw.flush();
    }
}

