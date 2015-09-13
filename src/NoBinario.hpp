#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>

using namespace std;

template<typename T>
class NoBinario {
protected:
	T* dado;

	NoBinario<T>* esquerda;
	NoBinario<T>* direita;
	std::vector<NoBinario<T>*> elementos;

public:
	NoBinario<T>(const T& dado) {
		this->dado = new T(dado);
		esquerda = NULL;
		direita = NULL;
	}

	virtual ~NoBinario<T>() {
		if (esquerda)
			delete esquerda;

		if (direita)
			delete direita;

		delete dado;
	}
	T* getDado() {
		return dado;
	}
	std::vector<NoBinario<T>*> getElementos() {
		return elementos;
	}

	NoBinario<T>* getEsquerda() {
		return esquerda;
	}
	NoBinario<T>* getDireita() {
		return direita;
	}
	T* busca(const T& dado, NoBinario<T>* arv) {
		while (*arv->getDado() != dado) {
			arv = *arv->dado > dado ? arv->esquerda : arv->direita;
			if (!arv)
				throw -999;
		}
		return arv->getDado();
	}
	NoBinario<T>* inserir(const T& dado, NoBinario<T>* arv) {
		if (arv->dado == NULL) {
			arv->dado = new T(dado);
			return arv;
		}

		bool bMenor = (dado < *arv->dado);
		NoBinario<T>* filho = bMenor ? arv->esquerda : arv->direita;

		if (filho) {
			filho->inserir(dado, filho);
		} else {
			filho = new NoBinario<T>(dado);
			bMenor ? arv->esquerda = filho : arv->direita = filho;
		}
		return arv;
	}
	NoBinario<T>* remover(NoBinario<T>* arv, const T& dado) {
		if (!arv)
			throw -999;
		if (dado != *arv->dado) {
			dado < *arv->dado ?
					arv->esquerda = remover(arv->esquerda, dado) :
					arv->direita = remover(arv->direita, dado);
			return arv;
		}
		if ((!arv->esquerda) && (!arv->direita)) {
			delete arv;
			return NULL;
		}
		if (arv->esquerda && arv->direita) {
			NoBinario<T>* temp = minimo(arv->direita);
			arv->dado = temp->dado;
			arv->direita = remover(arv->direita, dado);
			return arv;
		} else {
			return arv->esquerda == NULL ? arv->direita : arv->esquerda;
		}
	}
	NoBinario<T>* minimo(NoBinario<T>* nodo) {
		if (nodo == NULL)
			return NULL;

		NoBinario<T>* walk = nodo;

		while (walk->esquerda)
			walk = walk->esquerda;

		return walk;
	}
	void preOrdem(NoBinario<T>* nodo) {
		if (!nodo)
			return;

		elementos.push_back(nodo);
		preOrdem(nodo->esquerda);
		preOrdem(nodo->direita);

	}
	void emOrdem(NoBinario<T>* nodo) {
		if (!nodo)
			return;
		emOrdem(nodo->esquerda);
		elementos.push_back(nodo);
		emOrdem(nodo->direita);
	}
	void posOrdem(NoBinario<T>* nodo) {
		if (!nodo)
			return;
		posOrdem(nodo->esquerda);
		posOrdem(nodo->direita);
		elementos.push_back(nodo);
	}

	void DeletarArvoresFilhas() {
		posOrdem(this);
		elementos.clear();
	}
	;

	bool contem(const T& dado) {
		try {
			busca(dado, this);
		} catch (int e) {
			return false;
		}
		return true;
	}

};
#endif /* NO_BINARIO_HPP */
