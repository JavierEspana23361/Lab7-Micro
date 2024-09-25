#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <string>

struct Producto
{
    std::string nombre;
    int unidades_vendidas;
    double precio_unitario;
    double costo_fijo_por_unidad;
};

// Funcion que calcula las ventas de un producto (ingresos)
void *calcular_ventas(void *arg)
{
    Producto *producto = (Producto *)arg;
    double ingresos = producto->unidades_vendidas * producto->precio_unitario;
    printf("Ingresos por ventas de %s: %.2f\n", producto->nombre.c_str(), ingresos);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{
    Producto producto1 = {"Producto 1", 100, 10.5, 2.5};
    Producto producto2 = {"Producto 2", 200, 15.5, 3.5};

    pthread_t hilo1, hilo2;

    pthread_create(&hilo1, NULL, calcular_ventas, (void *)&producto1);
    pthread_create(&hilo2, NULL, calcular_ventas, (void *)&producto2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    return 0;
}