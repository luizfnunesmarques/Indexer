/*
 * AvlPaginaDisco.hpp
 *
 *  Created on: 28/06/2015
 *      Author: LuizF
 */

#ifndef AVLPAGINADISCO_HPP_
#define AVLPAGINADISCO_HPP_
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
#include "NoAvl.hpp"
#include "PaginaDisco.hpp"

class AvlPaginaDisco: public NoAVL<PaginaDisco> {
public:
	//explicit AvlPaginaDisco() :
	//		NoAVL(NULL) {
	//}

	void SalvarParaArquivo(NoAVL<PaginaDisco>* nodo) {
		ofstream output(DIRARVOREDAT, ios::app | ios::binary);

		if (nodo->getDireita())
			nodo->getDado()->IndiceFilhoDireita =
					nodo->getDireita()->getDado()->Indice;

		if (nodo->getEsquerda())
			nodo->getDado()->IndiceFilhoEsquerda =
					nodo->getEsquerda()->getDado()->Indice;

		//print indice

		output.write((char *) nodo->getDado(), sizeof(struct PaginaDisco));
		output.close();

		if (nodo->getEsquerda()) {
			SalvarParaArquivo(nodo->getEsquerda());
		};

		if (nodo->getDireita()) {
			SalvarParaArquivo(nodo->getDireita());
		}
	}

	PaginaDisco* BuscaArquivoEmDisco(const string& chave,
			int indice) {

		PaginaDisco* retorno = this->CarregarDadoEmDisco(indice);

		cout << "Comando: " << retorno->key << endl;

		int pos = chave.compare(retorno->key);
		if (pos == 0) {
			//retorno->key = (Char)carregado.key;
			//retorno->value = carregado.value;
			//retorno->Indice = carregado.Indice;
			return retorno;
		}

		int indesq = retorno->getIndiceEsquerda();
		int inddir = retorno->IndiceFilhoDireita;
		delete retorno;

		if (pos == -1) {
			cout << "Foi esquerda" << endl;
			if (indesq == -1) {
				return NULL;
			} else {
				return BuscaArquivoEmDisco(chave, indesq);
			}
		}
		if (pos == 1) {
			cout << "Foi direita" << endl;
			if (inddir == -1) {
				return NULL;
			} else {
				return BuscaArquivoEmDisco(chave, indesq);
			}
		}

	}

	PaginaDisco* CarregarDadoEmDisco(int nIndice) {
		ifstream input(DIRARVOREDAT, ios::in | ios::binary);

		if (!input) {
			cout << "Erro ao ler arquivo da árvore.";
		}

		PaginaDisco *dado = new PaginaDisco();

		input.seekg(streampos(nIndice * sizeof(PaginaDisco)));
		input.read((char *) dado, sizeof(PaginaDisco));
		input.close();

		return dado;
	}


}
;
#endif /* AVLPAGINADISCO_HPP_ */

