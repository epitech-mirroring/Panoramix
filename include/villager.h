/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef VILLAGER_H_
    #define VILLAGER_H_
    #include <stddef.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>
typedef struct villager_s villager_t;
    #include "panoramix.h"

typedef struct villager_s {
    size_t remaining_fights;
    size_t index;
    panoramix_t *panoramix;
} villager_t;

villager_t *create_villager(size_t remaining_fights, size_t index,
    panoramix_t *panoramix);
void destroy_villager(villager_t *villager);
void *run_villager(void *arg);
#endif /* !DRUID_H_ */
