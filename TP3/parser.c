#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int returnAux= 0;

    char nombreAux[100];
    char horasAux[100];
    char idAux[100];
    char sueldoAux[100];
    Employee* employee;

    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"[^\n]\n");
        do
        {
            fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",  idAux,
            											nombreAux,
														horasAux,
														sueldoAux);

            employee = employee_newParametros(idAux,nombreAux,horasAux,sueldoAux);

            if(employee != NULL)
            {
                ll_add(pArrayListEmployee,employee);
                returnAux++;
            }
        }while(!feof(pFile));
    }
    return returnAux;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    int returnAux= 0;

    if(pArrayListEmployee!=NULL && pFile!=NULL)
    {
        do
        {
    Employee* employee = employee_new();
            if(employee != NULL)
            {
                if(fread(employee,sizeof(Employee),1,pFile))
                {
                   ll_add(pArrayListEmployee,employee);
                   returnAux++;
                }
                else
                {
                   // employee_delete(employee);
                    free(employee);
                    returnAux=-1;
                }
            }
        }while(!feof(pFile));
    }
    return returnAux;
}
