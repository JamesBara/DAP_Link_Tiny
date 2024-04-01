#include "usbd.h"
#include "stm32l412_def.h"
#include "stm32l412.h"
#include "rcc.h"

#define USBD_RECIPIENT_POS (0x0U)
#define USBD_TYPE_POS (0x5U)
#define USBD_DIR_POS (0x7U)

#define USBD_RECIPIENT_MASK (0x1FU << USBD_RECIPIENT_POS)
#define USBD_TYPE_MASK (0x3U << USBD_TYPE_POS)
#define USBD_DIR_MASK (0x1U << USBD_DIR_POS)

#define USBD_DEVICE (0x0U)
#define USBD_INTERFACE (0x1U)
#define USBD_ENDPOINT (0x2U)
#define USBD_OTHER (0x3U)

#define USBD_DEVICE_MASK (USBD_DEVICE << USBD_RECIPIENT_POS)
#define USBD_INTERFACE_MASK (USBD_INTERFACE << USBD_RECIPIENT_POS)
#define USBD_ENDPOINT_MASK (USBD_ENDPOINT << USBD_RECIPIENT_POS)
#define USBD_OTHER_MASK (USBD_OTHER << USBD_RECIPIENT_POS)

#define USBD_STANDARD (0x0U << USBD_TYPE_POS)
#define USBD_CLASS (0x1U << USBD_TYPE_POS)
#define USBD_VENDOR (0x2U << USBD_TYPE_POS)


#define USBD_GET_STATUS (0x0U)  
#define USBD_CLEAR_FEATURE (0x1U)
#define USBD_SET_FEATURE (0x3U)
#define USBD_SET_ADDRESS (0x5U)
#define USBD_GET_DESCRIPTOR (0x6U)
#define USBD_SET_DESCRIPTOR (0x7U)
#define USBD_GET_CONFIGURATION (0x8U)
#define USBD_SET_CONFIGURATION (0x9U)
#define USBD_GET_INTERFACE (0xAU)
#define USBD_SET_INTERFACE (0xBU)
#define USBD_SYNCH_FRAME (0xCU)

#define USBD_DESC_TYPE_DEVICE (0x1U)
#define USBD_DESC_TYPE_CONF (0x2U)
#define USBD_DESC_TYPE_STRING (0x3U)
#define USBD_DESC_TYPE_INTERFACE (0x4U)
#define USBD_DESC_TYPE_ENDPOINT (0x5U)
#define USBD_DESC_TYPE_BOS (0xFU)
#define USBD_DESC_TYPE_DEV_CAP (0x10U)

struct usbd_transaction_data_type
{
	uint8_t *buffer;
	uint32_t leftover;
};

struct __attribute__((packed)) usbd_std_device_descriptor_type
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
};

struct __attribute__((packed)) usbd_conf_descriptor
{
	struct
	{
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint16_t wTotalLength;
		uint8_t bNumInterfaces;
		uint8_t bConfigurationValue;
		uint8_t iConfiguration;
		uint8_t bmAttributes;
		uint8_t bMaxPower;
	}__attribute__((packed)) usbd_std_configuration_descriptor_type;
	struct
	{
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bInterfaceNumber;
		uint8_t bAlternateSetting;
		uint8_t bNumEndpoints;
		uint8_t bInterfaceClass;
		uint8_t bInterfaceSubClass;
		uint8_t bInterfaceProtocol;
		uint8_t iInterface;
	} __attribute__((packed)) usbd_std_interface_descriptor_type;
	struct
	{
		uint8_t bLength;
		uint8_t bDescriptorType;
		uint8_t bEndpointAddress;
		uint8_t bmAttributes;
		uint16_t wMaxPacketSize;
		uint8_t bInterval;
	}__attribute__((packed)) usbd_std_endpoint_descriptor_type[2];
};

struct __attribute__((packed)) usbd_string_descriptor_zero_type
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wLangID;
};

struct __attribute__((packed)) usbd_manufacturer_string_descriptor_type
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t str[20];
};


struct __attribute__((packed)) usbd_product_string_descriptor_type
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t str[28];
};

struct __attribute__((packed)) usbd_serial_num_string_descriptor_type
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t str[10];
};

struct __attribute__((packed)) usbd_bos_descriptor_type
{
	struct
	{
		uint8_t bLength;
		uint8_t	bDescriptorType;
		uint16_t wLength;
		uint8_t bNumDeviceCaps;
	}__attribute__((packed)) usbd_std_bos_descriptor_type;
	struct
	{
		uint8_t bLength;
		uint8_t	bDescriptorType;
		uint8_t bDevCapabilityType;
		uint8_t bReserved;
		uint8_t PlatformCapabilityUUID[16];
	}__attribute__((packed)) usbd_std_platform_capability_descriptor_type;
	struct
	{
		uint32_t dwWindowsVersion;
		uint16_t wMSOSDescriptorSetTotalLength;
		uint8_t bMS_VendorCode;
		uint8_t bAltEnumCode;
	}__attribute__((packed)) usbd_ms_os20_set_information_descriptor_type;
};

