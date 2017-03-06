/*
 * 381. Making the Grade
 * TOPIC: rounding, easy
 * status: Accepted
 */
import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.Math.*;

class Main {
    int m,n;
    int []a = new int[100];
    int []b = new int[100];
    int [][]c = new int[100][100];
    int []L = new int[100];
    double []av = new double[100];
    double tol = 1e-9;
    char []gr = new char[100];
    double AV,SD,S;
    double []weight = new double[100];
    public static void main ( String [] args ) throws Exception {
        new Main().go();
    }
    double rnd( double x ) {
        int dx = (int)(10*(x+0.05)+tol);
        return dx/10.00;
    }
    void go() throws Exception {
        int i,j,k,ts,cs;

        System.out.println("MAKING THE GRADE OUTPUT");
        weight[0] = 4;
        weight[1] = 3;
        weight[2] = 2;
        weight[3] = 1;
        weight[4] = 0;
        Scanner scan = new Scanner(System.in);
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            m = scan.nextInt();
            n = scan.nextInt();
            AV = SD = 0;
            for ( i = 0; i < m; ++i ) {
                L[i] = 101;
                av[i] = 0;
                for ( j = 0; j < n; ++j ) {
                    c[i][j] = scan.nextInt();
                    if ( L[i] > c[i][j] )
                        L[i] = c[i][j];
                    av[i] += c[i][j];
                }
                // av[i] = rnd(av[i]);
                if ( n > 2 )
                    av[i] = (av[i]-L[i])/(n-1);
                else
                    av[i] = av[i]/n;
                av[i] = rnd(av[i]);
                b[i] = scan.nextInt()/2;
                a[i] = scan.nextInt();
                AV += av[i];
            }
            AV /= m;
            AV = rnd(AV);
            for ( i = 0; i < m; ++i )
                SD += (av[i]-AV)*(av[i]-AV);
            SD = Math.sqrt(SD/m);
            SD = rnd(SD);
            if ( SD < 1 ) SD = 1;
            for ( i = 0; i < m; ++i )
                av[i] = rnd(av[i]+b[i]*3);
            S = 0;
            for ( i = 0; i < m; ++i ) {
                if ( av[i] >= AV+SD )
                    gr[i] = 'A';
                else if ( av[i] >= AV )
                    gr[i] = 'B';
                else if ( av[i] >= AV-SD )
                    gr[i] = 'C';
                else gr[i] = 'D';
                if ( a[i] == 0 ) 
                    if ( gr[i] > 'A' ) --gr[i];
                for ( a[i] /= 4; a[i]-- > 0 && gr[i] <= 'F'; ++gr[i] );
                S += weight[gr[i]-'A'];
            }
            S = rnd(S/m);
            System.out.printf("%.1f\n",S+tol);
        }
        System.out.println("END OF OUTPUT");
    }
};

