/* SPDX-License-Identifier: LGPL-2.1-or-later */

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

#ifndef LIBSUPPORT_MEM_H
#define LIBSUPPORT_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

#define ALIGN_UP(x, m) (((x) + (m) - 1) & ~((m) - 1))

void backtrace_abort(void);

static inline bool would_overflow(unsigned int n, size_t sz)
{
	return n > SIZE_MAX / sz;
}

static inline void *zmalloc(size_t sz)
{
	return calloc(1, sz);
}

static inline void *nmalloc(unsigned int n, size_t sz)
{
	if (would_overflow(n, sz)) {
		fprintf(stderr, "allocation of %d * %zu bytes would overflow\n", n, sz);

		backtrace_abort();
	}

	return malloc(n * sz);
}

static inline void *znmalloc(unsigned int n, size_t sz)
{
	if (would_overflow(n, sz)) {
		fprintf(stderr, "allocation of %d * %zu bytes would overflow\n", n, sz);

		backtrace_abort();
	}

	return zmalloc(n * sz);
}

#ifdef __cplusplus
}
#endif

#endif /* LIBSUPPORT_MEM_H */