struct __attribute__((packed)) ms_os_20_descriptor
{
	struct
	{
		uint16_t wLength;
		uint16_t wDescriptorType;
		uint32_t dwWindowsVersion;
		uint16_t wTotalLength;
	}__attribute__((packed)) usbd_ms_os_20_set_header_type;
	struct
	{
		uint16_t wLength;
		uint16_t wDescriptorType;
		uint8_t CompatibleID[8];
		uint8_t SubCompatibleID[8];
	}__attribute__((packed)) usbd_ms_os_20_compatible_id_feature_type;
	struct
	{
		uint16_t wLength;
		uint16_t wDescriptorType;
		uint16_t wPropertyDataType;
		uint16_t wPropertyNameLength;
		uint8_t PropertyName[40];
		uint16_t wPropertyDataLength;
		uint8_t PropertyData[78];
	}__attribute__((packed)) usbd_ms_os_20_registry_property_feature_type;
};

typedef struct
{
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
}__attribute__((packed)) usbd_setup_packet_type;

static struct usbd_transaction_data_type ep0_xfer;
static const struct usbd_std_device_descriptor_type usbd_dev_desc =
{
	.bLength = sizeof(usbd_dev_desc),
	.bDescriptorType = USBD_DESC_TYPE_DEVICE,
	.bcdUSB = 0x0210U,
	.bDeviceClass = 0x0U,
	.bDeviceSubClass = 0x0U,
	.bDeviceProtocol = 0x0U,
	.bMaxPacketSize0 = USBD_FS_MAXPACKETSIZE,
	.idVendor = 0xC251U, /*!<Keil*/
	.idProduct = 0xF001U, /*!<DAP-Link*/
	.bcdDevice = 0x0100U,
	.iManufacturer = 0x0U,
	.iProduct = 0x1U,
	.iSerialNumber = 0x0U,
	.bNumConfigurations = 0x1U /*!<1 configuration.*/
};

static const struct usbd_conf_descriptor usbd_conf_desc =
{
	{
		.bLength = 0x9U, /*!<9 bytes.*/
		.bDescriptorType = USBD_DESC_TYPE_CONF,
		.wTotalLength = sizeof(usbd_conf_desc),
		.bNumInterfaces = 0x1U, /*!< 1 Interface.*/
		.bConfigurationValue = 0x1U, /*!< 1 Configuration.*/
		.iConfiguration = 0x0U,
		.bmAttributes = 0x80U, /*!< Bus powered, Remote wakeup is disabled.*/
		.bMaxPower = 0xFAU /*!< 250*2 = 500mA */
	},
	{
		.bLength = 0x9U, /*!<9 bytes.*/
		.bDescriptorType = USBD_DESC_TYPE_INTERFACE,
		.bInterfaceNumber = 0x0U,
		.bAlternateSetting = 0x0U,
		.bNumEndpoints = 0x2U,
		.bInterfaceClass = 0xFF, /*!<Vendor defined.*/
		.bInterfaceSubClass = 0x0U,
		.bInterfaceProtocol = 0x0U,
		.iInterface = 0x0U
	},
	{
		{
			.bLength = 0x7U, /*!<7 bytes.*/
			.bDescriptorType = USBD_DESC_TYPE_ENDPOINT,
			.bEndpointAddress = USBD_ENDPOINT_1,
			.bmAttributes = 0x2U, /*!<Bulk.*/
			.wMaxPacketSize = USBD_FS_MAXPACKETSIZE,
			.bInterval = 0x0U
		},
		{
			.bLength = 0x7U, /*!<7 bytes.*/
			.bDescriptorType = USBD_DESC_TYPE_ENDPOINT,
			.bEndpointAddress = (0x80U | USBD_ENDPOINT_2),
			.bmAttributes = 0x2U, /*!<Bulk.*/
			.wMaxPacketSize = USBD_FS_MAXPACKETSIZE,
			.bInterval = 0x0U
		}
	}
};

static const struct usbd_string_descriptor_zero_type usbd_str0_desc =
{
	.bLength = sizeof(usbd_str0_desc),
	.bDescriptorType = USBD_DESC_TYPE_STRING,
	.wLangID = 0x409U /*!<English US.*/
};

#if 0
static const struct usbd_manufacturer_string_descriptor_type usbd_manuf_desc =
{
	.bLength = sizeof(usbd_manuf_desc),
	.bDescriptorType = USBD_DESC_TYPE_STRING,
	.str = {'L', 0, 'e', 0, 'm', 0, 'o', 0, 'n', 0, 0x20, 0, 'P', 0, 'i', 0, 'l', 0 ,'l', 0}
};
#endif

