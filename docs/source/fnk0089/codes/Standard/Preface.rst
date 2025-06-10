##############################################################################
Preface
##############################################################################

Welcome to use Freenove 4WD Car Kit for Raspberry Pi Pico (W). Following this tutorial, you can make a very cool car with many functions. 

Based on the Raspberry Pi Pico (W) development board, a popular IoT control board, this kit uses the very popular Arduino IDE for programming, so you can share and exchange your experience and design ideas with enthusiasts all over the world. The parts in the kit include all electronic components, modules, and mechanical components required for making the car. They are all individually packaged. There are detailed assembly and debugging instructions in this book. If you encounter any problems, please feel free to contact us for fast and free technical support.

support@freenove.com 

This car does not require a high threshold for users. Even if you know little professional knowledge, you can make your own smart car easily with the guidance of the tutorial. If you’re really interested in Raspberry Pi Pico (W) and hope to learn how to program and build circuits, please visit our website: www.freenove.com or contact us to buy our kit designed for beginners: :red:`Freenove Ultimate Kit for Raspberry Pi Pico.`

Raspberry Pi Pico
************************************

Raspberry Pi Pico applies to all chapters except Wireless in this tutorial. 

Before learning Pico, we need to know about it. Below is an imitated diagram of Pico, which looks very similar to the actual Pico.

.. image:: ../_static/imgs/Standard/Preface/Preface00.png
    :align: center

The hardware interfaces are distributed as follows:

.. image:: ../_static/imgs/Standard/Preface/Preface01.png
    :align: center

.. table::
    :align: center
    :widths: 1 1
    :width: 80%

    +-------------+---------------+
    | Frame color | Description   |
    +-------------+---------------+
    | |Preface02| | Pins          |
    +-------------+---------------+
    | |Preface03| | BOOTSE button |
    +-------------+---------------+
    | |Preface04| | USB port      |
    +-------------+---------------+
    | |Preface05| | LED           |
    +-------------+---------------+
    | |Preface06| | Debugging     |
    +-------------+---------------+

.. |Preface02| image:: ../_static/imgs/Standard/Preface/Preface02.png
.. |Preface03| image:: ../_static/imgs/Standard/Preface/Preface03.png
.. |Preface04| image:: ../_static/imgs/Standard/Preface/Preface04.png
.. |Preface05| image:: ../_static/imgs/Standard/Preface/Preface05.png
.. |Preface06| image:: ../_static/imgs/Standard/Preface/Preface06.png

Function definition of pins:

.. image:: ../_static/imgs/Standard/Preface/Preface07.png
    :align: center

.. table::
    :align: center

    +-------------+----------------+-------------+-----------+
    | Color       | Pins           | Color       | Pins      |
    +-------------+----------------+-------------+-----------+
    | |Preface08| | GND            | |Preface13| | Power     |
    +-------------+----------------+-------------+-----------+
    | |Preface09| | GPIO           | |Preface14| | ADC       |
    +-------------+----------------+-------------+-----------+
    | |Preface10| | UART(defualt)  | |Preface15| | UART      |
    +-------------+----------------+-------------+-----------+
    | |Preface11| | SPI            | |Preface16| | I2C       |
    +-------------+----------------+-------------+-----------+
    | |Preface12| | System Control | |Preface17| | Debugging |
    +-------------+----------------+-------------+-----------+

.. |Preface08| image:: ../_static/imgs/Standard/Preface/Preface08.png
.. |Preface09| image:: ../_static/imgs/Standard/Preface/Preface09.png
.. |Preface10| image:: ../_static/imgs/Standard/Preface/Preface10.png
.. |Preface11| image:: ../_static/imgs/Standard/Preface/Preface11.png
.. |Preface12| image:: ../_static/imgs/Standard/Preface/Preface12.png
.. |Preface13| image:: ../_static/imgs/Standard/Preface/Preface13.png
.. |Preface14| image:: ../_static/imgs/Standard/Preface/Preface14.png
.. |Preface15| image:: ../_static/imgs/Standard/Preface/Preface15.png
.. |Preface16| image:: ../_static/imgs/Standard/Preface/Preface16.png
.. |Preface17| image:: ../_static/imgs/Standard/Preface/Preface17.png

