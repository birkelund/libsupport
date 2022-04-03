// SPDX-License-Identifier: LGPL-2.1-or-later

/*
 * This file is part of libsupport.
 *
 * Copyright (C) 2022 Klaus Jensen <its@irrelevant.dk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#include <errno.h>
#include <execinfo.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "support/mem.h"

void backtrace_abort(void)
{
	void *buf[10];
	char **symbols = NULL;
	int size;

	size = backtrace(buf, 10);
	symbols = backtrace_symbols(buf, size);

	if (symbols) {
		fprintf(stderr, "fatal error; dumping maximum %d stack frames\n", size);

		for (int i = 0; i < size; i++)
			fprintf(stderr, "[%d]: %s\n", i, symbols[i]);
	}

	free(symbols);

	abort();
}
