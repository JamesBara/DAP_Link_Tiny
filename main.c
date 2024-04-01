#include "rcc.h"
#include "usbd.h"
#include "DAP_config.h"
#include "DAP.h"

struct endpoint_1_buffer_type
{
	uint8_t buffer[DAP_PACKET_SIZE * DAP_PACKET_COUNT];
	uint32_t head;
	uint32_t tail;
};

struct endpoint_2_buffer_type
{
	uint8_t buffer[DAP_PACKET_SIZE * DAP_PACKET_COUNT];
	uint32_t head;
	uint32_t tail;
};

enum events
{
	NO_EVENT,
	RECEPTION_COMPLETE,
};

static struct endpoint_1_buffer_type endpoint_1_buffer;
static struct endpoint_2_buffer_type endpoint_2_buffer;
static usbd_callbacks usbd_handle;
static enum events event = NO_EVENT;


static void usbd_prepare_to_transmit(void *buf, size_t sz);
static void usbd_continue_to_transmit(void *buf, size_t sz);
static uint16_t usbd_continue_to_receive(void *buf);
static void endpoint_2_in(void);
static void endpoint_1_out(void);





int main(void)
{
	/*Set the cpu clock to 80 Mhz.*/
	system_error_code_type err = rcc_set_cpu_max_freq();

	if (err != SYS_ERR_CODE_OK)
	{
		__asm__("BKPT");
	}
	/*Enable prefetching.*/
	FLASH_SET_PREFETCH();
	/*Enable gpio clocks for usb.*/
	RCC_USB_DP_CLK_ENABLE();
	RCC_USB_DM_CLK_ENABLE();
	/*Enable usb gpio*/
	GPIO_USB_DM_DP_ENABLE();

	/*Select hsi48 as the usb source clock.*/
	err = rcc_set_usb_src_hsi48();

	if (err != SYS_ERR_CODE_OK)
	{
		__asm__("BKPT");
	}
	/*Enable usb and pwr peripheral clock*/
	RCC_USB_CLK_ENABLE();
	RCC_PWR_CLK_ENABLE();
	/*Disable usb isolation.*/
	PWR_SET_USB_SUPPLY_VALID();
	/*Enable USB interrupt.*/
	NVIC_SetPriority(USB_IRQn, ((1UL << __NVIC_PRIO_BITS) - 1UL));
	NVIC_EnableIRQ(USB_IRQn);
	usbd_register_endpoint_out_cb(&usbd_handle, endpoint_1_out);
	usbd_register_endpoint_in_cb(&usbd_handle, endpoint_2_in);
	usbd_register_dap_setup_cb(&usbd_handle, DAP_SETUP);
	usbd_init();

	while (1)
	{
		if (event == RECEPTION_COMPLETE)
		{		
			endpoint_2_buffer.head = (DAP_ExecuteCommand(&endpoint_1_buffer.buffer[endpoint_1_buffer.tail] ,&endpoint_2_buffer.buffer[endpoint_2_buffer.head]) & 0xFFFF);
			event = NO_EVENT;
			if (endpoint_2_buffer.head)
			{
				usbd_prepare_to_transmit(&endpoint_2_buffer.buffer[endpoint_2_buffer.tail], (endpoint_2_buffer.head - endpoint_2_buffer.tail));
			}
		}
	}
	return 0;
}

void USB_IRQHandler(void)
{

	usbd_irq_handler(&usbd_handle);
}


static void endpoint_2_in(void)
{
	uint32_t packet_size = _MACRO_MIN((endpoint_2_buffer.head - endpoint_2_buffer.tail), USBD_FS_MAXPACKETSIZE);
	endpoint_2_buffer.tail = ((endpoint_2_buffer.tail + packet_size) % (DAP_PACKET_SIZE * DAP_PACKET_COUNT));
	/*Transmission is complete.*/
	if (endpoint_2_buffer.tail == endpoint_2_buffer.head)
	{
		endpoint_2_buffer.head = 0;
		endpoint_2_buffer.tail = 0;	
		if (USBD_ENDPOINT_2_GET_DOUBLE_BUFFER())
		{
			USBD_ENDPOINT_2_CLEAR_DOUBLE_BUFFER();
		}
		return;
	}
	usbd_continue_to_transmit(&endpoint_2_buffer.buffer[endpoint_2_buffer.tail], _MACRO_MIN((endpoint_2_buffer.head - endpoint_2_buffer.tail), USBD_FS_MAXPACKETSIZE));
}

