/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#ifndef DRUID_H_
#define DRUID_H_
    #include <stddef.h>
    #include <pthread.h>
    #include <semaphore.h>
#include <stdbool.h>

typedef struct druid_s druid_t;
    #include "panoramix.h"

typedef struct druid_s {
    size_t remaining_refills;
    panoramix_t *panoramix;
    bool should_stop;
} druid_t;

druid_t *create_druid(size_t remaining_refills, panoramix_t *panoramix);
void refill_druid(druid_t *druid);
void destroy_druid(druid_t *druid);
void *run_druid(void *arg);
#endif /* !DRUID_H_ */