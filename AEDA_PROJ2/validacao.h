/**
 * Header File que contem funcoes utilizadas para validacoes de distritos e contribuintes
 *
 * @author Marcia e Pedro
 * @date Janeiro, 2019
 */

#ifndef VALIDACAO_H
#define VALIDACAO_H

#include <vector>
#include <string>

/**
 * Funcao que, dado um distrito nao existente, retorna o distrito mais parecido com a palavra escrita. Funciona como corretor automatico.
 * @param distrito Distrito mal escrito
 * @return Retorna o distrito mais parecido com a palavra escrita
 */
std::string distritoCorrecao(std::string &distrito);

/**
 * Funcao que verifica se um dado contribuinte e valido em Portugal
 * @param contribuinte Contribuinte a ser verificado
 * @return Retorna true se o contribuinte for valido. Caso contrario, retorna false
 */
bool valido_contribuinte(unsigned long contribuinte);

#endif