static void usbd_prepare_to_transmit(void* buf, size_t sz)
{
	/*Select whether to use double buffering or not.*/
	if (sz <= USBD_FS_MAXPACKETSIZE)
	{
		USBD_ENDPOINT_2_SET_TX_COUNT((uint16_t)sz);
		usbd_copy_to_pma(buf, USBD_ENDPOINT_2_TX_PMA_BUF, (uint16_t)sz);
		USBD_ENDPOINT_2_SET_VALID();
	}
	else
	{
		USBD_ENDPOINT_2_SET_DOUBLE_BUFFER();
		/*Select which buffer to use.*/
		if (!USBD_ENDPOINT_2_GET_DTOG_TX() && USBD_ENDPOINT_2_GET_SWBUF_TX())
		{
			USBD_ENDPOINT_2_SET_TX_1_COUNT((uint16_t)sz);
			usbd_copy_to_pma(buf, USBD_ENDPOINT_2_TX_1_PMA_BUF, USBD_FS_MAXPACKETSIZE);
		}
		else
		{
			USBD_ENDPOINT_2_SET_TX_0_COUNT((uint16_t)sz);
			usbd_copy_to_pma(buf, USBD_ENDPOINT_2_TX_0_PMA_BUF, USBD_FS_MAXPACKETSIZE);
			if (USBD_ENDPOINT_2_GET_DTOG_TX() == USBD_ENDPOINT_2_GET_SWBUF_TX())
			{
				USBD_ENDPOINT_2_TOGGLE_SWBUF_TX();
			}
		}
		USBD_ENDPOINT_2_SET_VALID();
	}
}

static void usbd_continue_to_transmit(void* buf, size_t sz)
{
	/*Select which buffer to use.*/
	if (!USBD_ENDPOINT_2_GET_DTOG_TX() && USBD_ENDPOINT_2_GET_SWBUF_TX())
	{
		usbd_copy_to_pma(buf, USBD_ENDPOINT_2_TX_1_PMA_BUF, (uint16_t)sz);
	}
	else
	{
		usbd_copy_to_pma(buf, USBD_ENDPOINT_2_TX_0_PMA_BUF, (uint16_t)sz);
		if (USBD_ENDPOINT_2_GET_DTOG_TX() == USBD_ENDPOINT_2_GET_SWBUF_TX())
		{
			USBD_ENDPOINT_2_TOGGLE_SWBUF_TX();
		}
	}
}




static void endpoint_1_out(void)
{

	uint16_t packet_size;
	if (!USBD_ENDPOINT_1_GET_DOUBLE_BUFFER())
	{
		/*Reset the buffer pointers.*/
		endpoint_1_buffer.head = 0x0U;
		endpoint_1_buffer.tail = 0x0U;

		packet_size = USBD_ENDPOINT_1_GET_RX_COUNT();


		usbd_read_from_pma(USBD_ENDPOINT_1_RX_PMA_BUF, &endpoint_1_buffer.buffer[endpoint_1_buffer.head], packet_size);
		endpoint_1_buffer.head = ((endpoint_1_buffer.head + packet_size) % (DAP_PACKET_SIZE * DAP_PACKET_COUNT));
		if (packet_size == USBD_FS_MAXPACKETSIZE)
		{
			USBD_ENDPOINT_1_SET_DOUBLE_BUFFER();
		}
		else
		{
			event = RECEPTION_COMPLETE;
			USBD_ENDPOINT_1_SET_VALID();
		}
	}
	else
	{
		packet_size = usbd_continue_to_receive(&endpoint_1_buffer.buffer[endpoint_1_buffer.head]);
		endpoint_1_buffer.head = ((endpoint_1_buffer.head + packet_size) % (DAP_PACKET_SIZE * DAP_PACKET_COUNT));
		if (packet_size < USBD_FS_MAXPACKETSIZE || endpoint_1_buffer.head == endpoint_1_buffer.tail)
		{
			event = RECEPTION_COMPLETE;
			USBD_ENDPOINT_1_CLEAR_DOUBLE_BUFFER();
		}
	}
}

static uint16_t usbd_continue_to_receive(void* buf)
{
	uint16_t cnt;
	/*Select which buffer to use.*/
	if ((!USBD_ENDPOINT_1_GET_DTOG_RX() && USBD_ENDPOINT_1_GET_SWBUF_RX()) || (USBD_ENDPOINT_1_GET_DTOG_RX() && USBD_ENDPOINT_1_GET_SWBUF_RX()))
	{
		cnt = USBD_ENDPOINT_1_GET_RX_1_COUNT();
		usbd_read_from_pma(USBD_ENDPOINT_1_RX_1_PMA_BUF, buf, USBD_FS_MAXPACKETSIZE);
	}
	else
	{
		cnt = USBD_ENDPOINT_1_GET_RX_0_COUNT();
		usbd_read_from_pma(USBD_ENDPOINT_1_RX_0_PMA_BUF, buf, USBD_FS_MAXPACKETSIZE);
	}

	if (USBD_ENDPOINT_1_GET_DTOG_RX() == USBD_ENDPOINT_1_GET_SWBUF_RX())
	{
		USBD_ENDPOINT_1_TOGGLE_SWBUF_RX();
	}

	return cnt;
}