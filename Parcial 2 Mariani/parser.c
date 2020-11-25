#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "bicicleta.h"
#include "parser.h"


int parser_BicicletaCargarTexto(FILE* pFile, LinkedList* pLista)
{


    int retorno= -1;

    char id_bike[10];
    char nombre[25];
    char tipo[25];
    char tiempo[30];

    eBici* pBici;

    if(pFile!=NULL && pLista!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", id_bike, nombre, tipo, tiempo);
        while(feof(pFile) == 0)
        {
            if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n", id_bike, nombre, tipo, tiempo)==4)
            {
                pBici = bici_NewParametros(id_bike, nombre, tipo, tiempo);

                if(pBici!=NULL)
                {
                    ll_add(pLista, pBici);
                    retorno=1;
                }
            }
            else
            {
                break;
            }
        }
    }
    return retorno;
}


int parser_BicicletaGuardarTexto(char* pArchivo, LinkedList* pLista)
{
    int retorno= -1;

    int auxId;
    char auxNombre[25];
    char auxTipo[25];
    int auxTiempo;

    FILE* pFile;
    eBici* pBici;

    if(pLista!=NULL && pArchivo!=NULL)
    {
        pFile= fopen(pArchivo, "w");
        if(pFile!=NULL)
        {

            for(int i = 0; i<ll_len(pLista); i++)
            {
                pBici = (eBici*)ll_get(pLista, i);
                bici_GetId(pBici, &auxId);
                bici_GetNombre(pBici, auxNombre);
                bici_GetTipo(pBici, auxTipo);
                bici_GetTiempo(pBici, &auxTiempo);

                fprintf(pFile, "%d,%s,%s,%d\n", auxId, auxNombre, auxTipo, auxTiempo);
            }
            retorno= 1;
            fclose(pFile);
        }
    }

    return retorno;
}

