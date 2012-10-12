/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'DE4_SOPC'
 * SOPC Builder design path: C:/Users/ydj/Workspace/DE4_DDR2_NIOS10.1/DE4_SOPC.sopcinfo
 *
 * Generated: Sat Oct 13 00:01:21 KST 2012
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x41040820
#define ALT_CPU_CPU_FREQ 200000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x0
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 31
#define ALT_CPU_DCACHE_LINE_SIZE 32
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_DCACHE_SIZE 2048
#define ALT_CPU_EXCEPTION_ADDR 0x41020020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 200000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 1
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INITDA_SUPPORTED
#define ALT_CPU_INST_ADDR_WIDTH 31
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_RESET_ADDR 0x41020000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x41040820
#define NIOS2_CPU_FREQ 200000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x0
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 31
#define NIOS2_DCACHE_LINE_SIZE 32
#define NIOS2_DCACHE_LINE_SIZE_LOG2 5
#define NIOS2_DCACHE_SIZE 2048
#define NIOS2_EXCEPTION_ADDR 0x41020020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 1
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INITDA_SUPPORTED
#define NIOS2_INST_ADDR_WIDTH 31
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_RESET_ADDR 0x41020000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_DMA
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2
#define __ALTMEMDDR2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "STRATIXIV"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x41041020
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x41041020
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x41041020
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "DE4_SOPC"


/*
 * button configuration
 *
 */

#define ALT_MODULE_CLASS_button altera_avalon_pio
#define BUTTON_BASE 0x40000020
#define BUTTON_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_CAPTURE 1
#define BUTTON_DATA_WIDTH 4
#define BUTTON_DO_TEST_BENCH_WIRING 0
#define BUTTON_DRIVEN_SIM_VALUE 0x0
#define BUTTON_EDGE_TYPE "ANY"
#define BUTTON_FREQ 50000000u
#define BUTTON_HAS_IN 1
#define BUTTON_HAS_OUT 0
#define BUTTON_HAS_TRI 0
#define BUTTON_IRQ 1
#define BUTTON_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTON_IRQ_TYPE "EDGE"
#define BUTTON_NAME "/dev/button"
#define BUTTON_RESET_VALUE 0x0
#define BUTTON_SPAN 16
#define BUTTON_TYPE "altera_avalon_pio"


/*
 * ddr2 configuration
 *
 */

#define ALT_MODULE_CLASS_ddr2 altmemddr2
#define DDR2_BASE 0x0
#define DDR2_IRQ -1
#define DDR2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR2_NAME "/dev/ddr2"
#define DDR2_SPAN 1073741824
#define DDR2_TYPE "altmemddr2"


/*
 * ddr2_i2c_sa configuration
 *
 */

#define ALT_MODULE_CLASS_ddr2_i2c_sa altera_avalon_pio
#define DDR2_I2C_SA_BASE 0x40000040
#define DDR2_I2C_SA_BIT_CLEARING_EDGE_REGISTER 0
#define DDR2_I2C_SA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DDR2_I2C_SA_CAPTURE 0
#define DDR2_I2C_SA_DATA_WIDTH 2
#define DDR2_I2C_SA_DO_TEST_BENCH_WIRING 0
#define DDR2_I2C_SA_DRIVEN_SIM_VALUE 0x0
#define DDR2_I2C_SA_EDGE_TYPE "NONE"
#define DDR2_I2C_SA_FREQ 50000000u
#define DDR2_I2C_SA_HAS_IN 0
#define DDR2_I2C_SA_HAS_OUT 1
#define DDR2_I2C_SA_HAS_TRI 0
#define DDR2_I2C_SA_IRQ -1
#define DDR2_I2C_SA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR2_I2C_SA_IRQ_TYPE "NONE"
#define DDR2_I2C_SA_NAME "/dev/ddr2_i2c_sa"
#define DDR2_I2C_SA_RESET_VALUE 0x0
#define DDR2_I2C_SA_SPAN 16
#define DDR2_I2C_SA_TYPE "altera_avalon_pio"


