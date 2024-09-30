#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t candado; // mutex para proteger la sección crítica
pthread_cond_t cond; // variable de condición para sincronizar los hilos

int silo = 0; // lbs de café tostada en el silo
int bodega = 0; // lbs de café en la bodega

void *tostadora(void *arg) // función que simula la producción de café tostada
{
    int id = *((int *)arg); // obtener el id de la tostadora
    for (int i = 0; i < 200; i++) { // ciclo de producción de 200 lbs de café tostada
        sleep(1); // simula el tiempo de producción
        pthread_mutex_lock(&candado); // bloquea el mutex para proteger la sección crítica
        silo++; // incrementa en 1 lb la cantidad de café tostada en el silo
        printf("Tostadura %d produjo: 1 lb de café tostada\n", id); 
        pthread_cond_signal(&cond); // despierta a la empacadora
        pthread_mutex_unlock(&candado); // desbloquea el mutex
    }
    return NULL;
}

void *empacadora(void *arg) // función que simula la producción de bolsas de café
{
    while (bodega < 400) { // ciclo de producción de bolsas de café
        pthread_mutex_lock(&candado); // bloquea el mutex para proteger la sección crítica
        while (silo < 5 && bodega < 400) { // si no hay suficiente café en el silo, la empacadora espera
            pthread_cond_wait(&cond, &candado); // bloquea a la empacadora
        }
        if (silo >= 5) { // si hay suficiente café en el silo, la empacadora produce 5 bolsas de 1 lb de café
            for (int i = 0; i < 5; i++) { // ciclo de producción de 5 bolsas de café
                silo--; // decrementa en 1 lb la cantidad de café en el silo
                bodega++; // incrementa en 1 lb la cantidad de café en la bodega
                printf("Empacadora produjo: 1 bolsa de 1 lb de café\n");
                printf("Lbs de café en silo: %d\n", silo); 
                printf("Lbs de café en bodega: %d\n", bodega);
            }
        }
        pthread_mutex_unlock(&candado); // desbloquea el mutex
    }
    return NULL;
}

int main()
{
    pthread_t hilo_tostadora1, hilo_tostadora2, hilo_empacadora; // hilos para las tostadoras y la empacadora
    int id_tostadora1 = 1, id_tostadora2 = 2; // IDs para cada tostadora
    
    pthread_mutex_init(&candado, NULL); // inicializa el mutex candado
    pthread_cond_init(&cond, NULL); // inicializa la variable de condición cond
    
    pthread_create(&hilo_tostadora1, NULL, tostadora, &id_tostadora1); // crea el hilo de la tostadora 1
    pthread_create(&hilo_tostadora2, NULL, tostadora, &id_tostadora2); // crea el hilo de la tostadora 2
    pthread_create(&hilo_empacadora, NULL, empacadora, NULL); // crea el hilo de la empacadora

    pthread_join(hilo_tostadora1, NULL); // espera a que termine el hilo de la tostadora 1
    pthread_join(hilo_tostadora2, NULL); // espera a que termine el hilo de la tostadora 2
    pthread_join(hilo_empacadora, NULL); // espera a que termine el hilo de la empacadora
    
    pthread_cond_destroy(&cond); // destruye la variable de condición cond
    pthread_mutex_destroy(&candado); // destruye el mutex candado

    return 0;
}
