#include <bits/stdc++.h>

using namespace std;

// structura ce modeleaza o actiune
typedef struct actiune {
	long cur;
	long min;
	long max;
} actiune;

int main() {
	ifstream fin("stocks.in");
	int N, B, L;

	// se citesc datele de la tastatura
	fin >> N >> B >> L;
	vector<actiune> actiuni(N);

	for (auto i = 0; i < N; i++) {
		fin >> actiuni[i].cur;
		fin >> actiuni[i].min;
		fin >> actiuni[i].max;
	}

	fin.close();

	// se declara un cub pentru calculul sumelor partiale
	vector<vector<vector<long>>> cautare(N + 1, vector<vector<long>>(B + 1,
													vector<long>(L + 1, 0)));

	// se parcurge cubul
	for (int  i = 1; i <= N; i++) {
		for (int j = 1; j <= B; j++) {
			for (int k = 1; k <= L; k++) {
				/* daca actiunea curenta are pretul si pierderea
				   acceptabile pentru pasul curent */
				if (actiuni[i - 1].cur <= j && actiuni[i - 1].cur -
													actiuni[i - 1].min <= k) {
					// se calculeaza profitul maxim daca s-ar lua aceasta actiune
					int aux = cautare[i - 1][j - actiuni[i - 1].cur][k -
									actiuni[i - 1].cur + actiuni[i - 1].min];
					aux += actiuni[i - 1].max - actiuni[i-1].cur;

					// daca aduce un beneficiu, se retine aceasta alegere
					if (aux > cautare[i - 1][j][k]) {
						cautare[i][j][k] = aux;
					} else {
						/* altfel se pastreaza cazul anterior, in care nu s-ar
						   fi cumparat actiunea curenta */
						cautare[i][j][k] = cautare[i-1][j][k];
					}
				} else {
					/* daca nu se poate adauga actiunea
					   se salveaza starea anterioara */
					cautare[i][j][k] = cautare[i-1][j][k];
				}
			}
		}
	}

	ofstream fout("stocks.out");
	fout << cautare[N][B][L];
	fout.close();

	return 0;
}
