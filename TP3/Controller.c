#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int ret=0;
    FILE* pFile;
    pFile = fopen(path,"r");
    ret=parser_EmployeeFromText(pFile, pArrayListEmployee);
    fclose(pFile);
    return ret;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int ret=0;
    FILE* pFile;
    pFile = fopen(path,"rb");
    ret=parser_EmployeeFromBinary(pFile, pArrayListEmployee);
    fclose(pFile);
    return ret;
}

/** \brief Obtiene el mayor id del LinkedList y lo carga en la estructura empleado.
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_lastIdEmployee(LinkedList* pArrayListEmployee)
{
    Employee* bufferEmployee;
    int bufferId;
    int auxId = -1;
    int ret = -1;
    int i;
    int len;
    if(pArrayListEmployee!=NULL)
    {
        len=ll_len(pArrayListEmployee);
        for(i=0; i<len; i++)
        {
            bufferEmployee=(Employee*)ll_get(pArrayListEmployee,i);
            employee_getId(bufferEmployee,&bufferId);
            if(bufferId>auxId)
            {
                auxId=bufferId;
            }
        }
        employe_idInit(auxId);
        ret = 0;
    }
    return ret;
}

/** \brief Obtiene el mayor id del LinkedList y lo carga en la estructura empleado.
 *
 * \param pArrayListEmployee LinkedList*
 * \param id int
 * \param index int*
 * \return int
 *
 */
int controller_searchEmployeeById(LinkedList* pArrayListEmployee,int id,int* index)
{
    Employee* bufferEmployee;
    int bufferId;
    int ret = -1;
    int i;
    int len;
    if(pArrayListEmployee!=NULL)
    {
        len=ll_len(pArrayListEmployee);
        for(i=0; i<len; i++)
        {
            bufferEmployee=(Employee*)ll_get(pArrayListEmployee,i);
            employee_getId(bufferEmployee,&bufferId);
            if(bufferId==id)
            {
                *index=i;
                ret = 0;
            }
        }
    }
    return ret;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int ret = -1;
    char bufferNombre[128];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    Employee* bufferEmployee;
    bufferEmployee = employee_new();
    if(pArrayListEmployee!=NULL && bufferEmployee!=NULL)
    {
        if(!utn_getName(bufferNombre,128,"Ingrese el nombre: ","Nombre Invalido",1,127,10)&&
                !utn_getInt(&bufferHorasTrabajadas,"Ingrese las horas trabajadas: ","Valor invalido",0,INT_MAX,10)&&
                !utn_getInt(&bufferSueldo,"Ingrese el sueldo: ","Valor invalido",0,INT_MAX,10))
        {
            employee_setId(bufferEmployee,employee_idGenerator());
            employee_setNombre(bufferEmployee,bufferNombre);
            employee_setHorasTrabajadas(bufferEmployee,bufferHorasTrabajadas);
            employee_setSueldo(bufferEmployee,bufferSueldo);

            ll_add(pArrayListEmployee,bufferEmployee);
        }
        else
        {
            employee_delete(bufferEmployee);
        }

    }
    return ret;
}

