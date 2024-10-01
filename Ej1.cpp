#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <unistd.h>  // Para sleep
#include <mutex>     // Para mutex

struct Producto {
    std::string nombre;
    int unidades_vendidas;
    double precio_unitario;
    double costo_fijo_por_unidad;
};

// Estructura para pasar tanto el producto como el índice a la función de los hilos
struct DatosHilo {
    Producto* producto;
    int indice;
};

std::mutex mtx;  // Mutex para proteger la consola

// Arrays para almacenar las ventas y utilidades por producto
double ventas[8];
double utilidades[8];

// Función que calcula las ventas y utilidad de un producto
void* calcular_ventas(void* arg) {
    DatosHilo* datos = (DatosHilo*)arg;

    // Simular tiempo de procesamiento
    sleep(1);

    // Calcular ventas y utilidad
    double ingresos = datos->producto->unidades_vendidas * datos->producto->precio_unitario;
    double utilidad = ingresos - (datos->producto->unidades_vendidas * datos->producto->costo_fijo_por_unidad);

    // Bloqueo del mutex para evitar acceso concurrente a los arrays y consola
    mtx.lock();
    ventas[datos->indice] = ingresos;
    utilidades[datos->indice] = utilidad;

    printf("Calculo de ventas para el producto '%s' iniciado...\n", datos->producto->nombre.c_str());
    printf("Calculo de ventas para el producto '%s' terminado.\n", datos->producto->nombre.c_str());
    mtx.unlock();

    pthread_exit(NULL);
    return NULL;
}

// Función para generar el reporte
void generar_reporte(Producto productos[], const char* mes) {
    double total_ventas = 0;
    double total_utilidad = 0;
    
    printf("\n------------------------------------------\n");
    printf("REPORTE DEL MES DE %s\n", mes);
    printf("--- Monto Ventas por Producto ---\n");
    
    for (int i = 0; i < 8; ++i) {
        printf("- %s: Q%.2f\n", productos[i].nombre.c_str(), ventas[i]);
        total_ventas += ventas[i];
    }
    
    printf("--- Utilidad por Producto ---\n");
    for (int i = 0; i < 8; ++i) {
        printf("%s: Q%.2f\n", productos[i].nombre.c_str(), utilidades[i]);
        total_utilidad += utilidades[i];
    }

    printf("\n--- Monto Total Ventas del Mes: Q%.2f\n", total_ventas);
    printf("--- Utilidad del mes: Q%.2f\n", total_utilidad);
    printf("------------------------------------------\n");
}

int main() {
    // Datos de productos para julio
    Producto productos[8] = {
        {"Porción de pastel de chocolate", 300, 60.00, 20.00},
        {"White mocha", 400, 32.00, 19.20},
        {"Café americano 8oz", 1590, 22.00, 13.20},
        {"Latte 8oz", 200, 24.00, 17.20},
        {"Toffee coffee", 390, 28.00, 20.10},
        {"Cappuccino 8oz", 1455, 24.00, 17.20},
        {"S'mores Latte", 800, 32.00, 23.00},
        {"Café tostado molido", 60, 60.00, 20.00}
    };
    
    pthread_t hilos[8];
    DatosHilo datos[8];

    // Crear hilos para calcular ventas de julio
    for (int i = 0; i < 8; ++i) {
        datos[i].producto = &productos[i];
        datos[i].indice = i;
        pthread_create(&hilos[i], NULL, calcular_ventas, (void*)&datos[i]);
        printf("Calculo hilo %d iniciado\n", i);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 8; ++i) {
        pthread_join(hilos[i], NULL);
    }

    // Generar reporte de julio
    generar_reporte(productos, "JULIO");

    // Actualizar datos de productos para agosto
    int unidades_agosto[8] = {250, 380, 800, 250, 600, 1200, 1540, 15};
    for (int i = 0; i < 8; ++i) {
        productos[i].unidades_vendidas = unidades_agosto[i];
    }

    // Reiniciar el índice de arrays de ventas y utilidades
    for (int i = 0; i < 8; ++i) {
        ventas[i] = 0;
        utilidades[i] = 0;
    }

    // Crear hilos para calcular ventas de agosto
    for (int i = 0; i < 8; ++i) {
        datos[i].producto = &productos[i];
        datos[i].indice = i;
        pthread_create(&hilos[i], NULL, calcular_ventas, (void*)&datos[i]);
        printf("Calculo hilo %d iniciado\n", i);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 8; ++i) {
        pthread_join(hilos[i], NULL);
    }

    // Generar reporte de agosto
    generar_reporte(productos, "AGOSTO");

    return 0;
}
