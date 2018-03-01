#include <stdio.h>
main()
{
      int pass, cont;
      while(pass!=9999){
      printf("\nIntroduzca el password ");
      scanf("%i",&pass);
      if (pass==9999) printf("Password correcto");
      else printf("Password incorrecto");}
      while(cont++<1000000000);
      FILE *a;
      FILE *b;
      a=fopen("mensajecifrado.txt","r");
      b=fopen("original.txt","a");
      char c,num;
      int clave=0;
      if (a!=NULL&&b!=NULL){
      while (clave<25){
                  clave=clave+1;
                  c=getc(a);
            while (c!=EOF){
                  c=c-clave;  
                  if (c<96){ num=c-96; c=122-num;}
                  else if (c<64){ num=c-64; c=90-num;}
                  putc(c,b);
                  c=getc(a);
                  }
                  fprintf(b,"\n");
                  fclose(a);
                  a=fopen("mensajecifrado.txt","r");
                  }
                  }
      else{ printf("Error al leer el archivo"); system("pause>null");}
fclose(a);
fclose(b);
}
