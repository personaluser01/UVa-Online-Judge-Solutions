/*
 * 1641. ASCII Area
 * TOPIC: careful simulation, invariants, mapping, technique, meditation
 * status: Accepted
 */

/**
 * Created by sj on 21/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    private final static int N = 0x80;
    int m,n;

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1641/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1641/src/out02.txt")));
        new Main().go();
    }
    int enc( int x, int y ) {
        return x|(y<<7);
    }

    char [][]g;

    int findCorner() {
        for ( int i = 1; i <= m; ++i )
            for ( int j = 1; j <= n; ++j )
                if ( g[i][j] == '/' )
                    return enc(i,j+1);
                else if ( g[i][j] == '\\' )
                    return enc(i,j);
        return -1;
    }

    void go() throws Exception {
        String s;
        int i,j,k,x,y,nx,ny,u,v;
        for ( ;(s = br.readLine()) != null; ) {
            Scanner scan = new Scanner(s);
            m = scan.nextInt();
            n = scan.nextInt();
            g = new char[m+2][n+2];
            for ( i = 0; i <= m+1; ++i )
                Arrays.fill(g[i],'.');
            for ( i = 0; i < m; ++i ) {
                String t = br.readLine();
                for ( j = 0; j < n; ++j )
                    g[i+1][j+1] = t.charAt(j);
            }
            if ( (u = findCorner()) == -1 ) {
                bw.write("0\n");
                continue ;
            }
            plen = 0;
            x = u&127; y = u>>7;
            x = x; y = y;
            findClosedWalk(u,-1,u,0);
            long ans = 0;
            for ( i = 0; i < plen; ++i ) {
                j = (i+1)%plen;
                x = p[i]&127;
                y = p[i]>>7;
                nx = p[j]&127;
                ny = p[j]>>7;
                ans += ((long)(x-nx))*(y+ny);
            }
            bw.write((Math.abs(ans)/2)+"\n");
        }
        bw.flush();
    }

    int []p = new int[N*N];
    int plen;
    char []ch = {'/','\\','/','\\'};
    int []dx = {-1,-1,1,1}, dy = {1,-1,-1,1};
    int []ddx = {-1,-1,0,0}, ddy = {0,-1,-1,0};

    int findNext( int pred, int cur ) {
        int x = (cur&127), y = (cur>>7);
        for ( int i = 0; i < 4; ++i ) {
            int nx = x+ddx[i], ny = y+ddy[i];
            if ( g[nx][ny] == ch[i] && enc(x+dx[i],y+dy[i]) != pred )
                return enc(x+dx[i],y+dy[i]);
        }
        return -1;
    }

    private void findClosedWalk(int src, int pred, int v, int len) {
        if ( src == v && len > 0 )
            return ;
        p[plen++] = v;
        int x = (v&127), y = (v>>7);
        x = x; y = y;
        int u = findNext(pred,v);
        myassert(u!=-1);
        findClosedWalk(src,v,u,len+1);
    }

    private void myassert(boolean b) {
        if ( !b ) {
            int trap = 1/0;
        }
    }
}
