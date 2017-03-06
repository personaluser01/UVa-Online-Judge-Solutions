/*
 * 398. 18-Wheeler Caravans (aka Semigroups)
 * TOPIC: ad hoc, text processing, output formatting
 * status: Accepted
 */

/**
 * Created by sj on 10/01/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    private final static int N = 32;
    int n;
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/398/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/398/src/out02.txt")));
        new Main().go();
    }

    Map<Character,Integer> var;
    char [][]g = new char[N][N];

    void go() throws Exception {
        int i,j,k,ts = 0;
        Scanner scan;
        String s,u,v;
        boolean ok,not_semi,not_comm;
        int [][]c = new int[N][N];
        char xx='a',yy='b',zz='c';
        while ( (s = br.readLine()) != null ) {
            scan = new Scanner(s);
            n = scan.nextInt();
            if ( n == 0 ) break ;
            if ( ++ts > 1 ) bw.write("\n");
            u = v = s = br.readLine();
            var = new TreeMap<>();
            for ( i = 0; i < n; ++i )
                var.put(s.charAt(i),i);
            not_semi = not_comm = false ;
            ok = true ;
            for ( i = 0; i < n; ++i ) {
                s = br.readLine();
                for ( j = 0; j < n; ++j ) {
                    if ( var.containsKey(g[i][j] = s.charAt(j)) )
                        c[i][j] = var.get(g[i][j]);
                    else {
                        if ( !ok ) continue ;
                        xx = u.charAt(i);
                        yy = u.charAt(j);
                        zz = g[i][j];
                        ok = false;
                    }
                }
            }
            if ( ok )
                for ( i = 0; i < n && !not_semi; ++i )
                    for ( j = 0; j < n && !not_semi; ++j )
                        for ( k = 0; k < n && !not_semi; ++k )
                            if ( c[c[i][j]][k] != c[i][c[j][k]] ) {
                                xx = u.charAt(i);
                                yy = u.charAt(j);
                                zz = u.charAt(k);
                                not_semi = true ;
                            }
            if ( ok && !not_semi )
                for ( i = 0; i < n && !not_comm; ++i )
                    for ( j = 0; j < n && !not_comm; ++j )
                        if ( c[i][j] != c[j][i] ) {
                            xx = u.charAt(i);
                            yy = u.charAt(j);
                            not_comm = true;
                        }
            bw.write("S = {");
            v = v.replaceAll("([a-z])([a-z])","$1,$2");
            v = v.replaceAll("([a-z])([a-z])","$1,$2");
            bw.write(v+"}\n");
            bw.write(" #|"+u+"\n");
            bw.write(" -+"+u.replaceAll("[a-z]","-")+"\n");
            for ( i = 0; i < n; ++i )
                bw.write(" "+u.charAt(i)+"|"+new String(Arrays.copyOfRange(g[i],0,n))+"\n");
            bw.write("\n");
            if ( !ok )
                bw.write("NOT A SEMIGROUP: "+String.format("%c#%c = %c",xx,yy,zz)+" WHICH IS NOT AN ELEMENT OF THE SET\n");
            else if ( not_semi )
                bw.write("NOT A SEMIGROUP: "+String.format("(%1$c#%2$c)#%3$c IS NOT EQUAL TO %1$c#(%2$c#%3$c)\n",xx,yy,zz));
            else if ( not_comm )
                bw.write("SEMIGROUP BUT NOT COMMUTATIVE "+String.format("(%1$c#%2$c IS NOT EQUAL TO %2$c#%1$c)\n",xx,yy));
            else bw.write("COMMUTATIVE SEMIGROUP\n");
            bw.write("------------------------------\n");
        }
        bw.flush();
    }
}
