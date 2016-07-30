/*
 ============================================================================
 Name        : main.c
 Author      : Stefano
 Version     :
 Copyright   : Questo codice è mio e ne detengo tutti i diritti. Forse avete il diritto di leggerlo ma non di comprenderlo.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct persona{	//contenuto puntato dal nodo
					char nome[80];
					char numero[11];
			  };

struct persona *creapersona(struct persona *base, int modo)
{
	if(base==NULL)	//crea un nuovo oggetto, altrimenti usa quello passato con *persona
	{
		base=(struct persona *)malloc(sizeof(struct persona));
		if(base==NULL) { printf("malloc err"); return NULL; }
	}

	//Scelta della modalità di inserimento, secondo quanto passato dal parametro modo

		 if(modo==1)	//Riempie solo il campo nome, lasciando invariati gli altri
 	{
		printf("\nInserisci il campo nome:    ");
		scanf("%s", base->nome);
	}
	else if(modo==2)	//Riempie solo il campo numero, lasciando invariati gli altri
	{
		printf("\nInserisci il campo numero: ");
		scanf("%s", base->numero);
	}
	else if(modo==3)	//Riempie tutti i campi
	{
		printf("\nInserisci il campo nome:    ");
		scanf("%s", base->nome);
		printf("\nRInserisci il campo numero: ");
		scanf("%s", base->numero);
	}

	return base;
}

/******************************************************************************/
//FUNZIONI DI CONFRONTO
int oggcmp(struct persona *a, struct persona *b)
{
	return( strcmp(a->nome, b->nome) || strcmp(a->numero, b->numero) );	//se uno dei due è vero, allora la funzione restituisce vero, cioè i due oggetti non sono uguali
}
int crescnome(struct persona *a, struct persona *b)
{
    return strcmp(a->nome, b->nome);
}

int crescnum(struct persona *a, struct persona *b)
{
    return strcmp(a->numero, b->numero);
}

int decrenome(struct persona *a, struct persona *b)
{
    return strcmp(b->nome, a->nome);
}

int decrenum(struct persona *a, struct persona *b)
{
    return strcmp(b->numero, a->numero);
}
/******************************************************************************/

void stampa(struct persona *dato)
{
	printf("\n%-12s %s", dato->nome, dato->numero);
}

