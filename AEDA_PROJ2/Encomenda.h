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
	/*
	 * Construtor da classe Encomenda
	 */
	Encomenda();

	/*
	 * Construtor da classe Encomenda
	 * @param fornecedor Nome do fornecedor
	 * @param prod Codigo do produto encomendado
	 * @param quant Numero de unidades de produto encomendadas
	 */
	Encomenda(std::string fornecedor, unsigned long prod, unsigned quant);

	/*
	 * Metodo que permite obter o nome do fornecedor
	 * @return Nome do fornecedor
	 */
	std::string getFornecedor() const;

	/*
	 * Metodo que permite obter o codigo da encomenda
	 * @return Codigo da encomenda
	 */
	unsigned long getCodigo() const;

	/*
	 * Metodo que permite obter o codigo do produto encomendado
	 * @return Codigo do produto
	 */
	unsigned long getProd() const;

	/*
	 * Metodo que permite obter a quantidade de produto encomendado
	 * @return Quantidade de produto
	 */
	unsigned getQuant() const;

	/*
	 * Metodo que permite alterar o fornecedor
	 * @param f Nome do fornecedor
	 */
	void setFornecedor(std::string f);

	/*
	 * Metodo que permite alterar o codigo do produto encomendado
	 * @param p Codigo do produto
	 */
	void setProd(unsigned long p);

	/*
	 * Metodo que permite alterar a quantidade de produto encomendado
	 * @param q Quantidade de produto
	 */
	void setQuant(unsigned q);

	/*
	 * Metodo que permite alterar o codigo da encomenda
	 * @param c Codigo da encomenda
	 */
	void setCodigo(unsigned long c);
};

#endif
