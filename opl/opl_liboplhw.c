//
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2022 David Gow
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//     OPL interface based on liboplhw
//

#include "config.h"


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "opl.h"
#include "opl_internal.h"
#include "opl_timer.h"

#include <oplhw.h>

static oplhw_device *opl_device;

static int OPL_liboplhw_Init(unsigned int port_base)
{

    opl_device = oplhw_OpenDevice(NULL);

    if (!opl_device)
	    return 0;

    // Start callback thread

    if (!OPL_Timer_StartThread())
    {
        oplhw_CloseDevice(opl_device);
        return 0;
    }

    return 1;
}

static void OPL_liboplhw_Shutdown(void)
{
    // Stop callback thread

    OPL_Timer_StopThread();

    // Close the device
    oplhw_CloseDevice(opl_device);

}

static unsigned int OPL_liboplhw_PortRead(opl_port_t port)
{
    if (port == OPL_REGISTER_PORT_OPL3)
    {
        return 0xff;
    }

    return 0;
}

static uint8_t active_reg = 0x00;

static void OPL_liboplhw_PortWrite(opl_port_t port, unsigned int value)
{
    if (port == OPL_REGISTER_PORT)
	   active_reg = value;
    else
	   oplhw_Write(opl_device, active_reg, value); 
}

opl_driver_t opl_liboplhw_driver =
{
    "oplhw",
    OPL_liboplhw_Init,
    OPL_liboplhw_Shutdown,
    OPL_liboplhw_PortRead,
    OPL_liboplhw_PortWrite,
    OPL_Timer_SetCallback,
    OPL_Timer_ClearCallbacks,
    OPL_Timer_Lock,
    OPL_Timer_Unlock,
    OPL_Timer_SetPaused,
    OPL_Timer_AdjustCallbacks,
};