For details: https://datasheets.raspberrypi.org/pico/pico-datasheet.pdf

UART, I2C, SPI Defalt Pin
===============================================

In Arduino IDE, the default pins of serial port are Pin0 and Pin1. 

.. note::
    
    Serial port is virtualized by RP2040. Therefore, when using the serial port, please enable the verification function of DTR. It can work under any baud rate.

UART
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | UART_BAUDRATE | X       |
    +---------------+---------+
    | UART_BITS     | 8       |
    +---------------+---------+
    | UART_STOP     | 1       |
    +---------------+---------+
    | UART_TX       | Pin 0   |
    +---------------+---------+
    | UART_RX       | Pin 1   |
    +---------------+---------+

I2C
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | I2C Frequency | 400000  |
    +---------------+---------+
    | I2C_SDA       | Pin 4   |
    +---------------+---------+
    | I2C_SCL       | Pin 5   |
    +---------------+---------+

SPI
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +--------------+---------+
    |   Function   | Default |
    +==============+=========+
    | SPI_BAUDRATE | 1000000 |
    +--------------+---------+
    | SPI_POLARITY | 0       |
    +--------------+---------+
    | SPI_PHASE    | 0       |
    +--------------+---------+
    | SPI_BITS     | 8       |
    +--------------+---------+
    | SPI_FIRSTBIT | MSB     |
    +--------------+---------+
    | SPI_SCK      | Pin 18  |
    +--------------+---------+
    | SPI_MOSI     | Pin 19  |
    +--------------+---------+
    | SPI_MISO     | Pin 16  |
    +--------------+---------+
    | SPI_SS       | Pin 17  |
    +--------------+---------+

Raspberry Pi Pico W
********************************************

:red:`Raspberry Pi Pico W applies to all chapters in this tutorial.`

Raspberry Pi Pico W adds CYW43439 as the WiFi function on the basis of Raspberry Pi Pico. It is connected to RP2040 chip through SPI interface.

.. image:: ../_static/imgs/Standard/Preface/Preface18.png
    :align: center

The hardware interfaces are distributed as follows:

.. image:: ../_static/imgs/Standard/Preface/Preface19.png
    :align: center

.. table::
    :align: center
    :widths: 1 1
    :width: 80%

    +-------------+---------------+
    | Frame color | Description   |
    +-------------+---------------+
    | |Preface02| | Pins          |
    +-------------+---------------+
    | |Preface03| | BOOTSE button |
    +-------------+---------------+
    | |Preface04| | USB port      |
    +-------------+---------------+
    | |Preface05| | LED           |
    +-------------+---------------+
    | |Preface06| | Debugging     |
    +-------------+---------------+
    | |Preface20| | Wireless      |
    +-------------+---------------+

.. |Preface20| image:: ../_static/imgs/Standard/Preface/Preface20.png

Function definition of pins:

.. image:: ../_static/imgs/Standard/Preface/Preface21.png
    :align: center

.. table::
    :align: center

    +-------------+----------------+-------------+-----------+
    | Color       | Pins           | Color       | Pins      |
    +-------------+----------------+-------------+-----------+
    | |Preface08| | GND            | |Preface13| | Power     |
    +-------------+----------------+-------------+-----------+
    | |Preface09| | GPIO           | |Preface14| | ADC       |
    +-------------+----------------+-------------+-----------+
    | |Preface10| | UART(defualt)  | |Preface15| | UART      |
    +-------------+----------------+-------------+-----------+
    | |Preface11| | SPI            | |Preface16| | I2C       |
    +-------------+----------------+-------------+-----------+
    | |Preface12| | System Control | |Preface17| | Debugging |
    +-------------+----------------+-------------+-----------+

For details: https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf

UART, I2C, SPI, Wireless Defalt Pin
===============================================

