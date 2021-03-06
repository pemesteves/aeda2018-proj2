#include "CadeiaFarmacias.h"

#include <stddef.h>
#include <iterator>
#include <string>

#include "Pessoa.h"
#include "Produto.h"
#include "Receita.h"
#include "util.h"
#include "Venda.h"

using namespace std;

template <> enum tipoSort sorting<Farmacia>::tipo = DEFAULT;
template <> bool sorting<Farmacia>::crescente = false;

CadeiaFarmacias::CadeiaFarmacias() {
	this->nome = ""; //Inicializacao de um nome vazio
	farmacias.resize(0); //Vetor de farmacias vazio
	clientes.clear(); //Set de clientes vazio
	registo_funcionarios.clear(); //Tabela de dispersao vazia
}

CadeiaFarmacias::CadeiaFarmacias(string nome) {
	this->nome = nome; //Inicializacao de uma cadeia com nome
	farmacias.resize(0); //Vetor de farmacias vazio
	clientes.clear(); //Set de clientes vazio
	registo_funcionarios.clear(); //Tabela de dispersao vazia
}

void CadeiaFarmacias::setNome(string nome) {
	this->nome = nome;
}

string CadeiaFarmacias::getNome() const {
	return nome;
}

unsigned int CadeiaFarmacias::getNumFarmacias() const {
	return farmacias.size();
}

unsigned int CadeiaFarmacias::getNumClientes() const {
	return clientes.size();
}

unsigned int CadeiaFarmacias::getNumFuncionarios() const {
	return registo_funcionarios.size();
}

vector<Farmacia *> CadeiaFarmacias::getFarmacias() const {
	return farmacias;
}

vector <Cliente*>  CadeiaFarmacias::getClientes() const {
	vector<Cliente*> v;

	for (set<Cliente*, clientesComp>::iterator it = clientes.begin(); it != clientes.end(); it++) {
		v.push_back(*it);
	}

	return v;
}

vector <FuncPtr> CadeiaFarmacias::getFuncionarios() const {
	vector<FuncPtr> f;

	tabHFunc::const_iterator it = registo_funcionarios.begin();

	for(; it!=registo_funcionarios.end(); it++){
		f.push_back(*it);
	}

	return f;
}

void CadeiaFarmacias::addFarmacia(Farmacia* farmacia) {
	farmacias.push_back(farmacia);
}

Farmacia* CadeiaFarmacias::removeFarmacia(const string &nomeF) {
	vector<Farmacia*>::iterator it = farmacias.begin();
	for (; it != farmacias.end(); it++) { //Percorrer o vetor farmacias
		if ((*it)->getNome() == nomeF) {
			farmacias.erase(it); //Eliminar o elemento pretendido
			tabHFunc::iterator itFunc = registo_funcionarios.begin();
			for (; itFunc != registo_funcionarios.end(); itFunc++) { //Percorrer o vetor funcionarios
				Farmacia* f = itFunc->func->getFarmacia();
				if (nomeF == f->getNome()) //Se a Farmacia a eliminar e igual a Farmacia onde trabalha o Funcionario, esta e apagada
					itFunc->func->setFarmacia(NULL);
			}
			return *it;
		}
	}
	throw FarmaciaInexistente(nomeF); //Lancamento de uma excecao caso a Farmacia nao exista
}

void CadeiaFarmacias::sortFarmacias(enum tipoSort tipo, bool crescente) {
	sorting<Farmacia> s;
	sorting<Farmacia>::tipo = tipo;
	sorting<Farmacia>::crescente = crescente;
	s.sort_p(farmacias);
}

void CadeiaFarmacias::addCliente(Cliente* cliente) {
	clientes.insert(cliente);
}

Cliente* CadeiaFarmacias::removeCliente(const string &nomeC) {
	set<Cliente*, clientesComp>::iterator it = clientes.begin();
	for (; it != clientes.end(); it++) {
		if ((*it)->getNome() == nomeC) {
			Cliente* c1;
			c1 = *it;
			clientes.erase(it);
			return c1;
		}
	}
	throw ClienteInexistente(nomeC); //Lan�amento de uma excecao caso o cliente nao exista
}

