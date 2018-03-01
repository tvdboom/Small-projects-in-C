#include <iostream>
#include <fstream>

#define CANTIDAD_PRIMOS 100000
#define TOPE_ARRAY 99999 //Debe ser CANTIDAD_PRIMOS - 1

using namespace std;

class Primos {
    public:

    unsigned int array [CANTIDAD_PRIMOS];

    bool esPrimo(unsigned int num) {
        bool flag = false;
        for(unsigned int i = 0; i < TOPE_ARRAY && flag == false; i++) {
            if (num == array[i])
                flag = true;
        }

        return flag;
    }

    unsigned int ultimoPrimo() {
        unsigned int pos = 0;
        for (; array[pos] != NULL; pos++);
        return pos;
    }

    void constructor () {
        array[0] = 2;
        array[1] = 3;
        for (unsigned int i = 1; i < CANTIDAD_PRIMOS; i++)
            array[i] = NULL; //Lleno de NULL el array
    }

    void imprimir () {
        cout << "1";
        for (unsigned int i = 0; i < CANTIDAD_PRIMOS; i++)
            cout << ", " << array[i];
        cout << endl;
    }

    void guardar() {
        ofstream fs("lista.txt");
        fs << "1" << endl;
        for (unsigned int i = 0; i < CANTIDAD_PRIMOS; i++)
            fs << array [i] << endl;
        fs.close();
    }
};

int main() {

    Primos nPrimos = new Primos();
    unsigned int numero;
    unsigned int nActual = 3;
    unsigned int i;
    bool flag;

    for(bool completo = false; completo == false; nActual += 2) {

    i = 0;
    flag = false;
    //Revisa solo un número, el de nActual. Es necesario iterarlo
    for(; flag == false && (nPrimos.array[i] != NULL); i++) {
        if (nActual % nPrimos.array[i] == 0)
            flag = true; //Si al dividir por un número primo da resto 0, digo que no es primo y paso al siguiente
        else //Si el resto es distinto de 0
            if (nPrimos.array[i + 1] == NULL) //Y además, no quedan más números en el array
                nPrimos.array[nPrimos.ultimoPrimo()] = nActual; //Guardo el número en el array

        if (nPrimos.array[TOPE_ARRAY] != NULL)
                completo = true;
    }
    }

    nPrimos.guardar();

    return 0;
}
