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

#ifndef LIBSUPPORT_LOG_H
#define LIBSUPPORT_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

extern struct state {
	unsigned int v;
} __log_state;

enum __log_level {
	LOG_ERROR,
	LOG_INFO,
	LOG_DEBUG,
};

static inline bool __logv(unsigned int v)
{
	if (__atomic_load_n(&__log_state.v, __ATOMIC_ACQUIRE) >= v)
		return true;

	return false;
}

static inline void __logv_set(unsigned int v)
{
	__atomic_store_n(&__log_state.v, &v, __ATOMIC_RELEASE);
}

static inline void __attribute__((format(printf, 2, 3))) __log(unsigned int v, char const *fmt, ...)
{
	va_list va;

	if (!__logv(v))
		return;

	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}

#define __debug(fmt, ...) \
	__log(LOG_DEBUG, "%s (%s:%d): "fmt, __func__, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* LIBSUPPORT_LOG_H */
