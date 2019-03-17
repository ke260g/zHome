#include<stdio.h>
#include<libusb.h>
#include<string.h>

int port_arr[7];
void print_dev(libusb_device *dev) {
    int ret,
        i, j, k; /* counter */
    int bus_number;
    int config;
#define PORT_LENGTH (7)
    struct libusb_device *parent;
    struct libusb_device_descriptor desc;
    struct libusb_config_descriptor *config_desc; // configuration list
    struct libusb_interface iface;
    struct libusb_interface_descriptor iface_desc;
    struct libusb_endpoint_descriptor ep_desc;
    struct libusb_device_handle *handler;
    char description[1024];

    ret = libusb_get_device_descriptor(dev, &desc);
    if(ret < 0) {
        printf("failed to get device desriptor.\n");
        return;
    }
#if 1 /* ax516 ezusb */
    libusb_get_config_descriptor(dev, 0, &config_desc);
    do {
    if(desc.idVendor == 0x04b4 && desc.idProduct == 0x1004)
        break;
    if(desc.idVendor == 0xface && desc.idProduct == 0x0050)
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
#else /* DaHeng cystal */
    libusb_get_config_descriptor(dev, 0, &config_desc);
    do {
    if(desc.idVendor == 0x4448 && desc.idProduct == 0x5670)
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
    libusb_open(dev, &handler);
    ret = libusb_get_configuration(handler, &config);
    if(!ret)
        printf("active_config:%d ", config);
    else
        printf("get config error ");

#if 1
    if(desc.iManufacturer >= 0) {
        memset(description, 0, 1024);
        libusb_get_string_descriptor_ascii(
            handler, desc.iManufacturer, description, 1024);
        printf("%s ", description);
    }
    if(desc.iProduct >= 0) {
        memset(description, 0, 1024);
        libusb_get_string_descriptor_ascii(
            handler, desc.iProduct, description, 1024);
        printf("%s ", description);
    }
#endif

#if 0 /* parent, speed */
    parent = libusb_get_parent(dev);
    printf("sf:%p pr:%p ", dev, parent); // self and parent
    printf("addr:%d ", libusb_get_device_address(dev));
    printf("speed:%d ", libusb_get_device_speed(dev));
#endif

#if 1 /* print info */
    ret = libusb_get_port_numbers(dev, (uint8_t *)port_arr, PORT_LENGTH);
    printf("\n\t>>>Port List: ");
    for(i = 0; i < ret; i++)
        printf("#%d ", port_arr[i]);
    printf("end");

    printf("\n\tConfiguration Number %2d ", // Configuration Numbers
        (int)desc.bNumConfigurations);
    printf("Interface Number%2d ", (int)config_desc->bNumInterfaces);
    if(config_desc->iConfiguration >= 0) {
        memset(description, 0, 1024);
        libusb_get_string_descriptor_ascii(
                handler, config_desc->iConfiguration, description, 1024);
        printf("%s ", description);
    }

    for(i = 0; i < (int)config_desc->bNumInterfaces; i++) {
        iface = config_desc->interface[i];
        printf("\n\t\tiface[%d] num_set(iface_desc) %2d ", i, iface.num_altsetting);

        for(j = 0; j < iface.num_altsetting; j++) {
            iface_desc = iface.altsetting[j];
            printf("\n\t\t\tiface_desc[%d] iface_num %d #", j, iface_desc.bInterfaceNumber);

            printf("class %03d ", iface_desc.bInterfaceClass);
            printf(" endpoint_number %d ", iface_desc.bNumEndpoints);
            for(k = 0; k < iface_desc.bNumEndpoints; k++) {
                ep_desc = iface_desc.endpoint[k];
                printf("\n\t\t\t\tep_desc[%d] Type %d ##", k, ep_desc.bDescriptorType);
                printf(" EndpointAddress 0x%x ", ep_desc.bEndpointAddress);
                printf(" size %d-bytes ", ep_desc.wMaxPacketSize);
            }
        }
    }
#endif
    libusb_set_interface_alt_setting(handler, 0, 2);
    printf("\n");
    unsigned char data[512];
    unsigned int bytes_transferred;

    ret = libusb_control_transfer(handler,
            0x00, 0xB1, 0x0000, 0x0000, NULL, 0x0000, 200);
    perror("control bRequest: 0xB1\n");
    printf("control transfer ret is %d\n", ret);
    getchar();

    ret = libusb_control_transfer(handler,
            0x00, 0xB1, 0x0000, 0x0000, NULL, 0x0000, 200);
    perror("control bRequest: 0xB1\n");
    printf("control transfer ret is %d\n", ret);
    getchar();

#if 0 /* 3 x 512 bytes bulk packets read from 0x86 */
    ret = libusb_bulk_transfer(handler, 0x86, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();

    ret = libusb_bulk_transfer(handler, 0x86, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();

    ret = libusb_bulk_transfer(handler, 0x86, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();
#endif

    ret = libusb_control_transfer(handler,
            0x00, 0xB0, 0x0000, 0x0000, NULL, 0x0000, 200);
    perror("control bRequest: 0xB0\n");
    printf("control transfer ret is %d\n", ret);
    getchar();

#if 1 /* 3 x 512 bytes bulk packets write to 0x2 */
    ret = libusb_bulk_transfer(handler, 0x2, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();

    ret = libusb_bulk_transfer(handler, 0x2, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();

    ret = libusb_bulk_transfer(handler, 0x2, data, 512, &bytes_transferred, 100);
    perror("bulk_transfer\n");
    printf("0x1 bulk transfer bytes: %d ret is %d\n", bytes_transferred, ret);
    getchar();
#endif
    ret = libusb_control_transfer(handler,
            0x00, 0xB0, 0x0000, 0x0000, NULL, 0x0000, 200);
    perror("control bRequest: 0xB0\n");
    printf("control transfer ret is %d\n", ret);
    getchar();

    libusb_close(handler);
}

int libusb_instance(void) {
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

int main(int argc, char **argv) {
    libusb_instance();
    return 0;
}
