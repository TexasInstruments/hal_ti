
/**
 *  \file EM_platform.h
 *
 *
 *  EM platform Header File contains OS related definitions and functions
 */

 /*
  *  Copyright (C) 2025. Mindtree Ltd.
  *  All rights reserved.
  */

#ifndef _H_EM_PLATFORM_
#define _H_EM_PLATFORM_

/* -------------------------------------------- Header File Inclusion */
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/types.h>
#include <time.h>
#include <errno.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <zephyr/shell/shell.h>
#include <zephyr/autoconf.h>

/* -------------------------------------------- Global Definitions */

/* -------------------------------------------- Structures/Data Types */
#if defined(CONFIG_SHELL)
#define CONSOLE_OUT(...)      shell_print(shell, __VA_ARGS__)
#else  /* CONFIG_SHELL */
#define CONSOLE_OUT(...)
#endif /* CONFIG_SHELL */

#if defined(CONFIG_PRINTK)
#define CONSOLE_TRC(...)      printk(__VA_ARGS__)
#define CONSOLE_INF(...)      printk(__VA_ARGS__)
#define CONSOLE_ERR(...)      printk(__VA_ARGS__)
#else /* CONFIG_PRINTK */
#define CONSOLE_TRC(...)
#define CONSOLE_INF(...)
#define CONSOLE_ERR(...)
#endif /* CONFIG_PRINTK */
/* --------------------------------------------------- Macros */

/* -------------------------------------------- Data Structures */

/* -------------------------------------------- Function Declarations */


#endif /* _H_EM_PLATFORM_ */

