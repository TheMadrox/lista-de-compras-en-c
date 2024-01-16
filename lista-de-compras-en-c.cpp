#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char* String;


typedef struct Abarrotes
{
	String producto;
	int cantidad;
	bool falta;
}ABARROTES;

typedef struct nodo
{
	ABARROTES abarrotes;
	struct nodo *sig;
}NODO;

char marco[] = "--------------------"; //Para hacer las tablas

NODO *h = NULL, *t = NULL; //Nodo de cabeza y de cola

NODO* crear_producto(); //Esta funcion crea un nodo con todos sus elementos
NODO* Push_Front(NODO *h); //Esta funcion introduce un nodo al principio de todos los elementos
void imprimir(NODO *h); //Muestra los productos que se ingresaron
NODO* checklist(NODO *h); //Sirve para saber si ya se tiene el producto o si aun hace falta comprarlo
void prod_faltantes(NODO *h, NODO *t); //Muestra los productos que hacen falta

int main()
{
	String producto;
	char opc;
	
	while(opc != '5')
	{
		fflush(stdin);
		system("cls");
		printf("Bienvenido a la lista de compras...\n");
	    printf("Seleccione una opcion: \n\n");
	    printf("\t1.-Ingresar articulos\n");
	    printf("\t2.-Imprimir lista\n");
	    printf("\t3.-Checklist\n");
	    printf("\t4.-Productos Faltantes\n");
	    printf("\t5.-Salir del programa\n");
	    printf("\n\nIngrese la opcion: ");
	    scanf("%c", &opc);
	    
	    if(opc != '1' && opc!= '2' && opc!= '3' && opc!='4' && opc!='5') 
	    {
	    	printf("\nLa opcion ingresada no es valida...\n");
	    	system("pause");
		}
		
		switch(opc)
		{
			case '1':
				system("cls");
				while(opc == '1')
				{
				    h = Push_Front(h); //Se crea un nodo al inicio y se actualiza la cabeza con el nuevo nodo
					system("cls");
				    printf("Desea agregar mas productos?\n");
					printf("\t1.-Si\n");
					printf("\t2.-No\n");
					printf("\nIngrese una opcion: ");
					fflush(stdin);
					scanf("%c", &opc);
					while(opc != '1' && opc !='2')
					{
						system("cls");
						printf("\nLa opcion ingresada no es valida, intente de nuevo...\n");
						system("pause");
						system("cls");
						printf("Desea agregar mas productos?\n");
					    printf("\t1.-Si\n");
					    printf("\t2.-No\n");
					    printf("\nIngrese una opcion: ");
					    fflush(stdin);
					    scanf("%c", &opc);
					}
				}
			    break;
		    case '2':
		    	system("cls");
		    	printf("+%s+%s+\n", marco, marco);
		    	printf("|%-20s|%-20s|\n", "PRODUCTO", "CANTIDAD");
			    imprimir(h);
			    printf("+%s+%s+\n", marco, marco);
			    system("pause");
			    break;
		    case '3':
		    	system("cls");
		    	checklist(h);
		    	system("pause");
			    break;
			case '4':
				system("cls");
				prod_faltantes(h,t);
				system("pause");
				break;
		}
	}
}

NODO* crear_producto()
{
	NODO *auxn = (NODO*)malloc(sizeof(NODO));
	char c;
	int i = 1, cantidad;
	String aux = NULL;
	
	fflush(stdin);
	printf("Introduzca el nombre del producto: ");
	while((c = getchar()) != '\n')
	{
		aux = (char*)realloc(aux, (i+2)*sizeof(char));
		if(aux == NULL)
		{
			printf("No hay suficiente memoria...");
			exit(1);
		}
		
		aux[i-1] = c;
		aux[i] = '\0';
		i++;
	}
	
	auxn->abarrotes.producto = aux;
	
	printf("Introduzca la cantidad de productos requeridos: ");
	scanf("%d", &cantidad);
	
	auxn->abarrotes.cantidad = cantidad;
	
	auxn->sig = NULL;
	
	return auxn;
}

NODO* Push_Front(NODO *h)
{
	NODO *aux = crear_producto();
	if(h == NULL)
	{
		t = aux;
	}
	
	aux->sig = h;
	
	h = aux;
	
	return h;
}

void imprimir(NODO *h)
{
	printf("+%s+%s+\n", marco, marco);
	printf("|%-20s|%-20d|\n", h->abarrotes.producto, h->abarrotes.cantidad);
	
	if(h->sig != NULL)
	{
		imprimir(h->sig);
	}
}

NODO* checklist(NODO *h)
{
	char opc;
	system("cls");
	printf("+%s+%s+\n", marco, marco);
	printf("|%-20s|%-20s|\n", "PRODUCTO", "CANTIDAD");
	printf("+%s+%s+\n", marco, marco);
	printf("|%-20s|%-20d|\n",h->abarrotes.producto, h->abarrotes.cantidad);
	printf("+%s+%s+\n", marco, marco);
	printf("\t\nYa compro este producto?\n");
	printf("\t1.-Si\n");
	printf("\t2.-No\n");
	printf("\n\nIntroduzca la opcion: ");
	fflush(stdin);
	scanf("%c", &opc);
	if(opc != '1' && opc != '2')
	{
		printf("La opcion ingresada no es correcta....\n");
		system("pause");
		system("cls");
		checklist(h);
		return h;
	}
	
	if(opc == '1')
	{
		h->abarrotes.falta = 1;
	}
	if(opc == '2')
	{
		h->abarrotes.falta = 0;
	}
	
	if(h->sig != NULL)
	{
		checklist(h->sig);
	}
}

void prod_faltantes(NODO *h, NODO *t)
{	
	printf("+%s+%s+\n", marco, marco);
	printf("|%-20s|%-20s|\n", "PRODUCTO FALTANTE", "CANTIDAD");
	while(h != t || h == t)
	{
		NODO *aux = h;
		if(aux->abarrotes.falta == 0)
		{
			printf("+%s+%s+\n", marco, marco);
			printf("|%-20s|%-20d|\n", aux->abarrotes.producto, aux->abarrotes.cantidad);
		}
		if(h->sig==NULL)
		{
			break;
		}
		h = h->sig;
	}
	printf("+%s+%s+\n", marco, marco);
}
