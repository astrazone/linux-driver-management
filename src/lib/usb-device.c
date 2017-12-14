/*
 * This file is part of linux-driver-management.
 *
 * Copyright © 2016-2017 Ikey Doherty
 *
 * linux-driver-management is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#define _GNU_SOURCE

#include "usb-device.h"
#include "ldm-private.h"
#include "util.h"

struct _LdmUSBDeviceClass {
        LdmDeviceClass parent_class;
};

/*
 * LdmUSBDevice
 *
 * An LdmUSBDevice is a specialised implementation of the #LdmDevice which
 * is aware of USB interfaces
 */
struct _LdmUSBDevice {
        LdmDevice parent;
};

G_DEFINE_TYPE(LdmUSBDevice, ldm_usb_device, LDM_TYPE_DEVICE)

/**
 * ldm_usb_device_dispose:
 *
 * Clean up a LdmUSBDevice instance
 */
static void ldm_usb_device_dispose(GObject *obj)
{
        G_OBJECT_CLASS(ldm_usb_device_parent_class)->dispose(obj);
}

/**
 * ldm_usb_device_class_init:
 *
 * Handle class initialisation
 */
static void ldm_usb_device_class_init(LdmUSBDeviceClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->dispose = ldm_usb_device_dispose;
}

/**
 * ldm_usb_device_init:
 *
 * Handle construction of the LdmUSBDevice
 */
static void ldm_usb_device_init(LdmUSBDevice *self)
{
        LdmDevice *ldm = LDM_DEVICE(self);
        ldm->os.devtype |= LDM_DEVICE_TYPE_USB;
}

/**
 * ldm_usb_device_init_private:
 * @device: The udev device that we're being created from
 *
 * Handle USB specific initialisation
 */
void ldm_usb_device_init_private(LdmDevice *self, udev_device *device)
{
        const gchar *devtype = NULL;

        /* Is this a USB interface? If so, we're gonna need a parent. */
        devtype = udev_device_get_devtype(device);
        if (devtype && g_str_equal(devtype, "usb_interface")) {
                self->os.attributes |= LDM_DEVICE_ATTRIBUTE_INTERFACE;
        }
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
