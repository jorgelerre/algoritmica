// g++ -O2 -o acciones_basico acciones_basico.cpp

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int MejorCompraVentaBasico(const vector<int> & v, int & maximo, int & minimo){
	int solucion = INT_MIN;

	for(int i = 0; i < v.size()-1; i++){
		for(int j = i+1; j < v.size(); j++){
			int ganancia = v[j]-v[i];
			if(ganancia > solucion){
				solucion = ganancia;
				minimo = i;
				maximo = j;
			}
		}
	}
	
	return solucion;
}


int main(){
	const int TAM = 10;
	int solucion, max, min;
	
	vector<int> v = {1, 2, 300, 4, 15, 0, 7, 20, 9, 0};
	
	solucion = MejorCompraVentaBasico(v, max, min);
	
	cout << "Solucion: " << endl;
	cout << "Elemento minimo -> v[" << min << "]= " << v[min]
	 	 << "\tElemento maximo -> v[" << max << "]= " << v[max] << endl;
	cout << "Ganancia = " << v[max] << " - " << v[min] << " = " << solucion << endl; 
	
}
