/*
 * AdicionaNomeManPages.hpp
 *
 *  Created on: 28/06/2015
 *      Author: LuizF
 */

#ifndef ADICIONANOMEMANPAGES_HPP_
#define ADICIONANOMEMANPAGES_HPP_

#include "ListaEnc.hpp"
using namespace std;

class AdicionaNomeManPages {
public:
	AdicionaNomeManPages() {
	}
	;

	ListaEnc<string> *PegarListaNomeArquivos() {
		ListaEnc<string>* lista = new ListaEnc<string>;
		std::string nome;
		nome.clear();
		ifstream myfile("E:\\ManPages\\nomes\\nomesManPages.txt");
		if (myfile.is_open()) {
			while (!myfile.eof()) {
				getline(myfile, nome);
				lista->adiciona(nome);
			}
			myfile.close();
		}

		return lista;
	}

};

#endif /* ADICIONANOMEMANPAGES_HPP_ */

