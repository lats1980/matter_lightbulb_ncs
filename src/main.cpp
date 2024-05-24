/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include "app_task.h"

#include <zephyr/logging/log.h>

#if DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart)
#include <zephyr/drivers/uart.h>
#include <zephyr/usb/usb_device.h>
#endif

LOG_MODULE_REGISTER(app, CONFIG_CHIP_APP_LOG_LEVEL);

#if DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart)
static int InitUSB()
{
    int err = usb_enable(nullptr);

    if (err)
    {
        LOG_ERR("Failed to initialize USB device");
    }

    return 0;
}
#endif

int main()
{
	CHIP_ERROR err = CHIP_NO_ERROR;

#if DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart)
    err = chip::System::MapErrorZephyr(InitUSB());
#endif

    if (err == CHIP_NO_ERROR)
    {
        err = AppTask::Instance().StartApp();
    }

	LOG_ERR("Exited with code %" CHIP_ERROR_FORMAT, err.Format());
	return err == CHIP_NO_ERROR ? EXIT_SUCCESS : EXIT_FAILURE;
}
