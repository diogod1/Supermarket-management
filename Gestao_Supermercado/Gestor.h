//******************Estruturas******************************************

//-----CLIENTE
struct cliente{
	int num_cliente;
	char nome[30];
	char morada[30];
	int num_contr;
	char num_ccredito[30];
	char password[30];
};

//-----GESTOR
struct gestor{
	int code_trab;
	char nome[30];
	char password[30];
};

//-----PRODUTOS
struct produtos{
	int codigo;
	char nome[30];
	float preco;
	char validade[10];
	int qtd_stock;
};


typedef struct elemento* Lista;
typedef struct elemento_clientes* Lista_c;
typedef struct elemento_gestor* Lista_g;

//***************PROTOTIPOS DE FUNÇÃO******************
//--login
int login(int option,Lista_g* li_g,Lista_c* li_c,Lista* li);
//--menu gestor
int menu_gestor(Lista* li, Lista_c* li_c,Lista_g* li_g);
//--menu cliente
int menu_cliente(Lista* li,Lista_c* li_c);

//--LISTA PARA PRODUTOS
Lista* cria_lista();
void liberta_lista(Lista* li);
int tamanho_lista(Lista* li);
int insere_lista_ordenada(Lista* li, struct produtos data);
void imprime_lista(Lista* li);
int consulta_lista_id_produto(Lista* li, int id);//consulta pelo conteudo
int remove_lista_produto(Lista* li, int id);
int ultimo_id_produto(Lista* li);
int imprime_fatura(Lista* li,int id,int qtd);
	//CARREGRAR PRODUTOS DO FICHEIRO
void load_txt_produtos(Lista* li);
void update_txt_produtos(Lista* li);

//---LISTA PARA USERS/CLIENTES
Lista_c* cria_lista_c();
void liberta_lista_c(Lista_c* li);
int insere_lista_ordenada_c(Lista_c* li, struct cliente data);
void imprime_lista_c(Lista_c* li);
int consulta_lista_id_cliente(Lista_c* li, int id);//consulta pelo conteudo
int remove_lista_c_cliente(Lista_c* li);//---funçao para o cliente remover a propria conta
int remove_lista_cliente(Lista_c* li, int id);//--funçao para o admin remover qualquer cliente
int verifica_cliente(Lista_c* li, int id);
const char* verifica_cliente_password(Lista_c* li, int id);
int ultimo_id_cliente(Lista_c* li);
	//CARREGRAR CLIENTES DO FICHEIRO
void load_txt_clientes(Lista_c* li);
void update_txt_clientes(Lista_c* li);

//---lISTA PARA GESTORES---
Lista_g* cria_lista_g();
void liberta_lista_g(Lista_g* li);
int insere_lista_ordenada_g(Lista_g* li, struct gestor data);
void imprime_lista_g(Lista_g* li);
int verifica_gestor(Lista_g* li, int id);
const char* verifica_gestor_password(Lista_g* li, int id);
	//CARREGRAR GESTOR DO FICHEIRO
void load_txt_gestor(Lista_g* li);
void update_txt_gestor(Lista_g* li);
