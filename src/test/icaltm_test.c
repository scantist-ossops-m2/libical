/*======================================================================
 FILE: icaltm_test.c

 SPDX-FileCopyrightText: 2017 Red Hat, Inc. <www.redhat.com>

 SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0

 The Initial Developer of the Original Code is Milan Crha
======================================================================*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "libical/ical.h"

#include <pthread.h>

static icaltimezone *zone, *utc;

static void *test_tread()
{
    struct icaltimetype itt;
    int ii;

    itt = icaltime_from_string("19710203T040506");
    itt.zone = zone;

    for (ii = 0; ii < 200; ii++, itt.year++) {
        icaltime_convert_to_zone(itt, utc);
    }

    return NULL;
}

int main()
{
    pthread_t thread[2];
    int ii;

    zone = icaltimezone_get_builtin_timezone("America/New_York");
    utc = icaltimezone_get_utc_timezone();

    for (ii = 0; ii < 2; ii++) {
        pthread_create(&thread[ii], NULL, test_tread, NULL);
    }

    for (ii = 0; ii < 2; ii++) {
        pthread_join(thread[ii], NULL);
    }

    return 0;
}
