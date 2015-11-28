Esse Projeto consiste em desenvolver um simulador de Pipeline


#TESTE DO DECODE COM PYTHON--------------------------------------------

#Inicia o python
python

#importa a lib
>> import serial

#configura a conexão
>> ser = serial.Serial('/dev/ttyACM0', 9600)

#código da operação 0b00000000 = Soma
#registrador onde será salvo 0b00000001 = $at
#registrador de soma 0b00000010 = $v0
#registrador de soma 0b00000001 = $at
>>> instruction = chr(0)+chr(1)+chr(2)+chr(1)

#Escreve a instrução
>>> ser.write(instruction)

#Testes prontos:

>>> instructionADD = chr(0)+chr(1)+chr(2)+chr(1) #ADD
>>> ser.write(instructionADD)
>>> instructionSUB = chr(1)+chr(1)+chr(2)+chr(1) #SUB
>>> ser.write(instructionSUB)
>>> instructionADDI = chr(2)+chr(1)+chr(2)+chr(1) #ADDI
>>> ser.write(instructionADDI)
>>> instructionLW = chr(3)+chr(1)+chr(2)+chr(1) #LW
>>> ser.write(instructionLW)
>>> instructionSW = chr(4)+chr(1)+chr(2)+chr(1) #SW
>>> ser.write(instructionSW)

#----------------------------------------------------------------------