bool CadeiaFarmacias::addFuncionario(Funcionario* funcionario, bool atual_funcionario=true) {
	FuncPtr f;
	f.func = funcionario;
	f.atual_funcionario = atual_funcionario;
	tabHFunc::iterator it = registo_funcionarios.begin();
	for (; it != registo_funcionarios.end(); it++) {//Percorrer o vetor de funcionarios
		if (it->func->getNoContribuinte() == funcionario->getNoContribuinte()) {
			return false;

		}
	}
	registo_funcionarios.insert(f);
	return true;
}

vector<Funcionario*> CadeiaFarmacias::getFuncionariosAntigos() const{
	tabHFunc::const_iterator it = registo_funcionarios.begin();
	vector<Funcionario*> v;
	for (; it != registo_funcionarios.end(); it++) {
		if(!it->atual_funcionario){
			v.push_back(it->func);
		}
	}
	return v;
}

vector<Funcionario*> CadeiaFarmacias::getFuncionariosAtuais() const{
	tabHFunc::const_iterator it = registo_funcionarios.begin();
	vector<Funcionario*> v;
	for (; it != registo_funcionarios.end(); it++) {
		if(it->atual_funcionario){
			v.push_back(it->func);
		}
	}
	return v;
}

void CadeiaFarmacias::mostrarFuncionariosAntigos() const{
	vector<Funcionario*> v = getFuncionariosAntigos();
	for(size_t i=0; i<v.size(); i++){
		cout << "Nome: " << v.at(i)->getNome() << endl;
		cout << "Contribuinte: " << v.at(i)->getNoContribuinte() << endl;
		cout << "Ultimo cargo exercido: " << v.at(i)->getCargo() << endl;
		cout << "Ultimo salario: " << v.at(i)->getSalario() << endl;

	}
}


Funcionario* CadeiaFarmacias::despedeFuncionario(const unsigned long contF) {
	tabHFunc::iterator it = registo_funcionarios.begin();
	Funcionario* f1;
	bool encontrou_funcionario = false;
	for (; it != registo_funcionarios.end(); it++) {//Percorrer o registo de funcionarios
		if (it->func->getNoContribuinte() == contF) {
			f1 = it->func;
			it->func->setFarmacia(NULL);
			it->atual_funcionario = false;
			encontrou_funcionario = true;
			break;
		}
	}

	if (!encontrou_funcionario)
		throw FuncionarioInexistente(contF); //Lancamento de uma excecao caso o funcionario nao exista

	//vector<Farmacia*>::iterator itf = farmacias.begin();

	/*for(; itf != farmacias.end(); itf++){
		if((*itf)->getDiretorTecnico() != NULL)
			if((*itf)->getDiretorTecnico()->getNoContribuinte() == contF){
				(*itf)->setDiretorTecnico(NULL);
				break;
			}
		if((*itf)->getGerente() != NULL){
			cout << "olaaaa" << endl;
			if((*itf)->getGerente()->getNoContribuinte() == contF){
				cout << "olaaaa" << endl;
				(*itf)->setGerente(NULL);
				cout << "olaaaa" << endl;
				break;
			}
		}

	}*/

	return f1;
}

int CadeiaFarmacias::contratarFuncAntigo(unsigned long contF){
	tabHFunc::iterator it = registo_funcionarios.begin();
	for(; it!=registo_funcionarios.end(); it++){
		if(it->func->getNoContribuinte() == contF){
			if(it->atual_funcionario)
				return 1;
			it->atual_funcionario = true;
			return 0;
		}
	}

	return 2;
}

