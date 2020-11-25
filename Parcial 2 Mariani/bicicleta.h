#ifndef PAIS_H_INCLUDED
#define PAIS_H_INCLUDED

typedef struct
{
    int id_bici;
    char nombre[128];
    char tipo[128];
    float tiempo;

}eBici;

#endif // PAIS_H_INCLUDED

eBici* bici_New();
void bicis_borrar(eBici* this);
eBici* bici_NewParametros(char* id_bici, char* nombre, char* tipo, char* tiempo);

///####### GET Y SET
int bici_SetId(eBici* this, int id);
int bici_GetId(eBici* this, int* id);

int bici_GetNombre(eBici* this, char* nombre);
int bici_SetNombre(eBici* this, char* nombre);

int bici_GetTipo(eBici* this, char* tipo);
int bici_SetTipo(eBici* this, char* tipo);

int bici_SetTiempo(eBici* this, int tiempo);
int bici_GetTiempo(eBici* this, int* tiempo);
///#######

int menu_1_cargarTexto(char* pArchivo, LinkedList* pLista);

int menu_2_listarBicicletas(LinkedList* listaBicis);

int menu_4_filtrarPorTipos(LinkedList* listaBicis, LinkedList* listaFiltrada);
int filtroBicicletas(void* pFilter, char* temp);

int menu_5_listarOrdenadas(LinkedList* listaBicicletas,LinkedList* listaOrdenada);
int ordenarTipoTiempo(void* tipo1, void* tipo2);

int RandomNumber(void* a);
