#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>

#define REFRESH_SECONDS 2
#define MAX_PROCESSES 20

/* =========================================================
   CPU USAGE
   ========================================================= */

void get_cpu_usage()
{
    FILE *fp = fopen("/proc/stat", "r");

    if (fp == NULL)
    {
        perror("Cannot open /proc/stat");
        return;
    }

    char line[512];

    unsigned long long user = 0;
    unsigned long long nice = 0;
    unsigned long long system = 0;
    unsigned long long idle = 0;
    unsigned long long iowait = 0;
    unsigned long long irq = 0;
    unsigned long long softirq = 0;
    unsigned long long steal = 0;

    if (fgets(line, sizeof(line), fp) != NULL)
    {
        sscanf(line,
               "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &user,
               &nice,
               &system,
               &idle,
               &iowait,
               &irq,
               &softirq,
               &steal);

        unsigned long long idle_time = idle + iowait;

        unsigned long long total_time =
            user + nice + system + idle +
            iowait + irq + softirq + steal;

        if (total_time > 0)
        {
            double usage =
                ((double)(total_time - idle_time) /
                 (double)total_time) * 100.0;

            printf("CPU Usage       : %.2f%%\n", usage);
        }
    }

    fclose(fp);
}

/* =========================================================
   MEMORY INFORMATION
   ========================================================= */

void get_memory_usage()
{
    FILE *fp = fopen("/proc/meminfo", "r");

    if (fp == NULL)
    {
        perror("Cannot open /proc/meminfo");
        return;
    }

    char line[256];

    long total = 0;
    long available = 0;
    long free_memory = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (sscanf(line, "MemTotal: %ld kB", &total) == 1)
        {
            continue;
        }

        if (sscanf(line, "MemAvailable: %ld kB", &available) == 1)
        {
            continue;
        }

        if (sscanf(line, "MemFree: %ld kB", &free_memory) == 1)
        {
            continue;
        }
    }

    if (total > 0)
    {
        double used_percentage =
            ((double)(total - available) /
             (double)total) * 100.0;

        printf("Memory Usage    : %.2f%%\n",
               used_percentage);

        printf("Total Memory    : %.2f GB\n",
               total / (1024.0 * 1024.0));

        printf("Available Memory: %.2f GB\n",
               available / (1024.0 * 1024.0));

        printf("Free Memory     : %.2f GB\n",
               free_memory / (1024.0 * 1024.0));
    }

    fclose(fp);
}

/* =========================================================
   SYSTEM UPTIME
   ========================================================= */

void get_uptime()
{
    FILE *fp = fopen("/proc/uptime", "r");

    if (fp == NULL)
    {
        perror("Cannot open /proc/uptime");
        return;
    }

    double uptime = 0.0;
    double idle_time = 0.0;

    if (fscanf(fp, "%lf %lf", &uptime, &idle_time) == 2)
    {
        int hours = (int)uptime / 3600;
        int minutes = ((int)uptime % 3600) / 60;
        int seconds = (int)uptime % 60;

        printf("System Uptime   : %02d:%02d:%02d\n",
               hours,
               minutes,
               seconds);
    }

    fclose(fp);
}

/* =========================================================
   PROCESS INFORMATION
   ========================================================= */

void get_process_information()
{
    DIR *proc_dir = opendir("/proc");

    if (proc_dir == NULL)
    {
        perror("Cannot open /proc");
        return;
    }

    struct dirent *entry;

    int process_count = 0;

    printf("\n");
    printf("%-8s %-8s %-12s %-25s\n",
           "PID",
           "STATE",
           "MEMORY",
           "PROCESS");

    printf("------------------------------------------------------------\n");

    while ((entry = readdir(proc_dir)) != NULL)
    {
        /*
         * Process directories inside /proc
         * have numeric names.
         */
        if (!isdigit((unsigned char)entry->d_name[0]))
        {
            continue;
        }

        char status_path[512];

        int written = snprintf(status_path,
                                sizeof(status_path),
                                "/proc/%s/status",
                                entry->d_name);

        if (written < 0 ||
            (size_t)written >= sizeof(status_path))
        {
            continue;
        }

        FILE *fp = fopen(status_path, "r");

        if (fp == NULL)
        {
            /*
             * A process may terminate while
             * we are reading its information.
             */
            continue;
        }

        char line[512];

        char process_name[128] = "Unknown";
        char state = '?';

        long memory = 0;

        while (fgets(line, sizeof(line), fp) != NULL)
        {
            if (strncmp(line, "Name:", 5) == 0)
            {
                sscanf(line,
                       "Name:\t%127[^\n]",
                       process_name);
            }

            else if (strncmp(line, "State:", 6) == 0)
            {
                sscanf(line,
                       "State:\t%c",
                       &state);
            }

            else if (strncmp(line, "VmRSS:", 6) == 0)
            {
                sscanf(line,
                       "VmRSS:\t%ld",
                       &memory);
            }
        }

        fclose(fp);

        printf("%-8s %-8c %-8ld KB   %-25s\n",
               entry->d_name,
               state,
               memory,
               process_name);

        process_count++;

        if (process_count >= MAX_PROCESSES)
        {
            break;
        }
    }

    closedir(proc_dir);

    printf("\nProcesses Displayed: %d\n",
           process_count);
}

/* =========================================================
   MAIN PROGRAM
   ========================================================= */

int main()
{
    while (1)
    {
        /*
         * Clear terminal screen before
         * displaying the latest information.
         */
        system("clear");

        printf("\n");
        printf("============================================================\n");
        printf("                    KERNEL MONITOR\n");
        printf("============================================================\n");

        printf("Monitor PID      : %d\n",
               getpid());

        time_t current_time = time(NULL);

        printf("Current Time     : %s",
               ctime(&current_time));

        printf("\n");
        printf("---------------- SYSTEM INFORMATION ----------------\n");

        get_uptime();

        get_memory_usage();

        printf("\n");
        printf("---------------- CPU INFORMATION --------------------\n");

        get_cpu_usage();

        printf("\n");
        printf("---------------- PROCESS INFORMATION ----------------\n");

        get_process_information();

        printf("\n");
        printf("============================================================\n");
        printf("Refreshing every %d seconds...\n",
               REFRESH_SECONDS);

        printf("Press CTRL+C to exit.\n");

        sleep(REFRESH_SECONDS);
    }

    return 0;
}
