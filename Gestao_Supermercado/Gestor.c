#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Gestor.h"

//*******************Estruturas*********************************************
struct elemento{
	struct produtos dados;
	struct elemento *prox;
};
typedef struct elemento Elemento;

struct elemento_clientes{
	struct cliente dados;
	struct elemento_clientes *prox;
};
typedef struct elemento_clientes Elemento_c;

struct elemento_gestor{
	struct gestor dados;
	struct elemento_gestor *prox;
};
typedef struct elemento_gestor Elemento_g;

int current_id;//--saber o id atual do cliente

//*******************************FUNÇÕES****************************************

int login(int option,Lista_g* li_g,Lista_c* li_c,Lista* li){ // option = 1 = menu_cliente // option = 2 = menu_gestor
	int x, id;
	char password[30];
	
	system("cls");
	if(option == 1){ //menu_cliente
		printf("1-Login\n2-Registar\n");
		scanf("%d", &x);
		fflush(stdin);
		if(x == 1){
			system("cls");
			printf("Introduza o seu numero de cliente: ");
			scanf("%d", &id);
			fflush(stdin);
			if(verifica_cliente(li_c, id)){
				printf("Introduza a sua password: ");
				gets(password);
				if(!strcmp(verifica_cliente_password(li_c,id),password)){
					current_id = id;
					menu_cliente(li,li_c);
				}else{
					printf("Passwords errada");
				}
			}
		}else if( x == 2){
			system("cls");
			struct cliente* data = (cliente*) malloc(sizeof(struct cliente)); //alocar espaço
			printf("Introduza o seu nome: ");
			gets(data->nome);
			fflush(stdin);
			printf("Introduza a sua morada: ");
			gets(data->morada);
			fflush(stdin);
			printf("Introduza numero contribuinte: ");
			scanf("%d", &data->num_contr);
			fflush(stdin);
			printf("Introduza o seu numero de credito: ");
			gets(data->num_ccredito);
			fflush(stdin);
			printf("Introduza uma password");
			gets(data->password);
			data->num_cliente = ultimo_id_cliente(li_c) + 1;
			current_id = ultimo_id_cliente(li_c) + 1;
			insere_lista_ordenada_c(li_c,*data);
			update_txt_clientes(li_c);
			free(data);
			menu_cliente(li,li_c);
		}
	}else if(option == 2){ // menu_gestor
		system("cls");
		printf("---Login---\n");
		printf("Introduza o seu numero de trabalhador: ");
		scanf("%d", &id);
		fflush(stdin);
		if(verifica_gestor(li_g,id)){
			printf("Introduza a sua password: ");
			gets(password);
			fflush(stdin);
			if(!strcmp(verifica_gestor_password(li_g,id),password)){
				menu_gestor(li,li_c,li_g);
			}else{
				printf("Password errada");
			}
		}
	}
}

