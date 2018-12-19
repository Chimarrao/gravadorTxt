#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

void cores(int ForgC, int BackC){ 															//cor do texto
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

void textcolor(int newcolor){ 																//cor do texto
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
     (csbi.wAttributes & 0xf0) | newcolor);
}

FILE* AbreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g': 																			//Puxa informação
            arquivo = fopen(caminho,"wb");
            break;
        case 'l': 																			//Somente leitura
            arquivo = fopen(caminho,"r");
            break;
        case 'a': 																			//Escreve
            arquivo = fopen(caminho,"a");
            break;
        case 'w':  																			//Lipar tudo
        	arquivo = fopen(caminho, "w");
    }
    if(arquivo==NULL){  																	//Caso não haja texto
    	textcolor(12);
        printf("Arquivo Vazio ou com Problema");
        textcolor(15);
        exit(0);
    }
    return arquivo;
}

void FecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void Cadastra(char nome[30], int num){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "vendas.txt");
    fprintf(arquivo, "%s\n%d\n", nome, num);  												//Escreve no arquivo e quebra linha
    FecharArquivo(arquivo);
}

void Listar(){
    FILE *arquivo;
    char nome[30], aux[10];
    int num;

    arquivo = AbreArquivo('l',"vendas.txt");

    while(!feof(arquivo)){  																//Enquanto haver elementos no arquivo
        fscanf(arquivo,"%[^\n] %d ", &nome, &num);  										//Imprime ate \n
        if(num == 0){  												  						//Evitar o erro da sujeira na lista
        	printf("Lista Vazia...\n");
			strcpy(nome, " ");
		}else{
        printf("Nome: %s Número: %d\n", nome, num);
    	}
	}
    FecharArquivo(arquivo);
}

void leitor(){
	char nome[30];
	int num;

	printf("\nDigite o nome: ");
    setbuf(stdin,NULL);
	gets(nome);
	printf("\nDigite o número da Venda: ");
    scanf("%d", &num);
	while(num < 1){
		textcolor(12);
		printf("Número Inválido");
		textcolor(15);
		printf("\nDigite o número da Venda: ");
    	scanf("%d", &num);
	}
	Cadastra(nome, num);
}

void limpar(){
	FILE *arquivo;
	char aux = "Nulo";
	int i;
	AbreArquivo('w', "vendas.txt");
	printf("Pronto, o arquivo foi Limpo !\n");
}

int main(){
	setlocale(LC_ALL, "");
    int opcao;
    do{
        system("cls");
        textcolor(10);
        printf("         Menu");
        textcolor(15);
        printf("\n\n 1 - Registrar Venda");
        printf("\n 2 - Listar Vendas");
        printf("\n 3 - Limpar Dados");
        printf("\n 4 - Sair");

        printf("\n\nDigite uma opcao: ");
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
            case 1:
                leitor();
                system("pause");
                break;
            case 2:
                Listar();
                system("pause");
                break;
            case 3:
				limpar();
				system("pause");
				break;    
            case 4:
                printf("\n\nFinalizando...\n\n");
                system("pause");
                exit(0);
                break;
            default:
            	textcolor(12);
                printf("\n\nOpcao invalida! Tente Novamente!\n\n");
                textcolor(15);
                system("pause");
        }
    }while(opcao!=4);

    return 0;
}
