# -*- coding: cp1252 -*-
import time
import threading
import serial


import sys

import paho.mqtt.client as mqtt
import os
from multiprocessing import Process, Queue
import webiopi
import subprocess
import sys

ser1 = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
vit = 120
delay = 10
mode = 'manuel'
client = mqtt.Client()
client.connect("localhost",1883,60)





@webiopi.macro
def FORWARD():
        ser1.write('1,%d,%d.'%(vit, delay))
        
@webiopi.macro
def BACKWARD():
        ser1.write('2,%d,%d.'%(vit, delay))
        
@webiopi.macro
def RIGHT():
        ser1.write('4,%d,%d.'%(vit, delay))
        
@webiopi.macro
def LEFT():
        ser1.write('3,%d,%d.'%(vit, delay))
       
@webiopi.macro
def STOP():
        ser1.write('5,%d,%d.'%(vit, delay))




  

def on_message(mosq, userdata, msg):
        print("Received message '" + str(msg.payload) + "' on topic '"+ msg.topic + "' with QoS " + str(msg.qos))
        

def on_message_move(mosq, obj, msg):
    move = str(msg.payload)
        if move == "avance":
                ser1.write('1,%d,%d.'%(vit, delay))
        if move == "recule":
                ser1.write('2,%d,%d.'%(vit, delay))
        if move == "droite":
                ser1.write('4,%d,%d.'%(vit, delay))
        if move == "gauche":
                ser1.write('3,%d,%d.'%(vit, delay))                
        if move == "stop":
                ser1.write('5,%d,%d.'%(vit, delay))
    


def on_message_mode(mosq, obj, msg):
        mod = str(msg.payload)
        if mod == "auto":
                return mode == 'auto'
def setup():
        STOP()
        
def destroy():
  t.join()


client.message_callback_add('corp/move', on_message_move)
client.message_callback_add('corp/mode', on_message_mod)


client.on_message = on_message
client.subscribe("corp/#", 0)
client.loop_forever()
#if __name__='__main__':
  