int menu_gestor(Lista* li, Lista_c* li_c,Lista_g* li_g){
	int option=1;
	
	system("cls");
	while(option != 0){
		system("cls");
		printf("----Menu Gestor----\n");
		printf("1-Consultar produtos\n");
		printf("2-Remover produtos\n");
		printf("3-Adicionar produtos\n");
		printf("4-Consultar Clientes\n");
		printf("5-Adicionar clientes\n");
		printf("6-Remover Clientes\n");
		printf("0-Sair\n");
		scanf("%d", &option);
		
		if(option == 1){
			
			system("cls");
			printf("______Nome_____|_Codigo_|_Preco_|__Validade__|_Stock_ \n");
			imprime_lista(li);
			printf("Prima uma tecla para continuar...\n");
			getch();
			
		}else if(option == 2){
			
			system("cls");
			int op3;
			printf("______Nome_____|_Codigo_|_Preco_|__Validade__|_Stock_ \n");
			imprime_lista(li);
			printf("Qual produto deseja remover? (Insira o id)\n");
			scanf("%d", &op3);	
			remove_lista_produto(li,op3);
			update_txt_produtos(li);
			printf("\nPrima uma tecla para continuar...\n");
			getch();
			
		}else if( option == 3){
			
			system("cls");
			struct produtos* data = (produtos*) malloc(sizeof(struct produtos)); //alocar espaço
			printf("Nome do produto: ");
			scanf("%s", &data->nome );
			fflush(stdin);
			printf("Preco: ");
			scanf("%f", &data->preco);
			fflush(stdin);
			printf("Validade: ");
			scanf("%s", &data->validade);
			fflush(stdin);
			printf("Stock: ");
			scanf("%d", &data->qtd_stock);
			data->codigo = ultimo_id_produto(li) + 1;
			insere_lista_ordenada(li,*data);
			update_txt_produtos(li);
			printf("\nPrima uma tecla para continuar...\n");
			getch();
			free(data);
			
		}else if(option == 4){
			
			system("cls");
			printf("_Id_|__________Nome_________________|_____________Morada____________|__N.Contrato__|____N.Credito____|_______Password_____\n");
			imprime_lista_c(li_c);
			printf("Prima uma tecla para continuar...\n");
			getch();
			
		}else if(option == 5){
			
			system("cls");
			struct cliente* data1 = (cliente*) malloc(sizeof(struct cliente));
			fflush(stdin);
			printf("Nome do cliente: ");
			gets(data1->nome);
			fflush(stdin);
			printf("Morada: ");
		    gets(data1->morada);
			printf("Numero de contribuinte: ");
			scanf("%d", &data1->num_contr);
			fflush(stdin);
			printf("Numero de credito: ");
			gets(data1->num_ccredito);
			fflush(stdin);
			printf("Password: ");
			gets(data1->password);
			data1->num_cliente = ultimo_id_cliente(li_c) + 1;
			insere_lista_ordenada_c(li_c,*data1);
			update_txt_clientes(li_c);
			free(data1);
			
		}else if(option == 6){
			system("cls");
			printf("_Id_|__________Nome_________________|_____________Morada____________|__N.Contrato__|____N.Credito____|_______Password_____\n");
			imprime_lista_c(li_c);
			int id;
			printf("Introduza o id do cliente que deseja remover: ");
			scanf("%d", &id);
			printf("Tem a certeza que deseja remover o cliente?\n1-Continuar\n2-Cancelar\n");
			int op1;
			scanf("%d", &op1);
			if(op1 == 1){
				remove_lista_cliente(li_c,id);
				update_txt_clientes(li_c);
				printf("\nPrima uma tecla para continuar...\n");
				getch();
			}else if(op1 == 2){
				printf("Operaçao cancelada\n");
				printf("Prima uma tecla para continuar...\n");
				getch();
			}else{
				printf("Opçao invalida\n");
				printf("Prima uma tecla para continuar...\n");
				getch();
			}
		}
	}
	return 0;
}

int menu_cliente(Lista* li,Lista_c* li_c){
	int option=1;
	
	system("cls");
	while(option != 0){	
		system("cls");
		printf("----Menu Cliente----\n");
		printf("1-Comprar produtos\n");
		printf("2-Remover conta\n");
		printf("0-Sair\n");
		scanf("%d", &option);
				
		switch(option){
			case 1:
				system("cls");
				printf("______Nome_____|_Codigo_|_Preco_|__Validade__|_Stock_ \n");
				imprime_lista(li);
				int id,qtd;
				printf("Introduza o id do produto que deseja comprar: ");
				scanf("%d", &id);
				printf("Introduza a quantidade: ");
				scanf("%d", &qtd);
				imprime_fatura(li, id, qtd);
				printf("Prima uma tecla para continuar...\n");
				getch();
				break;
				
			case 2:
				printf("Tem a certeza que deseja remover a sua conta?\n1-Continuar\n2-Cancelar\n");
				int op1;
				scanf("%d", &op1);
				if(op1 == 1){
					remove_lista_c_cliente(li_c);
					update_txt_clientes(li_c);
					option = 0;
				}else if(op1 == 2){
					printf("Operaçao cancelada\n");
					printf("Prima uma tecla para continuar...\n");
					getch();
				}else{
					printf("Opçao invalida\n");
					printf("Prima uma tecla para continuar...\n");
					getch();
				}
				break;
			case 0:
				break;
		}	
	}
	return 0;
}


//-------------------------------------------------------------------------------------
//-------------------------LISTA PRODUTOS----------------------------------------------
//-------------------------------------------------------------------------------------
Lista* cria_lista(){
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if (li != NULL)
		*li = NULL;
	return li;
}

