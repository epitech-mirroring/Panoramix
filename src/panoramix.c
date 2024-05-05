/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "panoramix.h"

static bool is_number(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

static void print_usage(void)
{
    write(2, "USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\n", strlen(
            "USAGE: ./panoramix <nb_villagers> <pot_size> "
            "<nb_fights> <nb_refills>\n"));
    write(2, "Values must be >0.\n", strlen("Values must be >0.\n"));
}

static bool are_args_valid(int ac, char **av)
{
    if (ac != 5)
        return false;
    for (int i = 1; i < ac; i++)
        if (!is_number(av[i]) || strtol(av[i], NULL, 10) <= 0)
            return false;
    return true;
}

void init_panoramix(char *const *av, panoramix_t *panoramix)
{
    panoramix->pot_size = strtol(av[2], NULL, 10);
    panoramix->pot_state = panoramix->pot_size;
    panoramix->sem = malloc(sizeof(sem_t));
    panoramix->mutex = malloc(sizeof(pthread_mutex_t));
    panoramix->druid = create_druid(strtol(av[4], NULL, 10), panoramix);
    panoramix->villager_count = strtol(av[1], NULL, 10);
    panoramix->villagers = calloc(panoramix->villager_count,
        sizeof(villager_t *));
    panoramix->villagers_threads = calloc(panoramix->villager_count,
        sizeof(pthread_t));
    for (size_t i = 0; i < panoramix->villager_count; i++) {
        panoramix->villagers[i] = create_villager(strtol(av[3], NULL, 10), i,
            panoramix);
    }
}

panoramix_t *parse_args(int ac, char **av)
{
    panoramix_t *panoramix = NULL;

    if (!are_args_valid(ac, av)) {
        print_usage();
        return NULL;
    }
    panoramix = malloc(sizeof(panoramix_t));
    if (!panoramix)
        return NULL;
    init_panoramix(av, panoramix);
    if (!panoramix->sem || !panoramix->druid) {
        destroy_panoramix(panoramix);
        return NULL;
    }
    sem_init(panoramix->sem, 0, 0);
    pthread_mutex_init(panoramix->mutex, NULL);
    return panoramix;
}

void destroy_panoramix(panoramix_t *panoramix)
{
    if (!panoramix)
        return;
    if (panoramix->sem)
        sem_destroy(panoramix->sem);
    if (panoramix->mutex)
        pthread_mutex_destroy(panoramix->mutex);
    if (panoramix->druid)
        destroy_druid(panoramix->druid);
    for (size_t i = 0; i < panoramix->villager_count; i++) {
        destroy_villager(panoramix->villagers[i]);
    }
    free(panoramix->villagers);
    free(panoramix->villagers_threads);
    free(panoramix);
}

void launch_panoramix(panoramix_t *panoramix)
{
    pthread_create(&panoramix->druid_thread, NULL, &run_druid,
        panoramix->druid);
    for (size_t i = 0; i < panoramix->villager_count; i++) {
        pthread_create(&panoramix->villagers_threads[i], NULL, &run_villager,
            panoramix->villagers[i]);
    }
    for (size_t i = 0; i < panoramix->villager_count; i++) {
        pthread_join(panoramix->villagers_threads[i], NULL);
    }
    pthread_join(panoramix->druid_thread, NULL);
}

void stop_panoramix(panoramix_t *panoramix)
{
    panoramix->druid->should_stop = true;
    sem_post(panoramix->sem);
}
