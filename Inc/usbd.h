#ifndef USBD_H
#define USBD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	void (*usbd_endpoint_in)(void);
	void (*usbd_endpoint_out)(void);
	void (*resume_from_stall)(void);
	void (*dap_init)(void);
}usbd_callbacks;

void usbd_copy_to_pma(uint8_t *src, uint16_t *dst, uint16_t sz);
void usbd_read_from_pma(uint16_t *src, uint8_t *dst, uint16_t sz);

void usbd_init(void);
void usbd_irq_handler(usbd_callbacks *ep_cb);



static inline void usbd_register_dap_setup_cb(usbd_callbacks *ep_cb, void (*cb)(void))
{
	ep_cb->dap_init = cb;
}

static inline void usbd_register_endpoint_in_cb(usbd_callbacks *ep_cb, void (*cb)(void))
{
	ep_cb->usbd_endpoint_in = cb;
}

static inline void usbd_register_endpoint_out_cb(usbd_callbacks *ep_cb, void (*cb)(void))
{
	ep_cb->usbd_endpoint_out = cb;
}

#ifdef __cplusplus
}
#endif
#endif /*endif USBD_H*/