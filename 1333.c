/*
 * 1333. Model Rocket Height
 * TOPIC: maths, system of linear equations, trigonometry, formula derivation
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol 1e-9
#define pi (2*acos(0.00))

double D,H,A,B,C;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
	for ( scanf("%lf %lf",&D,&H), D *= D; 3 == scanf("%lf %lf %lf",&A,&B,&C) && (A>0&&B>0&&C>0); ) {
		A *= pi, A /= 180, B *= pi, B /= 180, C *= pi, C /= 180;
		A = tan(A), B = tan(B), C = tan(C), A *= A, B *= B, C *= C;
		printf("%d\n",(int)(H+sqrt(2*A*B*C*D/(B*(A+C)-2*A*C))+0.5));
	}
    return 0;
}

