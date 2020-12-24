//
// CODIGO: 20171878
// NOMBRE: TORO VERA CARLOS SANTOS
//

#include "operators.hpp"

using namespace std;

int main(int argc, char **argv)
{
    Persona *p1, *p2;

    cin >> p1 >> p2;

    cout << p1 << p2;

    delete p1;
    delete p2;

    return 0;
}
