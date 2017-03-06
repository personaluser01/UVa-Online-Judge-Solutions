/*
 * 10769. Pillars
 * status: Accepted
 * REMARKS: Funny, the code written as back as 2006, AC in 2015.. 10 years? Jeez!
 */
    #include<stdio.h>
    #include<string.h>
    #include<ctype.h>
    #include<stdlib.h>
    #define N 100
    typedef unsigned long T;

    T w[N],b[N];
    T H;
    int n,m;
    int a[4];
    int used_b[N],used_w[N];

    int compare(const T *a,const T *b){
        if ( *a < *b ) return 1;
        if ( *a > *b ) return -1;
        return 0;
    }

    int F(T Total_Len, int k)
    {
       int t;
       if(k==4 && Total_Len==H)
       {
          printf("%lu ",b[a[0]]);
          printf("%lu ",w[a[1]]);
          printf("%lu ",b[a[2]]);
          printf("%lu\n",w[a[3]]);
          return 1;
       }
       else if(k<4 && Total_Len<H)
       {
          k++;
          if(k%2==1)
          {
             for(t=0;t<n;t++)
                if(!used_b[t])
                   if(Total_Len<H-b[t])
                   {
                      used_b[t]=1;
                      a[k-1]=t;
                      if(F(Total_Len+b[t],k))
                         return 1;
                      used_b[t]=0;
                   }
          }
          else
          {
             for(t=0;t<m;t++)
                if(!used_w[t])
                   if(Total_Len<=H-w[t])
                   {
                      used_w[t]=1;
                      a[k-1]=t;
                      if(F(Total_Len+w[t],k))
                         return 1;
                      used_w[t]=0;
                   }
          }
       }
       return 0;
    }

    int main()
    {
       int L,t;
       char buff[200000];
    #ifndef ONLINE_JUDGE
       freopen("input.txt","r",stdin);
    #endif
       while(scanf("%lu\n",&H)!=EOF)
       {
          n=0;
          b[n]=0;
          gets(buff);
          L=strlen(buff),t=0;
          while(t<L)
          {
             while(t<L && isdigit(buff[t]))
                b[n]=10*b[n]+(buff[t++]-'0');
             while(t<L && !isdigit(buff[++t]));
             n++;
             b[n]=0;
          }
          m=0;
          w[m]=0;
          gets(buff);
          L=strlen(buff),t=0;
          while(t<L)
          {
             while(t<L && isdigit(buff[t]))
                w[m]=10*w[m]+(buff[t++]-'0');
             while(t<L && !isdigit(buff[++t]));
             m++;
             w[m]=0;
          }
          qsort(b,n,sizeof(T),compare);
          qsort(w,m,sizeof(T),compare);
          for(t=0;t<n;t++)
             used_b[t]=0;
          for(t=0;t<m;t++)
             used_w[t]=0;
          if(!F(0,0))
             printf("no solution\n");
       }
       return 0;
    }