static const struct usbd_product_string_descriptor_type usbd_product_desc =
{
	.bLength = sizeof(usbd_product_desc),
	.bDescriptorType = USBD_DESC_TYPE_STRING,
	.str = {'C', 0, 'M', 0, 'S', 0, 'I', 0, 'S', 0, '-', 0, 'D', 0, 'A', 0, 'P', 0, 0x20, 0, 'T', 0, 'i', 0 , 'n', 0, 'y', 0}
};

#if 0
static const struct usbd_serial_num_string_descriptor_type usbd_serial_num_desc =
{
	.bLength = sizeof(usbd_serial_num_desc),
	.bDescriptorType = USBD_DESC_TYPE_STRING, 
	.str = {'0', 0, '0', 0, '0', 0, '0', 0, '0', 0}
};
#endif

static const struct usbd_bos_descriptor_type usbd_bos_desc =
{
	{
		.bLength = 0x5U, /*!<5 bytes.*/
		.bDescriptorType = USBD_DESC_TYPE_BOS,
		.wLength = sizeof(usbd_bos_desc),
		.bNumDeviceCaps = 0x1U /*!< 1 BOS Device Capability */
	},
	{
		.bLength = 0x1C,
		.bDescriptorType = USBD_DESC_TYPE_DEV_CAP, /*<! Device capability.*/
		.bDevCapabilityType = 0x5U, /*<! Platform capability.*/
		.bReserved = 0x0U,
		.PlatformCapabilityUUID = {0xDF, 0x60, 0xDD, 0xD8, 0x89, 0x45, 0xC7, 0x4C, 0x9C, 0xD2, 0x65, 0x9D, 0x9E, 0x64, 0x8A, 0x9F} /*<! CMSIS-DAP UUID.*/
	},
	{
		.dwWindowsVersion = 0x0A000000UL, /*Windows 10*/
		.wMSOSDescriptorSetTotalLength = 158U, /*<! Size of the ms os descriptor.*/
		.bMS_VendorCode = 0x1U,
		.bAltEnumCode = 0x0U
	}
};

static const struct ms_os_20_descriptor ms_os_desc =
{
	{
		.wLength = 10U,
		.wDescriptorType = 0x0U, /*<! Set header descriptor.*/
		.dwWindowsVersion = 0x0A000000UL, /*<! Windows 10.*/
		.wTotalLength = sizeof(ms_os_desc)
	},
	{
		.wLength = 20U,
		.wDescriptorType = 0x3U, /*<! Feature compatible id*/
		.CompatibleID = {'W', 'I', 'N', 'U', 'S', 'B', 0, 0},
		.SubCompatibleID = {0, 0, 0, 0, 0, 0, 0, 0}
	},
	{
		.wLength = 128U,
		.wDescriptorType = 0x4U, /*<! Feature register propery.*/
		.wPropertyDataType = 0x1U, /*<! REG_SZ*/
		.wPropertyNameLength = 40U,
		.PropertyName = {'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0,
		'r', 0, 'f', 0, 'a', 0, 'c', 0, 'e', 0, 'G', 0, 'U', 0, 'I', 0, 'D', 0, 0, 0},
		.wPropertyDataLength = 78U,
		.PropertyData = {'{', 0, 'C', 0, 'D', 0, 'B', 0, '3', 0, 'B', 0, '5', 0, 'A', 0, 'D', 0, '-', 0,
		'2', 0, '9', 0, '3', 0, 'B', 0, '-', 0, '4', 0, '6', 0, '6', 0, '3', 0, '-', 0,
		'A', 0, 'A', 0, '3', 0, '6', 0, '-', 0, '1', 0, 'A', 0, 'A', 0, 'E', 0, '4', 0,
		'6', 0, '4', 0, '6', 0, '3', 0, '7', 0, '7', 0, '6', 0, '}', 0, 0, 0 }
	}
};


static void (*setup_cb)(usbd_callbacks *ep_cb);
static void (*stage_cb)(void);
static bool is_set_address;
static uint16_t dev_addr;



static void usbd_ep_0_write(void *buf, uint16_t sz);
static uint16_t usbd_ep_0_read(void *buf);

static void usbd_get_status(usbd_setup_packet_type setup);
static void usbd_clear_feature(usbd_callbacks *ep_cb, usbd_setup_packet_type setup);
static void usbd_set_feature(usbd_setup_packet_type setup);
static void usbd_set_address(usbd_setup_packet_type setup);
static void usbd_get_descriptor(usbd_setup_packet_type setup);
static void usbd_get_configuration(void);
static void usbd_set_configuration(usbd_callbacks *ep_cb, usbd_setup_packet_type setup);
static void usbd_get_interface(usbd_setup_packet_type setup);
static void usbd_ms_os(usbd_setup_packet_type setup);

