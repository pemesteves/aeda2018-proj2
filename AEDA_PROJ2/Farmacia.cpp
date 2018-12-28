#include "Farmacia.h"
#include <iostream>

using namespace std;

template <> enum tipoSort sorting<Venda>::tipo = DEFAULT;
template <> bool sorting<Venda>::crescente = false;

Farmacia::Farmacia(string nome, string morada) {
	this->nome = nome;
	this->morada = morada;
	this->gerente = NULL;
	this->diretorTecnico = NULL;
}

string Farmacia::getNome() const {
	return nome;
}

string Farmacia::getMorada() const {
	return morada;
}

Funcionario* Farmacia::getGerente() const {
	return gerente;
}

Funcionario* Farmacia::getDiretorTecnico() const {
	return diretorTecnico;
}

vector<Venda*> Farmacia::getVendas() const {
	return vendas;
}

vector<ProdutoStock> Farmacia::getStock() const {

	vector<ProdutoStock> v;
	ProdutoStock tmp;

	priority_queue<ProdutoStock> st_tmp = stock;

	while (!st_tmp.empty()) {
		tmp = st_tmp.top();
		v.push_back(tmp);
		st_tmp.pop();
	}

	return v;

}

unsigned int Farmacia::getNumProdutos() const {
	return stock.size();
}

unsigned int Farmacia::getNumVendas() const {
	return vendas.size();
}

unsigned int Farmacia::getNumVendasTempo(Data d1, Data d2) const {
	unsigned int vendas_count = 0;
	for (size_t i = 0; i < vendas.size(); i++) {
		Data d = vendas.at(i)->getData();
		if ((d < d2 && d1 < d) || d1 == d || d2 == d) {
			vendas_count++;
		}
	}

	return vendas_count;
}

vector<Venda*> Farmacia::getVendasTempo(Data d1, Data d2) const {
	vector<Venda*> vendas_tempo;
	for (size_t i = 0; i < vendas.size(); i++) {
		Data d = vendas.at(i)->getData();
		if ((d < d2 && d1 < d) || d1 == d || d2 == d) {
			vendas_tempo.push_back(vendas.at(i));
		}
	}
	return vendas_tempo;
}

unsigned int Farmacia::getNumVendasDia(Data d) const {
	unsigned int vendas_count = 0;
	for (size_t i = 0; i < vendas.size(); i++) {
		Data d1 = vendas.at(i)->getData();
		if (d == d1)
			vendas_count++;
	}
	return vendas_count;
}

vector <Venda*> Farmacia::getVendasDia(Data d) const {
	vector<Venda*> vendas_dia;
	for (size_t i = 0; i < vendas.size(); i++) {
		Data d1 = vendas.at(i)->getData();
		if (d1 == d) {
			vendas_dia.push_back(vendas.at(i));
		}
	}
	return vendas_dia;
}

float Farmacia::getPrecoProduto(string nomeProd) const {
	vector<ProdutoStock>::const_iterator it;
	vector<ProdutoStock> v = getStock();
	for (it = v.begin(); it != v.end(); it++) {
		if (it->getProd()->getNome() == nomeProd)
			return it->getProd()->getPreco();
	}
	return -1;
}

int Farmacia::getQuantProduto(std::string nomeProd) const {
	vector<ProdutoStock>::const_iterator it;
	vector<ProdutoStock> v = getStock();
	for (it = v.begin(); it != v.end(); it++) {
		if (it->getProd()->getNome() == nomeProd)
			return it->getQuant();
	}
	return -1;
}

void Farmacia::setGerente(Funcionario* gerente) {
	this->gerente = gerente;
	if (gerente != NULL)
		gerente->setCargo("GERENTE");
}

void Farmacia::setDiretorTecnico(Funcionario* diretor) {
	this->diretorTecnico = diretor;
	if (diretor != NULL)
		diretor->setCargo("DIRETOR TECNICO");
}

void Farmacia::addProdutosVender(vector<Produto*> produtosVender_new) {
	Produto* p = NULL;
	for (size_t i = 0; i < produtosVender_new.size(); i++) {
		p = produtosVender_new.at(i);
		if (!existeProduto(p->getNome())) {
			ProdutoStock tmp(p, 0);
			stock.push(tmp);
		}
	}
}

