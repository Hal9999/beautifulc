/*
 ============================================================================
 Name        : list.c
 Author      : Stefano
 Version     :
 Copyright   : Questo codice è mio e ne detengo tutti i diritti. Forse avete il diritto di leggerlo ma non di comprenderlo.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

struct nodo{	//nodo contenitore
				struct nodo *prossimo;
				void *data;
		   };

//NUOVI PROTOTIPI: generici riguardo l'uso di strutture definite dall'utente
//int vislist(struct nodo *list, void (*stamp)());
//void stampa(struct persona *dato);
//void sortadd(void *oggetto, struct nodo **list, int (*compare)());
//int oggcmp(struct persona *a, struct persona *b);
//int crescnome(struct persona *a, struct persona *b);
//int crescnum(struct persona *a, struct persona *b);
//int decrenome(struct persona *a, struct persona *b);
//int decrenum(struct persona *a, struct persona *b);
//struct persona *creapersona(struct persona *base, int modo);
//int byelist(struct nodo **list, void (*fre)());
//void libera(struct persona *tofree);
//void totail(void *oggetto, struct nodo **list);
//void tohead(void *oggetto, struct nodo **list);
//void *cerca(void *oggetto, struct nodo *list, struct nodo **prev, int (*cmp)());

void sortadd(void *oggetto, struct nodo **list, int (*compare)())
{
    struct nodo *newn, *current, *previous;

    newn=(struct nodo *) malloc(sizeof(struct nodo));
    if(newn==NULL) printf("malloc err");
    else
	{
        newn->data=oggetto;   //Adesso il membro data del nuovo nodo punta all'oggetto passato

        current=*list;
        while( (current!=NULL) && ((*compare)(newn->data, current->data)>=0) )
        {
            previous=current;
            current=current->prossimo;
        }

        if( current==*list )
        {
            newn->prossimo=*list;
            *list=newn;
        }
        else
        {
            previous->prossimo=newn;
            newn->prossimo=current;
        }
    }
}

void libera(struct persona *tofree)
{
	free(tofree);
}

int byelist(struct nodo **list, void (*fre)())
{
	if(*list==NULL) return 0;
	else
	{
		struct nodo *current, *tofree;

		current=*list;
		while(current!=NULL)
		{
  			tofree = current;         		//conservo il puntatore del nodo da liberare
			current = current->prossimo;  	//punto al prossimo nodo; se il prossimo nodo sarà NULL, il while non entrerà nel prossimo ciclo

			(*fre)(tofree->data);			//libero la memoria allocata dall'oggetto (contenuto) tramite la funzione passata dall'utente
			free(tofree);          	 		//libero la memoria del nodo che fa da contenitore (involucro) all'oggetto dell'utente
        }
		*list = NULL;
		return 1;
	}
}

int vislist( struct nodo *list, void (*stamp)() )	//se viene richiamata almeno una volta la funzione passata, restituisce vero, altrimenti (se la lista è vuota) restituisce falso
{
	if(list==NULL) return 0;
	else
	{
		struct nodo *current;

		current = list;
		while(current!=NULL)
		{
			(*stamp)(current->data);
			current = current->prossimo;
		}
		return 1;
	}
}

void tohead(void *oggetto, struct nodo **list)    	//aggiungi nella testa, non vi è la necessità di percorrere tutta la lista
{
    struct nodo *newn;

    newn=(struct nodo *) malloc(sizeof(struct nodo));
    if(newn==NULL) printf("malloc err");
	else
    {
        newn->data = oggetto;   //nuovo nodo riempito

        newn->prossimo=*list;   //il nuovo puntatore punta all'ex primo nodo della lista
        *list=newn;         	//la lista punta al nuovo puntatore
    }
}

void totail(void *oggetto, struct nodo **list)
{
    struct nodo *newn;
    struct nodo *current, *previous;    //si deve percorrere tutta la lista

    newn=(struct nodo *) malloc(sizeof(struct nodo));
    if(newn==NULL) printf("malloc err");
    else
    {
        newn->data = oggetto;   		//nuovo nodo riempito

        current=*list;					//a questo punto, se la lista è vuota, allora current=NULL
        while( current!=NULL )
        {
            previous=current;
            current=current->prossimo;
        }

        if( current==*list )			//cioè se la lista è vuota
        {
            newn->prossimo=*list;
            *list=newn;
        }
        else
        {
            previous->prossimo=newn;
            newn->prossimo=current;
        }
    }
}

void *cerca(void *oggetto, struct nodo *list, struct nodo **prev, int (*cmp)())   //Cerca un valore nella lista che gli viene passata e, se gli viene passata una lista vuota, restituisce NULL (come se non avesse trovato il valore cercato)
{
    struct nodo *current;

    if(*prev==NULL) current=list;          	//prima esecuzione (cioè prev==NULL): cerca nella lista dall'inizio
    else current = (*prev)->prossimo;       //non è la prima esecuzione (cioè *prev!=NULL): cerca dal prossimo nodo puntato da prev in poi, escludendo dalla ricerca prev stesso

    while(current!=NULL)
    {
        if( (*cmp)(oggetto, current->data)==0 )
		{
			*prev = current;
			return current->data;     		//se il valore è quello cercato, restituisce il puntatore al nodo che lo contiene
		}
        current=current->prossimo;
    }

	*prev=NULL;
    return NULL;    //se arriva qui, vuol dire che current è uguale a NULL, ovvero che la lista è finita e che non è stata trovata alcuna corrispondenza (altrimenti il return all'interno dell'if lo avrebbe fatto uscire dalla funzione)
}

/*
int delhead(struct nodo **list)     //Cancella dalla testa
{
    if(*list==NULL) return 0;   //Niente da cancellare: la lista è già vuota
    else
    {
        struct nodo *tofree;
        int valore;

        tofree=*list;               //Puntatore da dare in pasto a free()
        valore=(*list)->numero;	//Valore del nodo da verrà ritornato dalla funzione

        *list=(*list)->prossimo;    //Ora list punta al prossimo nodo della lista


    }
}
*/

/*
struct persona *creapersona(void)
{
	struct persona *nuovo;
	nuovo=(struct persona *)malloc(sizeof(struct persona));
	printf("\nInserisci i campi: nome numero\n\n");
	scanf("%s %s", nuovo->nome, nuovo->numero);

	return nuovo;
}
*/
