#This is a makefile for avr,written by Sichen.

#---------------------------------------------------------------------------------------------
MCU=atmega16
FRE=8000000

# ISP=bsd      PORT=/dev/parport0
# ISP=ponyser  PORT=/dev/ttyS1
# ISP=stk500   PORT=/dev/ttyS1
# ISP=usbasp   PORT=/dev/usb/ttyUSB0
# ISP=stk500v2 PORT=/dev/ttyUSB0
# ISP=stk200   PORT=/dev/parport0

ISP=usbasp
PORT=PORT=/dev/usb/ttyUSB0
HFUSE=0xc9
LFUSE=0x3f

CSR=ds2788_lcd.c ds2788.c lcd.c  #添加或者删除C源文件
CSR1=
OBJ=ds2788_lcd.o ds2788.o lcd.o  #添加或者删除o源文件
OBJ1=

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# AVR-GCC代码优化级别，选项：[0, 1, 2, 3, s]

CS= -Wall -Wextra -Os -g -DF_CPU=$(FRE) -mmcu=$(MCU) -ffunction-sections\
 -Wl,-gc-sections,--relax

CS1= -Wall -Wextra -Os -g -DF_CPU=$(FRE) -mmcu=$(MCU) -ffunction-sections\
 -Wl,-gc-sections,--relax


#---------------------------------------------------------------------------------------------
main.hex:main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

$main_eeprom.hex:main.elf
	avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@
 
$(OBJ):$(CSR)
	avr-gcc $(CS) -c $(CSR) 

main.elf:$(OBJ) 
	avr-gcc $(CS) -o main.elf $(OBJ) 
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#---------------------------------------------------------------------------------------------
.PHONY:isp
isp:main.hex
	avrdude -c $(ISP) -p $(MCU) -P $(PORT) -U flash:w:main.hex

.PHONY:fuses
fuse:
	avrdude -c ${ISP} -p ${MCU} -P ${PORT} -u -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m

.PHONY:res
res:
	avrdude -c ${ISP} -p ${MCU} -P ${PORT}

.PHONY:readfuse
readfuse:
	avrdude -c ${ISP} -p ${MCU} -P ${PORT} -q -U hfuse:r:-:h\
	 -U lfuse:r:-:h -U lock:r:-:h -U calibration:r:-:h

.PHONY:readflash
readflash:
	avrdude -c ${ISP} -p ${MCU} -P ${PORT} -U flash:r:flash_dump.bin:r

.PHONY:readeep
readeep:
	avrdude -c ${ISP} -p ${MCU} -P ${PORT} -U eeprom:r:eeprom_dump.bin:r

.PHONY:clean
clean:
	$(RM) *.elf *.hex *.o 
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
