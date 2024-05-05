/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "panoramix.h"

int main(int ac, char **av)
{
    panoramix_t *panoramix = parse_args(ac, av);

    if (!panoramix)
        return 84;
    destroy_panoramix(panoramix);
    return 0;
}
