#include "includes/gerenciadorEspecies.h"  
#include "includes/capturas.h"
#include "includes/fileIO.h"     
#include "includes/listaDeRegistrosWorstFit.h"                                               
#include "includes/pilhaRegistros.h"
#include "includes/interpretarMsg.h"
#include <stdlib.h>
#include <cstring>
#include <iterator>
#include <unordered_map>

fileIO* ioHeadEspecies;
listaDeRegistrosWorstFit* ledEspecies;
gerenciadorEspecies* gerenEspecies;

void clear(){
	system("clear");
}

void initEspecies(){
	ioHeadEspecies = new fileIO();
	ledEspecies = new listaDeRegistrosWorstFit();
	ioHeadEspecies->openFile(string("./data/headEspecies"));
	ledEspecies->loadHead(ioHeadEspecies);
	gerenEspecies = new gerenciadorEspecies(ledEspecies);
	gerenEspecies->openFile(string("./data/especies"));
}

void insereEspecie(int id, string nomeCientifico, 
		string nomePopular, string descricao){
	especies especie(id,nomeCientifico,nomePopular,descricao);
	if(gerenEspecies->busca(&especie) == -1){
		gerenEspecies->insere(especie);
		cout << "Espécie cadastrada!" << endl;
	}else{
		cout << "Espécie já cadastrada" << endl; 
		getchar();
		getchar();	
	}
}

void interpretarMsg(string reason, map_atributes atributes){
	if (reason == "cadastrar"){
		insereEspecie(atoi(atributes["id"].c_str()),atributes["nomeCientifico"],
				atributes["nomePopular"],atributes["breveDesc"]);
	}
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

