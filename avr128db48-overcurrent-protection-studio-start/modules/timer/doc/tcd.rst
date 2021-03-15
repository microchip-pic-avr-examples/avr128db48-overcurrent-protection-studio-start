======================
TCD driver
======================
The Timer/Counter type D (TCD) is a high performance waveform controller that consists of an
asynchronous counter, a prescaler, compare logic, capture logic, and control logic. The purpose of the
TCD is to control power application like LED, motor control, H-bridge and power converters.
The TCD counter can select what clock source it should run on. The counter and the compare logic is
used for waveform generation on two separate outputs and can generate outputs such as pulse-width
modulation. Each output has a corresponding input event that can be used to capture counter values or
trigger fault exceptions. The different input fault options will enable fault protection for safe and
deterministic handling, disabling and/or shut down of external drivers.

Features
--------
* Initialization

Applications
------------
* Capture the event input.
* Timeout Checking
* 4-bit Pulse Width Modulation

Dependencies
------------
* CLKCTRL for clock
* CPUINT for Interrupt
* EVSYS for events
* UPDI for debug

Note
----
* ISR will be generated only when Global Interrupt checkbox and driver_isr Harness checkbox are enabled

Concurrency
-----------
N/A

Limitations
-----------
N/A

Knows issues and workarounds
----------------------------
N/A