In Arduino IDE, the default pins of serial port are Pin0 and Pin1. 

.. note::
    
    Serial port is virtualized by RP2040. Therefore, when using the serial port, please enable the verification function of DTR. It can work under any baud rate.

UART
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | UART_BAUDRATE | X       |
    +---------------+---------+
    | UART_BITS     | 8       |
    +---------------+---------+
    | UART_STOP     | 1       |
    +---------------+---------+
    | UART_TX       | Pin 0   |
    +---------------+---------+
    | UART_RX       | Pin 1   |
    +---------------+---------+

I2C
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | I2C Frequency | 400000  |
    +---------------+---------+
    | I2C_SDA       | Pin 4   |
    +---------------+---------+
    | I2C_SCL       | Pin 5   |
    +---------------+---------+

SPI
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +--------------+---------+
    |   Function   | Default |
    +==============+=========+
    | SPI_BAUDRATE | 1000000 |
    +--------------+---------+
    | SPI_POLARITY | 0       |
    +--------------+---------+
    | SPI_PHASE    | 0       |
    +--------------+---------+
    | SPI_BITS     | 8       |
    +--------------+---------+
    | SPI_FIRSTBIT | MSB     |
    +--------------+---------+
    | SPI_SCK      | Pin 18  |
    +--------------+---------+
    | SPI_MOSI     | Pin 19  |
    +--------------+---------+
    | SPI_MISO     | Pin 16  |
    +--------------+---------+
    | SPI_SS       | Pin 17  |
    +--------------+---------+

Wireless
----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +----------+------------+
    | Function |  Default   |
    +==========+============+
    | WL_ON    | GPIO23     |
    +----------+------------+
    | WL_D     | GPIO24     |
    +----------+------------+
    | WL_CLK   | GPIO29_ADC |
    +----------+------------+
    | WL_CS    | GPIO25     |
    +----------+------------+

Raspberry Pi Pico 2
*************************************

Raspberry Pi Pico 2 is applicable to all chapters in this tutorial except RFID and those involving WiFi. 

Raspberry Pi Pico 2 uses RP2350 chip as the main controller, which equipped with dual Cortex-M33 or Hazard3 processors, capable of running up to 150 MHz, providing a significant boost in processing power, compared with the original Pico. It also doubles the memory with 520KB of SRAM and 4MB of onboard flash memory, with the ADC sampling frequency increasing to up to 500ksps. In addition, it adds 8 more PWM channels, and features additional interfaces like 2x Timer with 4 alarms, 1x AON Timer and 4 x PIO.

.. image:: ../_static/imgs/Standard/Preface/Preface22.png
    :align: center

The hardware interfaces are distributed as follows:

.. image:: ../_static/imgs/Standard/Preface/Preface23.png
    :align: center

.. table::
    :align: center
    :widths: 1 1
    :width: 80%

    +-------------+---------------+
    | Frame color | Description   |
    +-------------+---------------+
    | |Preface02| | Pins          |
    +-------------+---------------+
    | |Preface03| | BOOTSE button |
    +-------------+---------------+
    | |Preface04| | USB port      |
    +-------------+---------------+
    | |Preface05| | LED           |
    +-------------+---------------+
    | |Preface06| | Debugging     |
    +-------------+---------------+

Function definition of pins:

.. image:: ../_static/imgs/Standard/Preface/Preface24.png
    :align: center

.. table::
    :align: center

    +-------------+----------------+-------------+-----------+
    | Color       | Pins           | Color       | Pins      |
    +-------------+----------------+-------------+-----------+
    | |Preface08| | GND            | |Preface13| | Power     |
    +-------------+----------------+-------------+-----------+
    | |Preface09| | GPIO           | |Preface14| | ADC       |
    +-------------+----------------+-------------+-----------+
    | |Preface10| | UART(defualt)  | |Preface15| | UART      |
    +-------------+----------------+-------------+-----------+
    | |Preface11| | SPI            | |Preface16| | I2C       |
    +-------------+----------------+-------------+-----------+
    | |Preface12| | System Control | |Preface17| | Debugging |
    +-------------+----------------+-------------+-----------+

