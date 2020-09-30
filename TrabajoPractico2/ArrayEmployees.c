#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include "ArrayEmployees.h"
#include "utn.h"

static int id = 0;

static int autoIncrementId(void)
{

    return id++;
}


int initEmployees(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int i;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            listEmployees[i].isEmpty = 0;
        }
        ret = 0;
    }

    return ret;
}

int printEmployees(sEmployee listEmployees[], int len)
{
    int ret = -1;

    int i;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(listEmployees[i].isEmpty == 1)
            {
                mostrarUnEmpleado(listEmployees,len,i);
                ret = 0;
            }
        }
        if(ret == -1)
        {
            printf("\nNo hay empleados cargados\n");
        }
    }
    return ret;
}

int mostrarUnEmpleado(sEmployee listEmployees[], int len, int index)
{
    int ret = -1;

    if(listEmployees != NULL)
    {
            printf("\nId: %d\nNombre: %s\nApellido: %s\nSalario: %.2f\nSector: %d\n",listEmployees[index].id,
                                                                                     listEmployees[index].name,
                                                                                     listEmployees[index].lastName,
                                                                                     listEmployees[index].salary,
                                                                                     listEmployees[index].sector);
            ret = 0;
    }
    return ret;
}


int buscarLibre(sEmployee listEmployees[], int len)
{
    int index = -1;
    int i;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(listEmployees[i].isEmpty == 0)
            {
                index = i;
            }
        }
        if(index == -1)
        {
            printf("\nNo hay espacio");
        }
    }
    return index;
}


int addEmployees(sEmployee listEmployees[], int len, int id, char* name, char* lastName, float salary, int sector)
{
    int ret = -1;
    int index;


    if(listEmployees != NULL && len >= 0)
    {
        index = buscarLibre(listEmployees,len);

        if(index != -1)
        {
            strncpy(listEmployees[index].name,name,sizeof(listEmployees[index].name));
            strncpy(listEmployees[index].lastName,lastName,sizeof(listEmployees[index].lastName));
            listEmployees[index].salary = salary;
            listEmployees[index].sector = sector;
            listEmployees[index].isEmpty = 1;
            listEmployees[index].id = autoIncrementId();
        }
        ret = 0;
    }

    return ret;
}

int altaEmpleados(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int i;
    char respuesta;
    char name[51];
    char lastName[51];
    float salary;
    int sector;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            utn_getString(name,"\nIngrese el nombre: ","\nInvalido, reingrese: ",3,51,3);
            utn_getString(lastName,"\nIngrese el apellido: ","\nInvalido, reingrese: ",3,51,3);
            utn_getFloat(&salary,"\nIngrese el salario: ","\nInvalido, reingrese: ",0,FLT_MAX);
            utn_getInt(&sector,"\nIngrese el sector: ","\nInvalido, reingrese: ",0,INT_MAX);

            if(addEmployees(listEmployees,len,id,name,lastName,salary,sector) == 0)
            {
                printf("\nAlta Exitosa");
            }

            respuesta = utn_getChar("\n¿Quiere continuar cargando altas? (s/n): ","\nInvalido, reingrese: ",'n','s');
            if(respuesta == 'n')
            {
                break;
            }
        }
        ret = 0;
    }
    return ret;
}

int findEmployeeById(sEmployee listEmployees[], int len, int id)
{
    int index = -1;
    int i;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(id == listEmployees[i].id && listEmployees[i].isEmpty == 1)
            {
                index = i;
                break;
            }
        }

        if(index == -1)
        {
            printf("\nNo existe ese empleado");
        }
    }

    return index;
}


int modificarEmpleado(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int idAux;
    int index;

    if(listEmployees != NULL && len >= 0)
    {
        if(printEmployees(listEmployees,len) == 0)
        {
            utn_getInt(&idAux,"\nIngrese el id: ","\nInvalido, reingrese: ",0,1000);
            index = findEmployeeById(listEmployees,len,idAux);

            if(index != -1)
            {
                utn_getString(listEmployees[index].name,"\nIngrese el nombre: ","\nInvalido, reingrese: ",3,51,3);
                utn_getString(listEmployees[index].lastName,"\nIngrese el apellido: ","\nInvalido, reingrese: ",3,51,3);
                utn_getFloat(&listEmployees[index].salary,"\nIngrese el salario: ","\nInvalido, reingrese: ",0,FLT_MAX);
                utn_getInt(&listEmployees[index].sector,"\nIngrese el sector: ","\nInvalido, reingrese: ",0,INT_MAX);
                printf("\nEmpleado modificado exitosamente\n");
                ret = 0;
            }

        }

    }

    return ret;
}


