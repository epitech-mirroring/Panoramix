/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "villager.h"

villager_t *create_villager(size_t remaining_fights, size_t index,
    panoramix_t *panoramix)
{
    villager_t *villager = calloc(1, sizeof(villager_t));

    if (!villager)
        return NULL;
    villager->panoramix = panoramix;
    villager->remaining_fights = remaining_fights;
    villager->index = index;
    return villager;
}

static void ask_for_potion(villager_t *villager)
{
    if (villager->panoramix->pot_state == 0 &&
        villager->panoramix->druid->remaining_refills > 0) {
        printf("Villager %zu: Hey Pano wake up! We need more potion.\n",
            villager->index);
        sem_post(villager->panoramix->sem);
        while (villager->panoramix->pot_state == 0) {
            usleep(5);
        }
    }
}

static void go_fight(villager_t *villager)
{
    villager->panoramix->pot_state--;
    pthread_mutex_unlock(villager->panoramix->mutex);
    printf("Villager %zu: Take that roman scum! Only %zu left.\n",
        villager->index, villager->remaining_fights - 1);
    villager->remaining_fights--;
}

void *run_villager(void *arg)
{
    villager_t *villager = (villager_t *) arg;

    printf("Villager %zu: Going into battle!\n", villager->index);
    while (villager->remaining_fights > 0) {
        pthread_mutex_lock(villager->panoramix->mutex);
        printf("Villager %zu: I need a drink... I see %zu servings left.\n",
            villager->index, villager->panoramix->pot_state);
        ask_for_potion(villager);
        if (villager->panoramix->druid->remaining_refills == 0 &&
            villager->panoramix->pot_state == 0) {
            pthread_mutex_unlock(villager->panoramix->mutex);
            break;
        }
        go_fight(villager);
    }
    printf("Villager %zu: I'm going to sleep now.\n", villager->index);
    return NULL;
}

void destroy_villager(villager_t *villager)
{
    free(villager);
}
