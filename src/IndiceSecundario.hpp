/*
 * IndiceSecundario.hpp
 *
 *  Created on: 30/06/2015
 *      Author: LuizF
 */

#ifndef INDICESECUNDARIO_HPP_
#define INDICESECUNDARIO_HPP_
#include "Lista.hpp"
#include "NoAvl.hpp"

#include "NoBinario.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#define SIMBOLOS " ,.\n:;!?<>-+_\\/#*\0{}"

using namespace std;

class IndiceSecundarioMemoria {
private:
	int nIndice;
public:
	IndiceSecundarioMemoria() {
		nIndice = 0;
	}
	std::string palavra;
	int indices[5000];
	void AdicionarIndice(int indiceArquivo) {
		this->indices[nIndice] = indiceArquivo;
		nIndice++;
	}

	bool operator==(const IndiceSecundarioMemoria& lhs) {
		return palavra.compare(lhs.palavra) == 0;
	}

	bool operator==(const string& chave) {
		return this->palavra == chave;
	}

	bool operator<(const IndiceSecundarioMemoria& lhs) const {
		return palavra.compare(lhs.palavra) < 0;
	}

	bool operator<=(const IndiceSecundarioMemoria& lhs) const {
		return (palavra.compare(lhs.palavra) < 1);
	}

	bool operator>(const IndiceSecundarioMemoria& lhs) {
		return palavra.compare(lhs.palavra) > 0;
	}
};

struct indiceSecundarioDisco {
public:
	indiceSecundarioDisco() {
		indices = new int[5000];
	}

	std::string palavra;
	int *indices;
};

class ListaOcorrencias: public ListaEnc<IndiceSecundarioMemoria*> {
public:
	void adicionaIndiceAPalavra(std::string palavra, int indiceArquivo) {
		IndiceSecundarioMemoria *elemento = new IndiceSecundarioMemoria();

		for (int i = 0; this->size; i++) {
			elemento = this->mostrarElemento(i);

			if (elemento->palavra == palavra) {
				elemento->AdicionarIndice(indiceArquivo);
				return;
			}
		}
		throw -999;
	}
	IndiceSecundarioMemoria* busca2(std::string palavra,
			NoAVL<IndiceSecundarioMemoria*>* arv) {

	}

};

//class ListaOcorrenciasAVL: public NoAVL<IndiceSecundarioMemoria*> {
//public:
//	void adicionaIndiceAPalavra(std::string palavra, int indiceArquivo) {
//		IndiceSecundarioMemoria * elemento;
//		this->busca(palavra, this);

//throw -999;
//}
//};

class IndiceSecundario {
private:
	NoAVL<string>* indicePalavrasGerais;
	ListaOcorrencias* listaOcorrenciasPalavras;
public:
	NoAVL<string>* exclusos;
	IndiceSecundario() {
		listaOcorrenciasPalavras = new ListaOcorrencias();
		indicePalavrasGerais = NULL;
		exclusos = new NoAVL<string>("aboard");
		PreencherConjuncoes();
	}
	;

	ListaOcorrencias* getListaPalavras() {
		return listaOcorrenciasPalavras;
	}

