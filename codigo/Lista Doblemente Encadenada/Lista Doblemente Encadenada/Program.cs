using System;

class Nodo
{
    public int Dato;
    public Nodo Anterior;
    public Nodo Siguiente;

    public Nodo(int dato)
    {
        Dato =dato;
        Anterior =null;
        Siguiente =null;
    }
}

class ListaDoblementeEnlazada
{
    private Nodo primero;
    private Nodo ultimo;

    public ListaDoblementeEnlazada()
    {
        primero=null;
        ultimo=null;
    }


    public void Insertar(int dato)
    {
        Nodo nuevo = new Nodo(dato);

        if (primero==null)
        {
            primero = nuevo;
            ultimo = nuevo;
        }
        else
        {
            ultimo.Siguiente = nuevo;
            nuevo.Anterior = ultimo;
            ultimo = nuevo;
        }
    }


    public void ExtraerNodo(int valor)
    {
        if (primero==null)
        {
            Console.WriteLine("Lista vacía");
            return;
        }

        Nodo actual = primero;

        // Buscar el nodo
        while (actual != null &&actual.Dato!=valor)
        {
            actual = actual.Siguiente;
        }

        if (actual ==null)
        {
            Console.WriteLine("Nodo no encontrado");
            return;
        }

        if (actual==primero && actual == ultimo)
        {
            primero = null;
            ultimo = null;
        }

        else if (actual == primero)
        {
            primero = actual.Siguiente;
            primero.Anterior = null;
        }

        else if (actual == ultimo)
        {
            ultimo = actual.Anterior;
            ultimo.Siguiente = null;
        }

        else
        {
            actual.Anterior.Siguiente = actual.Siguiente;
            actual.Siguiente.Anterior = actual.Anterior;
        }

        Console.WriteLine("Nodo eliminado correctamente");
    }


    public void MostrarLista()
    {
        Nodo actual=primero;

        while (actual!=null)
        {
            Console.Write(actual.Dato + " <-> ");
            actual = actual.Siguiente;
        }

        Console.WriteLine("NULL");
    }
}

class Program
{
    static void Main()
    {
        ListaDoblementeEnlazada lista=new ListaDoblementeEnlazada();
        lista.Insertar(10);
        lista.Insertar(20);
        lista.Insertar(30);
        lista.Insertar(40);

        Console.WriteLine("Lista origial:");
        lista.MostrarLista();

        lista.ExtraerNodo(30);

        Console.WriteLine("Lista depués de eliminar 30:");
        lista.MostrarLista();
    }
}