static void usbd_default_setup(usbd_callbacks *ep_cb);
static void usbd_addressed_setup(usbd_callbacks *ep_cb);
static void usbd_configured_setup(usbd_callbacks *ep_cb);
static void usbd_data_in_stage(void);
static void usbd_status_in_stage(void);
static void usbd_status_out_stage(void);

static void usbd_ctr(usbd_callbacks *ep_cb, uint8_t ep, uint8_t dir, uint8_t setup);
static inline void usbd_reset(void);
static inline void usbd_suspend(void);
static inline void usbd_wakeup(void);


uint32_t dbg_cntr;

void usbd_copy_to_pma(uint8_t *src, uint16_t *dst, uint16_t sz)
{
	uint16_t half_cnt, tmp_val;
	half_cnt = (sz >> 0x1U);

	/*Copy to packet buffer area.*/
	while (half_cnt--)
	{
		tmp_val = (uint16_t)(*src);
		src++;
		tmp_val |= (((uint16_t)(*src)) << 0x8U);
		*dst = tmp_val;
		dst++;
		src++;
	}

	/*If the size is odd copy the leftover bytes.*/
	if (sz & 0x1U)
	{	
		tmp_val = (uint16_t)(*src);
		*dst = tmp_val;
	}
}

void usbd_read_from_pma(uint16_t *src, uint8_t *dst, uint16_t sz)
{
	uint16_t half_cnt, tmp_val;
	half_cnt = (sz >> 0x1U);

	/*Copy from packet buffer area.*/
	while (half_cnt--)
	{
		tmp_val = *src;
		*dst = (uint8_t)(tmp_val & 0xFFU);
		dst++;
		*dst = (uint8_t)((tmp_val & 0xFF00U) >> 0x8U);
		src++;
		dst++;
	}

	/*If the size is odd copy the leftover bytes.*/
	if (sz & 0x1U)
	{
		tmp_val = *src;
		*dst = (uint8_t)(tmp_val & 0xFFU);
	}
}

static void usbd_ep_0_write(void *buf, uint16_t sz)
{
	ASSERT(!(buf == NULL && sz));
	uint16_t *reg = USBD_ENDPOINT_0_TX_PMA_BUF;
	USBD_ENDPOINT_0_SET_TX_COUNT(sz);
	usbd_copy_to_pma((uint8_t*)buf, reg, sz);
	USBD_ENDPOINT_0_SET_TX_VALID();
}

static uint16_t usbd_ep_0_read(void* buf)
{
	ASSERT(buf != NULL);
	uint16_t *reg = USBD_ENDPOINT_0_RX_PMA_BUF;
	uint16_t cnt;
	cnt = USBD_ENDPOINT_0_GET_RX_COUNT();
	usbd_read_from_pma(reg, (uint8_t*)buf, cnt);
	USBD_ENDPOINT_0_SET_RX_VALID();
	return cnt;
}

static void usbd_get_status(usbd_setup_packet_type setup)
{
	uint8_t ep_num, buf[2] = { 0x0U, 0x0U };

	switch (setup.bmRequestType & USBD_RECIPIENT_MASK)
	{
	case USBD_DEVICE_MASK:
		/*Device is bus powered and remote wakeup is not supported.*/
		break;
	case USBD_INTERFACE_MASK:
		/*Only interface 0 is supported*/
		if (setup.wIndex & 0x7FU)
		{
			USBD_ENDPOINT_0_SET_STALL();
			return;
		}
		break;
	case USBD_ENDPOINT_MASK:
		ep_num = (setup.wIndex & 0xFU);
		switch (ep_num)
		{
		case USBD_ENDPOINT_1:
			buf[0] = USBD_ENDPOINT_1_GET_STALL();
			break;
		case USBD_ENDPOINT_2:
			buf[0] = USBD_ENDPOINT_2_GET_STALL();
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			return;
			break;
		}
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		return;
		break;
	}
	ep0_xfer.buffer = buf;
	ep0_xfer.leftover = 0x2U;
	stage_cb = usbd_data_in_stage;
	usbd_ep_0_write(ep0_xfer.buffer, ep0_xfer.leftover);
}

static void usbd_clear_feature(usbd_callbacks *ep_cb, usbd_setup_packet_type setup)
{
	uint8_t ep_num = (setup.wIndex & 0xFU);
	/*Remote wakeup is not supported.*/
	switch (setup.bmRequestType & USBD_RECIPIENT_MASK)
	{
	case USBD_ENDPOINT_MASK:
		switch (ep_num)
		{
		case USBD_ENDPOINT_1:
			USBD_ENDPOINT_1_CLEAR_STALL();
			ep_cb->usbd_endpoint_in();
			break;
		case USBD_ENDPOINT_2:
			USBD_ENDPOINT_2_CLEAR_STALL();
			ep_cb->usbd_endpoint_out();
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			return;
			break;
		}
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		return;
		break;
	}
	stage_cb = usbd_status_in_stage;
	USBD_ENDPOINT_0_TRANSMIT_ZLP();
}

