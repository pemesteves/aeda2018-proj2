/**
 * Header File que contem a classe CadeiaFarmacias.
 *
 * @author Marcia e Pedro
 * @date Janeiro, 2019
 */

#ifndef CADEIAFARMACIAS_H
#define CADEIAFARMACIAS_H

#include "Farmacia.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>

/**
 * Struct hFuncPtr
 */
struct hFuncPtr {
	/**
	 * @brief Operador () que devolve a posição de um FuncPtr na tabela de dispersão
	 * @param f1 FuncPtr a colocar na tabela de dispersão
	 * @return Posição na tabela de dispersão
	 */
	int operator()(const FuncPtr & f1) const {
		return (int) f1.func->getSalario() + (int) f1.func->getNoContribuinte()
				+ f1.func->getNome().size();
	}

	/**
	 * @brief Operador () que compara dois FuncPtr
	 * @param f1, f2 FuncPtr a verificar se são iguais
	 * @return Retorna true se forem iguais, ou falso noutro caso
	 */
	bool operator()(const FuncPtr & f1, const FuncPtr & f2) const {
		return f1.func->getNome() == f2.func->getNome()
				&& f1.func->getNoContribuinte() == f2.func->getNoContribuinte();
	}
};

/**
 * Definição do unordered_set: tabela de dispersão
 */
typedef std::unordered_set<FuncPtr, hFuncPtr, hFuncPtr> tabHFunc;

/**
 * Classe CadeiaFarmacias
 */
class CadeiaFarmacias {
private:
	std::string nome; /**< @brief Nome da cadeia de farmacias */
	std::vector<Farmacia*> farmacias; /**< @brief Vetor de apontadores para objetos do tipo Farmacia */
	std::set<Cliente*, clientesComp> clientes; /**< @brief Set de apontadores para objetos do tipo Cliente */
	tabHFunc registo_funcionarios; /**< @brief Tabela de dispersao com funcionarios antigos e novos da Cadeia de Farmacias */
public:
	/**
	 *  Construtor da classe
	 *
	 *  Inicializa um objeto da classe colocando todos os vetores vazios
	 */
	CadeiaFarmacias();

	/**
	 *  Construtor da classe
	 *
	 * 	Inicializa um objeto da classe colocando todos os vetores vazios e atribuindo um nome
	 * 	@param nome Nome da cadeia de farmacias
	 */
	CadeiaFarmacias(std::string nome);

	/**
	 * Metodo para alterar o nome de uma cadeia de farmacias
	 * @param nome Novo nome da cadeia
	 */
	void setNome(std::string nome);

	/**
	 * Metodo que retorna o numero de farmacias
	 * @return Tamanho do vetor de farmacias(unsigned int)
	 */
	unsigned int getNumFarmacias() const;

	/**
	 * Metodo que retorna o numero de clientes
	 * @return Tamanho do vetor de clientes(unsigned int)
	 */
	unsigned int getNumClientes() const;

	/**
	 * Metodo que retorna o numero de funcionarios
	 * @return Tamanho do vetor de funcionarios(unsigned int)
	 */
	unsigned int getNumFuncionarios() const;

	/**
	 * Metodo que retorna o nome da cadeia de farmacias
	 * @return Nome da Cadeia (atributo da classe)
	 */
	std::string getNome() const;

	/**
	 * Metodo que retorna um vetor de farmacias
	 * @return Vetor farmacias (atributo da classe)
	 */
	std::vector<Farmacia *> getFarmacias() const;

	/**
	 * Metodo que retorna um vetor de clientes
	 * @return Vetor com os clientes da cadeia
	 */
	std::vector<Cliente*> getClientes() const;

	/**
	 * Metodo que retorna um vetor de funcionarios
	 * @return Vetor com os funcionarios da cadeia (atuais e antigos)
	 */
	std::vector<FuncPtr> getFuncionarios() const;

	/**
	 * Metodo que permite adicionar um apontador para Farmacia ao respetivo vetor
	 * @param farmacia Apontador para objeto do tipo Farmacia que sera adicionado ao vetor farmacias
	 */
	void addFarmacia(Farmacia* farmacia);

