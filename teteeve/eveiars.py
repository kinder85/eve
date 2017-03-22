# -*- coding: cp1252 -*-
import socket
import sys
import pyttsx

import os
from multiprocessing import Process, Queue
import time
import threading
import speech_recognition as sr
import pyaudio
from rivescript import RiveScript
import paho.mqtt.client as mqtt


client = mqtt.Client()
client.connect("192.168.100.103",1883,60)

rs = RiveScript()

rs.load_directory("./brain")

rs.sort_replies()
# Create a TCP/IP socket
#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
#host = "localhost"
#port = 10000
#server_address = (socket.gethostname(),port)
#print >>sys.stderr, 'starting up on %s port %s' % server_address
#sock.bind(server_address)
# Listen for incoming connections

        
        
        



def speak(q1):
    b=q1.get()
    engine = pyttsx.init()
    #if b!= o:
    engine.say(b)
    engine.runAndWait()
    
   


def listen(q):
    r = sr.Recognizer()
    r.pause_threshold = 0.8
    r.energy_threshold = 2000
    
    with sr.Microphone() as source:
        
        
        audio = r.listen(source)
        r.adjust_for_ambient_noise(source, duration = 1)
        
    try:
        #b=q.put(r.recognize_bing(audio,key=bcf76086c4d34b55bfe5270f377fe786, language = 'fr-FR'))
        #b=q.put(r.recognize_google(audio, language = 'fr-FR'))
        b=q.put(r.recognize_sphinx(audio, language = 'fr-FR'))
        return b
        
    except sr.UnknownValueError:
        #q1.put("j'ai pas compris tu peux repété?")
        print "hein"
        return(listen(q))
    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))
    

    


if __name__== '__main__':
    
    while True:
        
        q=Queue()
        q1=Queue()
        p=Process(target=speak,args=(q1,))
        t=Process(target=listen,args=(q,))
        #w=Process(target=server,args=(q1,))
        t.start()
        p.start()
        #w.start()
        response = raw_input("TOI : ")
        print "toi:" + response
        eve_speech = rs.reply('localuser',response)
        print "eve: " + eve_speech
        q1.put(eve_speech)
        time.sleep(1)

        if response == 'mode automatique':
            client.publish("corp/mode", "auto");
        if response == 'avance':
            client.publish("corp/move", "avance");
        if response == 'recule':
            client.publish("corp/move", "recule");            
        if response == 'tourne a droite':
            client.publish("corp/move", "droite");            
        if response == 'tourne a gauche':
            client.publish("corp/move", "gauche");        
        if response == 'stop':
            client.publish("corp/move", "stop");



         
