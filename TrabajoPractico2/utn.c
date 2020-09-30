#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

//*.FUNCIONES BASICAS.*//

/** \brief Obtiene un string
 * \param char* array el cual recorreremos
 * \param char* mensaje
 * \param char* mensajeError
 * \param int min
 * \param int max
 * \param int intentos
 * \return void
 */
int utn_getString(char* array,char* mensaje,char* mensajeError,int min,int max,int intentos)
{
    int ret=-1;
    char auxStr[1000];

    while(intentos>0)
    {
        fflush(stdin);
        printf("%s",mensaje);
        fgets(auxStr,sizeof(auxStr),stdin);
        auxStr[strlen(auxStr)-1] = '\0';//le saco el enter que quedo almacenado en la ultima posicion

        if( array != NULL && strlen(auxStr) >= min && strlen(auxStr) <= max)
        {
            strncpy(array,auxStr,max);
            ret=0;
            break;
        }
        else
        {
            printf("%s",mensajeError);
        }
        intentos--;
    }

    return ret;
}
/** \brief Obtiene un int con rangos predeterminados
 * \param int* numero es un puntero a int en el cual guardaremos el resultado
 * \param char* mensaje es un mensaje en el cual pediremos al usuario que ingrese, y varia para que se utilice la funcion
 * \param char* mensajeError es un mensaje para validar el error
 * \param float rangoMin es el rango minimo el cual puede tener el numero
 * \param float rangoMax es el mango maximo que puede tener el numero
 * \return si esta mal -1, si esta ok 0
 *
 */
int utn_getInt(int* numero, char* mensaje,char* mensajeError,int rangoMin, int rangoMax)
{
    int ret = -1;
    int auxNum;

    printf("%s",mensaje);
    scanf("%i",&auxNum);

    if(numero != NULL)
    {
        while(auxNum<rangoMin || auxNum>rangoMax)
            {
                printf("%s",mensajeError);
                scanf("%i",&auxNum);
            }
        *numero = auxNum;
        ret = 0;
    }

    return ret;
}

char utn_getChar(char* mensaje,char* mensajeError,char letra1, char letra2)
{
    char aux;

    printf("%s",mensaje);
    fflush(stdin);
    scanf("%c",&aux);

    while(aux != letra1 && aux != letra2)
    {
        printf("%s",mensajeError);
        fflush(stdin);
        scanf("%c",&aux);
    }
    return aux;
}

/** \brief Obtiene un flotante con rangos predeterminados
 * \param float* numero es un puntero a flotante en el cual guardaremos el resultado
 * \param char* mensaje es un mensaje en el cual pediremos al usuario que ingrese, y varia para que se utilice la funcion
 * \param char* mensajeError es un mensaje para validar el error
 * \param float rangoMin es el rango minimo el cual puede tener el numero
 * \param float rangoMax es el mango maximo que puede tener el numero
 * \return si esta mal -1, si esta ok 0
 *
 */
float utn_getFloat(float* numero, char* mensaje,char* mensajeError,float rangoMin, float rangoMax)
{
    int ret = -1;
    float auxNum;

    if(numero != NULL)
    {
        printf("%s",mensaje);
        scanf("%f",&auxNum);

        while(auxNum<rangoMin || auxNum>rangoMax)
        {
            printf("%s",mensajeError);
            scanf("%f",&auxNum);
        }
        *numero = auxNum;
        ret = 0;
    }

    return ret;
}

/** \brief Obtiene el factorial de un numero
 * \param un puntero a double en el cual guardaremos el resultado
 * \param por valor recibimos el numero al cual le aplicaremos la funcion
 * \return -1 si esta mal, 0 si esta ok
 *
 */
int utn_getFactorial(double* pFactorial, int numero)
{
    int ret = -1;
    double auxDouble = 1;
    int i;

    if(pFactorial != NULL)
    {
        if (numero == 1 || numero == 0)
        {
            auxDouble = 1;
            ret = 0;
        }
        else
        {
            if(numero < 0)
            {
                printf("No es posible sacar el factorial de un negativo");
            }
            else
            {
                for (i = 1; i <= numero; i++)
                {
                    auxDouble*=i;
                }
                *pFactorial = auxDouble;
                ret = 0;
            }
        }
    }
    return ret;
}

float utn_sacarPromedio(double total, int contador)
{
    float resultado;

    resultado = (float)(total/contador);

    return resultado;
}