	/**
	 * Metodo que permite eliminar a Farmacia nomeF do respetivo vetor. Tambem remove o apontador Farmacia de todos os funcionarios caso seja o mesmo
	 * @param nomeF Nome da farmacia que sera removida do vetor
	 * @return Retorna um apontador para o objeto removido ou, se este nao existir, lanca uma excecao do tipo FarmaciaInexistente
	 */
	Farmacia* removeFarmacia(const std::string &nomeF);

	/**
	 * Metodo que permite ordenar as farmacias
	 * @param tipo Enumeracao do tipo tipoSort que permite ao utilizador escolher o modo de ordenacao do vetor
	 * @param crescente Booleano que permite ao utilizador escolher se quer realizar a ordenacao por ordem crescente ou decrescente
	 */
	void sortFarmacias(enum tipoSort tipo, bool crescente);

	/**
	 * Metodo que permite adicionar um apontador para Cliente a respetiva estrutura de dados
	 * @param cliente Apontador para objeto do tipo Cliente que sera adicionado ao set clientes
	 */
	void addCliente(Cliente* cliente);

	/**
	 * Metodo que permite eliminar o Cliente nomeC do respetivo vetor
	 * @param nomeC Nome do cliente que sera removido do vetor
	 * @return Retorna um apontador para o objeto removido ou, se este nao existir, lanca uma excecao do tipo ClienteInexistente
	 */
	Cliente* removeCliente(const std::string &nomeC);

	/**
	 * Metodo que permite adicionar um Funcionario a Cadeia de Farmacias
	 * @param funcionario Objeto do tipo FuncPtr que sera adicionado a tabela de dispersao de funcionarios
	 * @param atual_funcionario Booleano que indica se o funcionario a adicionar trabalha atualmente na cadeia ou e um funcionario antigo
	 * @return Retorna true se o funcionario foi adicionado, ou seja, se nao existia nenhum funcionario com o mesmo numero de contribuinte, e false caso contrario
	 */
	bool addFuncionario(Funcionario* funcionario, bool atual_funcionario);

	/**
	 * Metodo que permite obter os funcionarios antigos da cadeia
	 * @return Vetor de apontadores para os antigos funcionarios da cadeia
	 */
	std::vector<Funcionario*> getFuncionariosAntigos() const;

	/**
	 * Metodo que permite obter os funcionarios atuais da cadeia
	 * @return Vetor de apontadores para os atuais funcionarios da cadeia
	 */
	std::vector<Funcionario*> getFuncionariosAtuais() const;

	/**
	 * Metodo que imprime no ecra os dados dos funcionarios antigos
	 */
	void mostrarFuncionariosAntigos() const;

	/**
	 * Metodo que permite despedir o Funcionario. Coloca-o como antigo funcionario na tabela de dispersao
	 * @param contF Numero de contribuinte do funcionario que sera despedido
	 * @return Retorna um apontador para o Funcionario despedido ou, se este nao existir, lanca uma excecao do tipo FuncionarioInexistente
	 */
	Funcionario* despedeFuncionario(const unsigned long contF);

	/**
	 * Metodo que permite voltar a contratar um funcionario antigo
	 * @param contF Numero de contribuinte do funcionario que vai ser contratado
	 * @return Retorna 0 se o funcionario foi contratado com sucesso (se o contribuinte correspondia a um funcionario antigo da cadeia), 1 se o contribuinte corresponde a um funcionario atual da cadeia e portanto nao pode voltar a ser contratado, e 2 se o contribuinte nao corresponde a um funcionario, atual ou antigo, da cadeia
	 */
	int contratarFuncAntigo(unsigned long contF);

	/**
	 * Overload do operador exportar a cadeia de farmacias
	 * @param output Variavel para onde se quer exportar(ecra, ficheiro, ...)
	 * @param cF Cadeia de Farmacias que se quer exportar
	 * @return Retorna referencia para a variavel para onde se quer exportar
	 */
	friend std::ostream& operator<<(std::ostream &output,
			const CadeiaFarmacias &cF);

	/**
	 * Metodo para importar a cadeia de farmacias
	 * @param f Ficheiro de onde se vai importar
	 * @param cF Cadeia de Farmacias que se quer exportar
	 */
	friend void import(std::ifstream &f, CadeiaFarmacias &cF);
};

#endif
