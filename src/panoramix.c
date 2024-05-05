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
    write(2, "USAGE: ./panoramix <nb_villagers> <pot_size>"
        "<nb_fights> <nb_refills>\n", 70);
    write(2, "Values must be >0.\n", 19);
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
    panoramix->pot_size = strtol(av[2], NULL, 10);
    panoramix->pot_state = panoramix->pot_size;
    return panoramix;
}

void destroy_panoramix(panoramix_t *panoramix)
{
    free(panoramix);
}