	void PreencherConjuncoes() {
		exclusos = new NoAVL<string>("aboard");
		exclusos = exclusos->inserir("a", exclusos);
		exclusos = exclusos->inserir("about", exclusos);
		exclusos = exclusos->inserir("and", exclusos);
		exclusos = exclusos->inserir("the", exclusos);
		exclusos = exclusos->inserir("that", exclusos);
		exclusos = exclusos->inserir("above", exclusos);
		exclusos = exclusos->inserir("across", exclusos);
		exclusos = exclusos->inserir("after", exclusos);
		exclusos = exclusos->inserir("against", exclusos);
		exclusos = exclusos->inserir("along", exclusos);
		exclusos = exclusos->inserir("amid", exclusos);
		exclusos = exclusos->inserir("among", exclusos);
		exclusos = exclusos->inserir("anti", exclusos);
		exclusos = exclusos->inserir("around", exclusos);
		exclusos = exclusos->inserir("as", exclusos);
		exclusos = exclusos->inserir("at", exclusos);
		exclusos = exclusos->inserir("before", exclusos);
		exclusos = exclusos->inserir("behind", exclusos);
		exclusos = exclusos->inserir("below", exclusos);
		exclusos = exclusos->inserir("beneath", exclusos);
		exclusos = exclusos->inserir("beside", exclusos);
		exclusos = exclusos->inserir("besides", exclusos);
		exclusos = exclusos->inserir("between", exclusos);
		exclusos = exclusos->inserir("beyond", exclusos);
		exclusos = exclusos->inserir("but", exclusos);
		exclusos = exclusos->inserir("by", exclusos);
		exclusos = exclusos->inserir("concerning", exclusos);
		exclusos = exclusos->inserir("considering", exclusos);
		exclusos = exclusos->inserir("despite", exclusos);
		exclusos = exclusos->inserir("down", exclusos);
		exclusos = exclusos->inserir("during", exclusos);
		exclusos = exclusos->inserir("except", exclusos);
		exclusos = exclusos->inserir("false", exclusos);
		exclusos = exclusos->inserir("true", exclusos);
		exclusos = exclusos->inserir("excepting", exclusos);
		exclusos = exclusos->inserir("excluding", exclusos);
		exclusos = exclusos->inserir("following", exclusos);
		exclusos = exclusos->inserir("for", exclusos);
		exclusos = exclusos->inserir("from", exclusos);
		exclusos = exclusos->inserir("in", exclusos);
		exclusos = exclusos->inserir("inside", exclusos);
		exclusos = exclusos->inserir("into", exclusos);
		exclusos = exclusos->inserir("like", exclusos);
		exclusos = exclusos->inserir("minus", exclusos);
		exclusos = exclusos->inserir("near", exclusos);
		exclusos = exclusos->inserir("of", exclusos);
		exclusos = exclusos->inserir("off", exclusos);
		exclusos = exclusos->inserir("on", exclusos);
		exclusos = exclusos->inserir("onto", exclusos);
		exclusos = exclusos->inserir("opposite", exclusos);
		exclusos = exclusos->inserir("outside", exclusos);
		exclusos = exclusos->inserir("over", exclusos);
		exclusos = exclusos->inserir("past", exclusos);
		exclusos = exclusos->inserir("per", exclusos);
		exclusos = exclusos->inserir("plus", exclusos);
		exclusos = exclusos->inserir("regarding", exclusos);
		exclusos = exclusos->inserir("round", exclusos);
		exclusos = exclusos->inserir("save", exclusos);
		exclusos = exclusos->inserir("since", exclusos);
		exclusos = exclusos->inserir("than", exclusos);
		exclusos = exclusos->inserir("through", exclusos);
		exclusos = exclusos->inserir("to", exclusos);
		exclusos = exclusos->inserir("toward", exclusos);
		exclusos = exclusos->inserir("towards", exclusos);
		exclusos = exclusos->inserir("under", exclusos);
		exclusos = exclusos->inserir("underneath", exclusos);
		exclusos = exclusos->inserir("unlike", exclusos);
		exclusos = exclusos->inserir("until", exclusos);
		exclusos = exclusos->inserir("up", exclusos);
		exclusos = exclusos->inserir("upon", exclusos);
		exclusos = exclusos->inserir("versus", exclusos);
		exclusos = exclusos->inserir("via", exclusos);
		exclusos = exclusos->inserir("with", exclusos);
		exclusos = exclusos->inserir("within", exclusos);
		exclusos = exclusos->inserir("without", exclusos);
		exclusos = exclusos->inserir("all", exclusos);
		exclusos = exclusos->inserir("another", exclusos);
		exclusos = exclusos->inserir("any", exclusos);
		exclusos = exclusos->inserir("anybody", exclusos);
		exclusos = exclusos->inserir("anyone", exclusos);
		exclusos = exclusos->inserir("anything", exclusos);
		exclusos = exclusos->inserir("both", exclusos);
		exclusos = exclusos->inserir("each", exclusos);
		exclusos = exclusos->inserir("other", exclusos);
		exclusos = exclusos->inserir("either", exclusos);
		exclusos = exclusos->inserir("everybody", exclusos);
		exclusos = exclusos->inserir("everyone", exclusos);
		exclusos = exclusos->inserir("everything", exclusos);
		exclusos = exclusos->inserir("few", exclusos);
		exclusos = exclusos->inserir("he", exclusos);
		exclusos = exclusos->inserir("her", exclusos);
		exclusos = exclusos->inserir("hers", exclusos);
		exclusos = exclusos->inserir("herself", exclusos);
		exclusos = exclusos->inserir("him", exclusos);
		exclusos = exclusos->inserir("himself", exclusos);
		exclusos = exclusos->inserir("his", exclusos);
		exclusos = exclusos->inserir("I", exclusos);
		exclusos = exclusos->inserir("it", exclusos);
		exclusos = exclusos->inserir("its", exclusos);
		exclusos = exclusos->inserir("itself", exclusos);
		exclusos = exclusos->inserir("many", exclusos);
		exclusos = exclusos->inserir("me", exclusos);
		exclusos = exclusos->inserir("mine", exclusos);
		exclusos = exclusos->inserir("more", exclusos);
		exclusos = exclusos->inserir("most", exclusos);
		exclusos = exclusos->inserir("much", exclusos);
		exclusos = exclusos->inserir("myself", exclusos);
		exclusos = exclusos->inserir("neither", exclusos);
		exclusos = exclusos->inserir("no", exclusos);
		exclusos = exclusos->inserir("one", exclusos);
		exclusos = exclusos->inserir("nobody", exclusos);
		exclusos = exclusos->inserir("none", exclusos);
		exclusos = exclusos->inserir("nothing", exclusos);
		exclusos = exclusos->inserir("one", exclusos);
		exclusos = exclusos->inserir("one", exclusos);
		exclusos = exclusos->inserir("another", exclusos);
		exclusos = exclusos->inserir("other", exclusos);
		exclusos = exclusos->inserir("others", exclusos);
		exclusos = exclusos->inserir("ours", exclusos);
		exclusos = exclusos->inserir("ourselves", exclusos);
		exclusos = exclusos->inserir("several", exclusos);
		exclusos = exclusos->inserir("she", exclusos);
		exclusos = exclusos->inserir("some", exclusos);
		exclusos = exclusos->inserir("somebody", exclusos);
		exclusos = exclusos->inserir("someone", exclusos);
		exclusos = exclusos->inserir("something", exclusos);
		exclusos = exclusos->inserir("their", exclusos);
		exclusos = exclusos->inserir("theirs", exclusos);
		exclusos = exclusos->inserir("them", exclusos);
		exclusos = exclusos->inserir("themselves", exclusos);
		exclusos = exclusos->inserir("these", exclusos);
		exclusos = exclusos->inserir("they", exclusos);
		exclusos = exclusos->inserir("this", exclusos);
		exclusos = exclusos->inserir("those", exclusos);
		exclusos = exclusos->inserir("us", exclusos);
		exclusos = exclusos->inserir("we", exclusos);
		exclusos = exclusos->inserir("what", exclusos);
		exclusos = exclusos->inserir("whatever", exclusos);
		exclusos = exclusos->inserir("which", exclusos);
		exclusos = exclusos->inserir("when", exclusos);
		exclusos = exclusos->inserir("whichever", exclusos);
		exclusos = exclusos->inserir("who", exclusos);
		exclusos = exclusos->inserir("whoever", exclusos);
		exclusos = exclusos->inserir("whom", exclusos);
		exclusos = exclusos->inserir("whomever", exclusos);
		exclusos = exclusos->inserir("whose", exclusos);
		exclusos = exclusos->inserir("you", exclusos);
		exclusos = exclusos->inserir("your", exclusos);
		exclusos = exclusos->inserir("yours", exclusos);
		exclusos = exclusos->inserir("yourself", exclusos);
		exclusos = exclusos->inserir("yourselves", exclusos);
	}

