/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* hello world example: calling functions from a static library */


#include <zephyr.h>
#include <stdio.h>

#include <zenoh_pico.h>

void main(void)
{
	printf("Hello World!\n");
	zenoh_pico_hello_world();
}
