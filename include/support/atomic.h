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

#ifndef LIBSUPPORT_ATOMIC_H
#define LIBSUPPORT_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define atomic_load_acquire(ptr) \
	__atomic_load_n(ptr, __ATOMIC_ACQUIRE)

#define atomic_cmpxchg(ptr, expected, desired) \
	__atomic_compare_exchange_n(ptr, &expected, desired, false, __ATOMIC_RELEASE, __ATOMIC_ACQUIRE)

/* sparse does not know about these gcc builtins */
#ifdef __CHECKER__
#define __atomic_load_n(ptr, memorder) (*(ptr))
#define __atomic_compare_exchange_n(ptr, expected, desired, weak, ok_memorder, fail_memorder) \
	({ *ptr = desired; })
#endif

#ifdef __cplusplus
}
#endif

#endif /* LIBSUPPORT_ATOMIC_H */