/*
 * ddr2_i2c_scl configuration
 *
 */

#define ALT_MODULE_CLASS_ddr2_i2c_scl altera_avalon_pio
#define DDR2_I2C_SCL_BASE 0x40000050
#define DDR2_I2C_SCL_BIT_CLEARING_EDGE_REGISTER 0
#define DDR2_I2C_SCL_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DDR2_I2C_SCL_CAPTURE 0
#define DDR2_I2C_SCL_DATA_WIDTH 1
#define DDR2_I2C_SCL_DO_TEST_BENCH_WIRING 0
#define DDR2_I2C_SCL_DRIVEN_SIM_VALUE 0x0
#define DDR2_I2C_SCL_EDGE_TYPE "NONE"
#define DDR2_I2C_SCL_FREQ 50000000u
#define DDR2_I2C_SCL_HAS_IN 0
#define DDR2_I2C_SCL_HAS_OUT 1
#define DDR2_I2C_SCL_HAS_TRI 0
#define DDR2_I2C_SCL_IRQ -1
#define DDR2_I2C_SCL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR2_I2C_SCL_IRQ_TYPE "NONE"
#define DDR2_I2C_SCL_NAME "/dev/ddr2_i2c_scl"
#define DDR2_I2C_SCL_RESET_VALUE 0x0
#define DDR2_I2C_SCL_SPAN 16
#define DDR2_I2C_SCL_TYPE "altera_avalon_pio"


/*
 * ddr2_i2c_sda configuration
 *
 */

#define ALT_MODULE_CLASS_ddr2_i2c_sda altera_avalon_pio
#define DDR2_I2C_SDA_BASE 0x40000060
#define DDR2_I2C_SDA_BIT_CLEARING_EDGE_REGISTER 0
#define DDR2_I2C_SDA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DDR2_I2C_SDA_CAPTURE 0
#define DDR2_I2C_SDA_DATA_WIDTH 1
#define DDR2_I2C_SDA_DO_TEST_BENCH_WIRING 0
#define DDR2_I2C_SDA_DRIVEN_SIM_VALUE 0x0
#define DDR2_I2C_SDA_EDGE_TYPE "NONE"
#define DDR2_I2C_SDA_FREQ 50000000u
#define DDR2_I2C_SDA_HAS_IN 0
#define DDR2_I2C_SDA_HAS_OUT 0
#define DDR2_I2C_SDA_HAS_TRI 1
#define DDR2_I2C_SDA_IRQ -1
#define DDR2_I2C_SDA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DDR2_I2C_SDA_IRQ_TYPE "NONE"
#define DDR2_I2C_SDA_NAME "/dev/ddr2_i2c_sda"
#define DDR2_I2C_SDA_RESET_VALUE 0x0
#define DDR2_I2C_SDA_SPAN 16
#define DDR2_I2C_SDA_TYPE "altera_avalon_pio"


/*
 * dma_0 configuration
 *
 */

#define ALT_MODULE_CLASS_dma_0 altera_avalon_dma
#define DMA_0_ALLOW_BYTE_TRANSACTIONS 1
#define DMA_0_ALLOW_DOUBLEWORD_TRANSACTIONS 1
#define DMA_0_ALLOW_HW_TRANSACTIONS 1
#define DMA_0_ALLOW_QUADWORD_TRANSACTIONS 1
#define DMA_0_ALLOW_WORD_TRANSACTIONS 1
#define DMA_0_BASE 0x41041000
#define DMA_0_IRQ 3
#define DMA_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DMA_0_LENGTHWIDTH 16
#define DMA_0_MAX_BURST_SIZE 16
#define DMA_0_NAME "/dev/dma_0"
#define DMA_0_SPAN 32
#define DMA_0_TYPE "altera_avalon_dma"


/*
 * dst_on_chip configuration as viewed by dma_0_write_master
 *
 */

