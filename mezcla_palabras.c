/*Mezcla palabras con todas las combinaciones que hay(sin repetir combinaciones).*/

#include<stdio.h>
void main()
{
   char pal[8],res[8000][8];
   int x,y,z,lon=0,mez[8],rep[8];
   unsigned long nres=0;
   printf("Introduce una palabra:");
   scanf("%s",pal);
   for(y=1;y<10 && lon==0;y++)
      if(pal[y]=='\x0')
         lon=y;
   for(y=0;y<11;y++)
      rep[y]=0;
   for(x=1;x<=lon;x++)
      for(y=0;y<x;y++)
         if(pal[x]==pal[y])
            rep[y]++;
   x=0;
   prefor:
   for(mez[x]=0;1;mez[x]++)
   {
      for(y=0;y<x;y++)
         if(mez[y]==mez[x])
            goto posfor;
      z=0;
      for(y=0;y<x;y++)
         if(pal[mez[y]]==pal[mez[x]])
            z++;
      if(z>rep[mez[x]])
         goto premen;
      if(x+1<lon)
      {
         x++;
         goto prefor;
      }
      nres++;
      for(y=0;y<lon;y++)
      {
         res[nres][y]=pal[mez[y]];
         printf("%c",pal[mez[y]]);
      }
      printf("\n");
      premen:
      x--;
      precam:
      for(y=x+1;y<lon;y++)
      {
         if(x<0)
            goto fin;
         if(y==lon-1 && mez[x]>mez[y])
         {
            x--;
            goto precam;
         }
         if(mez[y]>mez[x])
            y=lon;
      }
      posfor:
   }
   fin:
   printf("%d resultados obtenidos.\n",nres);
}