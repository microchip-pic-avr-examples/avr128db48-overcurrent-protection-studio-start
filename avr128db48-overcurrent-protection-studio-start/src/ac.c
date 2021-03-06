/**
 * \file
 *
 * \brief Analog Comparator related functionality implementation.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_ac_init AC Init Driver
 * \ingroup doc_driver_ac
 *
 * \section doc_driver_ac_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <ac.h>

/**
 * \brief Initialize Analog Comparator
 *
 * \return Initialization status.
 */
int8_t AC_0_init()
{

	// AC0.INTCTRL = AC_INTMODE_NORMAL_BOTHEDGE_gc /* Positive and negative inputs crosses */
	//		 | 0 << AC_CMP_bp; /* Analog Comparator Interrupt Enable: disabled */

	AC0.MUXCTRL = 0 << AC_INVERT_bp     /* Invert AC Output: disabled */
	              | AC_MUXNEG_DACREF_gc /* DAC Reference */
	              | AC_MUXPOS_AINP2_gc; /* Positive Pin 2 */

	AC0.DACREF = 0x13; /* DAC Voltage Reference: 0x13 */

	AC0.CTRLA = 1 << AC_ENABLE_bp      /* Enable: enabled */
	            | AC_HYSMODE_NONE_gc   /* No hysteresis */
	            | AC_POWER_PROFILE0_gc /* Power profile 0, Shortest respone time, highest consumption */
	            | 1 << AC_OUTEN_bp     /* Output Buffer Enable: enabled */
	            | 1 << AC_RUNSTDBY_bp; /* Run in Standby Mode: enabled */

	return 0;
}
