#include <stdio.h>
main()
{
      int a,b,c,x=0;
      printf("Introduzca un numero ");
      scanf("%i",&a);
      printf("Introduzca otro numero ");
      scanf("%i",&b);
      printf("Introduzca otro numero ");
      scanf("%i",&c);
      if(a>b&&b>c) printf("El orden de mayor a menor es %i>%i>%i",a,b,c);
      else if(a>c&&c>b) printf("El orden de mayor a menor es %i>%i>%i",a,c,b);
           else if(b>a&&a>c) printf("El orden de mayor a menor es %i>%i>%i",b,a,c);
                else if(b>c&&c>a) printf("El orden de mayor a menor es %i>%i>%i",b,c,a);
                     else if(c>a&&a>b) printf("El orden de mayor a menor es %i>%i>%i",c,a,b);
                          else printf("El orden de mayor a menor es %i>%i>%i",c,b,a);
      system("pause");
}
