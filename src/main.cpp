//============================================================================
// Name        : ManPages.cpp
// Author      : Luizf
// Version     :
// Copyright   : 2015 GNU
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include <dirent.h>

#include "Lista.hpp"
#include "NoAvl.hpp"
#include "NoBinario.hpp"
#include "ManPages.hpp"
#include "IndiceSecundario.hpp"
#include "AdicionaNomeManPages.hpp"
#include "ListaEnc.hpp";
#include "AvlPaginaDisco.hpp"
#include "ManPages.hpp"

int EntradaUsuario() {
	cout << "0: Fechar a aplica��o" << endl;
	cout << "1: Pesquisa por chave prim�ria" << endl;
	int opcao = 0;

	string entrada = "";

	while (true) {
		getline(cin, entrada);
		stringstream myStream(entrada);

		if (myStream >> opcao)
			break;
	}

	return opcao;
}

string getEntradaTexto() {
	string entrada = "";
	getline(cin, entrada);
	return entrada;
}

void Primaria(ManPages* manpage) {
	while (true) {
		cout << "Digite o nome da manPage desejada," << endl;
		cout << "ou vazio para voltar ao menu." << endl;
		string comando = getEntradaTexto();
		if (comando == "")
			return;
		manpage->BuscaArquivo(comando);
	}

}

void Secundario(ManPages* manpage) {
	while (true) {
		cout << "Digite o nome da Palavra desejada," << endl;
		cout << "ou vazio para voltar ao menu." << endl;
		string comando = getEntradaTexto();
		if (comando == "")
			return;
		manpage->BuscarPalavraIndiceSecundario(comando);
		cout <<"Fim busca" << endl;
	}

}

int main() {
	cout << "Inicializando a aplica��o." << endl;
	cout
			<< "Aten��o! Os ind�ces prim�rios previamente definidos ser�o exclu�dos"
			<< endl;
	cout << "--------------------------------------------------" << endl
			<< endl;

	ManPages *manpg = new ManPages();
	manpg->GerarArquivosEIndices();

	cout << "Ind�ces gerados. Escolha uma op��o:" << endl;

	switch (EntradaUsuario()) {
	case 0:
		cout << "Fechando a aplica��o." << endl;
		exit(0);
		return 0;
	case 1:
		Primaria(manpg);
		break;
	case 2:
		Secundario(manpg);
		break;
	default:
		cout << "Op��o inv�lida" << endl << endl;
	}
	return 0;
}

