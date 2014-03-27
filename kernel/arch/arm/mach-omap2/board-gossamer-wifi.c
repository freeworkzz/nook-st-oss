/* linux/arch/arm/mach-omap2/board-gossamer-wifi.c
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/err.h>

#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/wifi_tiwlan.h>

#include <linux/i2c/twl4030.h>

#define PM_RECEIVER                     TWL4030_MODULE_PM_RECEIVER
#define ENABLE_VAUX2_DEDICATED          0x05
#define ENABLE_VAUX2_DEV_GRP            0x20
#define ENABLE_VAUX3_DEDICATED          0x03
#define ENABLE_VAUX3_DEV_GRP            0x20

#define t2_out(c, r, v) twl4030_i2c_write_u8(c, r, v)

#define GOSSAMER_WIFI_PMENA_GPIO	22
#define GOSSAMER_WIFI_IRQ_GPIO		15
#define GOSSAMER_WIFI_EN_POW		16

#define WLAN_PWR_ALWAYS_ON		(1)

/* WIFI virtual 'card detect' status */
static int gossamer_wifi_cd = 0;

static int gossamer_wifi_power_state;
static int gossamer_wifi_reset_state;

static void (*wifi_status_cb)(int card_present, void *dev_id);
static void *wifi_status_cb_devid;

static int gossamer_wifi_v18io_power_enable_init(int enable)
{
	int return_value = 0;

	if (enable) {
		printk(KERN_DEBUG "Enabling VAUX for wifi \n");
		return_value  = t2_out(PM_RECEIVER, ENABLE_VAUX2_DEDICATED,
			       TWL4030_VAUX2_DEDICATED);
		return_value |= t2_out(PM_RECEIVER, ENABLE_VAUX2_DEV_GRP,
			       TWL4030_VAUX2_DEV_GRP);
	} else {
		printk(KERN_DEBUG "Disable VAUX for wifi \n");
		return_value |= t2_out(PM_RECEIVER, 0,
			       TWL4030_VAUX2_DEV_GRP);
	}

	if (0 != return_value)
		printk(KERN_ERR "Enabling VAUX for wifi incomplete error: %d\n",
		       return_value);

	return return_value;
}

int omap_wifi_status_register(void (*callback)(int card_present, void *dev_id),
			      void *dev_id)
{
	if (wifi_status_cb)
		return -EAGAIN;

	wifi_status_cb = callback;
	wifi_status_cb_devid = dev_id;

	return 0;
}

int gossamer_wifi_status(int irq)
{
	return gossamer_wifi_cd;
}

int gossamer_wifi_set_carddetect(int val)
{
	gossamer_wifi_cd = val;
	if (wifi_status_cb) {
		wifi_status_cb(val, wifi_status_cb_devid);
	} else
		printk(KERN_WARNING "%s: Nobody to notify\n", __func__);

	return 0;
}
#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(gossamer_wifi_set_carddetect);
#endif

int gossamer_wifi_power(int on)
{
	/* keep VAUX powered during operation */
	gossamer_wifi_v18io_power_enable_init(WLAN_PWR_ALWAYS_ON);

	/* VSYS-WLAN also enabled */
	gpio_direction_output(GOSSAMER_WIFI_EN_POW, WLAN_PWR_ALWAYS_ON);

	/* only WLAN_EN is driven during power-up/down */
	gpio_direction_output(GOSSAMER_WIFI_PMENA_GPIO, on);

	gossamer_wifi_power_state = on;

	return 0;
}
#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(gossamer_wifi_power);
#endif

int gossamer_wifi_reset(int on)
{
	gossamer_wifi_reset_state = on;

	return 0;
}
#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(gossamer_wifi_reset);
#endif

struct wifi_platform_data gossamer_wifi_control = {
	.set_power	= gossamer_wifi_power,
	.set_reset	= gossamer_wifi_reset,
	.set_carddetect	= gossamer_wifi_set_carddetect,
};

#ifdef CONFIG_WIFI_CONTROL_FUNC
static struct resource gossamer_wifi_resources[] = {
	[0] = {
		.name		= "device_wifi_irq",
		.start		= OMAP_GPIO_IRQ(GOSSAMER_WIFI_IRQ_GPIO),
		.end		= OMAP_GPIO_IRQ(GOSSAMER_WIFI_IRQ_GPIO),
		.flags          = IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	},
};

static struct platform_device gossamer_wifi_device = {
        .name           = "device_wifi",
        .id             = 1,
        .num_resources  = ARRAY_SIZE(gossamer_wifi_resources),
        .resource       = gossamer_wifi_resources,
        .dev            = {
                .platform_data = &gossamer_wifi_control,
        },
};
#endif

static int __init gossamer_wifi_init(void)
{
	int ret;

	ret = gpio_request(GOSSAMER_WIFI_IRQ_GPIO, "wifi_irq");
	if (ret < 0) {
		printk(KERN_ERR "%s: can't reserve GPIO: %d\n", __func__,
			GOSSAMER_WIFI_IRQ_GPIO);
		goto out;
	}

	ret = gpio_request(GOSSAMER_WIFI_PMENA_GPIO, "wifi_pmena");
	if (ret < 0) {
		printk(KERN_ERR "%s: can't reserve GPIO: %d\n", __func__,
			GOSSAMER_WIFI_PMENA_GPIO);
		goto out1;
	}

	ret = gpio_request(GOSSAMER_WIFI_EN_POW, "wifi_en_pow");
	if (ret < 0) {
		printk(KERN_ERR "%s: can't reserve GPIO: %d\n", __func__,
			GOSSAMER_WIFI_EN_POW);
		goto out2;
	}

	gpio_direction_input(GOSSAMER_WIFI_IRQ_GPIO);
#ifdef CONFIG_WIFI_CONTROL_FUNC
	ret = platform_device_register(&gossamer_wifi_device);
#endif
	return ret;
out2:
	gpio_free(GOSSAMER_WIFI_PMENA_GPIO);
out1:
	gpio_free(GOSSAMER_WIFI_IRQ_GPIO);
out:
        return ret;
}

device_initcall(gossamer_wifi_init);
