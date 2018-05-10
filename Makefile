#Change this variable to point to your Arduino device
#Mac - it may be different
#DEVICE = /dev/tty.usbmodemFD121

#Linux (/dev/ttyACM0 or possibly /dev/ttyUSB0)
#DEVICE = /dev/ttyACM0

#Windows
DEVICE = COM7

#default target to compile the code
main: main.c serial.c os.c synchro.c
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000 -O2 -o main.elf main.c serial.c os.c synchro.c
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

program2: program2.c serial.c os.c synchro.c
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000 -O2 -o main.elf program2.c serial.c os.c synchro.c
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

blink: blink.c serial.c os.c
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000 -O2 -o main.elf blink.c serial.c os.c
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf

statsOnly: statsOnly.c serial.c os.c
	avr-gcc -mmcu=atmega2560 -DF_CPU=16000000 -O2 -o main.elf statsOnly.c serial.c os.c
	avr-objcopy -O ihex main.elf main.hex
	avr-size main.elf


#flash the Arduino with the program
program: main.hex
	#Mac
	avrdude -D -pm2560 -P $(DEVICE) -c wiring -F -u -U flash:w:main.hex

#remove build files
clean:
	rm -fr *.elf *.hex *.o