void liberta_lista(Lista* li){
	if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int insere_lista_ordenada(Lista* li, struct produtos data){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = data;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.codigo < data.codigo){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elemento* no = *li;
    while(no != NULL){
        printf("%-15s|",no->dados.nome);
        printf(" %-6d |",no->dados.codigo);
        printf(" %-5.2f |",no->dados.preco);
        printf(" %-11s|",no->dados.validade);
        printf(" %d\n",no->dados.qtd_stock);
        no = no->prox;
    }
}

void load_txt_produtos(Lista* li){
	
	FILE* inp; 
    inp = fopen("produtos.txt","r");		//abrir ficheiro
    char arr[100][50];			//maximo da palavra 50
    int i = 0;
	int k = 0; 
    while(1){ 
        char r = (char)fgetc(inp); 
        int k = 0; 
        while(r!=',' && !feof(inp)){	//ler carateres ate "," ou o fim do ficheiro
            arr[i][k++] = r;			//guardar no array
            r = (char)fgetc(inp);
        } 
        arr[i][k]=0;		//meter o ultimo carater de cada palvra a null
        if(feof(inp)){		//verificar novamente o fim de ficheiro 
            break; 
        } 
        i++;
    } 
    int j;
   struct produtos* data = (produtos*) malloc(sizeof(struct produtos)); //alocar espaço
    for(j = 0;j<=i;j++){
    	if(k == 0){
    		char x[5];
    		strcpy(x,arr[j]);
    		float y = strtol(x,NULL,10);
    		data->codigo = y;
    		k++;
		}else if(k == 1){
			strcpy(data->nome, arr[j]);
			k++;
		}else if(k == 2){
			char *x;
    		x = arr[j];
    		float y = atof(x);
    		data->preco = y;
			k++;
		}else if(k == 3){
			strcpy(data->validade, arr[j]);
			k++;
		}else if(k == 4){
			char x[5];
    		strcpy(x,arr[j]);
    		int y = strtol(x,NULL,10);
    		data->qtd_stock = y; 
			k = 0; // inicializar o k para iniciar o registo de outro produto
			insere_lista_ordenada(li, *data);
		}
    }
    free(data);
}

void update_txt_produtos(Lista* li){
	fclose(fopen("produtos.txt","w"));
	FILE* inp; 
    inp = fopen("produtos.txt","w+");
    Elemento* no = *li;
    while(no != NULL){
    	fprintf(inp,"%d,%s,%.2f,%s,%d,\n",no->dados.codigo,no->dados.nome,no->dados.preco,no->dados.validade,no->dados.qtd_stock);  
    	no = no->prox;
	}
	fclose(inp);
}

int consulta_lista_id_produto(Lista* li, int id){
	if(li == NULL)
        return 0;
    Elemento *no = *li;
    while(no != NULL && no->dados.codigo != id){
        no = no->prox;
    }
    if(no == NULL){
    	printf("Produto inexistente");
        return 0;
    }else{
        printf("Produto encontrado!\n");
        printf("Nome: %s \nPreco: %.2f\nStock: %d", no->dados.nome,no->dados.preco,no->dados.qtd_stock);
        return 1;
    }
}

int remove_lista_produto(Lista* li, int id){ //id = codigo do produto
	if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento *ant, *no = *li;
    while(no != NULL && no->dados.codigo != id){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    printf("Produto removido");
    return 1;
}

int ultimo_id_produto(Lista* li){
	int ultimo_id = 0;
	
    if(li == NULL)
        return 0;
    Elemento* no = *li;
    while(no != NULL){
        no = no->prox;
       if(no->prox == NULL)
    		return no->dados.codigo;
    }
}

//-------------------------------------------------------------------------------------
//-------------------------LISTA CLIENTES----------------------------------------------
//-------------------------------------------------------------------------------------
Lista_c* cria_lista_c(){
	Lista_c* li = (Lista_c*) malloc(sizeof(Lista_c));
	if (li != NULL)
		*li = NULL;
	return li;
}

void liberta_lista_c(Lista_c* li){
	if(li != NULL){
        Elemento_c* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_ordenada_c(Lista_c* li, struct cliente data){
    if(li == NULL)
        return 0;
    Elemento_c *no = (Elemento_c*) malloc(sizeof(Elemento_c));
    if(no == NULL)
        return 0;
    no->dados = data;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }else{
        Elemento_c *ant, *atual = *li;
        while(atual != NULL && atual->dados.num_cliente < data.num_cliente){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

void imprime_lista_c(Lista_c* li){
    if(li == NULL)
        return;
    Elemento_c* no = *li;
    while(no != NULL){
    	printf("%-3d |",no->dados.num_cliente);
        printf("%-30s |",no->dados.nome);
        printf("%-30s |",no->dados.morada);
        printf("   %-10d |",no->dados.num_contr);
        printf("  %-15s|",no->dados.num_ccredito);
        printf("%-30s\n", no->dados.password);
        
        no = no->prox;
    }
}

void load_txt_clientes(Lista_c* li){
	
	FILE* inp; 
    inp = fopen("clientes.txt","r");		//abrir ficheiro
    char arr[100][50];			//maximo da palavra 50
    int i = 0;
	int k = 0; 
    while(1){ 
        char r = (char)fgetc(inp); 
        int k = 0; 
        while(r!=',' && !feof(inp)){	//ler carateres ate "," ou o fim do ficheiro
            arr[i][k++] = r;			//guardar no array
            r = (char)fgetc(inp);
        } 
        arr[i][k]=0;		//meter o ultimo carater de cada palvra a null
        if(feof(inp)){		//verificar novamente o fim de ficheiro 
            break; 
        } 
        i++;
    } 
    int j; 
    struct cliente* data = (cliente*) malloc(sizeof(struct cliente)); //alocar espaço
    
    for(j = 0;j<=i;j++){
        if(k == 0){
    		char x[10];
    		strcpy(x,arr[j]);
    		data->num_cliente = atoi(x);
    		k++;
		}else if(k == 1){
			strcpy(data->nome, arr[j]);
			k++;
		}else if(k == 2){
			strcpy(data->morada, arr[j]);
			k++;
		}else if(k == 3){
			char x[10];
			strcpy(x, arr[j]);
			data->num_contr = atoi(x);
			k++;
		}else if(k == 4){
			strcpy(data->num_ccredito, arr[j]);
			k++;
		}else if(k == 5){
			strcpy(data->password,arr[j]);
			k = 0; // inicializar o k para iniciar o registo de outro porduto
			insere_lista_ordenada_c(li, *data);
		}
    }
    free(data);
}

void update_txt_clientes(Lista_c* li){
	fclose(fopen("clientes.txt","w")); //serve para limpar o ficheiro
	FILE* inp; 
    inp = fopen("clientes.txt","w+");
    Elemento_c* no = *li;
    while(no != NULL){  
        fprintf(inp,"%d,%s,%s,%d,%s,%s,\n",no->dados.num_cliente,no->dados.nome,no->dados.morada,no->dados.num_contr,no->dados.num_ccredito,no->dados.password); 
    	no = no->prox;
	}
	fclose(inp);
}

int consulta_lista_id_cliente(Lista_c* li, int id){
    if(li == NULL)
        return 0;
    Elemento_c *no = *li;
    while(no != NULL && no->dados.num_cliente != id){
        no = no->prox;
    }
    if(no == NULL){
    	printf("Cliente inexistente");
        return 0;
    }else{
        printf("Cliente encontrado!\n");
        printf("Nome: %s \n", no->dados.nome);
        return 1;
    }
}

int remove_lista_c_cliente(Lista_c* li){
	if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento_c *ant, *no = *li;
    while(no != NULL && no->dados.num_cliente != current_id){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    printf("Conta removida com sucesso");
    return 1;
}

int remove_lista_cliente(Lista_c* li, int id){
	if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento_c *ant, *no = *li;
    while(no != NULL && no->dados.num_cliente != id){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    printf("Cliente removido com sucesso");
    return 1;
}

int verifica_cliente(Lista_c* li, int id){
    if(li == NULL)
        return 0;
    Elemento_c *no = *li;
    while(no != NULL && no->dados.num_cliente != id){
        no = no->prox;
    }
    if(no == NULL){
    	printf("Cliente inexistente");
        return 0;
    }else{
        printf("Cliente encontrado!\n");
        return 1;
    }
}

const char* verifica_cliente_password(Lista_c* li, int id){
    if(li == NULL)
        return 0;
    Elemento_c *no = *li;
    while(no != NULL && no->dados.num_cliente != id){
        no = no->prox;
    }
    if(no != NULL){
        return no->dados.password;
    }
}

int ultimo_id_cliente(Lista_c* li){
    if(li == NULL)
        return 0;
    Elemento_c* no = *li;
    while(no != NULL){
        no = no->prox;
       if(no->prox == NULL)
    		return no->dados.num_cliente;
    }
}

//-------------------------------------------------------------------------------------
//-------------------------LISTA GESTOR----------------------------------------------
//-------------------------------------------------------------------------------------

Lista_g* cria_lista_g(){
	Lista_g* li = (Lista_g*) malloc(sizeof(Lista_g));
	if (li != NULL)
		*li = NULL;
	return li;
}

void liberta_lista_g(Lista_g* li){
	if(li != NULL){
        Elemento_g* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_ordenada_g(Lista_g* li, struct gestor data){
    if(li == NULL)
        return 0;
    Elemento_g *no = (Elemento_g*) malloc(sizeof(Elemento_g));
    if(no == NULL)
        return 0;
    no->dados = data;
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }else{
        Elemento_g *ant, *atual = *li;
        while(atual != NULL && atual->dados.code_trab < data.code_trab){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int consulta_lista_id_gestor(Lista_g* li, int id){
    if(li == NULL)
        return 0;
    Elemento_g *no = *li;
    while(no != NULL && no->dados.code_trab != id){
        no = no->prox;
    }
    if(no == NULL){
    	printf("Gestor inexistente");
        return 0;
    }else{
        printf("Gestor encontrado!\n");
        printf("Nome: %s \n", no->dados.nome);
        return 1;
    }
}

void load_txt_gestor(Lista_g* li){
	
	FILE* inp; 
    inp = fopen("gestor.txt","r");		//abrir ficheiro
    char arr[100][50];			//maximo da palavra 50
    int i = 0;
	int k = 0; 
    while(1){
        char r = (char)fgetc(inp); 
        int k = 0; 
        while(r!=',' && !feof(inp)){	//ler carateres ate "," ou o fim do ficheiro
            arr[i][k++] = r;			//guardar no array
            r = (char)fgetc(inp);
        } 
        arr[i][k]=0;		//meter o ultimo carater de cada palvra a null
        if(feof(inp)){		//verificar novamente o fim de ficheiro 
            break; 
        } 
        i++;
    } 
    int j; 
    struct gestor* data = (gestor*) malloc(sizeof(struct gestor)); //alocar espaço
    
    for(j = 0;j<=i;j++){
        if(k == 0){
    		char x[10];
    		strcpy(x,arr[j]);
    		data->code_trab = atoi(x);
    		k++;
		}else if(k == 1){
			strcpy(data->nome, arr[j]);
			k++;
		}else if(k == 2){
			strcpy(data->password, arr[j]);
			k = 0; // inicializar o k para iniciar o registo de outro gestor
			insere_lista_ordenada_g(li, *data);
		}
    }
    free(data);
}

void update_txt_gestor(Lista_g* li){
	fclose(fopen("gestor.txt","w"));
	FILE* inp; 
    inp = fopen("gestor.txt","w+");
    Elemento_g* no = *li;
    while(no != NULL){
    	fprintf(inp,"%d,%s,%s,\n",no->dados.code_trab,no->dados.nome,no->dados.password);  
    	no = no->prox;
	}
	fclose(inp);
}

void imprime_lista_g(Lista_g* li){
    if(li == NULL)
        return;
    Elemento_g* no = *li;
    while(no != NULL){
    	printf("Numero cliente: %d",no->dados.code_trab);
        printf(" Nome: %s",no->dados.nome);
        printf(" Password: %s\n", no->dados.password);
        
        no = no->prox;
    }
}

int verifica_gestor(Lista_g* li, int id){
    if(li == NULL)
        return 0;
    Elemento_g *no = *li;
    while(no != NULL && no->dados.code_trab != id){
        no = no->prox;
    }
    if(no == NULL){
    	printf("Gestor inexistente");
        return 0;
    }else{
        printf("Gestor encontrado!\n");
        return 1;
    }
}

const char* verifica_gestor_password(Lista_g* li, int id){
	if(li == NULL)
        return 0;
    Elemento_g *no = *li;
    while(no != NULL && no->dados.code_trab != id){
        no = no->prox;
    }
    if(no != NULL){
        return no->dados.password;
    }
}

int imprime_fatura(Lista* li,int id,int qtd){
	if(li == NULL)
        return 0;
    Elemento *no = *li;
    while(no != NULL && no->dados.codigo != id){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
        
    }else{
        printf("Produto comprado: %s \n Quantidade: %d\nTotal: %.2f\n", no->dados.nome,qtd,no->dados.preco * qtd);
        return 1;
    }
}
