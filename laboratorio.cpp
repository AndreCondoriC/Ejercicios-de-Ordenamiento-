#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

vector<int> leerNumerosDesdeArchivo(const string& nombreArchivo) {
    vector<int> numeros;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo '" << nombreArchivo << "'. Verifique que el archivo exista y tenga permisos de lectura." << endl;
        return numeros;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int numero;
        while (ss >> numero) {
            numeros.push_back(numero);
        }
        if (ss.fail() && !ss.eof()) {
            cerr << "Advertencia: Se encontraron datos no válidos en el archivo. Ignorando..." << endl;
        }
    }

    archivo.close();

    if (numeros.empty()) {
        cerr << "Error: El archivo está vacío o no contiene números válidos." << endl;
    }

    return numeros;
}

int busquedaLineal(const vector<int>& numeros, int objetivo) {
    for (size_t i = 0; i < numeros.size(); i++) {
        if (numeros[i] == objetivo) {
            return i; 
        }
    }
    return -1; 
}

int busquedaLinealSimulada(size_t tamanio, int objetivo, int& pasos) {
    pasos = 0; 
    for (size_t i = 0; i < tamanio; i++) {
        pasos++; 
        if (i == objetivo) {
            return i; 
        }
    }
    return -1; 
}

int main() {
    const string nombreArchivo = "numeros_aleatorios.txt" ;

    vector<int> numeros = leerNumerosDesdeArchivo(nombreArchivo);
    if (!numeros.empty()) {
        cout << "Archivo '" << nombreArchivo << "' leído correctamente. Total de números: " << numeros.size() << endl;

        int objetivo;
        cout << "Ingrese el número que desea buscar: ";
        if (!(cin >> objetivo)) {
            cerr << "Error: Entrada no válida. Por favor, ingrese un número entero." << endl;
            return 1;
        }

        clock_t inicio = clock();
        int indice = busquedaLineal(numeros, objetivo);
        clock_t fin = clock();

        double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

        if (indice != -1) {
            cout << "Número encontrado en el índice " << indice << "." << endl;
        } else {
            cout << "Número no encontrado." << endl;
        }

        cout << "Tiempo de búsqueda: " << tiempo << " segundos." << endl;
    }

    vector<size_t> tamanios = {
        100, 1000, 10000, 100000, 1000000,
        10000000, 100000000, 1000000000
    };

    for (size_t tamanio : tamanios) {
        int objetivo = tamanio - 1; 
        int pasos = 0;

        clock_t inicio = clock();
        int indice = busquedaLinealSimulada(tamanio, objetivo, pasos);
        clock_t fin = clock();

        double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

        cout << "Tamaño del conjunto: " << tamanio << endl;
        cout << "Número buscado: " << objetivo << endl;
        if (indice != -1) {
            cout << "Número encontrado en el índice " << indice << "." << endl;
        } else {
            cout << "Número no encontrado." << endl;
        }
        cout << "Pasos realizados: " << pasos << endl;
        cout << "Tiempo de búsqueda: " << tiempo << " segundos." << endl;
        cout << "----------------------------------------" << endl;
    }

    return 0;
}                
