# ADC_driver_LCD_potentiometer
 ADC driver with poteniometer and LCD driver
ADC Configurable Driver you can use it with many different configuration based on your project all you can do is to change the definitions in module.h
This is what exactly the best do to make your system independent on each other, MCAL layer is totally independent on the hardware ex.temp sensor or poteniometer
Also you can use it based on Polling or interrupt (you can also change this define (#define ADC_uint8IMPLEMENTATION_BASED	ADC_uint8POOLLING_BASED) to be (ADC_uint8INTERRUPT_BASED). 
Please note that because i implemented another header file called adc.h in this header file you can find ADC registers implemented with BIT_FIELDS using union and structure, as a result if you included <avr/interrupt.h> the code won't be compiled and get many compiler error because you will find multiple names of register with .Bits and .Byte and  the definition of Register in the standard library of AVR, so this code will be perfect match based on polling or interrupt but use the standard library instead of the bit field.
![Screenshot 2023-05-02 012429](https://user-images.githubusercontent.com/44003494/235541430-d1a9eb3a-5178-41d1-9f34-4b8887d078fb.png)
