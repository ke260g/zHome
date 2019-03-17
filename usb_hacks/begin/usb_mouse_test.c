#include<stdio.h>
#include<libusb.h>

libusb_device **get_usb_dev_via_id(libusb_device **dev, /* original list */
    const int VendorID, const int ProductID,
    int *dev_num /* found devices number */
) {

}

int open_mouse(void) {
    libusb_context *ctx; // libusb session
    libusb_device **devs; // usb deivce list
    libusb_device_handle *dev_handle; //a device handle
    ssize_t cnt; // number of usb devices in list
    int ret, i, j;
    int size;
    unsigned char datain[1024]="\0";

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

#define VendorID (0x1c4f)
#define ProductID (0x0051)
    dev_handle = // my 1c4f:0051 SiGma Micro USB mouse
        libusb_open_device_with_vid_pid(
            ctx, VendorID, ProductID);
    if(dev_handle == NULL) {
        perror("Cannot open usb device handle");
        libusb_free_device_list(devs, 1); //free the list, unref the devices in it
        libusb_exit(ctx);                 //close the session
        return -1;
    }
    printf("usb mouse Opened\n");
    //free the list, unref the devices in it
    libusb_free_device_list(devs, 1);

    if(libusb_kernel_driver_active(dev_handle, 0) == 1) {
        //find out if kernel driver is attached
        printf("Kernel Driver Active\n");
        if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
            printf("Kernel Driver Detached!\n");
    }

    //claim interface 0 (the first) of device (mine had jsut 1)
    ret = libusb_claim_interface(dev_handle, 0);
    if(ret < 0) {
        printf("Cannot Claim Interface\n");
        return -1;
    }
    printf("Claimed Interface\n");
    for(i = 0; i < 300; i++) {
        int rr = libusb_interrupt_transfer(dev_handle,
                0x81,
                datain,
                0x0004,
                &size,
                1000);
        printf("libusb_interrupt_transfer rr: %d.\n", rr);
        printf("size: %d.\n", size);
        printf("data: ");
        for(j = 0; j < size; j++)
            printf("%02x ", (unsigned char)(datain[j]));
        printf("\n");
    }

    ret = libusb_release_interface(dev_handle, 0); //release the claimed interface
    if(ret != 0) {
        printf("Cannot Release Interface.\n");
        printf("Force Quit!\n");
        return 1;
    }
    printf("Released Interface.\n");

    libusb_attach_kernel_driver(dev_handle, 0); // attach back to kernel
    libusb_close(dev_handle); // close usb handle
    libusb_exit(ctx); // close libusb session
    return 0;
}

int main(int argc, char **argv) {
    open_mouse();
    return 0;
}