ostream& operator<<(ostream &output, const CadeiaFarmacias &cF) {
	output << cF.farmacias.size() << endl;
	for (size_t i = 0; i < cF.farmacias.size(); i++) {
		output << (*cF.farmacias[i]) << endl;
	}

	output << cF.clientes.size() << endl;
	for (set<Cliente*, clientesComp>::iterator it = cF.clientes.begin(); it != cF.clientes.end(); it++) {//size_t i = 0; i < cF.clientes.size(); i++) {
		output << *(*it) << endl; // *cF.clientes[i]) << endl;
	} //TODO Nao sei se funciona: vamos ter que testar isto

	output << cF.registo_funcionarios.size() << endl;
	vector<FuncPtr> f = cF.getFuncionarios();
	vector<FuncPtr>::iterator it = f.begin();
	for (; it != f.end(); it++) {
		output << *(it->func) << endl;
		output << it->atual_funcionario << endl;
	}
	/*
	for (size_t i = 0; i < cF.funcionarios.size(); i++) {
		output << (*cF.funcionarios[i]) << endl;
	}*/

	return output;
}

void import(ifstream &f, CadeiaFarmacias &cF) { //Falta corrigir o import
	string line;
	do {
		getline(f, line);
	} while (line.length() == 0);

	size_t numVars = stoi(line);
	vector<unsigned long> gerentes;
	vector<unsigned long> diretoresTecnicos;
	vector<unsigned long> clientesReceitas;
	vector<unsigned long> clientes;

	string nome, morada;
	unsigned long contribuinte;
	while (numVars > 0) {
		do {
			getline(f, nome);
		} while (nome.length() == 0);

		do {
			getline(f, morada);
		} while (morada.length() == 0);

		Farmacia *farm = new Farmacia(nome, morada);
		do {
			getline(f, nome);
		} while (nome.length() == 0);

		if (nome == "NULL") {
			gerentes.push_back(0);
			farm->setGerente(NULL);
		}
		else {
			contribuinte = stoul(nome);
			gerentes.push_back(contribuinte);
		}

		do {
			getline(f, nome);
		} while (nome.length() == 0);

		if (nome == "NULL") {
			diretoresTecnicos.push_back(0);
			farm->setDiretorTecnico(NULL);
		}
		else {
			contribuinte = stoul(nome);
			diretoresTecnicos.push_back(contribuinte);
		}

		do {
			getline(f, line);
		} while (line.length() == 0);
		size_t numProd = stoi(line);

		unsigned long codigo;
		float desconto, preco;
		bool pasReceita, vendaSemReceita;
		int quantidade;
		while (numProd > 0) {
			do {
				getline(f, line);
			} while (line.length() == 0);

			quantidade = stoi(line); //quantidade do produto: segundo campo do map
			do {
				getline(f, line);
			} while (line.length() == 0);

			codigo = stoul(line);
			do {
				getline(f, nome);
			} while (nome.length() == 0);

			do {
				getline(f, line);
			} while (line.length() == 0);

			preco = stof(line);
			do {
				getline(f, morada); //morada tera a descricao
			} while (morada.length() == 0);

			do {
				getline(f, line);
			} while (line.length() == 0);

			pasReceita = (bool)stoi(line);

			do {
				getline(f, line);
			} while (line.length() == 0);

			vendaSemReceita = (bool)stoi(line);

			do {
				getline(f, line);
			} while (line.length() == 0);

			desconto = stof(line);

			Produto *p = new Produto(codigo, nome, preco, morada, pasReceita, desconto, vendaSemReceita);
			farm->addProdutoVender(p);
			farm->setQuantidade(nome, quantidade);
			numProd--;
		}

		do{
			getline(f, line);
		} while(line.length() == 0);

		numProd = stoi(line); //numProd tera o numero de encomendas

		while(numProd > 0){
			unsigned long codigo_encomenda, codigo_produto;
			unsigned quantidade_stock, quantidade_encomenda;
			string fornecedor;

			do{
				getline(f, line);
			}while(line.length() == 0);

			codigo_encomenda = stoul(line);

			do{
				getline(f, fornecedor);
			}while(fornecedor.length() == 0);

			do{
				getline(f, line);
			} while(line.length() == 0);

			codigo_produto = stoul(line);

			do{
				getline(f, line);
			} while(line.length() == 0);

			quantidade_stock = stoi(line);

			do{
				getline(f, line);
			} while(line.length() == 0);

			quantidade_encomenda = stoi(line);

			Encomenda e(fornecedor, codigo_produto, quantidade_encomenda, quantidade_stock);
			e.setCodigo(codigo_encomenda);
			farm->addEncomenda(e);
			numProd--;
		}

		do {
			getline(f, line);
		} while (line.length() == 0);

		numProd = stoi(line); //numProd tera o numero de vendas

		int dia, mes, ano, hora, minutos, segundos;
		while (numProd > 0) {
			do {
				getline(f, line); //line tera: codigo data hora
			} while (line.length() == 0);

			codigo = stoul(line.substr(0, line.find(" ")));
			line = line.substr(line.find(" ") + 1); //line tera: hora data
			dia = stoi(line.substr(0, line.find("/")));
			line = line.substr(line.find("/") + 1); //line tera: mes/ano hora:minutos:segundos
			mes = stoi(line.substr(0, line.find("/")));
			line = line.substr(line.find("/") + 1); //line tera: ano hora:minutos:segundos
			ano = stoi(line.substr(0, line.find(" ")));
			line = line.substr(line.find(" ") + 1); //line tera: hora:minutos:segundos
			hora = stoi(line.substr(0, line.find(":")));
			line = line.substr(line.find(":") + 1); //line tera: minutos:segundos
			minutos = stoi(line.substr(0, line.find(":")));
			line = line.substr(line.find(":") + 1); //line tera: segundos
			segundos = stoi(line);

			do {
				getline(f, line);
			} while (line.length() == 0);

			clientes.push_back(stoul(line));

			Venda *v = new Venda(dia, mes, ano, hora, minutos, segundos, codigo);

			do {
				getline(f, line);
			} while (line.length() == 0);

			if (line == "NULL") {
				v->setReceita(NULL);
				clientesReceitas.push_back(0);
			}
			else {
				unsigned long numeroRec = stoul(line);

				do {
					getline(f, morada); //morada tera o nome do medico
				} while (morada.length() == 0);

				do {
					getline(f, line);
				} while (line.length() == 0);

				clientesReceitas.push_back(stoul(line));

				Receita *r = new Receita(numeroRec, morada, NULL); //default para Cliente* � NULL-> sera alterado depois

				do {
					getline(f, line);
				} while (line.length() == 0);

				size_t numProdutos = stoi(line);
				Produto *produto = NULL;

				while (numProdutos > 0) {
					do {
						getline(f, line);
					} while (line.length() == 0);

					codigo = stoul(line.substr(0, line.find(" "))); //codigo tera o codigo do Produto
					line = line.substr(line.find(" ") + 1);

					numeroRec = stoul(line); //numeroRec tera a quantidade do Produto

					Produto p = farm->getProduto(codigo);

					if (p.getCodigo() != 0)
						*produto = p;

					if (produto != NULL)
						r->addProduto(produto, numeroRec);

					numProdutos--;
				}
				v->setReceita(r);
			}
			size_t num;

			do {
				getline(f, line);
			} while (line.length() == 0);

			num = stoi(line); //total da venda

			do {
				getline(f, line);
			} while (line.length() == 0);

			num = stoi(line); //Numero de Produtos da venda

			while (num > 0) {
				do {
					getline(f, line);
				} while (line.length() == 0);

				codigo = stoul(line.substr(0, line.find(" ")));
				line = line.substr(line.find(" ") + 1);
				preco = stof(line.substr(0, line.find(" "))); //preco guarda a quantidade do produto
				line = line.substr(line.find(" ") + 1);
				desconto = stof(line.substr(0, line.find(" "))); //desconto guarda o valor do iva

				Produto *p = new Produto(0, "", 0, "", 0, 0, 0);
				*p = farm->getProduto(codigo);
				v->addProduto(p, preco, desconto);
				num--;
			}
			farm->addVenda(v);
			numProd--;
		}

		cF.farmacias.push_back(farm);
		numVars--;
	}


	numVars = 0;
	do {
		getline(f, line);
	} while (line.length() == 0);

	numVars = stoi(line);
	while (numVars > 0) { //Importar Clientes
		do {
			getline(f, nome);
		} while (nome.length() == 0);

		do {
			getline(f, line);
		} while (line.length() == 0);

		contribuinte = stoul(line);

		do {
			getline(f, morada);
		} while (morada.length() == 0);

		string distrito;
		do{
			getline(f, distrito);
		}while(distrito.length() == 0);

		Cliente *c = new Cliente(nome, morada, contribuinte, distrito);
		size_t numCompras = 0;

		do {
			getline(f, line);
		} while (line.length() == 0);

		numCompras = stoi(line);
		while (numCompras > 0) {
			do {
				getline(f, line);
			} while (line.length() == 0);

			contribuinte = stoul(line); //contribuinte ter� o c�digo da Venda
			Venda *v = NULL;
			for (vector<Farmacia *>::iterator it = cF.farmacias.begin(); it != cF.farmacias.end(); it++) {
				v = (*it)->getVenda(contribuinte);
				if (v != NULL)
					break;
			}
			c->addCompra(v);
			numCompras--;
		}

		cF.addCliente(c);
		numVars--;
	}

	numVars = 0;
	do {
		getline(f, line);
	} while (line.length() == 0);

	numVars = stoi(line);
	string cargo;
	while (numVars > 0) { //Importar Funcion�rios
		do {
			getline(f, nome);
		} while (nome.length() == 0);

		do {
			getline(f, line);
		} while (line.length() == 0);

		contribuinte = stoul(line);

		do {
			getline(f, morada);
		} while (morada.length() == 0);

		Funcionario *func = new Funcionario(nome, morada, contribuinte);

		do {
			getline(f, line);
		} while (line.length() == 0);

		nome = line.substr(0, line.find("-")); //nome conter� o cargo do Funcion�rio
		func->setCargo(nome);

		line = line.substr(line.find("-") + 1);
		double salario;
		salario = stod(line);
		func->changeSalario(salario);

		do {
			getline(f, nome); //nome conter� o nome da Farm�cia onde trabalha o Funcion�rio
		} while (nome.length() == 0);

		Farmacia *farm = NULL;
		for (vector<Farmacia*>::iterator it = cF.farmacias.begin(); it != cF.farmacias.end(); it++) {
			if ((*it)->getNome() == nome) {
				farm = (*it);
				break;
			}
		}

		do {
			getline(f, line);
		} while (line.length() == 0);

		func->setFarmacia(farm);
		cF.addFuncionario(func, (bool)stoi(line));
		numVars--;
	}

	for (size_t i = 0; i < cF.farmacias.size(); i++) {
		if (gerentes[i] != 0) {
			tabHFunc::iterator itfnc;
			for (itfnc = cF.registo_funcionarios.begin(); itfnc != cF.registo_funcionarios.end(); itfnc++) {
				if (itfnc->func->getNoContribuinte() == gerentes[i]) {
					cF.farmacias[i]->setGerente(itfnc->func);
					break;
				}
			}
		}

		if (diretoresTecnicos[i] != 0) {
			tabHFunc::iterator itfnc;
			for (itfnc = cF.registo_funcionarios.begin(); itfnc != cF.registo_funcionarios.end(); itfnc++) {
				if (itfnc->func->getNoContribuinte() == diretoresTecnicos[i]) {
					cF.farmacias[i]->setDiretorTecnico(itfnc->func);
					break;
				}
			}
		}
		vector<Venda *> v = cF.farmacias[i]->getVendas();
		for (size_t j = 0; j < v.size(); j++) {
			if (clientesReceitas[j] != 0) {
				for (set<Cliente*, clientesComp>::iterator it = cF.clientes.begin(); it != cF.clientes.end(); it++) {
					if ((*it)->getNoContribuinte() == clientesReceitas[j]) {
						v[j]->setCliente(*it);
						break;
					}
				}
			}

			if (clientes[j] != 0) {
				for (set<Cliente*, clientesComp>::iterator it = cF.clientes.begin(); it != cF.clientes.end(); it++) {
					if ((*it)->getNoContribuinte() == clientes[j]) {
						Receita *r;
						r = v[j]->getReceita();
						r->setCliente(*it);
						v[j]->setReceita(r);
						break;
					}
				}
			}

		}
		cF.farmacias[i]->setVendas(v);
	}
}


