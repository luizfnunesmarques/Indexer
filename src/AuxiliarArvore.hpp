/*
 * GeradorIndicesArvore.hpp
 *
 *  Created on: 28/06/2015
 *      Author: LuizF
 */

#ifndef GERADORINDICESARVORE_HPP_
#define GERADORINDICESARVORE_HPP_
#include "NoBinario.hpp"
#include "PaginaDisco.hpp"

class AuxiliarArvore {
private:
	int nIndice = 0;
public:
	AuxiliarArvore() {

	}
	;
	void SalvarParaArquivo(NoAVL<NoDisco>* nodo) {
		ofstream output(DIRARVOREDAT, ios::app | ios::binary);

		if (nodo->getDireita())
			nodo->getDado()->indiceDireita =
					nodo->getDireita()->getDado()->indiceNoDat;

		if (nodo->getEsquerda())
			nodo->getDado()->indiceEsquerda =
					nodo->getEsquerda()->getDado()->indiceNoDat;

		//print indice

		output.write((char *) nodo->getDado(), sizeof(struct NoDisco));
		output.close();

		if (nodo->getEsquerda()) {
			SalvarParaArquivo(nodo->getEsquerda());
		};

		if (nodo->getDireita()) {
			SalvarParaArquivo(nodo->getDireita());
		}
	}
	NoAVL<NoDisco>* GerarIndicesArvore(NoAVL<NoDisco>* arv) {
		// rint cmd indice

		arv->getDado()->indiceNoDat = nIndice;
		nIndice++;
		if (arv->getEsquerda()) {
			GerarIndicesArvore(arv->getEsquerda());
		}
		if (arv->getDireita()) {
			GerarIndicesArvore(arv->getDireita());
		}
		return arv;
	}
	;

	PaginaDisco* BuscaArquivoEmDisco(const string& chave, int indice) {
		PaginaDisco* retorno = NULL;
		retorno = this->CarregarDadoEmDisco(indice);

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
				return BuscaArquivoEmDisco(chave, inddir);
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

};
#endif /* GERADORINDICESARVORE_HPP_ */

