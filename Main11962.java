/*
 * 11962. DNA II
 * TOPIC: combinatorics, excellent interview question, lex orders
 * status: Accepted
 */

/**
 * Created by sj on 13/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/11962/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/11962/src/out02.txt")));
        code['A'] = 0;
        code['C'] = 1;
        code['G'] = 2;
        code['T'] = 3;
        new Main().go();
    }

    private static int []code = new int[256];

    void go() throws Exception {
        int i,j,k,cs = 0,ts = Integer.parseInt(br.readLine()),n;
        char ch;
        long ans;
        for (;ts-->0;) {
            String s = br.readLine();
            char []c = s.toCharArray();
            n = c.length;
            for ( i = 0; i < n; ++i )
                c[i] = (char)(code[c[i]]+'0');
            bw.write(String.format("Case %d: (%d:",++cs,n));
            for ( ans = 0, i = 0; i < n; i = ++j ) {
                for ( j = i; j < n && c[j] == '0'; ++j );
                if ( j < n )
                    ans += ((long)(c[j]-'0'))*((long)Math.pow(4,n-j-1));
            }
            bw.write(ans+")\n");
        }
        bw.flush();
    }
}
