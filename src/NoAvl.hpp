/*
 * NoAvl.hpp
 *
 *  Created on: 25/05/2015
 *      Author: LuizF
 */
#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#define tpNaoGira 0
#define tpGiroDireita 1
#define tpGiroEsquerda 2
#define ERROARVNULA -999
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
#define DIRARVOREDAT "E:\\ManPages\\IndPrimario\\arvore.dat"
using namespace std;

#include <vector>

template<typename T>
class NoAVL;

template<typename T>
class IndexadorArvoreAvl {
private:
	int nIndex;
public:
	void GerarIndices(NoAVL<T>* arvore) {
		arvore->setIndiceDisco(nIndex);
		nIndex++;
		if (arvore->getEsquerda()) {
			GerarIndices(arvore->getEsquerda());
		}
		if (arvore->getDireita()) {
			GerarIndices(arvore->getDireita());
		}
	}
};

template<typename T>

class NoAVL {
private:
	int altura; //!< Representa a altura do nó AVL
	T* dado;

	int indiceDiscoEsquerda;
	int indiceDiscoDireita;
	int indiceDisco;

	std::string caminhoDisco;

	NoAVL<T>* esquerda;
	NoAVL<T>* direita;
	std::vector<NoAVL<T>*> elementos;

	NoAVL<T>* executarBalanceamento(NoAVL<T>* arv);
	int definirTipoGira(NoAVL<T>* arv) {
		int alturaD, alturaE;

		alturaD = arv->direita ? arv->direita->altura : -1;

		alturaE = arv->esquerda ? arv->esquerda->altura : -1;
		int dif = alturaD - alturaE;

		if ((dif > -2) && (dif < 2))
			return tpNaoGira;

		if (dif == -2)
			return tpGiroDireita;

		return tpGiroEsquerda;
	}

	NoAVL<T>* girarAEsquerda(NoAVL<T>* arv) {
		int altNetoD, altNetoE;
		altNetoD =
				(!arv->direita) || (!arv->direita->direita) ?
						-1 : arv->direita->direita->altura;
		altNetoE =
				(!arv->direita) || (!arv->direita->esquerda) ?
						-1 : arv->direita->esquerda->altura;
		if ((altNetoD - altNetoE) < 0) {
			arv->direita = girar(arv->direita, true);
		};

		return girar(arv, false);
	}

	int FatorFilhoGiroDireita(NoAVL<T>* arv) {
		int fatorADicionalEsquerda =
				(!arv->esquerda) || (!arv->esquerda->esquerda) ?
						-1 : arv->esquerda->esquerda->altura;
		int fatorADicionalDireita =
				(!arv->esquerda) || (!arv->esquerda->direita) ?
						-1 : arv->esquerda->direita->altura;
		return fatorADicionalEsquerda - fatorADicionalDireita;
	}

	int FatorFilhoGiroEsquerda(NoAVL<T>* arv) {
		int fatorADicionalDireita =
				(!arv->direita) || (!arv->direita->direita) ?
						-1 : arv->direita->direita->altura;
		int fatorADicionalEsquerda =
				(!arv->direita) || (!arv->direita->esquerda) ?
						-1 : arv->direita->esquerda->altura;
		return fatorADicionalEsquerda - fatorADicionalDireita;
	}

	NoAVL<T>* girarADireita(NoAVL<T>* arv) {

		int fatorADicionalEsquerda =
				(!arv->esquerda) || (!arv->esquerda->esquerda) ?
						-1 : arv->esquerda->esquerda->altura;
		int fatorADicionalDireita =
				(!arv->esquerda) || (!arv->esquerda->direita) ?
						-1 : arv->esquerda->direita->altura;

		if ((fatorADicionalEsquerda - fatorADicionalDireita) < 0) {
			arv->esquerda = girar(arv->esquerda, false);
		};

		return girar(arv, true);
	}

	NoAVL<T>* girar(NoAVL<T>* arv, bool bDireita) {
		NoAVL<T>* temp = bDireita ? arv->esquerda : arv->direita;

		if (bDireita) {
			arv->esquerda = NULL;
			if (temp->direita)
				arv->esquerda = temp->direita;
			temp->direita = arv;
			temp->direita->altura = DefinirAltura(temp->direita);
			if (temp->esquerda)
				temp->esquerda->altura = DefinirAltura(temp->esquerda);
		} else {
			arv->direita = NULL;
			if (temp->esquerda)
				arv->direita = temp->esquerda;
			temp->esquerda = arv;
			if (temp->direita)
				temp->direita->altura = DefinirAltura(temp->direita);
			temp->esquerda->altura = DefinirAltura(temp->esquerda);
		}
		arv = temp;
		arv->altura = DefinirAltura(arv);

		return arv;
	}

public:
	explicit NoAVL(const T& dado) {
		this->altura = 0;
		this->dado = new T(dado);
		this->esquerda = NULL;
		this->direita = NULL;
		this->indiceDiscoDireita = -1;
		this->indiceDiscoEsquerda = -1;
		this->caminhoDisco = "";

	}

