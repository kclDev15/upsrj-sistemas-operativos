#include <stdio.h>
#include "process.h"

int main() {
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    int time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        // Buscar el proceso disponible con menor burst_time
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= time) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
            }
        }

        // Si no hay proceso disponible, avanzar el tiempo
        if (idx == -1) {
            time++;
            continue;
        }

        // Ejecutar el proceso seleccionado
        p[idx].waiting_time = time - p[idx].arrival_time;
        time += p[idx].burst_time;
        p[idx].turnaround_time = time - p[idx].arrival_time;
        p[idx].completed = 1;

        completed++;
    }

    print_results(p, n, "SJF Scheduling");
    return 0;
}
