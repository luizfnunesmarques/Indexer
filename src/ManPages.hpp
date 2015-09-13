/*
 * ManPages.hpp
 *
 *  Created on: 28/06/2015
 *      Author: LuizF
 */

#ifndef MANPAGES_HPP_
#define MANPAGES_HPP_
#define INDICESDAT "E:\\ManPages\\DAT\\manpages.dat"
#define INDICESSECUNDARIOS "E:\\ManPages\\DAT\\indSecundario.dat"
#define DIRFILES "E:\\ManPages\\txt\\"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <dirent.h>
#include <iosfwd>
#include <istream>

#include "NoBinario.hpp"
#include "NoAvl.hpp"
#include "ListaEnc.hpp"
#include "AdicionaNomeManPages.hpp"
#include "PaginaDisco.hpp"
#include "AuxiliarArvore.hpp"
#include "AvlPaginaDisco.hpp"
#include "IndiceSecundario.hpp"
using namespace std;

class ManPages {
private:
	NoAVL<NoDisco>* arv;

public:
	ManPages() {
		arv = NULL;
	}
	;

	PaginaDisco LerArquivoParaEstrutura(string nmArquivo) {
		PaginaDisco retorno = PaginaDisco();

		string nomeInteiro = DIRFILES + nmArquivo;

		FILE *fp;
		long lSize;
		char *buffer;

		fp = fopen(nomeInteiro.c_str(), "rb");
		if (!fp) {
			cout << "Arquivo não encontrado ou com erro." << endl;
		}

		fseek(fp, 0L, SEEK_END);
		lSize = ftell(fp);
		rewind(fp);

		buffer = new char[lSize + 1];

		if (!buffer) {
			fclose(fp);
			exit(1);
		}
		if (!fread(buffer, lSize, 1, fp)) {
			fclose(fp);
			free(buffer);
			exit(1);
		}

		nmArquivo = nmArquivo.substr(0, nmArquivo.find_last_of("."));

		fclose(fp);
		retorno.key.assign(nmArquivo.c_str());
		strcpy(retorno.value, buffer);
		delete buffer;

		return retorno;
	}

	void GerarArquivosEIndices() {

		DeletarIndices();
		string nome;
		ListaEnc<string>* lista = ListarArquivos();
		IndiceSecundario* indSecundario = new IndiceSecundario();
		ListaEnc<NoDisco>* listaNoDisco = new ListaEnc<NoDisco>;
		ListaEnc<PaginaDisco>* listaArquivosNoDat = new ListaEnc<PaginaDisco>;
		NoDisco noDisco;
		ofstream output(INDICESDAT, ios::app | ios::binary);
		int indice = 0;

		while (!lista->listaVazia()) {
			nome = lista->retira();
			ofstream output(INDICESDAT, ios::app | ios::binary);
			PaginaDisco chaveParaDat = LerArquivoParaEstrutura(nome);
			chaveParaDat.Indice = indice;
			output.write((char*) &chaveParaDat, sizeof(struct PaginaDisco));
			cout << chaveParaDat.Indice << endl;
			//indSecundario->IndexarNovoArquivo(chaveParaDat.value, chaveParaDat.Indice);
			listaArquivosNoDat->adicionaNoInicio(chaveParaDat);
			noDisco = NoDisco();
			noDisco.indiceNoDat = indice;
			noDisco.key = nome;

			listaNoDisco->adicionaNoInicio(noDisco);
			indice++;
		}

		output.close();

		while (!listaNoDisco->listaVazia()){
			NoDisco noDisco = listaNoDisco->retiraDoInicio();
			if (arv == NULL) {
				arv = new NoAVL<NoDisco>(noDisco);
			} else {
				arv = arv->inserir(noDisco, arv);
			};
		}

		GerarIndicesArvore(arv);
		SalvarArvoreDisco(arv);

		/*PaginaDisco chaveParaDatTemp;
		while (!listaArquivosNoDat->listaVazia()){
			chaveParaDatTemp = listaArquivosNoDat->retira();
			cout << chaveParaDatTemp.Indice << endl;
			indSecundario->IndexarNovoArquivo(chaveParaDatTemp.value, chaveParaDatTemp.Indice);
		}*/
/*
			//indSecundario->IndexarNovoArquivo(chaveParaDat.value, indice);
			indice++;
		}

		cout << "terminou de gerar os indices" << endl;*/


		//GerarIndicesArvore(arv);
		//SalvarArvoreDisco(arv);
		//GerarIndiceSecundario(indSecundario);
		//delete indSecundario;
	}

