#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/


int main()
{
    int option = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    clrscr();
    printf("/****************************************************\
\nMenu:\
\n1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\
\n2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\
\n\n3. Alta de empleado\
\n4. Modificar datos de empleado\
\n5. Baja de empleado\
\n6. Listar empleados\
\n7. Ordenar empleados\
\n\n8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\
\n9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\
\n\n10. Salir\
\n*****************************************************/");
     utn_getInt(&option,"\nSeleccione opcion: ","Opcion invalida",1,10,10);
        switch(option)
        {
            case 1:
                ll_clear(listaEmpleados);
                printf("%d elementos cargados\n",controller_loadFromText("data.csv",listaEmpleados));
                controller_lastIdEmployee(listaEmpleados);
                myPause();
                break;
            case 2:
                ll_clear(listaEmpleados);
                printf("%d elementos cargados\n",controller_loadFromBinary("datasavebin",listaEmpleados));
                controller_lastIdEmployee(listaEmpleados);
                myPause();
                break;
            case 3:
                controller_addEmployee(listaEmpleados);
                myPause();
                break;
            case 4:
                controller_editEmployee(listaEmpleados);
                myPause();
                break;
            case 5:
                controller_removeEmployee(listaEmpleados);
                myPause();
                break;
            case 6:
                controller_ListEmployee(listaEmpleados);
                myPause();
                break;
            case 7:
                controller_sortEmployee(listaEmpleados);
                myPause();
                break;
            case 8:
                printf("%d elementos guardados\n",controller_saveAsText("data.csv",listaEmpleados));
                myPause();
                break;
            case 9:
                printf("%d elementos guardados\n",controller_saveAsBinary("datasavebin",listaEmpleados));
                myPause();
                break;
        }
    }while(option != 10);
    return 0;
}