/** \brief Modificar datos de un empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int ret = -1;
    if(pArrayListEmployee != NULL)
    {
        if(ll_len(pArrayListEmployee))
        {
            char bufferNombre[128];
            int bufferHorasTrabajadas;
            int bufferSueldo;
            Employee* bufferEmployee;
            int option;
            int auxIndex;
            int auxId;
            if( !utn_getInt(&auxId,"Ingrese ID del empleado: ","Valor invalido",0,INT_MAX,10)&&
                    !controller_searchEmployeeById(pArrayListEmployee,auxId,&auxIndex))
            {
                do
                {
                    clrscr();
                    bufferEmployee = (Employee*)ll_get(pArrayListEmployee,auxIndex);
                    controller_PrintEmployeeWithFields(pArrayListEmployee,auxIndex);
                    printf("4. Salir.");
                    utn_getInt(&option,"\nSeleccione campo a modificar: ","Valor invalido",1,5,10);
                    switch(option)
                    {
                    case 1:
                        if(!utn_getName(bufferNombre,128,"Ingrese el nombre: ","Nombre Invalido",1,127,10))
                        {
                            employee_setNombre(bufferEmployee,bufferNombre);
                        }
                        break;
                    case 2:
                        if(!utn_getInt(&bufferHorasTrabajadas,"Ingrese las horas trabajadas: ","Valor invalido",0,INT_MAX,10))
                        {
                            employee_setHorasTrabajadas(bufferEmployee,bufferHorasTrabajadas);
                        }
                        break;
                    case 3:
                        if(!utn_getInt(&bufferSueldo,"Ingrese el sueldo: ","Valor invalido",0,INT_MAX,10))
                        {
                            employee_setSueldo(bufferEmployee,bufferSueldo);
                        }
                        break;
                    }
                }
                while(option!=4);
                ret=0;
            }
            else
            {
                printf("Id invalido.");
            }
        }
        else
        {
            printf("No existen registros cargados.");
        }
    }
    return ret;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int ret = -1;
    if(pArrayListEmployee != NULL)
    {
        if(ll_len(pArrayListEmployee)>0)
        {
            Employee* bufferEmployee;
            int option;
            int auxIndex;
            int auxId;
            if( !utn_getInt(&auxId,"Ingrese ID del empleado: ","Valor invalido",0,INT_MAX,10)&&
                    !controller_searchEmployeeById(pArrayListEmployee,auxId,&auxIndex))
            {
                do
                {
                    clrscr();
                    bufferEmployee = (Employee*)ll_get(pArrayListEmployee,auxIndex);
                    printf("Desea eliminar el siguiente registro?\n");
                    controller_PrintEmployeeWithFields(pArrayListEmployee,auxIndex);
                    utn_getInt(&option,"[1. Aceptar / 2.Cancelar]: ","Valor invalido",1,2,10);
                    switch(option)
                    {
                    case 1:
                        employee_delete(bufferEmployee);
                        ll_remove(pArrayListEmployee,auxIndex);
                        printf("Registro eliminado");
                        break;
                    case 2:
                        printf("Operacion cancelada.");
                        break;
                    }
                }
                while(option!=1 && option!=2);
                ret=0;
            }
            else
            {
                printf("Id invalido.");
            }
        }
        else
        {
            printf("No existen registros cargados.");
        }
    }
    return ret;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int i;
    int ret=0;
    int len;
    if(pArrayListEmployee!=NULL)
    {
        if(ll_len(pArrayListEmployee)>0)
        {
            len=ll_len(pArrayListEmployee);
            for(i=0; i<len; i++)
            {
                controller_PrintEmployee(pArrayListEmployee,i);
            }
            ret=0;
        }
        else
        {
            printf("No existen registros cargados.");
        }
    }
    return ret;
}
/** \brief Imprime un empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \param index int
 * \return int
 *
 */
