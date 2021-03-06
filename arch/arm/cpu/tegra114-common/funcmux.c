/*
 * Copyright (c) 2010-2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Tegra114 high-level function multiplexing */

#include <common.h>
#include <asm/arch/clock.h>
#include <asm/arch/funcmux.h>
#include <asm/arch/pinmux.h>

int funcmux_select(enum periph_id id, int config)
{
	int bad_config = config != FUNCMUX_DEFAULT;

	switch (id) {
	case PERIPH_ID_UART4:
		switch (config) {
		case FUNCMUX_UART4_GMI:
			pinmux_set_func(PINGRP_GMI_A16, PMUX_FUNC_UARTD);
			pinmux_set_func(PINGRP_GMI_A17, PMUX_FUNC_UARTD);
			pinmux_set_func(PINGRP_GMI_A18, PMUX_FUNC_UARTD);
			pinmux_set_func(PINGRP_GMI_A19, PMUX_FUNC_UARTD);

			pinmux_set_io(PINGRP_GMI_A16, PMUX_PIN_OUTPUT);
			pinmux_set_io(PINGRP_GMI_A17, PMUX_PIN_INPUT);
			pinmux_set_io(PINGRP_GMI_A18, PMUX_PIN_INPUT);
			pinmux_set_io(PINGRP_GMI_A19, PMUX_PIN_OUTPUT);

			pinmux_tristate_disable(PINGRP_GMI_A16);
			pinmux_tristate_disable(PINGRP_GMI_A17);
			pinmux_tristate_disable(PINGRP_GMI_A18);
			pinmux_tristate_disable(PINGRP_GMI_A19);
			break;
		}
		break;

	/* Add other periph IDs here as needed */

	default:
		debug("%s: invalid periph_id %d", __func__, id);
		return -1;
	}

	if (bad_config) {
		debug("%s: invalid config %d for periph_id %d", __func__,
		      config, id);
		return -1;
	}
	return 0;
}