#define DMA_0_WRITE_MASTER_DST_ON_CHIP_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_BASE 0x0
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_CONTENTS_INFO ""
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_DUAL_PORT 0
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_GUI_RAM_BLOCK_TYPE "Automatic"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_INIT_CONTENTS_FILE "dst_on_chip"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_INIT_MEM_CONTENT 1
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_INSTANCE_ID "NONE"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_IRQ -1
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_NAME "/dev/dst_on_chip"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_NON_DEFAULT_INIT_FILE_ENABLED 0
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_RAM_BLOCK_TYPE "Auto"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_READ_DURING_WRITE_MODE "DONT_CARE"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_SIZE_MULTIPLE 1
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_SIZE_VALUE 65536u
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_SPAN 65536
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_TYPE "altera_avalon_onchip_memory2"
#define DMA_0_WRITE_MASTER_DST_ON_CHIP_WRITABLE 1


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x41041020
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * led configuration
 *
 */

#define ALT_MODULE_CLASS_led altera_avalon_pio
#define LED_BASE 0x40000030
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0x0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 50000000u
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/led"
#define LED_RESET_VALUE 0x0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * onchip_memory2 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_BASE 0x41020000
#define ONCHIP_MEMORY2_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_DUAL_PORT 0
#define ONCHIP_MEMORY2_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_MEMORY2_INIT_CONTENTS_FILE "onchip_memory2"
#define ONCHIP_MEMORY2_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_IRQ -1
#define ONCHIP_MEMORY2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_NAME "/dev/onchip_memory2"
#define ONCHIP_MEMORY2_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_MEMORY2_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_SIZE_VALUE 131072u
#define ONCHIP_MEMORY2_SPAN 131072
#define ONCHIP_MEMORY2_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_WRITABLE 1


/*
 * src_on_chip configuration as viewed by dma_0_read_master
 *
 */

#define DMA_0_READ_MASTER_SRC_ON_CHIP_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define DMA_0_READ_MASTER_SRC_ON_CHIP_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define DMA_0_READ_MASTER_SRC_ON_CHIP_BASE 0x0
#define DMA_0_READ_MASTER_SRC_ON_CHIP_CONTENTS_INFO ""
#define DMA_0_READ_MASTER_SRC_ON_CHIP_DUAL_PORT 0
#define DMA_0_READ_MASTER_SRC_ON_CHIP_GUI_RAM_BLOCK_TYPE "Automatic"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_INIT_CONTENTS_FILE "DMA_INIT"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_INIT_MEM_CONTENT 1
#define DMA_0_READ_MASTER_SRC_ON_CHIP_INSTANCE_ID "NONE"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_IRQ -1
#define DMA_0_READ_MASTER_SRC_ON_CHIP_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DMA_0_READ_MASTER_SRC_ON_CHIP_NAME "/dev/src_on_chip"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_NON_DEFAULT_INIT_FILE_ENABLED 1
#define DMA_0_READ_MASTER_SRC_ON_CHIP_RAM_BLOCK_TYPE "Auto"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_READ_DURING_WRITE_MODE "DONT_CARE"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_SIZE_MULTIPLE 1
#define DMA_0_READ_MASTER_SRC_ON_CHIP_SIZE_VALUE 65536u
#define DMA_0_READ_MASTER_SRC_ON_CHIP_SPAN 65536
#define DMA_0_READ_MASTER_SRC_ON_CHIP_TYPE "altera_avalon_onchip_memory2"
#define DMA_0_READ_MASTER_SRC_ON_CHIP_WRITABLE 1


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid
#define SYSID_BASE 0x40000070
#define SYSID_ID 1333595182u
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1350053308u
#define SYSID_TYPE "altera_avalon_sysid"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x40000000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000u
#define TIMER_IRQ 2
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999ULL
#define TIMER_MULT 0.0010
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICKS_PER_SEC TIMER_TICKS_PER_SEC
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