Produto* Farmacia::removeProduto(std::string nomeP) {

	ProdutoStock tmp;

	Produto* p = NULL;

	priority_queue<ProdutoStock> st_tmp;

	while (!stock.empty()) {
		tmp = stock.top();
		if (tmp.getProd()->getNome() != nomeP)
			st_tmp.push(tmp);
		else
			p = tmp.getProd();
		st_tmp.pop();
	}

	stock = st_tmp;

	if (p == NULL)
		throw ProdutoInexistente(nomeP);

	return p;
}

bool Farmacia::addVenda(Venda* venda) {
	std::map<Produto, std::vector<float>> prodVenda;
	prodVenda = venda->getProdutosVendidos();
	map<Produto, vector<float>>::const_iterator it = prodVenda.begin();
	string nomeProd;
	int quant;
	for (; it != prodVenda.end(); it++) {
		nomeProd = it->first.getNome();
		quant = static_cast<int>(it->second.at(QUANTIDADE));
		if (!existeProdutoQuant(nomeProd, quant)) {
			return false;
		}
	}
	vendas.push_back(venda);
	for (; it != prodVenda.end(); it++) {
		nomeProd = it->first.getNome();
		quant = getQuantProduto(nomeProd) - static_cast<int>(it->second.at(QUANTIDADE));
		setQuantidade(nomeProd, quant);
	}
	Cliente *c = venda->getCliente();
	if (c != NULL)
		c->addCompra(venda);

	return true;
}

bool Farmacia::existeProduto(string nomeProduto) const {
	vector<ProdutoStock> v = getStock();
	vector<ProdutoStock>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (it->getProd()->getNome() == toupperstring(nomeProduto))
			return true;
	}
	return false;
}

bool Farmacia::existeProdutoQuant(string nomeProduto, int quant) const {
	unsigned uquant = (unsigned)quant;
	vector<ProdutoStock> v = getStock();
	vector<ProdutoStock>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (it->getProd()->getNome() == toupperstring(nomeProduto)) {
			if (it->getQuant() >= uquant)
				return true;
			else return false;
		}
	}
	return false;
}

bool Farmacia::addProdutoVender(Produto* produtoVender) {
	ProdutoStock p(produtoVender, 0);
	if (!existeProduto(produtoVender->getNome())) {
		stock.push(p);
		return true;
	}
	return false;
}

void Farmacia::sortVendas(enum tipoSort tipo, bool crescente) {
	sorting<Venda> s;
	sorting<Venda>::tipo = tipo;
	sorting<Venda>::crescente = crescente;
	s.sort_p(vendas);
}

bool Farmacia::setQuantidade(std::string nomeProd, int quant) {
	vector<ProdutoStock> v = getStock();
	vector<ProdutoStock>::iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (nomeProd == it->getProd()->getNome()) {
			it->setQuant(quant);
			return true;
		}
	}
	return false;
}

bool Farmacia::operator< (const Farmacia &f1) const {
	if (nome < f1.getNome())
		return true;
	if (nome == f1.getNome() && stock.size() > f1.getNumProdutos())
		return true;
	if (nome == f1.getNome() && stock.size() == f1.getNumProdutos() && vendas.size() < f1.getNumVendas())
		return true;
	return false;
}

void Farmacia::imprimeFatura(Venda* v) const {
	cout << "Farmacia " << nome << endl;
	cout << morada << endl;
	if (gerente != NULL)
		cout << endl << "Gerente: " << gerente->getNome() << endl;
	if (gerente != NULL)
		cout << "Diretor Tecnico: " << diretorTecnico->getNome() << endl;
	v->imprimeFatura();

	cout << "Obrigado pela sua visita! Volte sempre." << endl << endl;
}

void Farmacia::imprimeDados() const {
	cout << "Nome da farmacia: " << nome << endl;
	cout << "Morada: " << morada << endl;
	if (gerente != NULL)
		cout << "Gerente: " << gerente->getNome() << "  " << gerente->getNoContribuinte() << endl;
	if (diretorTecnico != NULL)
		cout << "Diretor Tecnico: " << diretorTecnico->getNome() << "  " << diretorTecnico->getNoContribuinte() << endl;
}

