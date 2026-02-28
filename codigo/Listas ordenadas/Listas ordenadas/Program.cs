using System;

namespace ListaOrdenadaTDA
{
    public class TipoElemento
    {
        public int Clave;
        public string Dato;

        public TipoElemento(int clave, string dato)
        {
            Clave=clave;
            Dato =dato;
        }
    }

    public class Nodo
    {
        public TipoElemento Info;
        public Nodo Sig;

        public Nodo(TipoElemento elem)
        {
            Info = elem;
            Sig = null;
        }
    }

    // TDA Lista Ordenada
    public class ListaOrdenada
    {
        private Nodo primero;

        public ListaOrdenada()
        {
            primero = null;
        }

        private int ComparaElemento(TipoElemento A, TipoElemento B)
        {
            if (A.Clave < B.Clave)
                return -1;

            else if (A.Clave==B.Clave)
                return 0;

            else
                return 1;
        }

 
        public void Insertar(TipoElemento nuevo)
        {
            Nodo nuevoNodo=new Nodo(nuevo);
            // Caso 1: lista vacía
            if (primero ==null)
            {
                primero=nuevoNodo;
                return;
            }

            // Caso 2: insertar al inicio
            if (ComparaElemento(nuevo, primero.Info) < 0)
            {
                nuevoNodo.Sig =primero;
                primero =nuevoNodo;
                return;
            }

            // Caso 3: insertar en medio o final
            Nodo actual = primero;

            while (actual.Sig != null &&
                   ComparaElemento(nuevo, actual.Sig.Info) > 0)
            {
                actual=actual.Sig;
            }

            nuevoNodo.Sig= actual.Sig;
            actual.Sig =nuevoNodo;
        }


        public void Mostrar()
        {
            Nodo actual=primero;
            while (actual!=null)
            {
                Console.WriteLine("Clave: " + actual.Info.Clave + " Dato: " + actual.Info.Dato);
                actual=actual.Sig;
            }
        }
    }
}
