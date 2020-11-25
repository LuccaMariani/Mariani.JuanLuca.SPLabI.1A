#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "utn.h"
#include "bicicleta.h"
#include "menu.h"
#include "parser.h"


void menu()
{
    int menuOpcion=0;
    int menuSalir;
    char archivo[50]={"bicicletas.csv"};

    int flagOrdenada=0;
    int flagCargar=0;

    LinkedList* listaBicicletas= ll_newLinkedList();
    LinkedList* listaOrdenada= NULL;
    LinkedList* listaFiltrada= NULL;

    while(menuOpcion!=-1)
    {
        printf("\n\n * Menu *\n");
        printf("\n1. Cargar archivo");
        printf("\n2. Imprimir lista");
        printf("\n3. Asignar tiempos");
        printf("\n4. Filtrar por tipo");
        printf("\n5. Mostrar posiciones");
        printf("\n6. Guardar posiciones");
        printf("\n7. Salir");

        getInt("\n\n - Seleccione la opcion del menu a ejecutar\n>","\n\nError, escriba un numero del 1 al 7.", 1, 7, 0, &menuOpcion);
        printf("\n");

        switch(menuOpcion)
        {
            case 1:
                if(menu_1_cargarTexto(archivo, listaBicicletas))
                {
                    printf("\n + Archivo %s cargado con exito.", archivo);
                    flagCargar=1;
                }
                else
                {
                    printf("\n Hubo un error en la carga del archivo %s.", archivo);
                }
                break;
            case 2:
                if(flagCargar)
                {
                    if(!menu_2_listarBicicletas(listaBicicletas))
                    {
                        printf("\n Hubo un error en el listado.");
                    }
                }
                else
                {
                   printf("\n Tiene que cargar los archivos primero.");
                }

                break;
            case 3:
                if(flagCargar)
                {
                    if(ll_map(listaBicicletas, RandomNumber))
                    {
                        printf("\n + Tiempos aleatorios cargados con exito");
                    }
                    else
                    {
                        printf("\n Hubo un error en la asginacion de tiempos aleatorios.");
                    }
                }
                else
                {
                   printf("\n Tiene que cargar los archivos primero.");
                }

                break;
            break;
            case 4:
                if(flagCargar)
                {
                   if(menu_4_filtrarPorTipos(listaBicicletas, listaFiltrada))
                    {
                        printf("\n + La lista ordenada fue creada, y luego un archivo fue generado y guardado correctamente.\n");
                    }
                    else
                    {
                        printf("\n Hubo un error.");
                    }
                }
                else
                {
                   printf("\n Tiene que cargar los archivos primero.");
                }

                break;
            case 5:
                if(flagCargar)
                {
                    if(menu_5_listarOrdenadas(listaBicicletas, listaOrdenada))
                    {
                        printf("\n + Lista creada exitosamente. No olvide guardarla!\n");
                        flagOrdenada=1;
                    }
                    else
                    {
                        printf("\n Hubo un error.");
                    }
                }
                else
                {
                   printf("\n Tiene que cargar los archivos primero.");
                }
                break;
            case 6:
                if(flagOrdenada==1)
                {
                    if(parser_BicicletaGuardarTexto("bicicletas_ordenadas.csv", listaBicicletas))
                    {
                        printf("\n + Archivo generado y guardado correctamente.\n");
                    }
                    else
                    {
                        printf("\n Hubo un error en el guardado del archivo.");
                    }
                }
                else
                {
                    printf("\n Tiene que crear la lista ordenada primeramente..");
                }

                break;
            case 7:
                printf("\n - Desea salir del programa? (SI = 1) (NO = 0)");

                getInt("\n>","\n - Error, re ingrese 1 o 0.", 1, 7, 0, &menuSalir);

                if(menuSalir == 1)
                {
                    printf("\nCerrardo programa y borrando likedList guardadas en memoria dinamica...\n");
                    ll_deleteLinkedList(listaOrdenada);
                    ll_deleteLinkedList(listaBicicletas);
                    ll_deleteLinkedList(listaFiltrada);
                    menuOpcion=-1;
                }
                break;;
            default:
                printf(" ");

        }
        printf("\n\n");
        system("pause");
        system("cls");
    }
    return;
}