bool Farmacia::menorQue(const Farmacia &f1, enum tipoSort tipo, bool crescente) const {
	switch (tipo) {
	case NOME:
		if (crescente)
			return nome < f1.getNome();
		else
			return nome > f1.getNome();
		break;
	case NUM_PROD:
		if (crescente)
			return stock.size() < f1.getNumProdutos();
		else
			return stock.size() > f1.getNumProdutos();
		break;
	case NUM_VENDA:
		if (crescente)
			return vendas.size() < f1.getNumVendas();
		else
			return vendas.size() > f1.getNumVendas();
		break;
	default:
		return (*this) < f1;
		break;
	}
}

ostream& operator<<(ostream &output, const Farmacia &f) {
	output << f.nome << endl;
	output << f.morada << endl;
	if (f.gerente != NULL) {
		output << f.gerente->getNoContribuinte() << endl;
	}
	else
		output << "NULL" << endl;

	if (f.diretorTecnico != NULL)
		output << f.diretorTecnico->getNoContribuinte() << endl;
	else
		output << "NULL" << endl;

	output << f.stock.size() << endl;
	vector<ProdutoStock> v = f.getStock();
	vector<ProdutoStock>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		output << it->getQuant() << endl;
		output << *(it->getProd()) << endl;
	}

	vector<Encomenda> enc = f.getEncomendas();
	output << enc.size() << endl;
	for(vector<Encomenda>::iterator it1 = enc.begin(); it1 != enc.end(); it1++){
		output << (*it1) << endl;
	}

	output << f.vendas.size() << endl;
	for (size_t i = 0; i < f.vendas.size(); i++) {
		output << (*f.vendas[i]) << endl;
	}


	return output;
}

Produto Farmacia::getProduto(unsigned long codigo) {
	vector<ProdutoStock> v = getStock();
	vector<ProdutoStock>::const_iterator it = v.begin();
	for (; it != v.end(); it++) {
		if (it->getProd()->getCodigo() == codigo) {
			return *(it->getProd());
		}
	}
	return Produto(0, "", 0, "", 0, 0, 0);
}

Venda* Farmacia::getVenda(unsigned long codigo) const {
	for (vector<Venda*>::const_iterator it = vendas.begin(); it != vendas.end(); it++) {
		if ((*it)->getCodigo() == codigo)
			return (*it);
	}

	return NULL;
}

void Farmacia::setVendas(vector<Venda*> v) {
	this->vendas = v;
}

vector<ProdutoStock> Farmacia::getProdsMenorQuant(unsigned N) {
	vector<ProdutoStock> stocktmp = getStock();
	vector<ProdutoStock> v;

	for (size_t i = 0; i < stocktmp.size(); i++) {
		if (stocktmp.at(i).getQuant() < N)
			v.push_back(stocktmp.at(i));
	}

	return v;
}

void Farmacia::criaEncomenda(string fornecedor, unsigned N, unsigned quantidade_encomenda){
	vector<ProdutoStock> v = getProdsMenorQuant(N);
	for(vector<ProdutoStock>::iterator it = v.begin(); it != v.end(); it++){
		Encomenda e(fornecedor, (*it).getProd()->getCodigo(), quantidade_encomenda, (*it).getQuant());
		encomendas.push(e);
	}
}

void Farmacia::entregaEncomendas(unsigned num_encomendas = 1){
	priority_queue<ProdutoStock> s;

	while(num_encomendas > 0){
		Encomenda e = encomendas.top();
		encomendas.pop();

		ProdutoStock p = stock.top();
		p.setQuant(p.getQuant() + e.getQuant());
		s.push(p);
		stock.pop();

		num_encomendas--;
	}

	while(!stock.empty()){
		s.push(stock.top());
		stock.pop();
	}

	stock = s;
}

vector<Encomenda> Farmacia::getEncomendas() const{
	vector<Encomenda> v;
	Encomenda tmp;

	priority_queue<Encomenda> enc_tmp = encomendas;

	while (!enc_tmp.empty()) {
		tmp = enc_tmp.top();
		v.push_back(tmp);
		enc_tmp.pop();
	}

	return v;
}

void Farmacia::addEncomenda(const Encomenda &e){
	encomendas.push(e);
}


