/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <printf.h>
#include <stdio.h>
#include "druid.h"

druid_t *create_druid(size_t remaining_refills, panoramix_t *panoramix)
{
    druid_t *druid = malloc(sizeof(druid_t));

    if (!druid)
        return NULL;
    druid->remaining_refills = remaining_refills;
    druid->panoramix = panoramix;
    druid->should_stop = false;
    return druid;
}

void refill_druid(druid_t *druid)
{
    if (druid->remaining_refills == 0 || druid->should_stop)
        return;
    printf("Druid: Ah! Yes, yes, yes, I'm awake! Working on it! Beware I can"
        " only make %zu more refills after this one!\n",
        druid->remaining_refills - 1);
    fflush(stdout);
    druid->remaining_refills--;
    druid->panoramix->pot_state = druid->panoramix->pot_size;
}

void destroy_druid(druid_t *druid)
{
    free(druid);
}

void *run_druid(void *arg)
{
    druid_t *druid = (druid_t *)arg;

    printf("Druid: I'm ready... but sleepy...\n");
    fflush(stdout);
    while (druid->remaining_refills > 0 && !druid->should_stop) {
        if (sem_wait(druid->panoramix->sem) == -1) {
            break;
        }
        refill_druid(druid);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    fflush(stdout);
    return NULL;
}
