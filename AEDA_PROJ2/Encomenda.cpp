#include "Encomenda.h"

using namespace std;

unsigned long Encomenda::codigo_sequencial = 0;

Encomenda::Encomenda(){
	fornecedor = "";
	prod = 0;
	quant = 0;
	quant_stock = 0;
	codigo = codigo_sequencial;
	codigo_sequencial++;
}

Encomenda::Encomenda(std::string fornecedor, unsigned long prod, unsigned quant, unsigned quant_stock){
	this->fornecedor = fornecedor;
	this->prod = prod;
	this->quant = quant;
	this->quant_stock = quant_stock;
	codigo = codigo_sequencial;
	codigo_sequencial++;
}

std::string Encomenda::getFornecedor() const{
	return fornecedor;
}

unsigned long Encomenda::getCodigo() const{
	return codigo;
}

unsigned long Encomenda::getProd() const{
	return prod;
}

unsigned Encomenda::getQuant() const{
	return quant;
}

void Encomenda::setFornecedor(std::string f){
	fornecedor = f;
}

void Encomenda::setProd(unsigned long p){
	prod = p;
}

void Encomenda::setQuant(unsigned q){
	quant = q;
}

void Encomenda::setCodigo(unsigned long c){
	codigo = c;
	codigo_sequencial = c++;
}

bool Encomenda::operator< (const Encomenda &e) const{
	if(quant_stock > e.getQuant())
		return true;
	return false;
}

ostream& operator<<(ostream &output, const Encomenda &e1){
	output << e1.codigo << endl;
	output << e1.fornecedor << endl;
	output << e1.prod << endl << e1.quant_stock << endl << e1.quant << endl;

	return output;
}


