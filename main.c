#include "rcc.h"
#include "usbd.h"
#include "DAP_config.h"
#include "DAP.h"

struct endpoint_buffer_type
{
	uint8_t buffer[DAP_PACKET_SIZE * DAP_PACKET_COUNT];
	uint32_t head;
	uint32_t tail;
};


static struct endpoint_buffer_type endpoint_1_out_buffer;
static struct endpoint_buffer_type endpoint_1_in_buffer;
static usbd_callbacks usbd_handle;
static bool has_data_been_received = false;


static void endpoint_1_transmit_packet(void *buf, size_t sz);
static void endpoint_1_in(void);
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
	usbd_register_endpoint_in_cb(&usbd_handle, endpoint_1_in);
	usbd_register_dap_setup_cb(&usbd_handle, DAP_SETUP);
	usbd_init();

	while (1)
	{
		if (has_data_been_received == true)
		{		
			endpoint_1_in_buffer.head = (DAP_ExecuteCommand(&endpoint_1_out_buffer.buffer[endpoint_1_out_buffer.tail] ,&endpoint_1_in_buffer.buffer[endpoint_1_in_buffer.head]) & 0xFFFFU);
			
			/*Flush the out buffer.*/
			endpoint_1_out_buffer.head = 0x0U;
			endpoint_1_out_buffer.tail = 0x0U;	
			/*Enable the out direction again.*/
			USBD_ENDPOINT_SET_RX_VALID(USBD_ENDPOINT_1);
			has_data_been_received = false;
			/*Start transmiting*/
			if (endpoint_1_in_buffer.head)
			{
				endpoint_1_transmit_packet(&endpoint_1_in_buffer.buffer[endpoint_1_in_buffer.tail], (endpoint_1_in_buffer.head - endpoint_1_in_buffer.tail));
			}
		}
	}
	return 0;
}

void USB_IRQHandler(void)
{

	usbd_irq_handler(&usbd_handle);
}


static void endpoint_1_in(void)
{
	uint32_t packet_size = _MACRO_MIN((endpoint_1_in_buffer.head - endpoint_1_in_buffer.tail), USBD_FS_MAXPACKETSIZE);
	endpoint_1_in_buffer.tail = ((endpoint_1_in_buffer.tail + packet_size) % (DAP_PACKET_SIZE * DAP_PACKET_COUNT));
	/*Transmission is complete.*/
	if (endpoint_1_in_buffer.tail == endpoint_1_in_buffer.head)
	{
		endpoint_1_in_buffer.head = 0;
		endpoint_1_in_buffer.tail = 0;	
		return;
	}
	endpoint_1_transmit_packet(&endpoint_1_in_buffer.buffer[endpoint_1_in_buffer.tail], _MACRO_MIN((endpoint_1_in_buffer.head - endpoint_1_in_buffer.tail), USBD_FS_MAXPACKETSIZE));
}

static void endpoint_1_transmit_packet(void* buf, size_t sz)
{
	USBD_ENDPOINT_1_SET_TX_COUNT((uint16_t)sz);
	usbd_copy_to_pma(buf, USBD_ENDPOINT_1_TX_PMA_BUF, (uint16_t)sz);
	USBD_ENDPOINT_SET_TX_VALID(USBD_ENDPOINT_1);
}


static void endpoint_1_out(void)
{

	uint16_t packet_size = USBD_ENDPOINT_1_GET_RX_COUNT();;
	usbd_read_from_pma(USBD_ENDPOINT_1_RX_PMA_BUF, &endpoint_1_out_buffer.buffer[endpoint_1_out_buffer.head], packet_size);
	endpoint_1_out_buffer.head = ((endpoint_1_out_buffer.head + packet_size) % (DAP_PACKET_SIZE * DAP_PACKET_COUNT));
	/*If data received is max packet and the buffer is not full continue receiving.*/
	if (packet_size == USBD_FS_MAXPACKETSIZE || endpoint_1_out_buffer.head != endpoint_1_out_buffer.tail)
	{
		USBD_ENDPOINT_SET_RX_VALID(USBD_ENDPOINT_1);
	}
	else
	{
		/*If the packet received was a short packet or the buffer is full stop receiving.*/
		has_data_been_received = true;
	}
}