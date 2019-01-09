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

	/*for(size_t i=0; i<distritos.size(); i++){
		if (distritos.at(i).length() + 2 >= distrito.length() && distritos.at(i).length() <= distrito.length()){
			dist_correcao.push_back(distritos.at(i));
		}
	}*/

	vector<int> pts(dist_correcao.size(), 0);
	vector<int> letras_dist(27, 0); //26 letras, ultima posicao corresponde ao espaço
	vector<int> letras_correcao(27, 0);

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

		for(size_t k=0; k<27; k++){
			diff += abs(letras_dist.at(k) - letras_correcao.at(k));
		}
		pts.at(i) = diff;
		diff = 0;
		letras_correcao.clear();
		letras_correcao.resize(27,0);
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
