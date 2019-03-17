#include<stdio.h>
#include<libusb.h>

void print_dev(libusb_device *dev) {
    struct libusb_device_descriptor desc;
    int ret,
        i, j, k; /* counter */
    int bus_number;
    struct libusb_config_descriptor *config_desc; // configuration list
    struct libusb_interface iface;
    struct libusb_interface_descriptor iface_desc;
    struct libusb_endpoint_descriptor ep_desc;

    ret = libusb_get_device_descriptor(dev, &desc);
    if(ret < 0) {
        printf("failed to get device desriptor.\n");
        return;
    }
    libusb_get_config_descriptor(dev, 0, &config_desc);
#if 1
    do {
    if(desc.idVendor == 0x14cd && desc.idProduct == 0x1212)
        break;
/*
    if(desc.idVendor == 0x04f2 && desc.idProduct == 0xb398)
        break;
    else if(desc.idVendor == 0x105b && desc.idProduct == 0xe065)
        break;
*/
    else
        return;
    } while(0);
#endif
    printf("Class: %3d ", (int)desc.bDeviceClass);
    printf("Bus %03d ", (int)libusb_get_bus_number(dev));
    printf("Port %03d ", (int)libusb_get_port_number(dev));
    //printf("VendorID:ProductID %03x:%04x ",
    printf("ID %04x:%04x ",
        desc.idVendor, desc.idProduct);

    printf("\n\tConfiguration Number %2d ", // Configuration Numbers
        (int)desc.bNumConfigurations);

    printf("Interface Number%2d ", (int)config_desc->bNumInterfaces);

    for(i = 0; i < (int)config_desc->bNumInterfaces; i++) {
        iface = config_desc->interface[i];
        printf("\n\t\tiface[%d] num_set(iface_desc) %2d ", i, iface.num_altsetting);

        for(j = 0; j < iface.num_altsetting; j++) {
            iface_desc = iface.altsetting[j];
            printf("\n\t\t\tiface_desc[%d] iface_num %d #", j, iface_desc.bInterfaceNumber);
            printf(" endpoint_number %d ", iface_desc.bNumEndpoints);

            for(k = 0; k < iface_desc.bNumEndpoints; k++) {
                ep_desc = iface_desc.endpoint[k];
                printf("\n\t\t\t\tep_desc[%d] Type %d ##", k, ep_desc.bDescriptorType);
                printf(" EndpointAddress %d ", ep_desc.bEndpointAddress);
            }
        }
    }

    printf("\n");
}

int main(int argc, char **argv) {
    libusb_device **devs; // pointer to device pointer list.
    libusb_context *ctx; // libusb session
    ssize_t cnt; // number of usb devices in list
    int ret, i;

    // session init
    ret = libusb_init(&ctx);
    if(ret < 0) {
        perror("libusb_init() error");
        return 1;
    }
    libusb_set_debug(ctx, 3); // verbosity level as suggested

    // get list
    cnt = libusb_get_device_list(ctx, &devs);
    if(cnt < 0) {
        perror("libusb_get_device_list()");
        return 0;
    }
    printf("%d usb devices in list.\n", (int)cnt);

    // enumerate all the device
    for(i = 0; i < cnt; i++)
        print_dev(devs[i]);

    libusb_free_device_list(devs, 1);  // free the list
    libusb_exit(ctx); // close session
    return 0;
}