static void usbd_set_feature(usbd_setup_packet_type setup)
{
	uint8_t ep_num = (setup.wIndex & 0xFU);
	/*Remote wakeup and test mode are not supported.*/
	switch (setup.bmRequestType & USBD_RECIPIENT_MASK)
	{
	case USBD_ENDPOINT_MASK:
		switch (ep_num)
		{
		case USBD_ENDPOINT_1:
			USBD_ENDPOINT_1_SET_STALL();
			break;
		case USBD_ENDPOINT_2:
			USBD_ENDPOINT_2_SET_STALL();
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			return;
			break;
		}
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		return;
	}
	stage_cb = usbd_status_in_stage;
	USBD_ENDPOINT_0_TRANSMIT_ZLP();
}

static void usbd_set_address(usbd_setup_packet_type setup)
{
	dev_addr = setup.wValue;
	is_set_address = true;
	stage_cb = usbd_status_in_stage;
	USBD_ENDPOINT_0_TRANSMIT_ZLP();
}



static void usbd_get_descriptor(usbd_setup_packet_type setup)
{
	switch ((((setup.wValue) >> 0x8U) & 0xFFU))
	{
	case USBD_DESC_TYPE_DEVICE:
		ep0_xfer.buffer = (uint8_t*)&usbd_dev_desc;
		ep0_xfer.leftover = sizeof(usbd_dev_desc);
		break;
	case USBD_DESC_TYPE_CONF:
		ep0_xfer.buffer = (uint8_t*)&usbd_conf_desc;
		ep0_xfer.leftover = sizeof(usbd_conf_desc);
		break;
	case USBD_DESC_TYPE_STRING:
		/*Only english us is available.*/
		if (setup.wIndex != 0x409 && (setup.wValue & 0xFF))
		{
			USBD_ENDPOINT_0_SET_STALL();
		}
		switch (setup.wValue & 0xFF)
		{
		case 0:
			ep0_xfer.buffer = (uint8_t*)&usbd_str0_desc; 
			ep0_xfer.leftover = sizeof(usbd_str0_desc);
			break;
		case 1:
			ep0_xfer.buffer = (uint8_t *)&usbd_product_desc;
			ep0_xfer.leftover = sizeof(usbd_product_desc);
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			break;
		}
		break;
	case USBD_DESC_TYPE_BOS:
		ep0_xfer.buffer = (uint8_t*)&usbd_bos_desc; 
		ep0_xfer.leftover = sizeof(usbd_bos_desc);
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		return;
		break;
	}

	/*Get the amount of bytes to be transmitted.*/
	ep0_xfer.leftover = _MACRO_MIN(setup.wLength, ep0_xfer.leftover);
	stage_cb = usbd_data_in_stage;
	usbd_ep_0_write(ep0_xfer.buffer, _MACRO_MIN(USBD_FS_MAXPACKETSIZE, ep0_xfer.leftover));
}


static void usbd_get_configuration(void)
{
	uint8_t buf = 0;
	if (setup_cb == usbd_configured_setup)
	{
		/*Only 1 configuration is valid*/
		buf = 1;
	}
	ep0_xfer.buffer = &buf;
	ep0_xfer.leftover = 0x1U;
	stage_cb = usbd_data_in_stage;
	usbd_ep_0_write(ep0_xfer.buffer, ep0_xfer.leftover);
}

static void usbd_set_configuration(usbd_callbacks *ep_cb, usbd_setup_packet_type setup)
{
	if (!(setup.wValue & 0xFFU))
	{
		USBD_CLEAR_ENDPOINT_1_CONFIGURATION();
		USBD_CLEAR_ENDPOINT_2_CONFIGURATION();
		setup_cb = usbd_addressed_setup;
	}
	else
	{
		/*There is only 1 configuration and 2 endpoints.*/
		USBD_SET_ENDPOINT_1_CONFIGURATION();
		USBD_SET_ENDPOINT_2_CONFIGURATION();
		setup_cb = usbd_configured_setup;
		if (ep_cb->dap_init != NULL)
		{
			ep_cb->dap_init();
		}
	}

	stage_cb = usbd_status_in_stage;
	USBD_ENDPOINT_0_TRANSMIT_ZLP();
}


