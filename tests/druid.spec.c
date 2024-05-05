/*
** EPITECH PROJECT, 2024
** Panoramix
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include "panoramix.h"

static void redirect_all_stds(void)
{
    cr_redirect_stdout();
    //cr_redirect_stderr();
}

void *launch_in_trhead(void *arg)
{
    panoramix_t *panoramix = (panoramix_t *)arg;

    launch_panoramix(panoramix);
    return NULL;
}

/*Test(druid, launch_then_stop, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(5, (char *[]){"./panoramix", "10", "10", "10", "10"});
    pthread_t test;

    cr_assert_not_null(panoramix);
    cr_assert_not_null(panoramix->druid);
    pthread_create(&test, NULL, &launch_in_trhead, panoramix);
    sleep(1);
    stop_panoramix(panoramix);
    pthread_join(test, NULL);
    cr_assert_stdout_eq_str("Druid: I'm ready... but sleepy...\n"
                            "Druid: I'm out of viscum. I'm going back to... zZz\n");
    destroy_panoramix(panoramix);
}*/

/*Test(druid, ask_for_refill, .init = redirect_all_stds)
{
    panoramix_t *panoramix = parse_args(5, (char *[]){"./panoramix", "10", "10", "10", "10"});
    pthread_t test;

    cr_assert_not_null(panoramix);
    cr_assert_not_null(panoramix->druid);
    pthread_create(&test, NULL, &launch_in_trhead, panoramix);
    sleep(1);
    cr_assert_stdout_eq_str("Druid: I'm ready... but sleepy...\n");
    if (sem_post(panoramix->sem) == -1) {
        cr_assert_fail();
    }
    sleep(1);
    cr_assert_stdout_eq_str("Druid: Ah! Yes, yes, yes, I'm awake! Working on it! Beware I can only make 9 more refills after this one!\n");
    stop_panoramix(panoramix);
    pthread_join(test, NULL);
    cr_assert_stdout_eq_str("Druid: I'm out of viscum. I'm going back to... zZz\n");
    destroy_panoramix(panoramix);
}*/