	//virtual ~NoAVL();
	int getAltura() {
		return altura;
	}
	std::vector<NoAVL<T>*> getElementos();
	NoAVL<T>* getEsquerda() {
		return esquerda;
	}

	NoAVL<T>* getDireita() {
		return direita;
	}

	int DefinirAltura(NoAVL<T>* arv) {
		if ((!arv->esquerda) && (!arv->direita))
			return 0;

		if (!arv->direita)
			return (arv->esquerda->altura) + 1;

		if (!arv->esquerda)
			return (arv->direita->altura) + 1;

		return arv->direita->altura > arv->esquerda->altura ?
				(arv->direita->altura) + 1 : (arv->esquerda->altura) + 1;
	}

	NoAVL<T>* inserir(const T& dado, NoAVL<T>* arv) {
		//*arv->getDado()

		if (dado <= *arv->dado) {
			arv->esquerda =
					(arv->esquerda) ?
							inserir(dado, arv->esquerda) : new NoAVL<T>(dado);

		} else {
			arv->direita =
					arv->direita ?
							inserir(dado, arv->direita) : new NoAVL<T>(dado);
		};

		arv->altura = DefinirAltura(arv);

		switch (definirTipoGira(arv)) {
		case tpGiroDireita: {
			if ((FatorFilhoGiroDireita(arv)) < 0)
				arv->esquerda = girar(arv->esquerda, false);
			arv = girar(arv, true);
			break;
		}
		case tpGiroEsquerda:
			if ((FatorFilhoGiroEsquerda(arv)) > 0)
				arv->direita = girar(arv->direita, true);
			arv = girar(arv, false);
			break;
		default:
			break;
		}

		return arv;
	}

	NoAVL<T>* BalancearArv(NoAVL<T>* arv) {
		switch (definirTipoGira(arv)) {
		case tpGiroDireita: {
			if ((FatorFilhoGiroDireita(arv)) < 0)
				arv->esquerda = girar(arv->esquerda, false);
			arv = girar(arv, true);
			break;
		}
		case tpGiroEsquerda:
			if ((FatorFilhoGiroEsquerda(arv)) > 0)
				arv->direita = girar(arv->direita, true);
			arv = girar(arv, false);
			break;
		default:
			break;
		}

		return arv;
	}

	NoAVL<T>* remover(NoAVL<T>* arv, const T& dado) {
		if (!arv)
			throw ERROARVNULA;

		if (dado < *arv->dado) {
			if (!arv->esquerda)
				throw ERROARVNULA;
			arv->esquerda = remover(arv->esquerda, dado);

		}

		if (dado > *arv->dado) {
			if (!arv->direita)
				throw ERROARVNULA;

			arv->direita = remover(arv->direita, dado);

		}

		NoAVL<T>* temp;
		if (dado == *arv->dado) {
			if (!arv->esquerda && !arv->direita) {
				delete arv;
				return NULL;
			}

			NoAVL<T> *temp;

			if (!arv->esquerda && arv->direita) {
				temp = arv->direita;
				delete arv;
				DefinirAltura(temp);
				return temp;
			}

			if (arv->esquerda && !arv->direita) {
				temp = arv->esquerda;
				delete arv;
				DefinirAltura(temp);
				return temp;
			}

			temp = minimo(arv->direita);
			if (temp->dado != arv->direita->dado) {
				temp->direita = arv->direita;
				temp->direita->esquerda = NULL;
			}
			temp->esquerda = arv->esquerda;

			delete arv;
			if (temp->direita)
				temp->direita = BalancearArv(temp->direita);
			if (temp->esquerda)
				temp->esquerda = BalancearArv(temp->esquerda);
			temp->altura = DefinirAltura(temp);
			return BalancearArv(temp);
		}

		arv->altura = DefinirAltura(arv);

		switch (definirTipoGira(arv)) {
		case tpGiroDireita: {
			if ((FatorFilhoGiroDireita(arv)) < 0)
				arv->esquerda = girar(arv->esquerda, false);
			arv = girar(arv, true);
			break;
		}
		case tpGiroEsquerda:
			if ((FatorFilhoGiroEsquerda(arv)) > 0)
				arv->direita = girar(arv->direita, true);
			arv = girar(arv, false);
			break;
		default:
			break;
		}

		return arv;
	}
	NoAVL<T>* minimo(NoAVL<T>* nodo) {
		return nodo->esquerda ? minimo(nodo->esquerda) : nodo;
	}
	T* getDado() const {
		return dado;
	}

