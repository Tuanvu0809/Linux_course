#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/CPU_parameter.h"
void get_cpu_usage() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return ;

    char line[256];
    unsigned long long user, nice, system, idle, iowait, irq, softirq;
    fgets(line, sizeof(line), fp);
    fclose(fp);

    sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle, &iowait, &irq, &softirq);

    unsigned long long total_time = user + nice + system + idle + irq + softirq;

    if (total_time == 0) return ;
     printf("Cpu percent total :%f per ",(float)( 100.0f * (total_time - (idle + iowait) ) / total_time));

}



void calculate_cpu_frequencies() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) {
        perror("Cannot open /proc/cpuinfo");
        return;
    }

    char line[256];
    int core_id = -1;

    printf("\n[CPU Frequencies]\n");
    while (fgets(line, sizeof(line), fp)) {

        if (strncmp(line, "processor", 9) == 0) {
            sscanf(line, "processor\t: %d", &core_id);
        }

        if (strncmp(line, "cpu MHz", 7) == 0 && core_id >= 0) {
            float Freq;
            sscanf(line, "cpu MHz\t: %f", &Freq);
            printf("Core %d: %.2f MHz\n", core_id, Freq);
            core_id = -1; 
        }
    }
    fclose(fp);
}