int controller_PrintEmployee(LinkedList* pArrayListEmployee, int index)
{
    Employee* bufferEmployee;
    int bufferId;
    char bufferNombre[4096];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int ret=0;
    if(pArrayListEmployee!=NULL && index>=0 && index<ll_len(pArrayListEmployee))
    {
        bufferEmployee=(Employee*)ll_get(pArrayListEmployee,index);
        employee_getId(bufferEmployee,&bufferId);
        employee_getNombre(bufferEmployee,bufferNombre);
        employee_getHorasTrabajadas(bufferEmployee,&bufferHorasTrabajadas);
        employee_getSueldo(bufferEmployee,&bufferSueldo);
        printf("%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
        ret=0;
    }
    return ret;
}

/** \brief Imprime un empleado con sus campos numerados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \param index int
 * \return int
 *
 */
int controller_PrintEmployeeWithFields(LinkedList* pArrayListEmployee, int index)
{
    Employee* bufferEmployee;
    int bufferId;
    char bufferNombre[4096];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int ret=0;
    if(pArrayListEmployee!=NULL && index>=0 && index<ll_len(pArrayListEmployee))
    {
        bufferEmployee=(Employee*)ll_get(pArrayListEmployee,index);
        employee_getId(bufferEmployee,&bufferId);
        employee_getNombre(bufferEmployee,bufferNombre);
        employee_getHorasTrabajadas(bufferEmployee,&bufferHorasTrabajadas);
        employee_getSueldo(bufferEmployee,&bufferSueldo);
        printf("ID: %d\n1.Nombre: %s\n2.Horas trabajadas: %d\n3.Sueldo: %d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
        ret=0;
    }
    return ret;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int ret = -1;
    if(pArrayListEmployee != NULL)
    {
        int order;
        int option;
        if(ll_len(pArrayListEmployee)>0)
        {
            clrscr();
            if(!utn_getInt(&option,"Seleccione criterio para ordenar:\n1.Id\n2.Nombre\n3.Horas Trabajadas\n4.Sueldo\n-> ","Opcion invalida\n",1,4,10))
            {
                clrscr();
                if(!utn_getInt(&order,"Seleccione orden:\n1.Ascendente\n2.Descendente\n-> ","Opcion invalida\n",1,2,10))
                {
                    if(order==2)
                    {
                        order=0;
                    }
                    switch(option)
                    {
                    case 1:
                        ll_sort(pArrayListEmployee,employee_compareId,order);
                        break;
                    case 2:
                        ll_sort(pArrayListEmployee,employee_compareId,order);
                        ll_sort(pArrayListEmployee,employee_compareNombre,order);
                        break;
                    case 3:
                        ll_sort(pArrayListEmployee,employee_compareId,order);
                        ll_sort(pArrayListEmployee,employee_compareHorasTrabajadas,order);
                        break;
                    case 4:
                        ll_sort(pArrayListEmployee,employee_compareId,order);
                        ll_sort(pArrayListEmployee,employee_compareSueldo,order);
                        break;
                    }
                    ret = 0;
                    printf("Operacion completada");
                }
                else
                {
                    printf("Demasiados intentos erroneos, operacion cancelada.");
                }
            }
            else
            {
                printf("Demasiados intentos erroneos, operacion cancelada.");
            }
        }
        else
        {
            printf("No existen registros cargados.");
        }
    }
    return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    Employee* bufferEmployee;
    FILE* pf;
    int bufferId;
    char bufferNombre[4096];
    int bufferHorasTrabajadas;
    int bufferSueldo;
    int i;
    int ret=0;
    int len;
    pf=fopen(path,"w");
    if(pArrayListEmployee!=NULL && pf!=NULL)
    {
        fprintf(pf,"id,nombre,horasTrabajadas,sueldo\n");
        len=ll_len(pArrayListEmployee);
        for(i=0; i<len; i++)
        {
            bufferEmployee=(Employee*)ll_get(pArrayListEmployee,i);
            employee_getId(bufferEmployee,&bufferId);
            employee_getNombre(bufferEmployee,bufferNombre);
            employee_getHorasTrabajadas(bufferEmployee,&bufferHorasTrabajadas);
            employee_getSueldo(bufferEmployee,&bufferSueldo);
            fprintf(pf,"%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            ret++;
        }
        fclose(pf);
    }
    return ret;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    Employee* bufferEmployee;
    FILE* pf;
    int i;
    int ret=0;
    int len;
    pf=fopen(path,"wb");
    if(pArrayListEmployee!=NULL && pf!=NULL)
    {
        len=ll_len(pArrayListEmployee);
        for(i=0; i<len; i++)
        {
            bufferEmployee=(Employee*)ll_get(pArrayListEmployee,i);
            fwrite(bufferEmployee,sizeof(Employee),1,pf);
            ret++;
        }
        fclose(pf);
    }
    return ret;
}
