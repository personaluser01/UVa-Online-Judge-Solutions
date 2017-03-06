/*
 * 1589. Xioangqi
 * TOPIC: ad hoc, simulation, good interview question
 * status: Accepted
 */

/**
 * Created by sj on 25/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    final private static int M = 10, N = 9;
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    Scanner scan = new Scanner(System.in);
    static int enc( int x, int y ) { return x|(y<<4); }

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/1589/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/1589/src/out02.txt")));
        new Main().go();
    }

    static boolean vc( int x, int y ) {
        return 0<= x && x<M && 0<=y && y<N;
    }

    List<Integer> lst = new ArrayList<>();
    List<String> f = new ArrayList<>();
    char [][]g = new char[M][N];

    void mass( boolean x ) {
        if ( !x ) { int trap = 1/0; }
    }

    int interveningPieces( int x, int y, int xx, int yy ) {
        int ans = 0;
        if ( y == yy ) {
            for ( int k = Math.min(x,xx)+1; k <= Math.max(x,xx)-1; ++k )
                if ( g[k][y] != '.' )
                    ++ans;
        }
        else {
            mass(x == xx);
             for ( int k = Math.min(y,yy)+1; k <= Math.max(y,yy)-1; ++k )
                if ( g[x][k] != '.' )
                    ++ans;
        }
        return ans;
    }

    boolean hobbling( int x, int y, int dx, int dy ) {
        mass( (Math.abs(dx) == 2)^(Math.abs(dy)==2) );
        if ( Math.abs(dx) == 2 && g[x+dx/2][y] != '.' )
            return true ;
        if ( Math.abs(dy) == 2 && g[x][y+dy/2] != '.' )
            return true ;
        return false ;
    }

    boolean underAttack( int x, int y ) {
        for ( int i = 0; i < lst.size(); ++i ) {
            int xx = lst.get(i)&15, yy = lst.get(i)>>4;
            if ( xx == x && yy == y ) continue ;
            switch ( f.get(i) ) {
                case "G": if ( xx == x || y == yy )
                            if ( 0 == interveningPieces(x,y,xx,yy) )
                                return true ;
                            break ;
                case "C": if ( xx == x || y == yy )
                            if ( 1 == interveningPieces(x,y,xx,yy) )
                                return true ;
                            break ;
                case "H":   for ( int dx = -2; dx <= 2; ++dx )
                                for ( int dy = -2; dy <= 2; ++dy ) {
                                    if ( Math.abs(dx)+Math.abs(dy) != 3 )
                                        continue ;
                                    int nx = xx+dx, ny = yy+dy;
                                    if ( vc(nx,ny) && !hobbling(xx,yy,dx,dy) )
                                        if ( x == nx && y == ny )
                                            return true ;
                                }
                            break ;
                case "R": if ( xx == x || y == yy )
                            if ( 0 == interveningPieces(x,y,xx,yy) )
                                return true ;
                            break ;
            }
        }
        return false ;
    }

    void go() throws Exception {
        int i,j,k,st,di,dj;
        boolean ok;
        String fig;
        for (;scan.hasNext() && (n=scan.nextInt()) != 0; ) {
            for ( i = 0; i < M; ++i )
                for ( j = 0; j < N; ++j )
                    g[i][j] = '.';
            i = scan.nextInt()-1;
            j = scan.nextInt()-1;
            st = enc(i,j);
            for ( lst.clear(), f.clear(), i = 0; i < n; ++i ) {
                f.add(fig = scan.next());
                j = scan.nextInt()-1;
                k = scan.nextInt()-1;
                g[j][k] = fig.charAt(0);
                lst.add(enc(j,k));
            }
            for ( ok = false, di = -1; di <= 1 && !ok; ++di )
                for ( dj = -1; dj <= 1 && !ok; ++dj )
                    if ( Math.abs(di)+Math.abs(dj) == 1 )
                        if ( vc(di+(st&15),dj+(st>>4)) ) {
                            int x = di+(st&15), y = dj+(st>>4);
                            if ( !(0<=x && x<=2 && 3<=y && y<=5 ) ) continue ;
                            if ( !underAttack(x,y) ) ok = true ;
                        }
            bw.write(ok?"NO\n":"YES\n");
        }
        bw.flush();
    }
}
