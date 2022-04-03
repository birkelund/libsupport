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

#ifndef LIBSUPPORT_MMIO_H
#define LIBSUPPORT_MMIO_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * mmio_readle32 - read 4 bytes in memory-mapped register
 * @addr: memory-mapped register
 *
 * Return: read value (little endian)
 */
static inline leint32_t mmio_readle32(void __iomem *addr)
{
	/* memory-mapped register */
	return *(const volatile leint32_t __force *)addr;
}

/**
 * mmio_lh_readle64 - read 8 bytes in memory-mapped register
 * @addr: memory-mapped register
 *
 * Read the low 4 bytes first, then the high 4 bytes.
 *
 * Return: read value (little endian)
 */
static inline leint64_t mmio_lh_readle64(void __iomem *addr)
{
	uint32_t lo, hi;

	lo = *(const volatile uint32_t __force *)addr;
	hi = *(const volatile uint32_t __force *)(addr + 4);

	return (leint64_t __force)(((uint64_t)hi << 32) | lo);
}

#define mmio_readle64(addr) mmio_lh_readle64(addr)

/**
 * mmio_writele32 - write 4 bytes to memory-mapped register
 * @addr: memory-mapped register
 * @v: value to write (little endian)
 */
static inline void mmio_writele32(void __iomem *addr, leint32_t v)
{
	/* memory-mapped register */
	*(volatile leint32_t __force *)addr = v;
}

/**
 * mmio_lh_writele64 - write 8 bytes to memory-mapped register
 * @addr: memory-mapped register
 * @v: value to write (little endian)
 *
 * Write 8 bytes to memory-mapped register as two 4 byte writes (low bytes
 * first, then high).
 */
static inline void mmio_lh_writele64(void __iomem *addr, leint64_t v)
{
	mmio_writele32(addr, (leint32_t __force)v);
	mmio_writele32(addr + 4, (leint32_t __force)(v >> 32));
}

/**
 * mmio_hl_writele64 - write 8 bytes to memory-mapped register
 * @addr: memory-mapped register
 * @v: value to write (little endian)
 *
 * Write 8 bytes to memory-mapped register as two 4 byte writes (high bytes
 * first, then low).
 */
static inline void mmio_hl_writele64(void __iomem *addr, leint64_t v)
{
	mmio_writele32(addr + 4, (leint32_t __force)((uint64_t __force)v >> 32));
	mmio_writele32(addr, (leint32_t __force)v);
}

#ifdef __cplusplus
}
#endif

#endif /* LIBSUPPORT_MMIO_H */
