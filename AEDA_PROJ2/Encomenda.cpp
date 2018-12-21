#include "Encomenda.h"

using namespace std;

unsigned long Encomenda::codigo_sequencial = 0;

Encomenda::Encomenda(){
	fornecedor = "";
	prod = 0;
	quant = 0;
	codigo = codigo_sequencial;
	codigo_sequencial++;
}

Encomenda::Encomenda(std::string fornecedor, unsigned long prod, unsigned quant){
	this->fornecedor = fornecedor;
	this->prod = prod;
	this->quant = quant;
	codigo = codigo_sequencial;
	codigo_sequencial++;
}

std::string Encomenda::getFornecedor(){
	return fornecedor;
}

unsigned long Encomenda::getCodigo(){
	return codigo;
}

unsigned long Encomenda::getProd(){
	return prod;
}

unsigned Encomenda::getQuant(){
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