static void usbd_get_interface(usbd_setup_packet_type setup)
{
	uint8_t buf = 0;
	/*There is only 1 interface with 1 alternate function. So return 0.*/
	/*Check if the interface is valid*/
	if (setup.wIndex & 0x7FU)
	{
		USBD_ENDPOINT_0_SET_STALL();
		return;
	}
	/*Prepare the buffer*/
	ep0_xfer.buffer = &buf;
	ep0_xfer.leftover = 0x1U;
	stage_cb = usbd_data_in_stage;
	usbd_ep_0_write(ep0_xfer.buffer, ep0_xfer.leftover);
}

static void usbd_ms_os(usbd_setup_packet_type setup)
{
	switch(setup.bRequest)
	{
	case 0x1U:
		switch(setup.wIndex)
		{
			/*MS OS descriptor index.*/
		case 0x7U:
			ep0_xfer.buffer = (uint8_t*)&ms_os_desc;
			ep0_xfer.leftover = _MACRO_MIN(setup.wLength, sizeof(ms_os_desc));
			stage_cb = usbd_data_in_stage;
			usbd_ep_0_write(ep0_xfer.buffer, _MACRO_MIN(USBD_FS_MAXPACKETSIZE, ep0_xfer.leftover));
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			break;
		}
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		break;
	}
}



static void usbd_default_setup(usbd_callbacks *ep_cb)
{
	(void)ep_cb;
	usbd_setup_packet_type setup = {0};

	if (usbd_ep_0_read((uint8_t*)&setup) != sizeof(usbd_setup_packet_type))
	{
		USBD_ENDPOINT_0_SET_STALL();
		return;
	}
//	__asm__("BKPT");
	switch (setup.bmRequestType & USBD_TYPE_MASK)
	{
		case (USBD_STANDARD):		
			switch(setup.bRequest)
			{
			case USBD_GET_DESCRIPTOR:
				usbd_get_descriptor(setup);
				break;
			case USBD_SET_ADDRESS:
				usbd_set_address(setup);
				break;
			default:
				USBD_ENDPOINT_0_SET_STALL();
				break;
			}
		break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
		break;
	}
}

static void usbd_addressed_setup(usbd_callbacks *ep_cb)
{
	usbd_setup_packet_type setup = {0};

	if (usbd_ep_0_read((uint8_t*)&setup) != sizeof(usbd_setup_packet_type))
	{
		USBD_ENDPOINT_0_SET_STALL();
		return;
	}

	switch (setup.bmRequestType & USBD_TYPE_MASK)
	{
	case (USBD_STANDARD):
		switch(setup.bRequest)
		{
		case USBD_GET_STATUS:
			usbd_get_status(setup);
			break;
		case USBD_CLEAR_FEATURE:
			usbd_clear_feature(ep_cb, setup);
			break;
		case USBD_SET_FEATURE:
			usbd_set_feature(setup);
			break;
		case USBD_GET_DESCRIPTOR:
			usbd_get_descriptor(setup);
			break;
		case USBD_SET_ADDRESS:
			usbd_set_address(setup);
			break;
		case USBD_GET_CONFIGURATION:
			usbd_get_configuration();
			break;
		case USBD_SET_CONFIGURATION:
			usbd_set_configuration(ep_cb, setup);
			break;
		default:
			USBD_ENDPOINT_0_SET_STALL();
			break;
		}
		break;
	case (USBD_VENDOR):
		usbd_ms_os(setup);
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		break;
	}
}

static void usbd_configured_setup(usbd_callbacks *ep_cb)
{
	usbd_setup_packet_type setup = {0};

	if (usbd_ep_0_read((uint8_t*)&setup) != sizeof(usbd_setup_packet_type))
	{
		USBD_ENDPOINT_0_SET_STALL();
		return;
	}

	switch (setup.bmRequestType & USBD_TYPE_MASK)
	{
	case (USBD_DEVICE_MASK):		
		switch(setup.bRequest)
		{
		case USBD_GET_STATUS:
			usbd_get_status(setup);
			break;
		case USBD_CLEAR_FEATURE:
			usbd_clear_feature(ep_cb, setup);
			break;
		case USBD_SET_FEATURE:
			usbd_set_feature(setup);
			break;
		case USBD_GET_DESCRIPTOR:
			dbg_cntr++;
			usbd_get_descriptor(setup);
			break;
		case USBD_GET_CONFIGURATION:
			usbd_get_configuration();
			break;
		case USBD_SET_CONFIGURATION:
			usbd_set_configuration(ep_cb, setup);
			break;
		case USBD_GET_INTERFACE:
			usbd_get_interface(setup);
			break;
		case USBD_SET_INTERFACE:
		case USBD_SYNCH_FRAME:
		default:
			USBD_ENDPOINT_0_SET_STALL();
			break;
		}
		break;
	case (USBD_VENDOR):
		usbd_ms_os(setup);
		break;
	default:
		USBD_ENDPOINT_0_SET_STALL();
		break;
	}
}

