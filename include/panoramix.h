/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <stddef.h>

typedef struct panoramix_s {
    size_t pot_size;
    size_t pot_state;
} panoramix_t;

panoramix_t *parse_args(int ac, char **av);
void destroy_panoramix(panoramix_t *panoramix);
