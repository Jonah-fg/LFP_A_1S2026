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
    stringstream ss(linea);
    string item;

    while (getline(ss, item, ',')) {
        datos.push_back(item);
    }
    return datos;
}

/* ======================================
                CARGAR DATOS
   ======================================*/

void cargarEstudiantes(){

    ifstream archivo("estudiantes.lfp");

    if (!archivo.is_open()) {
        cout << "Error al abrir estudiantes.lfp" << endl;
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
    cout << "Estudintes cargados correctamnte." << endl;
}


void cargarCursos(){

    ifstream archivo("cursos.lfp");
    if (!archivo.is_open()){
        cout <<"Error al abrir curos.lfp"<<endl;
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
    cout << "Cursos cargados correctamente." << endl;
}


void cargarNotas(){

    ifstream archivo("notas.lfp");

    if (!archivo.is_open()) {
        cout <<"Error al abrir notas.lfp" << endl;
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
    cout << "Notas cargadas correctamente." << endl;
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
        suma += pow(v -promedio, 2);
    }

    return sqrt(suma/valores.size());
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
                    REPORTES
    ======================================*/

struct Ranking {
    int carnet;
    string nombreCompleto;
    string carrera;
    double promedio;
    int semestre;
};

struct Reprobacion {
    int codigo;
    string nombre;
    int total;
    int aprobados;
    int reprobados;
    double porcentaje;
};

 void generarReporteEstadisticasCursoHTML(){

     ofstream archivo("reporte_cursos.html");
     if (!archivo.is_open()) {
         cout << "Error al crear el archivo HTML" << endl;
         return;
     }

     archivo << "<html>"<<endl;
     archivo << "<head>"<<endl;
     archivo << "<title>Reporte por Curso</title>"<<endl;
     archivo << "</head>"<<endl;
     archivo << "<body>"<<endl;
     archivo << "<h1>Estadisticas Generales por Curso</h1>"<<endl;

     archivo << "<table border='1'>"<<endl;
     archivo << "<tr>";
     archivo << "<tr>";
     archivo << "<th>Codigo</th>";
     archivo << "<th>Curso</th>";
     archivo << "<th>Total Estudiantes</th>";
     archivo << "<th>Promedio</th>";
     archivo << "<th>Mediana</th>";
     archivo << "<th>Desviacion</th>";
     archivo << "<th>Maximo</th>";
     archivo << "<th>Minimo</th>";
     archivo << "</tr>"<<endl;

     for (Curso cur:cursos){
         vector<double> notasCurso;

         for (Nota n:notas){
             if (n.codigoCurso == cur.codigo){
                 notasCurso.push_back(n.nota);
             }
         }
         if (!notasCurso.empty()){

             double promedio = calcularPromedio(notasCurso);
             double mediana = calcularMediana(notasCurso);
             double desviacion = calcularDesviacion(notasCurso);
             double maximo = calcularMaximo(notasCurso);
             double minimo = calcularMinimo(notasCurso);

             archivo <<"<tr>";
             archivo <<"<td>"<< cur.codigo << "</td>";
             archivo << "<td>"<< cur.nombre << "</td>";
             archivo << "<td>" << notasCurso.size() << "</td>";
             archivo << "<td>" << promedio << "</td>";
             archivo << "<td>" << mediana << "</td>";
             archivo << "<td>"<< desviacion << "</td>";
             archivo << "<td>" << maximo << "</td>";
             archivo << "<td>"<< minimo << "</td>";
             archivo << "</tr>"<<endl;
         }
     }

     archivo << "</table>"<<endl;
     archivo << "</body>"<<endl;
     archivo << "</html>"<<endl;

     archivo.close();

     cout <<"Reporte HTML generado correctamente."<<endl;
 }


 void generarReporteRendimientoEstudianteHTML() {

     ofstream archivo("reporte_estudiantes.html");

     if (!archivo.is_open()){
         cout <<"Error al crear el archivo HTML" << endl;
         return;
     }

     archivo << "<html>" << endl;
     archivo << "<head>" << endl;
     archivo << "<title>Reporte Rendimiento por Estudiante</title>" << endl;
     archivo << "</head>" << endl;
     archivo << "<body>" << endl;

     archivo <<"<h1>Rendimiento por Estudiante</h1>" << endl;

     archivo << "<table border='1'>" << endl;
     archivo << "<tr>";
     archivo << "<th>Carnet</th>";
     archivo << "<th>Nombre</th>";
     archivo << "<th>Carrera</th>";
     archivo << "<th>Semestre</th>";
     archivo << "<th>Promedio</th>";
     archivo << "<th>Aprobados</th>";
     archivo << "<th>Reprobados</th>";
     archivo << "<th>Creditos</th>";
     archivo << "</tr>"<<endl;

     for (Estudiante estu:estudiantes){

         vector<double> notasEstudiante;
         int aprobados=0;
         int reprobados=0;
         int creditosAcumulados= 0;

         for (Nota n:notas){

             if(n.carnet==estu.carnet) {
                 notasEstudiante.push_back(n.nota);

                 if (n.nota >= 61){
                     aprobados++;

                     for (Curso cur:cursos){
                         if (cur.codigo==n.codigoCurso) {
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

         if (!notasEstudiante.empty()){

             double promedio=calcularPromedio(notasEstudiante);

             archivo << "<tr>";
             archivo << "<td>"<< estu.carnet <<"</td>";
             archivo << "<td>"<< estu.nombre <<" " << estu.apellido << "</td>";
             archivo << "<td>"<< estu.carrera <<"</td>";
             archivo << "<td>"<< estu.semestre <<"</td>";
             archivo << "<td>"<< promedio <<"</td>";
             archivo << "<td>"<< aprobados <<"</td>";
             archivo << "<td>"<< reprobados <<"</td>";
             archivo << "<td>" << creditosAcumulados<<"</td>";
             archivo << "</tr>"<<endl;
         }
     }

     archivo << "</table>\n";
     archivo << "</body>" << endl;
     archivo << "</html>" << endl;

     archivo.close();
     cout << "Reporte de estudiantes generado correctamente.\n";
 }



 void generarReporteTop10HTML(){

     ofstream archivo("reporte_top10.html");
     if (!archivo.is_open()){
         cout <<"Error al crear el archivo HTML\n";
         return;
     }
     vector<Ranking>ranking;

     for (Estudiante estu:estudiantes){
         vector<double> notasEst;

         for (Nota n:notas){
             if (n.carnet==estu.carnet) {
                 notasEst.push_back(n.nota);
             }
         }
         if (!notasEst.empty()){
             Ranking r;
             r.carnet=estu.carnet;
             r.nombreCompleto = estu.nombre+ " " +estu.apellido;
             r.carrera=estu.carrera;
             r.semestre= estu.semestre;
             r.promedio= calcularPromedio(notasEst);

             ranking.push_back(r);
         }
     }

     sort(ranking.begin(), ranking.end(), [](Ranking a, Ranking b){
         return a.promedio>b.promedio;
         });

     archivo << "<html>"<<endl;
     archivo << "<head>"<<endl;
     archivo << "<title>Top 10 Estudiantes</title>" <<endl;
     archivo << "</head>" <<endl;
     archivo << "<body>" <<endl;
     archivo << "<h1>Top 10 Mejores Estudiantes</h1>" << endl;

     archivo << "<table border='1'>" << endl;
     archivo << "<tr>";
     archivo << "<th>Posicion</th>";
     archivo << "<th>Carnet</th>";
     archivo << "<th>Nombre</th>";
     archivo << "<th>Carrera</th>";
     archivo << "<th>Semestre</th>";
     archivo << "<th>Promedio</th>";
     archivo << "</tr>" << endl;

     for (int i=0; i<ranking.size()&&i<10; i++) {
         archivo << "<tr>";
         archivo <<"<td>" << i + 1 << "</td>";
         archivo <<"<td>" << ranking[i].carnet << "</td>";
         archivo <<"<td>" <<ranking[i].nombreCompleto << "</td>";
         archivo <<"<td>"<< ranking[i].carrera << "</td>";
         archivo << "<td>" << ranking[i].semestre <<"</td>";
         archivo <<"<td>"<< ranking[i].promedio <<"</td>";
         archivo <<"</tr>";
     }
     archivo << "</table>" << endl;
     archivo << "</body>" <<endl;
     archivo << "</html>" << endl;

     archivo.close();
     cout << "Reporte Top 10 generado correctamete." << endl;
 }



 void generarReporteMayorReprobacionHTML() {

     ofstream archivo("reporte_mayor_reprobacion.html");

     if (!archivo.is_open()) {
         cout << "Error al crear el archivo HTML" << endl;
         return;
     }

     vector<Reprobacion> lista;

     for (Curso cur :cursos) {
         int aprobados =0;
         int reprobados =0;

         for (Nota n:notas) {
             if (n.codigoCurso == cur.codigo) {
                 if (n.nota >= 61)
                     aprobados++;
                 else
                     reprobados++;
             }
         }

         int total=aprobados + reprobados;
         if (total> 0){

             Reprobacion r;
             r.codigo=cur.codigo;
             r.nombre =cur.nombre;
             r.total =total;
             r.aprobados=aprobados;
             r.reprobados= reprobados;
             r.porcentaje=(double)reprobados / total * 100;
             lista.push_back(r);
         }
     }
     sort(lista.begin(), lista.end(), [](Reprobacion a, Reprobacion b) {
         return a.porcentaje>b.porcentaje;
         });

     archivo << "<html>" << endl;
     archivo << "<head>" <<endl;
     archivo << "<title>Reporte Mayor Reprobacion</title>" << endl;
     archivo << "</head>" <<endl;
     archivo << "<body>" <<endl;
     archivo << "<h1>Cursos con Mayor Reprobacion</h1>" << endl;

     archivo << "<table border='1'>"<< endl;
     archivo << "<tr>";
     archivo << "<th>Codigo</th>";
     archivo << "<th>Curso</th>";
     archivo << "<th>Total</th>";
     archivo << "<th>Aprobados</th>";
     archivo << "<th>Reprobados</th>";
     archivo << "<th>% Reprobacion</th>";
     archivo << "</tr>" << endl;

     for (Reprobacion repro:lista){
         archivo << "<tr>";
         archivo << "<td>" << repro.codigo << "</td>";
         archivo << "<td>" << repro.nombre << "</td>";
         archivo << "<td>" << repro.total << "</td>";
         archivo << "<td>" << repro.aprobados << "</td>";
         archivo << "<td>" << repro.reprobados << "</td>";
         archivo << "<td>" << repro.porcentaje << "</td>";
         archivo << "</tr>" << endl;
     }

     archivo << "</table>" << endl;
     archivo << "</body>" << endl;
     archivo << "</html>" << endl;
     archivo.close();
     cout << "Reporte de mayor reprobacion generado correctamente.\n";
 }



 void generarReporteAnalisisCarreraHTML(){

     ofstream archivo("reporte_analisis_carrera.html");

     if (!archivo.is_open()){
         cout <<"Error al crear el archivo HTML\n";
         return;
     }
     archivo << "<html>" << endl;
     archivo << "<head>" << endl;
     archivo << "<title>Analisis por Carrera</title>" << endl;
     archivo << "</head>" << endl;
     archivo << "<body>" << endl;
     archivo << "<h1>Analisis por Carrera</h1>" << endl;

     archivo << "<table border='1'>" << endl;
     archivo << "<tr>";
     archivo << "<th>Carrera</th>";
     archivo << "<th>Total Estudiantes</th>";
     archivo << "<th>Promedio General</th>";
     archivo << "<th>Total Aprobados</th>";
     archivo << "<th>Total Reprobados</th>";
     archivo << "</tr>" << endl;

     for (Estudiante estu:estudiantes){
         string carreraActual=estu.carrera;

         int totalEstudiantes=0;
         int totalAprobados=0;
         int totalReprobados=0;
         vector<double> todasLasNotas;

         for (Estudiante e: estudiantes){

             if (e.carrera==carreraActual){
                 totalEstudiantes++;

                 for (Nota n:notas){
                     if (n.carnet==e.carnet){
                         todasLasNotas.push_back(n.nota);

                         if (n.nota>=61)
                             totalAprobados++;
                         else
                             totalReprobados++;
                     }
                 }
             }
         }

         if (totalEstudiantes >0) {

             double promedioGeneral=calcularPromedio(todasLasNotas);
             archivo << "<tr>";
             archivo << "<td>"<< carreraActual << "</td>";
             archivo << "<td>"<< totalEstudiantes << "</td>";
             archivo << "<td>"<<promedioGeneral << "</td>";
             archivo << "<td>"<< totalAprobados << "</td>";
             archivo << "<td>" << totalReprobados << "</td>";
             archivo << "</tr>" << endl;
         }

         for (Estudiante& e : estudiantes){
             if (e.carrera ==carreraActual) {
                 e.carrera="";
             }
         }
     }
     archivo << "</table>" << endl;
     archivo << "</body>" << endl;
     archivo << "</html>" << endl;

     archivo.close();
     cout << "Reporte de analsis por carrera generado correctmente." << endl;
 }



int main(){
	int opcion;
    do {
        cout << "====================================" << endl;
        cout << "   SISTEMA DE ANALISIS ACADEMICO" << endl;
        cout << "====================================" << endl;
        cout << "1. Cargar estudiantes" << endl;
        cout << "2. Cargar cursos" << endl;
        cout << "3. Cargar notas" << endl;
        cout << "4. Reporte: Estadisticas por curso" << endl;
        cout << "5. Reporte: Rendimiento por estudiante" << endl;
        cout << "6. Reporte: Top 10 estudiantes" << endl;
        cout << "7. Reporte: Cursos con mayor reprobacion" << endl;
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >>opcion;

        switch (opcion) {

        case 1:
            cargarEstudiantes();
            break;

        case 2:
            cargarCursos();
            break;

        case 3:
            cargarNotas();
            break;

        case 4:
            generarReporteEstadisticasCursoHTML();
            break;

        case 5:
            generarReporteRendimientoEstudianteHTML();
            break;

        case 6:
            generarReporteTop10HTML();
            break;

        case 7:
            generarReporteMayorReprobacionHTML();
            break;

        case 8:
            generarReporteAnalisisCarreraHTML();
            break;

        case 9:
            cout << "Saliendo del program."<<endl;
			break;

        default:
		    cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion!= 9);

    return 0;
}
