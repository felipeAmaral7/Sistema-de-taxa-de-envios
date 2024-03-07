#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct{

	char nome[101];
	int cpf;

} Pessoa;

typedef struct{

	int tipoProduto;
	int destino;
	double peso;

} Produto;

void printc(char c, int tamanho){
	
	int cont;
	
	for(cont = 0; cont < tamanho; cont++){
		printf("%c", c);
	}
}

void imprimeInformacoesProduto(){

	printf("\nOs tipos de Produtos sao divididos em 4, sendo eles:\n ");
	printf("Tipo 0: Frageis (Espelhos pequenos, tacas, garrafas de bebidas)\n ");
	printf("Tipo 1: Leves ate 1 kilo (Peca de roupa, tenis, chapeu, relogio, etc)\n ");
	printf("Tipo 2: Grande dimensoes maiores que 1.5 x 1.5 (Cortina, Tapete, Quadro, Televisoes, etc)\n ");
	printf("Tipo 3: Outros ( Produtos que nao se encaixam nas opcoes anteriores)\n");
}

void imprimeInformacoesDistancia(){

	printf("\nAs distancias tambem sao divididos em 4:\n ");
	printf("Tipo 0: 0 a 50km\n ");
	printf("Tipo 1: 50km a 150km\n ");
	printf("Tipo 2: 150km a 500km\n ");
	printf("Tipo 3: 500km ou mais\n ");
}

double taxaPeso(double peso){
	
	double tarifa;
	
	tarifa = 4 * peso;		//a taxa do peso se baseia no peso vezes uma taxa fixa de 4 Reais;
	
	return tarifa;
	
}

double taxaDistancia(int tipoProduto, int distancia){
	
	// preco da taxa dos produtos, somando a distancia com o tipo do produto;
	
	double matriz[4][4] = {
	3.5, 6.5, 9.5, 17,
	2.5, 5.5, 8.5, 16,
	6.5, 9.5, 12.5, 20,
	4.5, 7.5, 10.5, 18
	};
	
	return matriz[tipoProduto][distancia];
	
}

int main(void){
	
	setlocale(LC_ALL, "Portuguese");
	
	printf("SISTEMA DE TAXA DE ENVIOS\n\n");
	
	printf("Ola, deseja enviar um produto? (caso sim, digite 's'. Caso nao digite 'n')\n");
	
	char yesOrNo;
	
	scanf("%c", &yesOrNo);
	
	if(yesOrNo == 's'){

		int quantPessoas;
		printf("Ok, quantas pessoas irão efetuar o envio do produto?\n");
		scanf("%d", &quantPessoas);	
		Pessoa person[quantPessoas];
		Produto product;

		int entra1x = 1;
		for(int i = 0; i < quantPessoas; i++){
			fflush(stdin);

			if(entra1x){

				//preenche a struct pessoa com suas informacoes
				for(int j = 0; j < quantPessoas; j++){
					printf("\nDigite o nome do %d ° que ira enviar:\n", j+1);
					scanf("%101[^\n]", person[j].nome);

					printf("\nDigite seu cpf: ");
					scanf("%d", &person[j].cpf);
					fflush(stdin);
				}
				entra1x = 0;
			}	
			
			printf("\nOk, sua vez %s. Para isso fique ciente de algumas informacoes a seguir:\n", person[i].nome);
			
			double imprimeTaxas[50];
			
			int tamanhoVetor = 0;
			
			char repit = 's';
			
			int cont = 0;
					
			while(repit == 's'){
			
				if(cont == 0){
					printc('-', 100);
					imprimeInformacoesProduto();		//imprime as informacoes sobre o produto somente 1x
					printc('-', 100);
				}
				
				printf("\nDigite o tipo do produto: \n");
				do{
					scanf("%d", &product.tipoProduto);
					
					if(product.tipoProduto < 0 || product.tipoProduto > 4){
						printf("Digite um valor valido:\n");
					}
				}while(product.tipoProduto < 0 || product.tipoProduto > 4);
				
				if(cont == 0){
					printc('-', 100);
					imprimeInformacoesDistancia();		//imprime as informacoes sobre a distancia somente 1x
					printc('-', 100);
				}
				
				printf("\nAgora digite o tipo de destino:\n");

				do{
					scanf("%d", &product.destino);
					
					if(product.destino < 0 || product.destino > 4){
						printf("Digite um valor valido:\n");
					}
					
				}while(product.destino < 0 || product.destino > 4);
				
				printf("\nDigite o peso do produto em Kg: ");
				scanf("%lf", &product.peso);
				
				if(product.tipoProduto >= 0 && product.tipoProduto <=4 && product.destino >= 0 && product.destino <=4){
					
					double taxa1, taxa2;
					
					taxa1 = taxaPeso(product.peso);
					
					taxa2 = taxaDistancia(product.tipoProduto, product.destino);		//procura a devida taxa na matriz;
					
					double taxaFinal = taxa1 + taxa2;
					
					imprimeTaxas[cont] = taxaFinal;
					
					cont ++;
				}
				else{
					printf("\nValores invalidos");
				}
				
				tamanhoVetor = cont;
				
				fflush(stdin);
				
				printf("\nDeseja enviar novamente? Se sim, digite 's', caso nao 'n'");
				scanf("%c", &repit);
			}
					
			double somaTaxas = 0;
			
			int contador = 0;
			
			printc('-', 100);
			
			for(contador = 0; contador < tamanhoVetor; contador++){
				printf("\nTaxa do Produto %d: %.2lf", contador + 1, imprimeTaxas[contador]);
				
				somaTaxas += imprimeTaxas[contador];
			}
			
			printf("\n%s, o valor de sua taxa total resultou em: %.2lf Reais\n", person[i].nome, somaTaxas);
			
			printc('-', 100);
			printf("\n");

		}
	}
	else{
		printf("Certo, tenha um bom dia! :)");
	}
}
