#include<stdio.h>
void main()
{
  unsigned int x,y,z,mcm,mcd,dv1,dv2;
  printf("Introduce 2 n�meros:");
  scanf("%d",&x);
  printf("Introduce otro:");
  scanf("%d",&y);
  if(x>y)
  {
     z=x;
     x=y;
     y=z;
  }
  for(z=1;z<=x;z++)
  {
     dv1=x/z;
     dv2=y/z;
     if(dv1*z==x && dv2*z==y)
        mcd=z;
  }
  mcm=0;
  for(z=x;mcm==0;z=z+x)
  {
     dv1=z/y;
     if(dv1*y==z)
        mcm=z;
  }
  printf("EL m�ximo com�n divisor de %d y %d es %d y el m�nimo com�n m�ltiplo es el %d.\n",x,y,mcd,mcm);
}