	void GerarIndiceSecundario(IndiceSecundario* indSecundario){
		ofstream output(INDICESSECUNDARIOS, ios::app | ios::binary);
		//IndiceSecundarioMemoria* ind =indSecundario->getListaPalavras()->retiraDoInicio();
		indiceSecundarioDisco* indDisco;
		/*while (!indSecundario->getListaPalavras()->listaVazia()){
			indDisco = new indiceSecundarioDisco();
			cout << "indice para" <<endl;
			cout << ind->palavra <<endl;
			indDisco->palavra = ind->palavra;
			ind = indSecundario->getListaPalavras()->retiraDoInicio();
			indDisco->indices = new int[5000];
			//indDisco->indices = ind->indices;
			output.write((char*) indDisco, sizeof(struct indiceSecundarioDisco));
		}*/

		output.close();

		//output.write((char*) &chaveParaDat, sizeof(struct PaginaDisco));
	}

	void SalvarArvoreDisco(NoAVL<NoDisco>* arv) {
		AuxiliarArvore* aux = new AuxiliarArvore();
		aux->SalvarParaArquivo(arv);
		//arv->SalvarParaArquivo(arv);
	}

	void GerarIndicesArvore(NoAVL<NoDisco>* arv) {
		AuxiliarArvore* aux = new AuxiliarArvore();
		aux->GerarIndicesArvore(arv);
		//arv->IndexarArvore(0);
	}

	ListaEnc<string>* ListarArquivos() {
		ListaEnc<string>* lista = new ListaEnc<string>();
		AdicionaNomeManPages obj = AdicionaNomeManPages();

		lista = obj.PegarListaNomeArquivos();

		return lista;
	}

	void BuscaArquivo(const string& chave) {
		AuxiliarArvore* aux = new AuxiliarArvore();
		PaginaDisco* retorno = NULL;
		retorno = aux->BuscaArquivoEmDisco(chave, 0);

		if (!retorno) {
			cout << "===================" << endl;
			cout << "===================" << endl;
			cout << "===================" << endl;
			cout << "Não encontrado" << endl;
			return;
		}

		cout << "===================" << endl;
		cout << "===================" << endl;
		cout << "===================" << endl;
		cout << "Página encontrada, início do conteúdo:" << endl;
		cout << endl;
		cout << retorno->value;
		cout << "Fim do conteúdo:" << endl;
	}

	void DeletarIndices() {
		struct dirent *next_file;
		DIR *theFolder;

		char filepath[256];

		theFolder = opendir("E:\\ManPages\\IndPrimario");

		while (next_file = readdir(theFolder)) {
			sprintf(filepath, "%s/%s", "E:\\ManPages\\IndPrimario",
					next_file->d_name);
			remove(filepath);
		}

		theFolder = opendir("E:\\ManPages\\DAT");

		while (next_file = readdir(theFolder)) {

			sprintf(filepath, "%s/%s", "E:\\ManPages\\DAT", next_file->d_name);
			remove(filepath);
		}
	}

	void BuscarPalavraIndiceSecundario(const string& chave){
		IndiceSecundario* ind = new IndiceSecundario;
		ind->BuscarPalavra(chave);
		delete ind;
	}
}
;

#endif /* MANPAGES_HPP_ */