	void IndexarNovoArquivo(char textoDoArquivo[], int indiceArquivoNoDat) {
		RefinarTextoArquivo(
				textoDoArquivo, indiceArquivoNoDat);
	}

	void AdicionarPalavraAoIndiceGeral(int nIndice, NoAVL<string>* arv) {

	}

	void RefinarTextoArquivo(char textoDoArquivo[], int indice) {
			char limiters[] = " ,.\n:;!?<>-+_\\/#*{}[]|()";
			string s(textoDoArquivo);
		char *textoRefinado = strtok(textoDoArquivo, limiters);
		NoBinario<string>* palavrasJaIndexadasNesteArquivo = new NoBinario<
				string>("dumb");


		for (int i = 0; textoRefinado; ++i) {
			string subst;
			subst.clear();
			subst = textoRefinado;
			transform(subst.begin(), subst.end(), subst.begin(), ::tolower);

			if (subst.length() == 1) {
				textoRefinado = strtok(NULL, limiters);
				continue;
			}

			int pos = subst.find("=");
			if (pos > -1) {
				subst = subst.substr(0, pos);
			}
			pos = subst.find("^");
			if (pos > -1) {
				textoRefinado = strtok(NULL, limiters);
				continue;
			};
			pos = subst.find("0x");
			if (pos > -1) {
				textoRefinado = strtok(NULL, limiters);
				continue;
			};

			pos = subst.find("\"");
			if (pos > -1) {
				subst = subst.substr(0, pos);
			}

			if (exclusos->contem(textoRefinado)) {
				textoRefinado = strtok(NULL, limiters);
				continue;
			};

			if (palavrasJaIndexadasNesteArquivo->contem(subst)) {
				textoRefinado = strtok(NULL, limiters);
				continue;
			}

			palavrasJaIndexadasNesteArquivo =
					palavrasJaIndexadasNesteArquivo->inserir(subst,
							palavrasJaIndexadasNesteArquivo);

			textoRefinado = strtok(NULL, limiters);

			if (indicePalavrasGerais
					&& indicePalavrasGerais->contem(textoRefinado)) {
				listaOcorrenciasPalavras->adicionaIndiceAPalavra(textoRefinado,
						indice);
				textoRefinado = strtok(NULL, limiters);
				continue;
			}

			if (!indicePalavrasGerais)
				indicePalavrasGerais = new NoAVL<string>(textoRefinado);

			//palavrasJaIndexadasNesteArquivo->adicionaEmOrdem(palavra);
			indicePalavrasGerais = indicePalavrasGerais->inserir(textoRefinado,
					indicePalavrasGerais);

			IndiceSecundarioMemoria* ind = new IndiceSecundarioMemoria;
			ind->palavra = textoRefinado;
			ind->indices[0] = indice;

			listaOcorrenciasPalavras->adicionaEmOrdem(ind);
			textoRefinado = strtok(NULL, limiters);
		}
		delete palavrasJaIndexadasNesteArquivo;
	}

	bool BuscarPalavra(const string& chave) {
		indiceSecundarioDisco* dado = pegaDadoDisco(chave);
		if (!dado) {
			cout << "Não achou a palavra em nenhum dos índices." << endl;
			return true;
		}

		cout << dado->palavra << endl;
		return false;

	}

	indiceSecundarioDisco* pegaDadoDisco(const string& chave) {
		int i = 1;
		ifstream input(INDICESSECUNDARIOS, ios::in | ios::binary);

		indiceSecundarioDisco *dado = new indiceSecundarioDisco();
		while (!input.eof()) {

			if (!input) {
				cout << "Erro ao ler arquivo da árvore.";
				return NULL;
			}

			dado = new indiceSecundarioDisco();

			input.seekg(streampos(i * sizeof(indiceSecundarioDisco)));
			input.read((char *) dado, sizeof(indiceSecundarioDisco));
			cout << "Incide atual" << endl;
			cout << dado->palavra << endl;
			if (dado->palavra == chave) {
				input.close();
				return dado;
			}

			delete dado;
			i++;
		}
		input.close();
		return NULL;
	}
}
;

#endif /* INDICESECUNDARIO_HPP_ */

