#include <atmel_start.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define VREF_AC_MV 4096
#define AC_TRIGGER_VOLTAGE_MV_INIT 1100

void fan_start(void);
void button_init(void);


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	fan_start();
	button_init();
	sei();
	while (1) {
	}
}


void tcd_enable(void)
{
	TCD0.CTRLA = TCD_ENABLE_bm;
	TCD0.CTRLE = TCD_RESTART_bm;
}

uint8_t ac_calculate_trigger_voltage(uint16_t mV)
{
	uint8_t triggerVoltage = (((uint32_t)mV*256)/VREF_AC_MV);
	return triggerVoltage;
}

void ac_calibration(void)
{
	PORTB.DIRSET = PIN3_bm;
	PORTB.OUTCLR = PIN3_bm;
	uint8_t calibrating = 1;
	uint16_t ac_trigger_voltage_mv=AC_TRIGGER_VOLTAGE_MV_INIT;
	AC0.INTCTRL = AC_INTMODE_NORMAL_POSEDGE_gc;
	while (calibrating)
	{
		ac_trigger_voltage_mv += 50;
		AC0.DACREF = ac_calculate_trigger_voltage(ac_trigger_voltage_mv);
		_delay_ms(100);//Allow some time for the flag to be raised
		if (!(AC0.STATUS & AC_CMPIF_bm))
		{
			calibrating=0;
			PORTB.OUTSET =PIN3_bm;
		}
		AC0.STATUS=AC_CMPIF_bm;
	}
	
}

void ac_trig_event_enable(void)
{
	AC0.INTCTRL = AC_INTMODE_NORMAL_POSEDGE_gc | AC_CMP_bm;
	EVSYS.SWEVENTA = EVSYS_SWEVENTA_CH1_gc;
	EVSYS.CHANNEL0=EVSYS_CHANNEL0_CCL_LUT0_gc; //Output from the RS latch as trigger
	EVSYS.USERTCD0INPUTA=EVSYS_USER_CHANNEL0_gc;
	EVSYS.USEREVSYSEVOUTD = EVSYS_USER_CHANNEL0_gc;
}

void ac_trig_event_disable(void)
{
	AC0.INTCTRL &= ~AC_CMP_bm;
	EVSYS.CHANNEL0=EVSYS_CHANNEL0_OFF_gc;
	EVSYS.USERTCD0INPUTA = EVSYS_USER_OFF_gc;
	EVSYS.USEREVSYSEVOUTD = EVSYS_USER_OFF_gc;
}

void fan_start(void)
{
	ac_trig_event_disable();
	tcd_enable();
	ac_calibration();
	_delay_ms(1000);
	ac_trig_event_enable();

}

void button_init(void)
{
	PORTB.DIRCLR=PIN2_bm;
	PORTB.PIN2CTRL=PORT_ISC_FALLING_gc | PORT_PULLUPEN_bm;
	sei();
}

ISR(PORTB_PORT_vect)
{
	fan_start();
	PORTB.INTFLAGS=0xff; // Clear interrupt flags
}

ISR(AC0_AC_vect)
{
	AC0.STATUS = AC_CMPIF_bm; // Clear interrupt flag
	PORTC.OUTTGL = PIN4_bm;
}