static void usbd_data_in_stage(void)
{
	uint32_t previous_packet = _MACRO_MIN(USBD_FS_MAXPACKETSIZE, ep0_xfer.leftover);
	/*Decrement the leftover bytes.*/
	ep0_xfer.leftover -= previous_packet;
	/*If there is no leftover data, Data In stage is completed.*/
	if (!ep0_xfer.leftover)
	{
		USBD_ENDPOINT_0_SET_KIND();
		stage_cb = usbd_status_out_stage;
		return;
	}
	/*Increment the buffer.*/
	ep0_xfer.buffer += previous_packet;
	/*Copy a packet to usb sram*/
	usbd_ep_0_write(ep0_xfer.buffer, _MACRO_MIN(USBD_FS_MAXPACKETSIZE, ep0_xfer.leftover));
}

/**
* @brief Process status in stage for endpoint 0.
* @param self Pointer to usbd_core_type.
*/
static void usbd_status_in_stage(void)
{
	if (is_set_address == true)
	{
		if (!dev_addr)
		{
			setup_cb = usbd_default_setup;
			_MACRO_CLEAR_BIT_VAL(USBD->daddr, USBD_DADDR_MASK, USBD_DADDR_POS);
		}
		else
		{
			setup_cb = usbd_addressed_setup;
			_MACRO_SET_BIT_VAL(USBD->daddr, dev_addr, USBD_DADDR_POS);
		}
		is_set_address = false;
	}
	/*Clear the ep0 transfer struct.*/
	ep0_xfer.buffer = NULL;
	ep0_xfer.leftover = 0x0U;
	stage_cb = NULL;
}

/**
* @brief Process status out stage for endpoint 0.
* @param self Pointer to usbd_core_type.
*/
static void usbd_status_out_stage(void)
{

	/*Clear hardware status out*/
	USBD_ENDPOINT_0_CLEAR_KIND();
	/*Clear the ep0 transfer struct.*/
	ep0_xfer.buffer = NULL;
	ep0_xfer.leftover = 0x0U;
	stage_cb = NULL;
}

static void usbd_ctr(usbd_callbacks *ep_cb, uint8_t ep_num, uint8_t dir, uint8_t setup)
{
	if (ep_num == USBD_ENDPOINT_0)
	{
		if (dir == USBD_DIR_OUT && setup && setup_cb != NULL)
		{
			setup_cb(ep_cb);
		}
		else if (stage_cb != NULL)
		{
			stage_cb();
		}
		else
		{
			USBD_ENDPOINT_0_SET_STALL();
		}
	}
	else if (ep_num == USBD_ENDPOINT_1 && dir == USBD_DIR_OUT && ep_cb->usbd_endpoint_out != NULL)
	{
		ep_cb->usbd_endpoint_out();
	}
	else if (ep_num == USBD_ENDPOINT_2 && dir == USBD_DIR_IN && ep_cb->usbd_endpoint_in != NULL)
	{
		ep_cb->usbd_endpoint_in();
	}
	else
	{
		USBD_ENDPOINT_0_SET_STALL();
	}
}

static inline void usbd_reset(void)
{
	/*Clear the interrupt.*/
	_MACRO_CLEAR_BIT(USBD->istr, USBD_ISTR_RESET_POS);
	ep0_xfer.buffer = NULL;
	ep0_xfer.leftover = 0x0U;
	/*Clear all endpoints.*/
	USBD_CLEAR_ENDPOINT_0_CONFIGURATION();
	USBD_CLEAR_ENDPOINT_1_CONFIGURATION();
	USBD_CLEAR_ENDPOINT_2_CONFIGURATION();
	/*Configure endpoint 0*/
	USBD_SET_ENDPOINT_0_CONFIGURATION();
	setup_cb = usbd_default_setup;
	stage_cb = NULL;
	/*Clear the device address.*/
	_MACRO_CLEAR_BIT_VAL(USBD->daddr, USBD_DADDR_MASK, USBD_DADDR_POS);
	_MACRO_SET_BIT(USBD->daddr, USBD_DADDR_EF_POS);
}

