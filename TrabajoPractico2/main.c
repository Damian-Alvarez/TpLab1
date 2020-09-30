#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayEmployees.h"
#include "utn.h"


#define QTY_EMPLOYEES 5

int main()
{
    sEmployee listEmployees[QTY_EMPLOYEES];

    int option;
    int subOption;
    int flag1 = 0;
    int order;

    initEmployees(listEmployees, QTY_EMPLOYEES);

    do
    {
        printf("\n1.ALTA");
        printf("\n2.MODIFICAR");
        printf("\n3.BAJA");
        printf("\n4.INFORMAR");
        printf("\n 1.LISTA DE LOS EMPLEADOS ORDENADOS ALFABETICAMENTE POR APELLIDO Y SECTOR");
        printf("\n 1.TOTAL Y PROMEDIO DE LOS SALARIOS, Y CUANTOS EMPLEADOS SUPERAN EL SALARIO PROMEDIO");
        printf("\n5.SALIR\n");
        utn_getInt(&option,"\nIngrese la opcion: ","\nInvalido, reingrese: ",0,7);

        switch(option)
        {
        case 1:
            if(altaEmpleados(listEmployees,QTY_EMPLOYEES) == 0)
            {
                flag1 = 1;
            }
            break;

        case 2:
            if(flag1)
            {
                modificarEmpleado(listEmployees, QTY_EMPLOYEES);
            }
            else
            {
                printf("\nNo se cargaron empleados\n");
            }
            break;

        case 3:
            if(flag1)
            {
                borrarEmpleado(listEmployees, QTY_EMPLOYEES);
            }
            else
            {
                printf("\nNo se cargaron empleados\n");
            }
            break;

        case 4:
            if(flag1)
            {
                printf("\n 1.LISTA DE LOS EMPLEADOS ORDENADOS ALFABETICAMENTE POR APELLIDO Y SECTOR");
                printf("\n 2.TOTAL Y PROMEDIO DE LOS SALARIOS, Y CUANTOS EMPLEADOS SUPERAN EL SALARIO PROMEDIO");

                utn_getInt(&subOption,"\nIngrese la opcion: ","\nInvalido, reingrese: ",0,3);
                switch(subOption)
                {
                    case 1:
                    utn_getInt(&order,"\n0.Ascendente\n1.Descendente\norden: ","\nInvalido, reingrese: ",0,1);
                    sortEmployees(listEmployees, QTY_EMPLOYEES, order);
                    printEmployees(listEmployees, QTY_EMPLOYEES);
                    break;

                    case 2:
                    totalYPromedioSalariosEmpleados(listEmployees, QTY_EMPLOYEES);
                    break;

                    default:
                        printf("\nOpcion Inexistente");
                        break;
                }
            }
            else{
                printf("\nNo se han cargado empleados\n");
            }
            break;

        case 5:
            break;

        default:
            printf("\nOpcion Inexistente");
            break;
        }

    }
    while(option != 5);

    return 0;
}
