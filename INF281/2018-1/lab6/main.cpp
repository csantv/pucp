#include "Bib_Func_Preg1.h"
#include "Bib_Func_Preg2.h"

int main(int argc, char **argv)
{
    void *usuarios;
    leerUsuarios(usuarios);
    imprimirUsuarios(usuarios);
    leerPrestamos(usuarios);
    imprimirPrestamos(usuarios);
    return 0;
}