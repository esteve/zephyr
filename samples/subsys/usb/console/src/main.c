/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <logging/log.h>
// LOG_MODULE_REGISTER(net_telnet_sample, LOG_LEVEL_DBG);

// #include <zephyr.h>
// #include <linker/sections.h>
// #include <errno.h>
// #include <stdio.h>

// #include <net/net_core.h>
// #include <net/net_if.h>
// #include <net/net_mgmt.h>

#include <zephyr.h>
#include <sys/printk.h>
#include <sys/util.h>
#include <string.h>
#include <usb/usb_device.h>
#include <drivers/uart.h>

// #if defined(CONFIG_NET_IPV4) && !defined(CONFIG_NET_DHCPV4)

// #if !defined(CONFIG_NET_CONFIG_MY_IPV4_ADDR)
// #error "You need to define an IPv4 Address or enable DHCPv4!"
// #endif

// static void setup_ipv4(struct net_if *iface)
// {
// 	char hr_addr[NET_IPV4_ADDR_LEN];
// 	struct in_addr addr;

// 	if (net_addr_pton(AF_INET, CONFIG_NET_CONFIG_MY_IPV4_ADDR, &addr)) {
// 		LOG_ERR("Invalid address: %s", CONFIG_NET_CONFIG_MY_IPV4_ADDR);
// 		return;
// 	}

// 	net_if_ipv4_addr_add(iface, &addr, NET_ADDR_MANUAL, 0);

// 	LOG_INF("IPv4 address: %s",
// 		log_strdup(net_addr_ntop(AF_INET, &addr, hr_addr,
// 					 NET_IPV4_ADDR_LEN)));
// }

// #else
// #define setup_ipv4(...)
// #endif /* CONFIG_NET_IPV4 && !CONFIG_NET_DHCPV4 */

void main(void)
{
	const struct device *dev = device_get_binding(
			CONFIG_UART_CONSOLE_ON_DEV_NAME);
	uint32_t dtr = 0;

	if (usb_enable(NULL)) {
		return;
	}

	/* Poll if the DTR flag was set, optional */
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
	}

	if (strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME) !=
	    strlen("CDC_ACM_0") ||
	    strncmp(CONFIG_UART_CONSOLE_ON_DEV_NAME, "CDC_ACM_0",
		    strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME))) {
		printk("Error: Console device name is not USB ACM\n");

		return;
	}

	for (int i = 0; i < 10; ++i) {
		printk("Hello Teixoneta!!!!: %d\n", i);
		k_sleep(K_SECONDS(1));
	}

	// struct net_if *iface = net_if_get_default();

	printk("Starting Telnet sample");
}