UART, I2C, SPI, Wireless Defalt Pin
===============================================

UART
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | UART_BAUDRATE | X       |
    +---------------+---------+
    | UART_BITS     | 8       |
    +---------------+---------+
    | UART_STOP     | 1       |
    +---------------+---------+
    | UART_TX       | Pin 0   |
    +---------------+---------+
    | UART_RX       | Pin 1   |
    +---------------+---------+

I2C
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | I2C Frequency | 400000  |
    +---------------+---------+
    | I2C_SDA       | Pin 4   |
    +---------------+---------+
    | I2C_SCL       | Pin 5   |
    +---------------+---------+

SPI
--------------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +--------------+---------+
    |   Function   | Default |
    +==============+=========+
    | SPI_BAUDRATE | 1000000 |
    +--------------+---------+
    | SPI_POLARITY | 0       |
    +--------------+---------+
    | SPI_PHASE    | 0       |
    +--------------+---------+
    | SPI_BITS     | 8       |
    +--------------+---------+
    | SPI_FIRSTBIT | MSB     |
    +--------------+---------+
    | SPI_SCK      | Pin 18  |
    +--------------+---------+
    | SPI_MOSI     | Pin 19  |
    +--------------+---------+
    | SPI_MISO     | Pin 16  |
    +--------------+---------+
    | SPI_SS       | Pin 17  |
    +--------------+---------+

Raspberry Pi Pico 2W
*************************************

:red:`Raspberry Pi Pico 2W applies to all chapters in this tutorial.`

The Raspberry Pi Pico 2W adds WiFi functionality based on the Raspberry Pi Pico 2 by incorporating the CYW43439 module, which connects to the RP2350 chip via an SPI interface.

.. image:: ../_static/imgs/Standard/Preface/Preface25.png
    :align: center

The hardware interfaces are distributed as follows:

.. image:: ../_static/imgs/Standard/Preface/Preface26.png
    :align: center

.. table::
    :align: center
    :widths: 1 1
    :width: 80%

    +-------------+---------------+
    | Frame color | Description   |
    +-------------+---------------+
    | |Preface02| | Pins          |
    +-------------+---------------+
    | |Preface03| | BOOTSE button |
    +-------------+---------------+
    | |Preface04| | USB port      |
    +-------------+---------------+
    | |Preface05| | LED           |
    +-------------+---------------+
    | |Preface06| | Debugging     |
    +-------------+---------------+
    | |Preface20| | Wireless      |
    +-------------+---------------+

Function definition of pins:

.. image:: ../_static/imgs/Standard/Preface/Preface27.png
    :align: center

.. table::
    :align: center

    +-------------+----------------+-------------+-----------+
    | Color       | Pins           | Color       | Pins      |
    +-------------+----------------+-------------+-----------+
    | |Preface08| | GND            | |Preface13| | Power     |
    +-------------+----------------+-------------+-----------+
    | |Preface09| | GPIO           | |Preface14| | ADC       |
    +-------------+----------------+-------------+-----------+
    | |Preface10| | UART(defualt)  | |Preface15| | UART      |
    +-------------+----------------+-------------+-----------+
    | |Preface11| | SPI            | |Preface16| | I2C       |
    +-------------+----------------+-------------+-----------+
    | |Preface12| | System Control | |Preface17| | Debugging |
    +-------------+----------------+-------------+-----------+

For details: https://datasheets.raspberrypi.com/picow/pico-2-w-datasheet.pdf

UART, I2C, SPI, Wireless Defalt Pin
===============================================

UART
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | UART_BAUDRATE | X       |
    +---------------+---------+
    | UART_BITS     | 8       |
    +---------------+---------+
    | UART_STOP     | 1       |
    +---------------+---------+
    | UART_TX       | Pin 0   |
    +---------------+---------+
    | UART_RX       | Pin 1   |
    +---------------+---------+