static inline void usbd_suspend(void)
{
	/*Clear the interrupt.*/
	_MACRO_CLEAR_BIT(USBD->istr, USBD_ISTR_SUSP_POS);
	/*Set the fsuspend and lp bits.*/
	_MACRO_SET_BIT(USBD->cntr, USBD_CNTR_FSUSP_POS);
	_MACRO_SET_BIT(USBD->cntr, USBD_CNTR_LP_MODE_POS);
	/*Enter stop mode 1*/
	PWR_CLEAR_LOW_POWER_MODE();
	PWR_SET_LOW_POWER_MODE_STOP_1();
	_MACRO_SET_BITS(SCB->scr, (SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
}

static inline void usbd_wakeup(void)
{
	/*Clear the interrupt.*/
	_MACRO_CLEAR_BIT(USBD->istr, USBD_ISTR_WKUP_POS);
	/*Detect noise on bus and go back to suspend.*/
	if (_MACRO_GET_BIT(USBD->fnr, USBD_FNR_RXDP_POS))
	{
		__asm__("BKPT");
		/*Reenable the lp bit.*/
		_MACRO_SET_BIT(USBD->cntr, USBD_CNTR_LP_MODE_POS);
		return;
	}
	/*Clear bits.*/
	_MACRO_CLEAR_BITS(SCB->scr, (SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));
	_MACRO_CLEAR_BIT(USBD->cntr, USBD_CNTR_FSUSP_POS);
	/*Leave stop mode 1.*/
	(void)rcc_set_cpu_max_freq();

	//RCC_USB_DP_CLK_ENABLE();
	//RCC_USB_DM_CLK_ENABLE();
	(void)rcc_set_usb_src_hsi48();

	RCC_USB_CLK_ENABLE();
	//RCC_PWR_CLK_ENABLE();
	//PWR_SET_USB_SUPPLY_VALID();
}

void usbd_init(void)
{
	volatile uint16_t *reg = (uint16_t*)USBD_SRAM_BASE_ADDR;
	_MACRO_CLEAR_BIT(USBD->cntr, USBD_CNTR_PDWN_POS);
	cpu_busy_wait(1);
	USBD->btable = 0x0U;
	/*Clear the SRAM.*/
	for (uint16_t i = 0x0U; i < (USBD_SRAM_SIZE >> 0x1U); i++)
	{
		*reg++ = 0x0U;
	}
	/*Remove force reset.*/
	_MACRO_CLEAR_BIT(USBD->cntr, USBD_CNTR_FRES_POS);
	/*Enable interrupts.*/
	_MACRO_SET_BITS(USBD->cntr, (USBD_CNTR_CTRM | USBD_CNTR_RESETM | USBD_CNTR_SUSPM | USBD_CNTR_WKUPM | USBD_CNTR_ESOFM)); 
	/*Clear interrupts*/
	USBD->istr = 0x0U;
	/*Connect to host.*/
	_MACRO_SET_BIT(USBD->bcdr, USBD_BCDR_DP_PULLUP_POS);
}



//uint16_t istr_dbg[100];
void usbd_irq_handler(usbd_callbacks *ep_cb)
{
	uint8_t ep, dir, setup;
	uint16_t istr, ep_val; 
	istr = (uint16_t)USBD->istr;
	ep = _MACRO_GET_BIT_VAL(istr, USBD_ISTR_EP_ID_MASK, USBD_ISTR_EP_ID_POS);
	dir = _MACRO_GET_BIT(istr, USBD_ISTR_DIR_POS);
	setup = 0;
	ep_val = 0;
	//istr_dbg[dbg_cntr] = istr;
	//if (dbg_cntr >= 8)
	////{
	//	__asm__("BKPT");
	//}
	//dbg_cntr++;
	if (_MACRO_GET_BIT(istr, USBD_ISTR_CTR_POS))
	{
		ep_val = *USBD_ENDPOINT_N_REG(ep);
		if (_MACRO_GET_BIT(ep_val, USBD_EP_CTR_TX_POS))
		{
			/*Set the direction*/
			dir = USBD_DIR_IN;
			/*Clear the interrupt.*/
			*USBD_ENDPOINT_N_REG(ep) = USBD_EP_CLEAR_RC_W0(ep_val, USBD_EP_CTR_TX_MASK);
		}
		else
		{
			setup = _MACRO_GET_BIT(ep_val, USBD_EP_SETUP_POS);
			/*Set the direction*/
			dir = USBD_DIR_OUT;
			/*Clear the interrupt.*/
			*USBD_ENDPOINT_N_REG(ep) = USBD_EP_CLEAR_RC_W0(ep_val, USBD_EP_CTR_RX_MASK);
		}
		usbd_ctr(ep_cb, ep, dir, setup);
	}

	if (_MACRO_GET_BIT(istr, USBD_ISTR_RESET_POS))
	{
		usbd_reset();
	}

	if (_MACRO_GET_BIT(istr, USBD_ISTR_WKUP_POS))
	{
		usbd_wakeup();
	}

	if (_MACRO_GET_BIT(istr, USBD_ISTR_SUSP_POS))
	{
		usbd_suspend();
	}

	if (_MACRO_GET_BIT(istr, USBD_ISTR_ESOF_POS))
	{
		_MACRO_CLEAR_BIT(USBD->istr, USBD_ISTR_ESOF_POS);
	}
}