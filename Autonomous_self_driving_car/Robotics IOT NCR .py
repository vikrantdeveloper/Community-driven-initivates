#written by Vikrant Thakur
#license : open source
import datetime
import time
import picamera
import RPi.GPIO as GPIO
from time import sleep
import paho.mqtt.client as mqtt
broker="localhost"
decode="hello"
GPIO.setmode(GPIO.BCM)
Trig=14
Echo=15
Motor1= 18
Motor2= 23
Motor3= 24
Motor4= 25
GPIO.setup(Motor1,GPIO.OUT)
GPIO.setup(Motor2,GPIO.OUT)
GPIO.setup(Motor3,GPIO.OUT)
GPIO.setup(Motor4,GPIO.OUT)
GPIO.setup(Trig,GPIO.OUT)
GPIO.setup(Echo,GPIO.IN)

try:

     date = datetime.datetime.now().strftime("%m_%d_%Y_%H_%M_%S")
     while True:        
          def on_connect(client, userdata, message, buf):
                time.sleep(1)
                print("log: "+ buf)
          def on_message(client,userdata,msg):
                topic=msg.topic
                print("message topic=",topic)
                globals()['decode']=str(msg.payload.decode("utf-8"))
                print("message received",decode)
          with picamera.PiCamera() as camera:
                  camera.start_preview()
                  camera.start_recording("/home/pi/"+ date + "video.h264")
                  camera.wait_recording(30)
                  camera.stop_recording()
                  camera.stop_preview()
          client= mqtt.Client("vikrant") 
          client.on_message = on_message
          print("connecting to broker ",broker)
          client.connect(broker) 
          client.loop_start()
          client.subscribe("hello")
          time.sleep(1)   
          client.loop_stop()
          client.disconnect()
          GPIO.output(Trig,False)
       	  time.sleep(1)
       	  GPIO.output(Trig,True)
       	  time.sleep(0.00001)
          GPIO.output(Trig,False)

          while GPIO.input(Echo)==False:
                end=time.time()

          while GPIO.input(Echo)==True:
                start=time.time()

          sig_time=start-end
          distance=165*100*sig_time

          if(distance>20.0):
            while(decode=='f'):

               GPIO.output(Motor1,GPIO.LOW)
               GPIO.output(Motor2,GPIO.HIGH)
               GPIO.output(Motor3,GPIO.LOW)
               GPIO.output(Motor4,GPIO.HIGH)
               print('Move Forward')
               time.sleep(1)
               if(decode=='r'):
               
                  GPIO.output(Motor1,GPIO.LOW)
                  GPIO.output(Motor2,GPIO.HIGH)
                  GPIO.output(Motor3,GPIO.LOW)
                  GPIO.output(Motor4,GPIO.LOW)
                  time.sleep(2)
                  print('Move Right')
                  break
               
               if(decode=='l'):

                 GPIO.output(Motor1,GPIO.LOW)
                 GPIO.output(Motor2,GPIO.LOW)
                 GPIO.output(Motor3,GPIO.LOW)
                 GPIO.output(Motor4,GPIO.HIGH)
                 time.sleep(2)
                 print('Move left')
                 break

            if(decode=='s'):
          
               GPIO.output(Motor1,GPIO.LOW)
               GPIO.output(Motor2,GPIO.LOW)
               GPIO.output(Motor3,GPIO.LOW)
               GPIO.output(Motor4,GPIO.LOW)
               time.sleep(0.1)
               print('Move Stop')
            print('distance from object is:() cm',format(distance))
except KeyboardInterrupt:

        GPIO.cleanup()
