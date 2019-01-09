#include "util.h"
#include "validacao.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>


using namespace std;

string distritoCorrecao(string &distrito) {
	string d;

	vector<string> distritos = {"Aveiro","Beja","Braganca","Castelo Branco","Coimbra","Evora","Faro","Guarda","Leiria","Portalegre","Porto","Santarem","Setubal","Viana do Castelo","Vila Real","Viseu"};

	for(size_t i = 0; i<distritos.size(); i++){
		distritos.at(i) = toupperstring(distritos.at(i));
	}

	vector<string> dist_correcao = distritos;


	vector<int> pts(dist_correcao.size(), 0);
	vector<int> letras_dist(26, 0);
	vector<int> letras_correcao(26, 0);

	distrito = toupperstring(distrito);

	for(size_t i=0; i<distrito.length(); i++){
		if(isalpha(distrito.at(i))){
			letras_dist.at(distrito.at(i) - 'A')++;
		}
	}

	int diff = 0;

	for(size_t i=0; i<dist_correcao.size(); i++){

		for(size_t j=0; j<dist_correcao.at(i).length(); j++){
			if(isalpha(dist_correcao.at(i).at(j))){
				letras_correcao.at(dist_correcao.at(i).at(j) - 'A')++;

			}
		}

		for(size_t k=0; k<26; k++){
			diff += abs(letras_dist.at(k) - letras_correcao.at(k));
		}
		pts.at(i) = diff;
		diff = 0;
		letras_correcao.clear();
		letras_correcao.resize(26,0);
	}

	int n = 100;

	for (size_t i = 0; i<pts.size(); i++){
		if(pts.at(i) < n){
			d = dist_correcao.at(i);
			n = pts.at(i);
		}
	}

	return d;
}

bool valido_contribuinte(unsigned long contribuinte){
	unsigned num_digitos = 0;
	unsigned long temp_cont = contribuinte;
	while(temp_cont != 0){
		num_digitos++;
		temp_cont /= 10;
	}

	if(num_digitos != 9)
		return false;

	std::vector<unsigned> digitos(9, 0);

	temp_cont = contribuinte;

	for(int i = 8; i >= 0; i--){
		digitos[i] = temp_cont % 10;
		temp_cont /= 10;
	}

	unsigned digito_controlo = 0;

	digito_controlo += digitos[7]*2;
	digito_controlo += digitos[6]*3;
	digito_controlo += digitos[5]*4;
	digito_controlo += digitos[4]*5;
	digito_controlo += digitos[3]*6;
	digito_controlo += digitos[2]*7;
	digito_controlo += digitos[1]*8;
	digito_controlo += digitos[0]*9;

	digito_controlo = digito_controlo % 11;
	if ((digito_controlo == 1 || digito_controlo == 0) && (digitos[8] == 0))
		return true;
	else if (digito_controlo != 0 && digito_controlo != 1){
		if((11 - digito_controlo) == digitos[8])
			return true;
	}
	return false;
}
