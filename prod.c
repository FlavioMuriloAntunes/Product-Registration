#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define tam 3

typedef struct {
    char nome[100];
    int quantidade;
    float valor;


}produto;

  produto produtos[tam];
  int quant=0;



void cadastrarProd(){
    if(quant>=tam){
        printf("limite de produtos atingido");
        return;

    }
    printf("digite o nome do produto:");
    getchar();
    fgets(produtos[quant].nome, sizeof(produtos[quant].nome), stdin);


    printf("Digite a quantidade do produto:");
    scanf("%d", &produtos[quant].quantidade);


    printf("digite o valor de cada unidade do produto:");
    scanf("%f", &produtos[quant].valor);


    FILE *arq= fopen("listaProd", "ab");   // Abre o arquivo para adicionar o produto ao final
    if(!arq){
        printf("erro ao abrir o arquivo para escrita");

        return;
    }

    fwrite(&produtos[quant],sizeof(produto), 1, arq); // escreve o produto no arquivo
    fclose(arq);

    quant ++;  // avança uma casa na lista

    system("cls");

}

void mostrarProd(){
    FILE *arq= fopen("listaProd", "rb");

    if(!arq){
        printf("erro ao abrir o arquivo\n");
        return;
    }
   produto prodTemp;
    printf("---------lista dos produtos cadastrados---------- \n");
    while(fread(&prodTemp,sizeof(produto), 1,arq )){
        printf("nome: %s", prodTemp.nome);
        printf("quantidade: %d\n", prodTemp.quantidade);
        printf("Valor: %.2f\n", prodTemp.valor);
        printf("---------------------------------------------\n");


    }
    fclose(arq);
}


int main(){
    setlocale(LC_ALL, "Portuguese");

    FILE *arq= fopen("listaProd", "rb");
    int op;
    if(!arq){   // verifica se existe o arquivo
     arq=fopen("listaProd", "wb"); // se nao existir ele cria um
     printf("Lista de produtos criada!!!\n");
     fclose(arq);
    }else{
     fclose(arq);
    }






    do{

    printf("Digite 1 para cadastrar produto\n 2-lista dos produtos\n 0- sair do programa\n");
    scanf("%d", &op);
       switch(op){
        case 1:
            cadastrarProd();
            printf("produto cadastrado com sucesso!!!\n\n\n");
            break;
        case 2:
            mostrarProd();
            break;
        case 0:
            printf("fim!!");
            break;
        default:
             printf("Operação inválida! Tente novamente.\n");
            break;

       }
    }while(op!= 0);

    return 0;
}
