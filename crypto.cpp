#include <bits/stdc++.h>

using namespace std;

// structura auxiliara pentru modelarea unui calculator
typedef struct calculator {
	long p;
	long u;

	// functie pentru ordonarea a doua obiecte de tipul operator
	bool operator<(const struct calculator& a) const {
		return (p < a.p);
	}
} calculator;

int main() {
	int N;
	long B;

	ifstream fin("crypto.in");

	// se citesc de la tastatura datele de intrare
	fin >> N;
	fin >> B;
	vector<calculator> mina(N);

	// se citesc parametrii fiecarui calculator
	for (auto i = 0; i < N; i++) {
		fin >> mina[i].p;
		fin >> mina[i].u;
	}

	fin.close();

	// sortam "mina"(pentru minat criptomonede) crescator, in functie de putere
	sort(mina.begin(), mina.end());

	// costul pentru UN upgrade al calculatoarelor cu putere minima
	long cost_partial = 0;

	/* pozitia de unde se cauta urmatoarele calculatoare cu putere
	   minima deoarece sortam vectorul, initial va fi 0 */
	size_t poz = 0;

	// costul total de upgrade
	long cost_upgrade = 0;

	while (1) {
		/* puterea(sau rangul) minim actual
		   va fi mereu 0 */
		long rang = mina[0].p;

		/* daca mai exista calculatoare ce nu au fost
		   luate la calculul costului partial */
		if (poz < N) {
			/* se parcurge de la ultimul calculator ramas, cat timp mai
			   avem calculatoare de rang/putere minima si se adauga
			   costul acestuia la costul partial */
			while (mina[poz].p == rang) {
				cost_partial += mina[poz].u;
				poz++;
			}
		}

		/* se calculeaza diferenta de putere dintre rangul minim actual si
		   urmatorul rang existent */
		long dif_rang = mina[poz].p - mina[0].p;

		/* daca toate calculatoarele sunt de aceeasi putere, se face maxim un
		   singur upgrade */
		if (poz == N) {
			dif_rang = 1;
		}

		// cate uprgrade-uri se vor face
		long posibil_upgrade = 1;

		// daca nu se poate face nici macar un upgrade, se iese
		if (cost_upgrade + cost_partial > B) {
			break;
		}

		/* se creste numarul de upgrade-uri pana ajungem
		   la numarul maxim sau depasim bugetul */
		while (posibil_upgrade < dif_rang &&
			(cost_upgrade + cost_partial * posibil_upgrade < B)) {
			posibil_upgrade++;
		}

		/* daca momentan se depaseste bugetul, am mers cu un pas mai in fata
		   (s-a iesit pentru ca s-a ajuns la numarul maxim de upgrade-uri) */
		if (cost_upgrade  + cost_partial * posibil_upgrade > B) {
			posibil_upgrade--;
		}

		/* daca upgrade-ul actual consuma toti banii,
		   se face upgrade-ul si se iese */
		if (cost_upgrade + cost_partial * posibil_upgrade == B) {
			mina[0].p += posibil_upgrade;
			break;
		}

		// se modifica upgrade-ul actual
		cost_upgrade += cost_partial * posibil_upgrade;

		// se face upgrade la puterea primului calculator
		mina[0].p += posibil_upgrade;
	}

	ofstream fout("crypto.out");
	fout << mina[0].p;
	fout.close();

	return 0;
}
