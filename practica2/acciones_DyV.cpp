//Algoritmo DyV de acciones
// g++ -O2 -o acciones_DyV acciones_DyV.cpp

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

/**
*
* @brief Resuelve el problema de encontrar la mejor operación de compra-venta.
*
* @param v vector sobre el que aplicar DyV
* @param ini Primer elemento sobre el que ejecutar el algoritmo
* @param fin Posición siguiente al último elemento sobre el que ejecutar el algoritmo
* @param dia_compra Día compra solucion previo, y donde se devolverá la nueva solución
* @param dia_venta  Día venta solución previo, y donde se devolverá la nueva solución
* @param minimo Devuelve el valor mínimo del vector en el tramo [ini,fin)
* @param maximo Devuelve el valor máximo del vector en el tramo [ini,fin) 
*
* @return Ganancia solución al problema.
*/
int MejorCompraVentaDyV(const vector<int> & v, int ini, int fin, int & dia_compra, int & dia_venta, int & minimo, int & maximo){
  int solucion = INT_MIN;

  //Si el tamaño del trozo de vector es 3 o menos, operamos sobre el tramo
  if(fin - ini < 3){
    maximo = minimo = ini;
    //Calculamos maximo y minimo
    for(int i = ini+1; i < fin; i++){
      if(v[i] > v[maximo])
        maximo = i;
      else if(v[i] < v[minimo])
        minimo = i;
    }
    cout << "Max min hecho" << endl;
    //Calculamos ganancia, dia_compra y dia_venta
    for(int i = ini; i < fin-1; i++){     
		  for(int j = i+1; j < fin; j++){
        int ganancia = v[j]-v[i];
        if(ganancia > solucion){
          solucion = ganancia;
          dia_compra = i;
          dia_venta = j;
        }
      }
    }
    cout << "Ganancia hecho" << endl;
  }
  //Si el tamaño del trozo es 4 o más, dividimos y después combinamos soluciones
  else{
    int dia_compra_izq, dia_compra_dcha, dia_venta_izq, dia_venta_dcha, minimo_izq, minimo_dcha, maximo_izq, maximo_dcha, media;
    int ganancia_izq, ganancia_dcha, ganancia_comb, sol;
    //Dividimos el vector dado en dos trozos (lo más iguales posible)
    media = (fin+ini)/2 + 1;
    //Llamamos a la función de forma recursiva
    ganancia_izq  = MejorCompraVentaDyV(v, ini, media, dia_compra_izq,  dia_venta_izq,  minimo_izq,  maximo_izq );
    ganancia_dcha = MejorCompraVentaDyV(v, media, fin, dia_compra_dcha, dia_venta_dcha, minimo_dcha, maximo_dcha);
    //Combinamos soluciones
    
    minimo = (minimo_izq < minimo_dcha) ? minimo_izq : minimo_dcha;
    maximo = (maximo_izq > maximo_dcha) ? maximo_izq : maximo_dcha;
   
    ganancia_comb = v[maximo_dcha] - v[minimo_izq];
    if(ganancia_comb > ganancia_izq && ganancia_comb > ganancia_dcha){
      solucion = ganancia_comb;
      dia_compra = minimo_izq;
      dia_venta = maximo_dcha;
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
  int minimo, maximo;
  cout << v.size() << endl;
  return MejorCompraVentaDyV(v, 0, v.size(), dia_compra, dia_venta, minimo, maximo);
}


int main(){
	int solucion, dia_compra, dia_venta;
	
	vector<int> v = {1, 2, 300, 4, 15, 0, 7, 20, 9, 0};
	
	solucion = MejorCompraVentaDyV(v, dia_compra, dia_venta);
	
	cout << "Solucion: " << endl;
	cout << "Elemento minimo -> v[" << dia_compra << "]= " << v[dia_compra]
	 	 << "\tElemento maximo -> v[" << dia_venta << "]= " << v[dia_venta] << endl;
	cout << "Ganancia = " << v[dia_venta] << " - " << v[dia_compra] << " = " << solucion << endl; 
	
}