int removeEmployee(sEmployee listEmployees[], int len, int id)
{
    int ret = -1;
    int index;

    if(listEmployees != NULL && len >= 0)
       {
         index = findEmployeeById(listEmployees, len, id);
         listEmployees[index].isEmpty = 0;
         ret = 0;
       }

    return ret;
}


int borrarEmpleado(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int idAux;

    if(listEmployees != NULL && len >= 0)
    {
        if(printEmployees(listEmployees,len) == 0)
        {
            utn_getInt(&idAux,"\nIngrese el id: ","\nInvalido, reingrese: ",0,1000);
            if(removeEmployee(listEmployees,len,idAux) == 0)
            {
                printf("\nEmpleado eliminado\n");
                ret = 0;
            }
        }

    }
    return ret;
}


void swapEmployee(sEmployee listEmployees [], int i)
{
    sEmployee auxEmployee;

    auxEmployee = listEmployees[i];
    listEmployees[i] = listEmployees[i+1];
    listEmployees[i+1] = auxEmployee;

}


int sortEmployees(sEmployee listEmployees[], int len, int order)
{
    int ret = -1;
    int i;
    int flagSwap;

    if(listEmployees != NULL && len >= 0)
    {
        do
        {
            flagSwap = 0;

            for(i=0; i<len-1; i++)
            {
                if(order == 0 && strcmp(listEmployees[i].lastName, listEmployees[i+1].lastName) > 0)//A-Z
                {
                    swapEmployee(listEmployees,i);
                    flagSwap = 1;
                }
                if(order == 1 && strcmp(listEmployees[i].lastName, listEmployees[i+1].lastName) < 0)//Z-A
                {
                    swapEmployee(listEmployees,i);
                    flagSwap = 1;
                }
                if(strcmp(listEmployees[i].lastName,listEmployees[i+1].lastName) == 0)
                {
                    if(order == 0 && listEmployees[i].sector > listEmployees[i+1].sector)
                    {
                        swapEmployee(listEmployees,i);
                        flagSwap=1;
                    }
                    if(order == 1 && listEmployees[i].sector < listEmployees[i+1].sector)
                    {
                        swapEmployee(listEmployees,i);
                        flagSwap=1;
                    }
                }
            }

        } while(flagSwap);

        ret = 0;
    }

    return ret;
}


int cantidadEmpleados(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int i;
    int cantidadEmpleados = 0;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(listEmployees[i].isEmpty == 1)
            {
                cantidadEmpleados++;
            }
        }
        ret = cantidadEmpleados;
    }

    return ret;
}

int cantidadEmpleadosQueSuperanElPromedio(sEmployee listEmployees[], int len, float promedioSalarios)
{
    int ret = -1;
    int i;
    int cantidadSuperanPromedio = 0;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(listEmployees[i].isEmpty == 1 && listEmployees[i].salary > promedioSalarios)
            {
                cantidadSuperanPromedio++;
            }
        }
        ret = cantidadSuperanPromedio;
    }
    return ret;
}


int totalYPromedioSalariosEmpleados(sEmployee listEmployees[], int len)
{
    int ret = -1;
    int i;
    double totalSalarios = 0;
    float promedioSalarios;
    int cantEmpleados = 0;
    int cantidadSuperanPromedio = 0;

    if(listEmployees != NULL && len >= 0)
    {
        for(i=0;i<len;i++)
        {
            if(listEmployees[i].isEmpty == 1)
            {
                totalSalarios += listEmployees[i].salary;
            }

        }
        cantEmpleados = cantidadEmpleados(listEmployees,len);
        promedioSalarios = utn_sacarPromedio(totalSalarios,cantEmpleados);
        cantidadSuperanPromedio = cantidadEmpleadosQueSuperanElPromedio(listEmployees,len,promedioSalarios);

        printf("\nEl total de los salarios es: %.2f, el promedio de los salarios es: %.2f, y la cantidad de empleados que superan el promedio de salarios es: %d\n",totalSalarios,promedioSalarios,cantidadSuperanPromedio);
        ret = 0;
    }

    return ret;
}
