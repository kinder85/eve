# -*- coding: cp1252 -*-
import socket
import sys
import pyttsx
import aiml
import os
from multiprocessing import Process, Queue
import time
import threading
import speech_recognition as sr
import pyaudio

# Create a TCP/IP socket
#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
#host = "localhost"
#port = 10000
#server_address = (socket.gethostname(),port)
#print >>sys.stderr, 'starting up on %s port %s' % server_address
#sock.bind(server_address)
# Listen for incoming connections
kernel = aiml.Kernel()
        
        
        

if os.path.isfile("bot_brain.brn"):
    kernel.bootstrap(brainFile = "bot_brain.brn")
else:
    kernel.bootstrap(learnFiles = "std-startup.xml", commands = "load aiml b")
    #kernel.saveBrain("bot_brain.brn")

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
    
#def server(q1):
    #sock.listen(1)


    # Wait for a connectio

    
    #connection, client_address = sock.accept()
    
    #while True:
        #data = q1.get()
        #if data:
            #connection.send(data)
    


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
        eve_speech = kernel.respond(response)
        print "eve: " + eve_speech
        q1.put(eve_speech)
        time.sleep(1)

         