int main()
{
	struct nodo *list=NULL;	//puntatore alla lista
	int scelta=1;

	for(;;)
	{
        printf("\n\nMenu:\n\n");
		printf("1. Visualizza lista\n");
		printf("2. Aggiungi nodo\n");
		printf("3. Svuota lista\n");
		printf("4. Cerca elemento\n");
		printf("5. Elimina un elemento\n");
		printf("6. Esci\n");
		printf("Scelta: ");
		char string[80];
		fgets(string, sizeof(string), stdin);
		scelta = atoi(string);


/******************************************************************************/

			 if(scelta==1) 	//Visualizzazione della lista
		{
            printf("\n\nVisualizzazione della lista:\n\n");

            if( vislist(list, stampa)==0 )
				 printf("Lista vuota: nessun elemento da visualizzare");
            else printf("\n\nFine della lista.");
		}

/******************************************************************************/

		else if(scelta==2) 	//Aggiunta di elementi
        {
            printf("\n\nAggiunta di elementi nella lista\n\n");
            printf("Scegli la modalità di inserimento:\n\n");
            printf("1. Ordine crescente per nome\n");
            printf("2. Ordine crescente per numero\n");
            printf("3. Ordine decrescente per nome\n");
            printf("4. Ordine decrescente per numero\n");
            printf("5. Inserisci in testa\n");
            printf("6. Inserisci in coda\n");
            printf("\nScelta: ");

			int scelta;
			scanf("%d", &scelta);

			printf("\n\nCreazione di una nuova persona:\n");

			struct persona *tmp;
            tmp=creapersona(NULL, 3);

            	 if(scelta==1) sortadd(tmp, &list, crescnome);
            else if(scelta==2) sortadd(tmp, &list, crescnum);
            else if(scelta==3) sortadd(tmp, &list, decrenome);
            else if(scelta==4) sortadd(tmp, &list, decrenum);
            else if(scelta==5)  tohead(tmp, &list);
            else if(scelta==6)  totail(tmp, &list);

            printf("Inserimento effettuato!");
        }

/******************************************************************************/

        else if(scelta==3) 	//Svuota la lista
        {
            printf("\n\nSvuotamento della lista\n\n");

            if( byelist(&list, libera)==0 )
				 printf("\n\nLista già vuota. Nulla da fare.\n\n");
            else printf("\n\nLista svuotata.\n\n");
        }

/******************************************************************************/

        else if(scelta==4) //Ricerca di un valore
        {
			printf("\n\nRicerca di un elemento:\n\n");
			printf("Scegli la modalità di ricerca:\n");
			printf("1. Per nome\n");
			printf("2. Per numero\n");
			printf("3. Per nome e numero (verifica l'esistenza)\n");
			printf("Scelta: ");

			int scelta;
			scanf("%d", &scelta);

			//setto le variabili necessarie a seconda della modalità indicata dall'utente
			struct persona *confronto, *trovato;
			struct nodo *postit;
			void *funzi;

				 if(scelta==1)	//vi è corrispondenza tra i numeri del menù e i numeri che stabiliscono la modalità di funzionamento della funzione creapersona; MA è solo una coincidenza: sviluppi futuri potrebbero perdere questa corrispondenza e utilizzare composizioni delle modalità della funzione stessa (richiamare più volte la funzione con modalità diverse per riempire determinati campi)
		 	{
				confronto = creapersona(NULL, 1);
				funzi=crescnome;
			}
			else if(scelta==2)
		 	{
				confronto = creapersona(NULL, 2);
				funzi=crescnum;
			}
			else if(scelta==3)
		 	{
				confronto = creapersona(NULL, 3);
				funzi=oggcmp;
			}

			//la prima chiamata a cerca() deve essere fatta con un puntatore nullo e si deve verificare che venga restituito un valore non nullo, altrimenti significa che l'oggetto non è stato trovato nella lista
			postit = NULL;
			trovato = cerca( confronto, list, &postit, funzi );					//prima chiama: postit è NULL

			if( trovato==NULL ) printf("\n\nValore non trovato nella lista!\n");	//valore non trovato, trovato==NULL
			else
			{
				printf("\n\nElenco delle voci trovate:\n");
				do{
						stampa(trovato);				//stampa l'oggeto trovato

						trovato = cerca( confronto, list, &postit, funzi );		//passo successivo nella ricerca
				  }while( trovato!=NULL );
				printf("\n\nFine elenco.\n");
			}
			free(confronto);
		}

/******************************************************************************************/

/*
        else if(scelta==5)  //Eliminazione di un nodo
        {
            int val;
            struct nodo *tmp;
			printf("\n\nEliminazione di un elemento dalla lista\n\n");
            printf("Scegli:\n");
            printf("1. Elimina un elemento per numero\n");
            printf("2. Elimina un elemento dalla testa\n");
            printf("3. Elimina un elemento dalla coda\n");
            printf("\nScegli: ");

            int scelta;
            scanf("%d", &scelta);


                 if(scelta==1)
            {
                printf("\n\nEliminazione di un elemento per valore\n\n");
                printf("Inserisci il campo: numero\n\n");
                scanf("%d", &val);

                //funzione per l'eliminazione di un determinato elemento
            }
            else if(scelta==2)
            {
                printf("\n\nEliminazione di un elemento dalla testa...\n\n");

                if( tmp=delhead(list)==NULL ) printf("Lista già vuota: nulla da cancellare.");
				else printf("N
            }
            else if(scelta==3)
            {
                printf("\n\nEliminazione di un elemento dalla coda...\n\n");

                //funzione di un elemento dalla coda
            }
        }
*/
/******************************************************************************************/
        else if(scelta==6) //Uscita dal programma
        {
            printf("\n\nUscita dal programma\n\n");
            exit(0);
        }
        else printf("\n\nScelta non valida...\n");
/******************************************************************************************/

    }
} //FINE MAIN
