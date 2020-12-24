/*
 * NOMBRE: TORO VERA CARLOS SANTOS
 * CODIGO: 20171878
 */

#include "Ambulatorio.h"
#include "Urgencia.h"
#include "Emergencia.h"
#include "ListaDePacientes.h"

int main(int argc, char **argv)
{
    ListaDePacientes lista;

    Ambulatorio amb;
    amb.setDni(123);
    amb.setNombre("Jaimito");
    amb.setCodMed("ABC123");
    amb.setPorcSeguro(32.15);

    Urgencia urg;
    urg.setDni(456);
    urg.setNombre("Pepito");
    urg.setCodMed("ABC123");
    urg.setPorcSeguro(10.15);
    urg.setPorcUrgencia(40.18);

    Emergencia eme;
    eme.setDni(789);
    eme.setNombre("Luisito");
    eme.setCodMed("ABC123");
    eme.setTelefonoRef(999333111);
    eme.setNombreRef("Ursula");

    lista + amb;
    lista + urg;
    lista + eme;

    return 0;
}