I2C
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +---------------+---------+
    |   Function    | Default |
    +===============+=========+
    | I2C Frequency | 400000  |
    +---------------+---------+
    | I2C_SDA       | Pin 4   |
    +---------------+---------+
    | I2C_SCL       | Pin 5   |
    +---------------+---------+

SPI
-----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +--------------+---------+
    |   Function   | Default |
    +==============+=========+
    | SPI_BAUDRATE | 1000000 |
    +--------------+---------+
    | SPI_POLARITY | 0       |
    +--------------+---------+
    | SPI_PHASE    | 0       |
    +--------------+---------+
    | SPI_BITS     | 8       |
    +--------------+---------+
    | SPI_FIRSTBIT | MSB     |
    +--------------+---------+
    | SPI_SCK      | Pin 18  |
    +--------------+---------+
    | SPI_MOSI     | Pin 19  |
    +--------------+---------+
    | SPI_MISO     | Pin 16  |
    +--------------+---------+
    | SPI_SS       | Pin 17  |
    +--------------+---------+

Wireless
----------------------------------

.. table::
    :align: center
    :class: freenove-ow

    +----------+------------+
    | Function |  Default   |
    +==========+============+
    | WL_ON    | GPIO23     |
    +----------+------------+
    | WL_D     | GPIO24     |
    +----------+------------+
    | WL_CLK   | GPIO29_ADC |
    +----------+------------+
    | WL_CS    | GPIO25     |
    +----------+------------+

Pins of the Car
************************************

To learn what each GPIO corresponds to, please refer to the following table.

The functions of the pins are allocated as follows:

.. table::
    :align: center

    +-----------------------------+--------------------------------------+-------------+
    | Pins of Raspberry Pi Pico W | Funtions                             | Description |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO18                      | Motor                                | M1_IN1      |
    +-----------------------------+                                      +-------------+
    | GPIO19                      |                                      | M1_IN2      |
    +-----------------------------+                                      +-------------+
    | GPIO20                      |                                      | M2_IN1      |
    +-----------------------------+                                      +-------------+
    | GPIO21                      |                                      | M2_IN2      |
    +-----------------------------+                                      +-------------+
    | GPIO6                       |                                      | M3_IN1      |
    +-----------------------------+                                      +-------------+
    | GPIO7                       |                                      | M3_IN2      |
    +-----------------------------+                                      +-------------+
    | GPIO8                       |                                      | M4_IN1      |
    +-----------------------------+                                      +-------------+
    | GPIO9                       |                                      | M4_IN2      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO13                      | Servo                                | Servo1      |
    +-----------------------------+                                      +-------------+
    | GPIO14                      |                                      | Servo2      |
    +-----------------------------+                                      +-------------+
    | GPIO15                      |                                      | Servo3      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO10                      | Tracking module                      | Track1      |
    +-----------------------------+                                      +-------------+
    | GPIO11                      |                                      | Track2      |
    +-----------------------------+                                      +-------------+
    | GPIO12                      |                                      | Track3      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO4                       | I2C port/Ultrasonic module interface | SDA/Trig    |
    +-----------------------------+                                      +-------------+
    | GPIO5                       |                                      | SCL/Echo    |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO16                      | WS2812                               | WS2812      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO26                      | Battery detection                    | A0          |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO27                      | Search light ADC port                | A1          |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO28                      | Search light ADC port                | A2          |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO22                      | Unused GPIO                          | GPIO22      |
    +-----------------------------+                                      +-------------+
    | GPIO17                      |                                      | GPIO17      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO3                       | Infrared receiver port               | IR          |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO2                       | Buzzer port                          | Buzzer      |
    +-----------------------------+--------------------------------------+-------------+
    | GPIO1                       | Serial port                          | RX          |
    +-----------------------------+                                      +-------------+
    | GPIO0                       |                                      | TX          |
    +-----------------------------+--------------------------------------+-------------+

Introduction to the Car
************************************************

The function diagram of the Raspberry Pi Pico W car is as follows:

.. image:: ../_static/imgs/Standard/Preface/Preface28.png
    :align: center