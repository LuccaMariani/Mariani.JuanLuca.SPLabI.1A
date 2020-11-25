#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "menu.h"
#include "bicicleta.h"
#include "LinkedList.h"
#include "parser.h"
#include "utn.h"

eBici* bici_New()
{
    eBici* nuevaBici;
    nuevaBici = (eBici*) malloc(sizeof(eBici));

    return nuevaBici;
}

void bicis_borrar(eBici* this)
{
    if(this != NULL)
    {
        free(this);
    }
}

eBici* bici_NewParametros(char* id_bike, char* nombre, char* tipo, char* tiempo)
{
    eBici* nuevaBici = NULL;
    nuevaBici= bici_New();

    if(id_bike != NULL && nombre != NULL && tipo != NULL && tiempo != NULL)
    {

        if(bici_SetId(nuevaBici, atoi(id_bike)) == -1 ||
           bici_SetNombre(nuevaBici, nombre) == -1 ||
           bici_SetTipo(nuevaBici, tipo) == -1 ||
           bici_SetTiempo(nuevaBici, atoi(tiempo)) == -1)
        {
            bicis_borrar(nuevaBici);
            nuevaBici = NULL;
        }
        else
        {
            bici_SetId(nuevaBici, atoi(id_bike));
            bici_SetNombre(nuevaBici, nombre);
            bici_SetTipo(nuevaBici, tipo);
            bici_SetTiempo(nuevaBici, atoi(tiempo));
        }
    }
    return nuevaBici;
}

///#################################### GET Y SET ##############

int bici_SetId(eBici* this, int id)
{
    int retorno = 0;
    if(this != NULL && id > 0)
    {
        this->id_bici = id;
        retorno = 1;
    }
    return retorno;
}

int bici_GetId(eBici* this, int* id)
{
    int retorno = 0;

    if(this != NULL && id != NULL)
    {
        *id = this->id_bici;
        retorno = 1;
    }

    return retorno;
}

int bici_SetNombre(eBici* this, char* nombre)
{
    int retorno = 0;
    if (this != NULL && nombre != NULL)
    {
        strcpy(this->nombre, nombre);
        retorno = 1;
    }
    return retorno;
}

int bici_GetNombre(eBici* this, char* nombre)
{
    int retorno = 0;
    if (this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        retorno = 1;
    }

    return retorno;
}

int bici_SetTipo(eBici* this, char* tipo)
{
    int retorno = 0;
    if(this != NULL && tipo != NULL)
    {
        strcpy(this->tipo, tipo);
        retorno = 1;
    }
    return retorno;
}

int bici_GetTipo(eBici* this, char* tipo)
{
    int retorno = 0;

    if(this != NULL && tipo != NULL)
    {
        strcpy(tipo, this->tipo);
        retorno = 1;
    }

    return retorno;
}

int bici_SetTiempo(eBici* this, int tiempo)
{
    int retorno = 0;
    if(this != NULL)
    {
        this->tiempo= tiempo;
        retorno = 1;
    }

    return retorno;
}

int bici_GetTiempo(eBici* this, int* tiempo)
{
    int retorno = 0;
    if(this != NULL)
    {
        *tiempo = this->tiempo;
        retorno = 1;
    }
    return retorno;
}

///#################################

int menu_1_cargarTexto(char* pArchivo, LinkedList* pLista)
{
    int retorno= -1;

    FILE* pFile;
    pFile= fopen(pArchivo, "r");

    if(pFile!=NULL)
    {
        if(parser_BicicletaCargarTexto(pFile, pLista))
        {
            retorno= 1;
        }
    }
    fclose(pFile);
    return retorno;
}


int menu_2_listarBicicletas(LinkedList* listaBicicletas)
{
    int retorno= -1;

    int auxId_bike;
    char auxNombre[100];
    char auxTipo[100];
    int auxTiempo;

    eBici* nuevaBici;

    if(listaBicicletas != NULL)
    {

        if(ll_len(listaBicicletas)>0)
        {
            printf(" Id |         Nombre |            Tipo |      Tiempo |\n");
            printf("    |                |                 |             |\n");

            for(int i=0; i<ll_len(listaBicicletas); i++)
            {
                nuevaBici= (eBici*) ll_get(listaBicicletas, i);

                bici_GetId(nuevaBici, &auxId_bike);
                bici_GetNombre(nuevaBici, auxNombre);
                bici_GetTipo(nuevaBici, auxTipo);
                bici_GetTiempo(nuevaBici, &auxTiempo);
                printf("%3d |  %13s |   %13s |  %10d |\n",auxId_bike, auxNombre, auxTipo, auxTiempo);
            }
            retorno = 1;
        }
    }
    return retorno;
}

int menu_4_filtrarPorTipos(LinkedList* listaBicicletas,LinkedList* listaFiltrada)
{
    int retorno=-1;
    int opcionBici;
    char biciElejida[20];

    if(listaBicicletas!=NULL)
    {


        printf("- Elija el tipo de bicicleta a filtrar.\n 1 - BMX\n 2 - PASEO\n 3 - MTB\n 4 - PLAYERA\n");
        getInt("\n>","Error, escriba un numero del 1 al 4", 1,4,3, &opcionBici);

        switch(opcionBici)
        {
            case 1:
                strcpy(biciElejida,"BMX");
                break;
            case 2:
                strcpy(biciElejida,"PASEO");
                break;
            case 3:
                strcpy(biciElejida, "MTB");
                break;
            case 4:
                strcpy(biciElejida, "PLAYERA");
                break;
        }

        printf("\n\n- Bicicleta %s elejida correctamente.", biciElejida);
        listaFiltrada= ll_filter_parametro(listaBicicletas, filtroBicicletas, biciElejida);

        parser_BicicletaGuardarTexto("bicicletas_filtradas.csv", listaFiltrada);

        retorno=1;
    }

    return retorno;
}
int filtroBicicletas(void* pFilter, char* temp)
{
    int retorno= -1;

    if(pFilter!=NULL)
    {
        eBici* nuevaBici = (eBici*)pFilter;

        if(strcmp(nuevaBici->tipo, temp)==0)
        {
            retorno=1;
        }
    }
    return retorno;
}

int menu_5_listarOrdenadas(LinkedList* listaBicicletas,LinkedList* listaOrdenada)
{
    int retorno=-1;

    listaOrdenada= ll_clone(listaBicicletas);

    if(listaOrdenada!=NULL)
    {
        ll_sort(listaOrdenada, ordenarTipoTiempo, 1);
        menu_2_listarBicicletas(listaOrdenada);
        retorno=1;
    }

    return retorno;
}


int ordenarTipoTiempo(void* tipo1, void* tipo2)
{
    int retorno=0;

    int compararPorTipo;

    eBici* aux1=(eBici*)tipo1;
    eBici* aux2=(eBici*)tipo2;


    if(aux1!=NULL && aux2!=NULL)
    {
        compararPorTipo=strcmp(aux1->tipo, aux2->tipo);

        if(compararPorTipo!=0)
        {
            retorno=compararPorTipo;
        }
        else if(compararPorTipo==0 && aux1->tiempo<aux2->tiempo)
        {
            retorno=-1;
        }
        else if(compararPorTipo==0 && aux1->tiempo>aux2->tiempo)
        {
            retorno=1;
        }
    }

    return retorno;
}

int RandomNumber(void* r)
{
    int retorno= -1;

    if(r!= NULL)
    {
        eBici* nuevaBici= (eBici*)r;
        nuevaBici->tiempo= rand()%(71)+50;
        retorno= 1;
    }
    return retorno;
}

