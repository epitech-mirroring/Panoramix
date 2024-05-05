/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef PANORAMIX_H_
#define PANORAMIX_H_
    #include <stddef.h>
    #include <semaphore.h>
    typedef struct panoramix_s panoramix_t;
    #include "druid.h"

typedef struct panoramix_s {
    size_t pot_size;
    size_t pot_state;
    sem_t *sem;
    pthread_mutex_t *mutex;
    druid_t *druid;
    pthread_t druid_thread;
    pthread_t *villagers_threads;
} panoramix_t;

panoramix_t *parse_args(int ac, char **av);
void destroy_panoramix(panoramix_t *panoramix);
void launch_panoramix(panoramix_t *panoramix);
void stop_panoramix(panoramix_t *panoramix);
#endif /* !PANORAMIX_H_ */
