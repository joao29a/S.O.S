#include "includes/gerenciadorEspecies.h"  
#include "includes/capturas.h"
#include "includes/fileIO.h"     
#include "includes/listaDeRegistrosWorstFit.h"                                               
#include "includes/pilhaRegistros.h"
#include "stdlib.h"
#include <cstring>
#include <iterator>

fileIO* ioHeadEspecies;
listaDeRegistrosWorstFit* ledEspecies;
gerenciadorEspecies* gerenEspecies;

void clear(){
		system("clear");
}

void removeEspecie(){
	int id = -1;

	clear();
	cout << "Digite o id do espécie a ser removido: ";
	scanf("%d",&id);
	especies especie(id,"","","");

	bool removeu = gerenEspecies->remove(especie);

	clear();
	if(removeu){
		cout << "Remoção efetuado com sucesso!" << endl;
	}else{
		cout << "Registro não encontrado!" << endl;	
	}
	getchar();
	getchar();
	clear();
}

void menuBuscaEspecie(){
	int id = -1;

	clear();
	cout << "Digite o id da espécie a ser buscada: ";
	scanf("%d",&id);
	especies* especie = new especies(id,"","","");
	int encontrou = gerenEspecies->busca(especie);
	if(encontrou != -1){
		clear();
		cout << "Encontrado." << endl;
		cout << "Id: " << id << endl;
		cout << "Nome Científico: " << especie->getNomeCientifico() << endl;
		cout << "Nome Popular: " << especie->getNomePopular() << endl;
		cout << "Descrição: " << especie->getDescricao() << endl;
		cout << "Enter para continuar." << endl;
	}else{
		clear();
		cout << "Nenhum registro encontrado." << endl;
	}
	getchar();
	getchar();
	clear();
}

void menuInsereEspecie(){
	clear();
	int id;
	string nomeCientifico;
	string nomePopular;
	string descricao;

	cout << "Inserir nova espécie:" << endl;
	cout << "Digite id: ";
	scanf("%d",&id);
	cout << "Digite o nome científico:";
	getchar();
	getline(cin, nomeCientifico, '\n'); 
	cout << "Digite o nome popular:";
	getline(cin, nomePopular, '\n');  
	cout << "Digite uma descrição: ";
	getline(cin, descricao, '\n');  

	especies especie(id,nomeCientifico,nomePopular,descricao);
	if(gerenEspecies->busca(&especie) == -1){
		gerenEspecies->insere(especie);
	}else{
		cout << "Espécie já cadastrada" << endl; 
		getchar();
		getchar();	
	}

	clear();	
}
