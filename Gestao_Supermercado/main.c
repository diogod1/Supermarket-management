#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Gestor.h"

int main(){
	
	Lista *li = cria_lista();
	Lista_c *li_c = cria_lista_c();
	Lista_g *li_g = cria_lista_g();
	
	load_txt_produtos(li);
	load_txt_clientes(li_c);
	load_txt_gestor(li_g);
	
	int op1;
	printf("Prima '1' para entrar como cliente\n");
	printf("Prima '2' para entrar como gestor\n");
	scanf("%d", &op1);
	
	login(op1,li_g,li_c,li);
	
		
	liberta_lista(li);
	liberta_lista_c(li_c);
	liberta_lista_g(li_g);
	
	return 0;
}
