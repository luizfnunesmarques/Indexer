#ifndef PAGINADISCO_HPP_
#define PAGINADISCO_HPP_
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
using namespace std;
struct NoDisco{
public:
	NoDisco(){
		key.clear();
		indiceNoDat =-1;
		indiceEsquerda=-1;
		indiceDireita=-1;
	}
	std::string key;
	int indiceNoDat;
	int indiceEsquerda;
	int indiceDireita;

	bool operator==(const NoDisco& lhs) {
			return key.compare(lhs.key) == 0;
		}

		/*bool operator==(const string& chave) {
		 return this->key == chave;
		 }*/

		bool operator<(const NoDisco& lhs) const {
			return key.compare(lhs.key) < 0;
		}

		bool operator<=(const NoDisco& lhs) const {
			return (key.compare(lhs.key) < 1);
		}

		bool operator>(const NoDisco& lhs) {
			return key.compare(lhs.key) > 0;
		}
};

struct PaginaDisco {
public:
	PaginaDisco() {
		int indiceDiscoDat;
		IndiceFilhoDireita = -1;
		IndiceFilhoEsquerda = -1;
		key.clear();
	}
	;

	bool operator==(const PaginaDisco& lhs) {
		return key.compare(lhs.key) == 0;
	}

	/*bool operator==(const string& chave) {
	 return this->key == chave;
	 }*/

	bool operator<(const PaginaDisco& lhs) const {
		return key.compare(lhs.key) < 0;
	}

	bool operator<=(const PaginaDisco& lhs) const {
		return (key.compare(lhs.key) < 1);
	}

	friend bool operator<=(string &cC1, string &cC2) {
		return cC1 < cC2;
	}

	bool operator>(const PaginaDisco& lhs) {
		return key.compare(lhs.key) > 0;
	}

	int getIndiceEsquerda(){
		return IndiceFilhoEsquerda;
	}
	std::string key;
	char value[140000];
	int Indice;
	int IndiceFilhoDireita;
	int IndiceFilhoEsquerda;
};

#endif /* PAGINADISCO_HPP_ */
