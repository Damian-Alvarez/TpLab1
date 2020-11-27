#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = malloc(sizeof(LinkedList));

    if(this != NULL)
    {
    	this->pFirstNode=NULL;
    	this->size=0;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

	if(this!=NULL)
	{
		returnAux = this->size;
	}


    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
    (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;

	if(this != NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
	{
		pNode = this -> pFirstNode;//en el caso de que sea index 0 return el primer nodo

		for(int i=1;i <= nodeIndex;i++)
		{
			pNode = pNode -> pNextNode;
		}
	}
    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pAuxNode;
    Node* pNewNode;
    pNewNode = (Node*)malloc(sizeof(Node));

	if(this!=NULL && pNewNode != NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
	{
        pNewNode->pElement = pElement;
		this->size++;

		if(nodeIndex==0)
		{
            pNewNode->pNextNode = this->pFirstNode;
            this->pFirstNode = pNewNode;
		}
		else
		{
			pAuxNode=getNode(this,nodeIndex-1);//obtengo el nodo anterior y lo guardo en pAuxNode
			pNewNode->pNextNode = pAuxNode->pNextNode;
			pAuxNode->pNextNode = pNewNode;//guardo el nuevo nodo
		}

		returnAux=0;

	}
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{//ultima posicion
    int returnAux = -1;

    if(this!=NULL)
    {
    	addNode(this,ll_len(this),pElement);
    	returnAux=0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pElement = NULL;
    Node* pAux = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
      {
      	pAux=getNode(this,index);
      	pElement=pAux->pElement;

      	returnAux=pElement;
      }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pAux=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pAux=getNode(this,index);
    	pAux->pElement=pElement;
    	returnAux=0;

    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pAux=NULL;
    Node* pAuxAnterior=NULL;
    Node* pAuxFirstRemove=NULL;
    //Node* pAuxNewFirst=NULL;


    if(this!= NULL && index>=0 && index<ll_len(this))
    {


    	if(index==0)
    	{
        	//pAuxNewFirst=getNode(this,index+1);//obtengo la posicion 1 que va a ser nuestro FirstNode de la ll
        	pAuxFirstRemove=getNode(this,index);//obtengo el nodo que quiero borrar que es de la posicion 0
        	this->pFirstNode=pAuxFirstRemove->pNextNode;//ahora la ll firstnode apunta a la direccion 1 y no a la 0, por lo tanto se borra
        	free(pAuxFirstRemove);//libero la memoria

    	}
    	else
    	{
    		pAuxAnterior=getNode(this,index-1);//guardo el nodo anterior en pAuxAnterior
        	pAux=getNode(this,index);//guardo el nodo que quiero borrar
        	pAuxAnterior->pNextNode=pAux->pNextNode;//guardo la direccion del siguiente que tenia en el que queria borrar en el anterior
        	free(pAux);//libero memoria de pAux
    	}
        this->size--;
    	returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	while(0<ll_len(this))//cuando llegue a 0 ya elimino tdos los elementos
    	{
    		ll_remove(this,0);//borra el primero hasta que no queda nada
    	}
    	returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	ll_clear(this);//borro todos los elementos
    	free(this);//borro la ll
    	returnAux=0;
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    Node* pAuxNode=NULL;

    if(this!=NULL)
    {
    	for(i=0;i<ll_len(this);i++)
    	{
    		pAuxNode=getNode(this,i);
    		if(pAuxNode->pElement==pElement)
    		{
    			returnAux=i;
    		}

    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	if(ll_len(this)==0)
    	{
    		returnAux=1;
    	}
    	else
    	{
    		returnAux=0;
    	}
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    //int returnAux = -1;

    return addNode(this,index,pElement);
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* pAuxNode=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pAuxNode=getNode(this,index);
    	returnAux=pAuxNode->pElement;
    	ll_remove(this,index);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index;

    if(this!=NULL)
    {
    	 index=ll_indexOf(this,pElement);
    	 if(index>=0)
    	 {
    		 returnAux=1;
    	 }
    	 else
    	 {
    		 returnAux=0;
    	 }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* pElementAux;

    if(this!=NULL && this2!=NULL)
    {
    	returnAux=1;
    	for(int i=0;i<ll_len(this2);i++)//recorro this 2
    	{
    		pElementAux=ll_get(this2,i);
    		if(ll_contains(this,pElementAux)==0)
    		{
    			returnAux=0;
    			break;
    		}
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pAux=NULL;
    int i;

    if(this!=NULL && from>=0 && from<ll_len(this) && to>from && to<=ll_len(this))
    {
    	cloneArray = malloc(sizeof(LinkedList));
    	for(i=from;i<to;i++)
    	{
    		pAux=ll_get(this,i);
    		ll_add(cloneArray,pAux);

    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {
    	cloneArray=ll_subList(this,0,ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
   int returnAux =-1;
   int swap;
   int i;
   Node* pAux1;
   Node* pAux2;
   if(this != NULL && pFunc != NULL && ll_len(this)>1 && (order==1 || order==0))
   {
       do
       {
           swap=0;
           for(i=0;i<ll_len(this)-1;i++)
           {
               pAux1 = getNode(this,i);
               pAux2 = getNode(this,i+1);
               if(order==0 && pFunc(pAux1->pElement,pAux2->pElement)<0)
               {
                   swapNode(pAux1,pAux2);
                   swap=1;
               }
               if(order==1 && pFunc(pAux1->pElement,pAux2->pElement)>0)
               {
                   swapNode(pAux1,pAux2);
                   swap=1;
               }
           }
       }while(swap!=0);

       returnAux = 0;
   }
   return returnAux;
}

static void swapNode(Node *a,Node *b)
{
   void* temp = a->pElement;
   a->pElement = b->pElement;
   b->pElement = temp;
}

