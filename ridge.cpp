#include <bits/stdc++.h>

using namespace std;

// structura ce stocheaza inaintimea unui munte si costul unei sapaturii
typedef struct munte {
	long high;
	long cost;
} munte;

// functie de calcul al minimului
long my_min(long a, long b) {
	return (a < b)?a:b;
}

int main() {
	int N;  // numarul de munti
	ifstream fin("ridge.in");

	// se citesc datele de intrare
	fin >> N;
	vector<munte> lant(N);

	for (int i = 0; i < N; i++) {
		fin >> lant[i].high;
		fin >> lant[i].cost;
	}

	fin.close();

	// se creaza matricea de cautare a costului minim
	vector<vector<long>> cautare(N, vector<long>(3));

	// valorile pentru cazurile de baza ale primului element
	cautare[0][0] = 0;
	cautare[0][1] = lant[0].cost;
	cautare[0][2] = lant[0].cost * 2;

	// se cauta toate posibilitatile
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			long minim = LONG_MAX;

			/* se verifica daca modificarea muntelui curent cu j nivele este
			   diferita de cea a muntelui anterior fara a se modifica */
			if (lant[i].high - j != lant[i - 1].high && lant[i].high - j >= 0) {
				// se actualizeaza minimul
				minim = my_min(minim, cautare[i-1][0]);
			}

			/* se verifica daca modificarea muntelui curent cu j nivele este
			   diferita de cea a muntelui anterior modificat cu un nivel */
			if (lant[i].high - j != lant[i-1].high - 1 && lant[i].high - j >= 0) {
				// se actualizeaza minimul
				minim = my_min(minim, cautare[i-1][1]);
			}

			/* se verifica daca modificarae muntelui curent cu j nivele este
			   diferita de cea a muntelui anterior cu doua nivele */
			if (lant[i].high - j != lant[i - 1].high - 2 && lant[i].high - j >= 0) {
				// se actualizeaza minimul
				minim = my_min(minim, cautare[i-1][2]);
			}

			/* daca nu s-a gasit vreo posibilitate pentru a modifica, costul
			   devine infinit pentru a nu influenta deciziile viitoare */ 
			if (minim == LONG_MAX) {
				cautare[i][j] = LONG_MAX;
			} else {
				/* altfel se calculeaza costul pentru a sapa j nivele, pentru
				   modificarea optima a muntilor anteriori */
				cautare[i][j] = j * lant[i].cost + minim;
			}
		}
	}

	// solutia se initializeaza cu infinit
	long sol = LONG_MAX;

	// se verifica toate posibilitatile finale si se alege varianta minima
	for (int i = 0; i < 3; i++) {
		sol = my_min(sol, cautare[N-1][i]);
	}

	ofstream fout("ridge.out");

	fout << sol;

	fout.close();

	return 0;
}
