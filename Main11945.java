/*
 * 11945. Financial Management
 * status: Accepted
 * TOPIC: java features, rounding to nearest penny
 */
import java.io.*;
import java.util.*;
import java.text.NumberFormat;

class Main {
    int cs = 0;
    double tol = 1e-9;
    public static void main ( String [] args ) throws Exception { new Main().go(); }
    void displayCurrency( Locale currentLocale, double sum ) throws Exception {
        double x = ((int)(100*(sum+tol)))/100.00;
        Double currencyAmount = new Double(x+tol);
        Currency currentCurrency = Currency.getInstance(currentLocale);
        NumberFormat currencyFormatter = NumberFormat.getCurrencyInstance(currentLocale);

        System.out.println((++cs)+" "+currencyFormatter.format(currencyAmount));
    }


    void go() throws Exception {
        int i,j,k,ts;
        double T;
        Scanner scan = new Scanner(System.in);
        for ( ts = scan.nextInt(); ts-- > 0; ) {
            T = 0;
            for ( i = 12; i-- > 0; T += scan.nextDouble() );
            displayCurrency(Locale.US,T/12+0.005);
        }
    }
};

