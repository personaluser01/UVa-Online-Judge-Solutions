/*
 * 12897. Decoding Baby Boos
 * TOPIC: very neat, almost a joke problem, very neat IQ problem
 * status: Accepted
 */

/**
 * Created by sj on 17/02/17.
 */

import java.io.*;
import java.util.*;

public class Main {
    BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String... args) throws Exception {
        System.setIn(new FileInputStream(new File("/home/sj/IdeaProjects/12897/src/input.txt")));
        System.setOut(new PrintStream(new File("/home/sj/IdeaProjects/12897/src/out02.txt")));
        new Main().go();
    }

    Map<Character,List<Integer>> pos = new HashMap<>();

    void go() throws Exception {
        int i,j,k,ts = Integer.parseInt(br.readLine());
        while ( ts-->0 ) {
            String s = br.readLine();
            String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            k = Integer.parseInt(br.readLine());
            for ( i = 0; i < k; ++i ) {
                String t = br.readLine();
                Character a = t.charAt(0);
                Character b = t.charAt(2);
                assert 'A' <= a && a <= 'Z';
                assert 'A' <= b && b <= 'Z';
                alphabet = alphabet.replace(b,a);
            }
            char []c = new char[s.length()];
            Arrays.fill(c,'_');
            k = 0;
            for ( Character ch: s.toCharArray() ) {
                if (ch == '_') { ++k; continue; }
                c[k++] = alphabet.charAt((int)(ch-'A'));
            }
            s = new String(c);
            bw.write(s+"\n");
        }
        bw.flush();
    }
}
