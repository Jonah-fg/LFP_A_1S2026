#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<Estudiante> estudiantes;
vector<Curso> cursos;
vector<Nota> notas;

/* ======================================
         STRUCTS (MODELOS DE DATOS)
   ======================================*/

struct Estudiante {
    int carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;
};

struct Curso {
    int codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;
};

struct Nota {
    int carnet;
    int codigoCurso;
    double nota;
    string ciclo;
    int anio;
};


/* ======================================
             FUNCION SPLIT
   ======================================*/

vector<string> split(string linea) {

    vector<string> datos;
    stringstream ss (linea);
    string item;

    while (getline(ss, item, ',')) {
        datos.push_back(item);
    }
    return datos;
}

/* ======================================
         CARGAR ESTUDIANTES
   ======================================*/

void cargarEstudiantes(){

    ifstream archivo("estudiantes.lfp");

    if (!archivo.is_open()) {
        cout << "Error al abrir estudiantes.lfp\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {

        vector<string> datos = split(linea);

        if (datos.size()==5){
            Estudiante estu;
            estu.carnet = stoi(datos[0]);
            estu.nombre = datos[1];
            estu.apellido = datos[2];
            estu.carrera = datos[3];
            estu.semestre = stoi(datos[4]);

            estudiantes.push_back(estu);
        }
    }
    archivo.close();
    cout << "Estudintes cargados correctamnte.\n";
}


void cargarCursos(){

    ifstream archivo("cursos.lfp");

    if (!archivo.is_open()){
        cout << "Error al abrir curos.lfp\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {

        vector<string> datos=split(linea);
        if (datos.size()==5){

            Curso cur;
            cur.codigo= stoi(datos[0]);
            cur.nombre= datos[1];
            cur.creditos =stoi(datos[2]);
            cur.semestre= stoi(datos[3]);
            cur.carrera = datos[4];

            cursos.push_back(cur);
        }
    }

    archivo.close();
    cout << "Cursos cargados correctamente.\n";
}


void cargarNotas(){

    ifstream archivo("notas.lfp");

    if (!archivo.is_open()) {
        cout <<"Error al abrir notas.lfp\n";
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        vector<string> datos=split(linea);

        if (datos.size()==5){

            Nota n;
            n.carnet= stoi(datos[0]);
            n.codigoCurso= stoi(datos[1]);
            n.nota= stod(datos[2]);
            n.ciclo= datos[3];
            n.anio = stoi(datos[4]);

            notas.push_back(n);
        }
    }
    archivo.close();
    cout << "Notas cargadas correctamente.\n";
}


int main()
{
	cout << "Hola mundo";
}
