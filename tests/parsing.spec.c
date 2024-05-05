/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "panoramix.h"

static void redirect_all_stds(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parsing, no_args, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(1, (char *[]){"./panoramix"});

    cr_assert_null(panoramix);
    cr_assert_stderr_eq_str("USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\nValues must be >0.\n");
}

Test(parsing, invalid_args, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(5, (char *[]){"./panoramix", "0", "0", "0", "0"});

    cr_assert_null(panoramix);
    cr_assert_stderr_eq_str("USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\nValues must be >0.\n");
}

Test(parsing, invalid_args_2, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(5, (char *[]){"./panoramix", "abc", "10", "10", "10"});

    cr_assert_null(panoramix);
    cr_assert_stderr_eq_str("USAGE: ./panoramix <nb_villagers> <pot_size> "
        "<nb_fights> <nb_refills>\nValues must be >0.\n");
}

Test(parsing, valid_args, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(5, (char *[]){"./panoramix", "10", "10", "10", "10"});

    cr_assert_not_null(panoramix);
    cr_assert_eq(panoramix->pot_size, 10);
    cr_assert_eq(panoramix->pot_state, 10);
    cr_assert_not_null(panoramix->sem);
    cr_assert_not_null(panoramix->mutex);
    cr_assert_not_null(panoramix->druid);
    cr_assert_eq(panoramix->druid->remaining_refills, 10);
    //TODO update this test
    destroy_panoramix(panoramix);
}
