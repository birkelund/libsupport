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

#ifndef LIBSUPPORT_COMPILER_H
#define LIBSUPPORT_COMPILER_H

#ifdef __cplusplus
extern "C" {
#endif

#define STATIC_ASSERT(x, msg) _Static_assert(!(x), msg)
#define STATIC_ASSERT_ON(x) STATIC_ASSERT_MSG(x, "not expecting: " #x)

#define barrier() asm volatile("" ::: "memory")

#if defined(__aarch64__)
# define rmb() asm volatile("dsb ld" ::: "memory")
# define wmb() asm volatile("dsb st" ::: "memory")
# define mb()  asm volatile("dsb sy" ::: "memory")
#elif defined(__x86_64__)
# define rmb() asm volatile("lfence" ::: "memory")
# define wmb() asm volatile("sfence" ::: "memory")
# define mb()  asm volatile("mfence" ::: "memory")
#else
# error unsupported architecture
#endif

/* force volatile access */
#define LOAD(x) (*(const volatile typeof(x) *)&(x))

/* force volatile access */
#define STORE(x, val) (*(volatile typeof(x) *)&(x) = (val))

#define likely(cond) __builtin_expect(!!(cond), 1)
#define unlikely(cond) __builtin_expect(!!(cond), 0)

#ifdef __CHECKER__
# define __iomem	__attribute__((noderef, address_space(__iomem)))
# define __private	__attribute__((noderef))
# define __force	__attribute__((force))
# define ACCESS_PRIVATE(p, member) (*((typeof((p)->member) __force *) &(p)->member))
#else
# define __iomem
# define __private
# define __force
# define ACCESS_PRIVATE(p, member) ((p)->member)
#endif

#ifdef __cplusplus
}
#endif

#endif /* LIBSUPPORT_COMPILER_H */