	virtual void SalvarParaArquivo(NoAVL<T>* nodo) {
		ofstream output(DIRARVOREDAT, ios::app | ios::binary);

		if (nodo->getDireita()) {
			nodo->setIndiceDiscoDireita(nodo->getDireita()->getIndiceDisco());
		}

		if (nodo->getEsquerda())
			nodo->setIndiceDiscoEsquerda(nodo->getEsquerda()->getIndiceDisco());

		output.write((char *) nodo->getDado(), sizeof(T));
		output.close();

		if (nodo->getEsquerda()) {
			SalvarParaArquivo(nodo->getEsquerda());
		};

		if (nodo->getDireita()) {
			SalvarParaArquivo(nodo->getDireita());
		}
	}
	;

	T* busca(const T& dado, NoAVL<T>* arv){
		if (!arv)
			throw -999;
		if (dado == *arv->dado) {
			return arv->dado;
		}
		if (dado < *arv->dado) {
			if (!arv->esquerda)
				throw -999;
			return busca(dado, arv->esquerda);
		}

		if (dado > *arv->dado) {
			if (!arv->direita)
				throw -999;
			return busca(dado, arv->direita);
		}
	}

	bool contem(const T& dado) {
		try {
			busca(dado, this);
		} catch (int e) {
			return false;
		}
		return true;
	}

	void preOrdem(NoAVL<T>* nodo);
	void emOrdem(NoAVL<T>* nodo);
	void posOrdem(NoAVL<T>* nodo) {
		if (!nodo)
			return;
		posOrdem(nodo->esquerda);
		posOrdem(nodo->direita);
		elementos.push_back(nodo);
	}
	void setIndiceDisco(int indice) {
		indiceDisco = indice;
	}

	int getIndiceDisco() {
		return indiceDisco;
	}
	int getIndiceDiscoEsquerda() {
		return indiceDiscoEsquerda;
	}
	int getIndiceDiscoDireita() {
		return indiceDiscoDireita;
	}

	void setIndiceDiscoEsquerda(int index) {
		indiceDiscoEsquerda = index;
	}

	void setIndiceDiscoDireita(int index) {
		indiceDiscoDireita = index;
	}

	void IndexarArvore(int pindice) {
		IndexadorArvoreAvl<T> * indexador = new IndexadorArvoreAvl<T>();
		indexador->GerarIndices(this);
	}

	T* BuscaDoDisco(const string& chave, int indice, NoAVL<T> *arvore) {
		T* retorno = this->CarregaDoDisco(indice);

		cout << "Comando: " << retorno->key << endl;

		int pos = chave.compare(retorno->key);
		if (pos == 0) {
			cout << "ACHOU " << retorno->key << endl;
			return retorno;
		}

		delete retorno;

		if (pos == -1) {
			cout << "Foi à esquerda: " << endl;
			if (arvore->indiceDiscoEsquerda == -1) {
				return NULL;
			} else {
				return BuscaDoDisco(chave, arvore->indiceDiscoEsquerda,
						arvore->getEsquerda());
			}
		}

		if (pos == 1) {
			cout << "Foi à direita: " << endl;
			if (arvore->indiceDiscoDireita == -1) {
				return NULL;
			} else {
				return BuscaDoDisco(chave, arvore->indiceDiscoDireita,
						arvore->getDireita());
			}
		}
	}

	T* CarregaDoDisco(int nIndice) {
		ifstream input(DIRARVOREDAT, ios::in | ios::binary);

		if (!input) {
			cout << "Erro ao ler arquivo da árvore.";
		}

		T *dado = new T();

		int tamanho = sizeof(T);

		input.seekg(streampos(nIndice * tamanho));
		input.read((char *) dado, tamanho);
		input.close();

		return dado;
	}

	void DeletarArvoresFilhas() {
		posOrdem(this);
		elementos.clear();
	}
};

#endif /* NO_AVL_HPP */
