#ifndef ENCOMENDA_H
#define ENCOMENDA_H

#include "Produto.h"
#include <string>

class Encomenda{
	std::string fornecedor;
	unsigned long codigo;
	unsigned long prod;
	static unsigned long codigo_sequencial;
	unsigned quant;

public:
	Encomenda();
	Encomenda(std::string fornecedor, unsigned long prod, unsigned quant);
	std::string getFornecedor();
	unsigned long getCodigo();
	unsigned long getProd();
	unsigned getQuant();
	void setFornecedor(std::string f);
	void setProd(unsigned long p);
	void setQuant(unsigned q);
	void setCodigo(unsigned long c);
};

#endif
