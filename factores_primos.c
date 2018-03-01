#include<stdio.h>
#include<stdlib.h>
void main()
{
   unsigned long nm,nm2,x,y,r,res[20];
   unsigned int nres=0,a,z=1,t,ree[20];
   char ch[10];
   printf("Introduce un número: ");
   gets(ch);
   nm=atoi(ch);
   nm2=nm;
   for(x=1;x<20;x++)
   {
      res[x]=0;
      ree[x]=1;
   }
   for(x=2;z;x++)
   {
      y=nm/x;
      r=y*x;
      if(r==nm)
      {
         a=1;
         for(t=1;t<=nres;t++)
            if(res[t]==x)
            {
               ree[t]++;
               t=nres+1;
               a=0;
            }
         if(a==1)
         {
            nres++;
            res[nres]=x;
         }
         nm=y;
         x=1;
         if(nm==1)
         {
            z=0;
            printf("\nLos factores primos de %d son: ",nm2);
            for(x=1;x<=nres;x++)
               {
               printf("%d",res[x]);
               if(ree[x]>1)
                  printf("^%d",ree[x]);
               printf("\t");
               }
            printf("\n");
         }
      }
   }
}
