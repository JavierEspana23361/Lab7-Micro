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
    printf("- %s: %.2f\n", producto->nombre.c_str(), ingresos);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{   
    // Julio
    printf("\nREPORTE DEL MES DE JULIO\n");
    printf("---Monto Ventas por Producto---\n");
    Producto producto1 = {"Porción de pastel de chocolate", 300, 60.00, 20.00};
    Producto producto2 = {"White mocha", 400, 32.00, 19.20};
    Producto producto3 = {"Café americano 8oz", 1590, 22.00, 13.20};
    Producto producto4 = {"Latte 8onz ", 200, 24.00, 17.20};
    Producto producto5 = {"Toffee coffee", 390, 28.00, 20.10};
    Producto producto6 = {"Cappuccino 8onz", 1455, 24.00, 17.20};
    Producto producto7 = {"S'mores Latte", 800, 32.00, 23.00};
    Producto producto8 = {"Café tostado molido", 60, 60.00, 20.00};

    pthread_t hilo1, hilo2, hilo3, hilo4, hilo5, hilo6, hilo7, hilo8;

    pthread_create(&hilo1, NULL, calcular_ventas, (void *)&producto1);
    printf("Calculo hilo 1 iniciado\n");
    pthread_create(&hilo2, NULL, calcular_ventas, (void *)&producto2);
    printf("Calculo hilo 2 iniciado\n");
    pthread_create(&hilo3, NULL, calcular_ventas, (void *)&producto3);
    printf("Calculo hilo 3 iniciado\n");
    pthread_create(&hilo4, NULL, calcular_ventas, (void *)&producto4);
    printf("Calculo hilo 4 iniciado\n");
    pthread_create(&hilo5, NULL, calcular_ventas, (void *)&producto5);
    printf("Calculo hilo 5 iniciado\n");
    pthread_create(&hilo6, NULL, calcular_ventas, (void *)&producto6);
    printf("Calculo hilo 6 iniciado\n");
    pthread_create(&hilo7, NULL, calcular_ventas, (void *)&producto7);
    printf("Calculo hilo 7 iniciado\n");
    pthread_create(&hilo8, NULL, calcular_ventas, (void *)&producto8);
    printf("Calculo hilo 8 iniciado\n");

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);
    pthread_join(hilo5, NULL);
    pthread_join(hilo6, NULL);
    pthread_join(hilo7, NULL);
    pthread_join(hilo8, NULL);

    // Agosto
    printf("\nREPORTE DEL MES DE AGOSTO\n");
    printf("---Monto Ventas por Producto---\n");

    producto1.unidades_vendidas = 250;
    producto2.unidades_vendidas = 380;
    producto3.unidades_vendidas = 800;
    producto4.unidades_vendidas = 250;
    producto5.unidades_vendidas = 600;
    producto6.unidades_vendidas = 1200;
    producto7.unidades_vendidas = 1540;
    producto8.unidades_vendidas = 15;

    pthread_create(&hilo1, NULL, calcular_ventas, (void *)&producto1);
    pthread_create(&hilo2, NULL, calcular_ventas, (void *)&producto2);
    pthread_create(&hilo3, NULL, calcular_ventas, (void *)&producto3);
    pthread_create(&hilo4, NULL, calcular_ventas, (void *)&producto4);
    pthread_create(&hilo5, NULL, calcular_ventas, (void *)&producto5);
    pthread_create(&hilo6, NULL, calcular_ventas, (void *)&producto6);
    pthread_create(&hilo7, NULL, calcular_ventas, (void *)&producto7);
    pthread_create(&hilo8, NULL, calcular_ventas, (void *)&producto8);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);
    pthread_join(hilo5, NULL);
    pthread_join(hilo6, NULL);
    pthread_join(hilo7, NULL);
    pthread_join(hilo8, NULL);
    return 0;
}