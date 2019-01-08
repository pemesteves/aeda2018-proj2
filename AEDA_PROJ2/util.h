/**
 * Header File que contem enumeracoes e metodos sort importantes para o projeto
 *
 * @author Marcia e Pedro
 * @date Janeiro, 2019
 */

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

 /**
  * Declaracao de uma enumeracao: tipoSort, e utilizada para todas as operacoes de sort
  */
enum tipoSort {
	NOME, /**< @brief Ordenacao por nome*/
	CONTRIBUINTE, /**< @brief Ordenacao por contribuinte */
	NUM_PROD, /**< @brief Ordenacao por numero de produtos */
	NUM_VENDA, /**< @brief Ordenacao por numero de vendas/compras */
	SALARIO, /**< @brief Ordenacao por salario */
	DATA, /**< @brief Ordenacao por Data */
	HORA, /**< @brief Ordenacao por Hora */
	DEFAULT /**< @brief Ordenacao por um criterio pre-definido */
};

/**
 * Declaracao de uma enumeracao: dadosProd, e utilizada para facilitar o acesso a dados de um produto numa venda
 */
enum dadosProd {
	QUANTIDADE,  /**< @brief Unidades do produto vendidas */ 
	IVA, /**< @brief Percentagem de IVA do produto */
	COMPARTICIPACAO, /**< @brief Percentagem de comparticipacao do produto */
	PRECO_PAGO /**< @brief Preco pago pelo produto, tendo em conta o IVA e a comparticipacao */
};

/**
 * Metodo que retorna uma string com todas as letras maiusculas, usado para comparacoes de strings case-insensitive
 * @param str String cujas letras se vai converter para uppercase
 * @return string com todas as letras maiusculas
 */
inline std::string toupperstring(std::string str) {
	std::string s = str;
	for (size_t i = 0; i < s.length(); i++) {
		s.at(i) = toupper(s.at(i));
	}
	return s;
}

/**
 *	Classe sorting para ordenacao de vetores
 */
template<typename T>
class sorting {
public:
	static enum tipoSort tipo; /**< @brief Tipo de sort a realizar */
	static bool crescente; /**< @brief Booleano que indica se o sort será realizado de modo crescente ou decrescente */

	/**
	 * Funcao que compara dois tipos de dados
	 * @param a, b Valores a serem comparados
	 * @return Retorna true se foi menor que b. Retorna false caso contrario
	 */
	static bool compare_p(const T* a, const T* b) {
		return a->menorQue(*b, tipo, crescente);
	}

	/**
	 * Funcao que ordena um vetor de apontadores para valores T
	 * @param v Vetor a ser ordenado
	 */
	void sort_p(std::vector<T*> &v) {
		sort(v.begin(), v.end(), compare_p);
	}
};

/**
 * Struct clientesComp: compara apontadores de Cliente
 */
struct clientesComp {
	/**
	 * Funcao para comparar dois apontadores para Clientes, usada na bst da classe CadeiaFarmacias
	 * @param c1, c2 Apontadores para Clientes a serem comparados
	 * @return Retorna true se o Cliente c1 for menor que c2. Caso contrário, retorna false
	 */
	template<class T>
	bool operator()(const T* c1, const T* c2) const {
		return (*c1) < (*c2);
	}
};

class Receita;
class Pessoa;
class Cliente;
class Funcionario;
class Venda;

#endif

