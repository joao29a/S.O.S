#include "includes/gerenciadorEspecies.h"  
#include "includes/fileIO.h"     
#include "includes/listaDeRegistrosWorstFit.h"                                               
#include "includes/pilhaRegistros.h"
#include "includes/interpretarMsg.h"
#include <stdlib.h>
#include <cstring>
#include <iterator>

fileIO* ioHeadEspecies;
listaDeRegistrosWorstFit* ledEspecies;
gerenciadorEspecies* gerenEspecies;

void initEspecies(){
	ioHeadEspecies = new fileIO();
	ledEspecies = new listaDeRegistrosWorstFit();
	ioHeadEspecies->openFile(string("./data/headEspecies"));
	ledEspecies->loadHead(ioHeadEspecies);
	gerenEspecies = new gerenciadorEspecies(ledEspecies);
	gerenEspecies->openFile(string("./data/especies"));
}

void commit(){
	ledEspecies->commitHead(ioHeadEspecies);
}

string insereEspecie(int id, string nomeCientifico, 
		string nomePopular, string descricao){
	especies especie(id,nomeCientifico,nomePopular,descricao);
	if(gerenEspecies->busca(&especie) == -1){
		gerenEspecies->insere(especie);
		commit();
		return string("status?v=1");
	}
	return string("status?v=0");
}

string buscaEspecie(int id){
	especies* especie = new especies(id,"","","");
	int encontrou = gerenEspecies->busca(especie);
	if(encontrou != -1){
		return string("resultado?v=1&nomeCientifico="+
				especie->getNomeCientifico()+"&nomePopular="+
				especie->getNomePopular()+"&breveDesc="+
				especie->getDescricao());
	}
	return string("status?v=0");
}

string removeEspecie(int id){
	especies especie(id,"","","");

	bool removeu = gerenEspecies->remove(especie);

	if(removeu){
		commit();
		return string("status?v=1");
	}
	return string("status?v=0");
}

string interpretarMsg(string reason, map_atributes atributes){
	if (reason == "cadastrar"){
		return insereEspecie(atoi(atributes["id"].c_str()),atributes["nomeCientifico"],
					atributes["nomePopular"],atributes["breveDesc"]);
	}
	else if (reason == "buscar"){
		return buscaEspecie(atoi(atributes["id"].c_str()));
	}
	else if (reason == "remover"){
		return removeEspecie(atoi(atributes["id"].c_str()));
	}
	return string("NULL");
}
