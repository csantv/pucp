/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "ListaDePacientes.h"

ListaDePacientes::ListaDePacientes():
lUrg(nullptr),
lAmb(nullptr),
lEmer(nullptr)
{}

ListaDePacientes::ListaDePacientes(const ListaDePacientes &orig)
{
    int numUrg = orig.numUrg(), numAmb = orig.numAmb(), numEme = orig.numEme();
    lUrg = new Urgencia[numUrg+1];
    lAmb = new Ambulatorio[numAmb+1];
    lEmer = new Emergencia[numEme+1];
    for (int i = 0; i < numUrg; ++i) lUrg[i] = orig.lUrg[i];
    for (int i = 0; i < numAmb; ++i) lAmb[i] = orig.lAmb[i];
    for (int i = 0; i < numEme; ++i) lEmer[i] = orig.lEmer[i];
}

ListaDePacientes::~ListaDePacientes()
{
    delete[] lAmb;
    delete[] lEmer;
    delete[] lUrg;
}

std::istream& operator>>(std::istream &is, ListaDePacientes &lista)
{
    int dni, telef; char nombre[100], codigo[100], nombreref[100], tipo, _; double tarifa = 0, descuento = 0;
    while (true) {
        if (is.peek() == '\n') break;
        is >> dni >> _;
        is.getline(nombre, 100, ',');
        is >> tipo >> _;
        is.getline(codigo, 100, ',');
        if (tipo == 'U') {
            is >> tarifa >> _ >> descuento >> _;
            Urgencia urg;
            urg.setNombre(nombre); urg.setDni(dni); urg.setCodMed(codigo); urg.setPorcSeguro(tarifa);
            urg.setPorcUrgencia(descuento);
            lista + urg;
        } else if (tipo == 'A') {
            is >> tarifa >> _;
            Ambulatorio amb;
            amb.setNombre(nombre); amb.setDni(dni); amb.setCodMed(codigo); amb.setPorcSeguro(tarifa);
            lista + amb;
        } else if (tipo == 'E') {
            is.getline(nombreref, 100, ',');
            is >> telef >> _;
            Emergencia eme;
            eme.setNombre(nombre); eme.setDni(dni); eme.setCodMed(codigo); eme.setNombreRef(nombreref);
            eme.setTelefonoRef(telef);
            lista + eme;
        }
    }
    return is;
}

void ListaDePacientes::operator+(const Ambulatorio &rhs)
{
    if (!lAmb) lAmb = new Ambulatorio();
    int numDat = numAmb();
    Ambulatorio *aux = new Ambulatorio[numDat+2];
    for (int i = 0; i < numDat; ++i) aux[i] = lAmb[i];
    aux[numDat] = rhs;
    delete lAmb;
    lAmb = aux;
}

void ListaDePacientes::operator+(const Emergencia &rhs)
{
    if (!lEmer) lEmer = new Emergencia();
    int numDat = numEme();
    Emergencia *aux = new Emergencia[numDat+2];
    for (int i = 0; i < numDat; ++i) aux[i] = lEmer[i];
    aux[numDat] = rhs;
    delete lEmer;
    lEmer = aux;
}

void ListaDePacientes::operator+(const Urgencia &rhs)
{
    if (!lUrg) lUrg = new Urgencia();
    int numDat = numUrg();
    Urgencia *aux = new Urgencia[numDat+2];
    for (int i = 0; i < numDat; ++i) aux[i] = lUrg[i];
    aux[numDat] = rhs;
    delete lUrg;
    lUrg = aux;
}

int ListaDePacientes::numAmb() const
{
    int num = 0;
    while (!lAmb[num].isNull()) num++;
    return num;
}

int ListaDePacientes::numUrg() const
{
    int num = 0;
    while (!lUrg[num].isNull()) num++;
    return num;
}

int ListaDePacientes::numEme() const
{
    int num = 0;
    while (!lEmer[num].isNull()) num++;
    return num;
}
