#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

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

vector<Estudiante> estudiantes;
vector<Curso> cursos;
vector<Nota> notas;


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
        cout <<"Error al abrir curos.lfp\n";
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
            n.carnet=stoi(datos[0]);
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


/* ======================================
		OPERACIONES ESTADISTICAS
   ====================================== */

double calcularPromedio(vector<double> valores){

    if(valores.empty())
        return 0;

    double suma=0;

    for (double v : valores) {
        suma += v;
    }
    return suma/valores.size();
}


double calcularMediana(vector<double> valores){

    if (valores.empty())
        return 0;

    sort(valores.begin(), valores.end());

    int n=valores.size();

    if (n % 2==0){
        return(valores[n/2-1]+valores[n/2])/2.0;
    }
    else{
        return valores[n/2];
    }
}



double calcularDesviacion(vector<double> valores) {

    if (valores.empty())
        return 0;

    double promedio =calcularPromedio(valores);
    double suma=0;

    for (double v :valores) {
        suma += pow(v - promedio, 2);
    }

    return sqrt(suma / valores.size());
}



double calcularMaximo(vector<double> valores) {

    if (valores.empty())
        return 0;

    double maximo=valores[0];
    for (int i=0; i<valores.size(); i++) {
        if (valores[i]>maximo) {
            maximo=valores[i];
        }
    }
    return maximo;
}


double calcularMinimo(vector<double> valores) {

    if (valores.empty())
        return 0;

    double minimo=valores[0];
    for (int i=0; i < valores.size(); i++) {
        if (valores[i]<minimo) {
            minimo = valores[i];
        }
    }
    return minimo;
}



   /*======================================
      REPORTE
    ======================================*/

struct Ranking {
    string nombreCompleto;
    double promedio;
};

 void reporteEstadisticasPorCurso(){

     for (Curso cur:cursos){

         vector<double> notasCurso;
         int aprobados=0;
         int reprobados =0;

         for (Nota n:notas){

             if (n.codigoCurso==cur.codigo){
                 notasCurso.push_back(n.nota);

                 if (n.nota>=61)
                     aprobados++;
                 else
                     reprobados++;
             }
         }

         if (!notasCurso.empty()){

             double promedio= calcularPromedio(notasCurso);
             double mediana=calcularMediana(notasCurso);
             double desviacion=calcularDesviacion(notasCurso);
             double maximo =calcularMaximo(notasCurso);
             double minimo = calcularMinimo(notasCurso);
             double porcentajeAprobacion=(double)aprobados/notasCurso.size() * 100;
                
             cout << "\n====================================\n";
             cout << "Curso: "<< cur.nombre << endl;
             cout << "Promedio: "<< promedio << endl;
             cout << "Mediana: "<< mediana << endl;
             cout << "Desviacion: "<< desviacion << endl;
             cout << "Nota maxima: " << maximo<< endl;
             cout << "Nota minima: " << minimo<< endl;
             cout << "Aprobados: "<< aprobados << endl;
             cout << "Reprobados: "<< reprobados << endl;
             cout << "Porcentaje aprobacion: "<<porcentajeAprobacion << "%\n";
         }
     }
 }



 void reporteRendimientoPorEstudiante() {

     for (Estudiante estu :estudiantes){

         vector<double> notasEstudiante;
         int aprobados=0;
         int reprobados =0;
         int creditosAcumulados= 0;

         for (Nota n:notas){

             if (n.carnet == estu.carnet){

                 notasEstudiante.push_back(n.nota);

                 if (n.nota >= 61){
                     aprobados++;
                     // Buscar el curso para sumar créditos
                     for (Curso cur:cursos){
                         if (cur.codigo == n.codigoCurso) {
                             creditosAcumulados += cur.creditos;
                             break;
                         }
                     }
                 }
                 else{
                     reprobados++;
                 }
             }
         }

         if (!notasEstudiante.empty()) {
             double promedio =calcularPromedio(notasEstudiante);

             cout << "\n====================================\n";
             cout << "Estudiante: " << estu.nombre << " " << estu.apellido << endl;
             cout << "Promedio general: " << promedio << endl;
             cout << "Cursos aprobados: " << aprobados << endl;
             cout << "Cursos reprobados: " << reprobados << endl;
             cout << "Creditos acumulados: " << creditosAcumulados << endl;
         }
     }
 }



int main(){


    return 0;
}
