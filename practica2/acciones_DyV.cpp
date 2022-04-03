//Algoritmo DyV de acciones
// g++ -O2 -o acciones_DyV acciones_DyV.cpp

#include <iostream>
#include <vector>

using namespace std;

/**
*
*
*
* @param v vector sobre el que aplicar DyV
* @param ini Primer elemento sobre el que ejecutar el algoritmo
* @param fin Posición siguiente al último elemento sobre el que ejecutar el algoritmo
* @param dia_compra Día compra solucion previo, y donde se devolverá la nueva solución
* @param dia_venta  Día venta solución previo, y donde se devolverá la nueva solución
* @param min Devuelve el valor mínimo del vector en el tramo [ini,fin)
* @param max Devuelve el valor máximo del vector en el tramo [ini,fin) 
*
* @return Ganancia solución al problema.
*/
int MejorCompraVentaDyV(const vector<int> & v, int ini, int fin, int & dia_compra, int & dia_venta, int & min, int & max){
  //Si el tamaño del trozo de vector es 3 o menos, operamos sobre el tramo
  int solucion = INT_MIN;
  if(fin - ini < 2){
    max = min = ini;
    //Calculamos max y min
    for(int i = ini+1; i < fin; i++){
      if(v[i] > v[max])
        max = i;
      else if(v[i] < v[min])
        min = i;
    }
    //Calculamos ganancia, dia_compra y dia_venta
    for(int i = ini; i < fin-1; i++){     
		  for(int j = i; j < fin; j++){
        
        int ganancia = v[j]-v[i];
        if(ganancia > solucion){
          solucion = ganancia;
          dia_compra = i;
          dia_venta = j;
        }
      }
    }
  }
  else{
    int dia_compra_izq, dia_compra_dcha, dia_venta_izq, dia_venta_dcha, min_izq, min_dcha, max_izq, max_dcha, media;
    int ganancia_izq, ganancia_dcha, ganancia_comb, sol;
    //Dividimos el vector dado en dos trozos (lo más iguales posible)
    media = (fin+ini)/2 + 1;
    //Llamamos a la función de forma recursiva
    ganancia_izq  = MejorCompraVentaDyV(v, ini, media, dia_compra_izq,  dia_venta_izq,  min_izq,  max_izq );
    ganancia_dcha = MejorCompraVentaDyV(v, media, fin, dia_compra_dcha, dia_venta_dcha, min_dcha, max_dcha);
    //Combinamos soluciones
    
    min = (min_izq < min_dcha) ? min_izq : min_dcha;
    max = (max_izq > max_dcha) ? max_izq : max_dcha;
   
    ganancia_comb = v[max_dcha] - v[min_izq];
    if(ganancia_comb > ganancia_izq && ganancia_comb > ganancia_dcha){
      solucion = ganancia_comb;
      dia_compra = min_izq;
      dia_venta = max_dcha;
    }
    else if(ganancia_izq > ganancia_dcha){
      solucion = ganancia_izq;
      dia_compra = dia_compra_izq;
      dia_venta = dia_venta_izq;
    }
    else{
      solucion = ganancia_dcha;
      dia_compra = dia_compra_dcha;
      dia_venta = dia_venta_dcha;
    }
   
  }
  
  return solucion;
}

int MejorCompraVentaDyV(const vector<int> & v, int & dia_compra, int & dia_venta){
  int min, max;
  return MejorCompraVentaDyv(v, 0, v.size(), dia_compra, dia_venta, min, max);
}


int main(){
	const int TAM = 10;
	int solucion, dia_compra, dia_venta;
	
	vector<int> v = {1, 2, 300, 4, 15, 0, 7, 20, 9, 0};
	
	solucion = MejorCompraVentaDyV(v, dia_compra, dia_venta);
	
	cout << "Solucion: " << endl;
	cout << "Elemento minimo -> v[" << min << "]= " << v[min]
	 	 << "\tElemento maximo -> v[" << max << "]= " << v[max] << endl;
	cout << "Ganancia = " << v[max] << " - " << v[min] << " = " << solucion << endl; 
	
}
