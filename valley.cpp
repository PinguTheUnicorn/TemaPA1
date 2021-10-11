#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	bool vale = true;
	ifstream fin("valley.in");

	// se citesc datele de intrare
	fin >> N;

	long min;
	long index_min = 1;
	vector<long> elem(N);

	fin >> elem[0];

	fin >> elem[1];
	min = elem[1];
	vale = (elem[1] == elem[0]);

	for (int i = 2; i < N - 1; i++) {
		fin >> elem[i];

		if (elem[i] != elem[i - 1]) {
			vale = false;
		}

		if (min > elem[i]) {
			min = elem[i];
			index_min = i;
		}
	}

	fin >> elem[N - 1];
	fin.close();

	long total_cost = 0;

	/* daca valorile de intrare sunt constante
	   costul total este 0, se iese din functie */
	if (vale) {
		ofstream fout("valley.out");
		fout << total_cost << endl;
		fout.close();
		return 0;
	}

	// se iau toate elementele de la 1 la index_min
	// daca sunt mai mari decat anteriorul, se aduna costul si se actualizeaza
	for (int i = 1; i <= index_min; i++) {
		if (elem[i] > elem[i - 1]) {
			total_cost += elem[i] - elem[i - 1];
			elem[i] = elem[i - 1];
		}
	}

	/* similar cu pasul anterior, se pleaca de la dreapta spre mijloc
	   daca valoarea curenta este mai mare decat cea anterioara
	   se fac modificarile necesare */
	for (int i = N - 1; i > index_min; i--) {
		if (elem[i] < elem[i - 1]) {
			total_cost += elem[i - 1] - elem[i];
			elem[i - 1] = elem[i];
		}
	}

	ofstream fout("valley.out");
	fout << total_cost<< endl;
	fout.close();

	return 0;
}
