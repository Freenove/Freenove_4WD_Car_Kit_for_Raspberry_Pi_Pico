#!/usr/bin/python 
# -*- coding: utf-8 -*-
import numpy as np
import socket
import os
import io
import time
import imghdr
import sys
from threading import Timer
from threading import Thread
from PIL import Image
import string

from Command import COMMAND as cmd
from Thread import *
from Client_Ui import Ui_Client
from Video import *

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *

class mywindow(QMainWindow,Ui_Client):
    def __init__(self):
        global timer
        super(mywindow,self).__init__()
        self.setupUi(self)
        self.endChar='\n'
        self.intervalChar='#'
        self.trackFlag=0
        self.lightFlag=0
        self.commandFlag=1
        self.LED_Flag=0
        self.Matrix_Flag=0
        self.ws2812_number=255
        self.camera_angle=0
        super(mywindow, self).__init__()
        self.setupUi(self)
        self.img=QImage()
        self.img.load("*.png")
        self.img.save("*.png")
        self.img.load("*.jpg")
        self.img.save("*.jpg")
        self.W_flag=0

        self.setWindowIcon(QIcon('image/logo_Mini.png'))
        self.label_Video.setPixmap(QPixmap('image/Pico_W_4WD_Car.png'))
        ipValidator = QRegExpValidator(QRegExp('^((2[0-4]\d|25[0-5]|\d?\d|1\d{2})\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)$'))
        self.IP.setValidator(ipValidator)
        self.h=self.IP.text()
        self.TCP=VideoStreaming()
        self.servo1=90
        self.label_FineServo1.setText("0")
        self.m_DragPosition=self.pos()
        self.setMouseTracking(True)
        self.Key_W=False
        self.Key_A=False
        self.Key_S=False
        self.Key_D=False
        self.Key_Space=False
        self.setFocusPolicy(Qt.StrongFocus)
        self.progress_Power.setMinimum(0)
        self.progress_Power.setMaximum(100)
        self.label_Servo1.setText('90')
        self.HSlider_Servo1.setMinimum(30)
        self.HSlider_Servo1.setMaximum(150)
        self.HSlider_Servo1.setSingleStep(1)
        self.HSlider_Servo1.setValue(self.servo1)
        self.HSlider_FineServo1.setMinimum(-10)
        self.HSlider_FineServo1.setMaximum(10)
        self.HSlider_FineServo1.setSingleStep(1)
        self.HSlider_FineServo1.setValue(0)
        self.checkBox_Led_Mode1.setChecked(False)
        self.checkBox_Led_Mode2.setChecked(False)
        self.checkBox_Led_Mode3.setChecked(False)
        self.checkBox_Led_Mode4.setChecked(False)
        self.checkBox_Matrix_Mode1.setChecked(False)
        self.checkBox_Matrix_Mode2.setChecked(False)
        self.checkBox_Matrix_Mode3.setChecked(False)
        self.checkBox_Matrix_Mode4.setChecked(False)
        file = open('IP.txt', 'r')
        self.IP.setText(str(file.readline()))
        file.close()
        self.HSlider_Servo1.valueChanged.connect(self.Change_Left_Right)
        self.HSlider_FineServo1.valueChanged.connect(self.Fine_Tune_Left_Right)
        self.Led_Module.clicked.connect(lambda: self.LedChange(self.Led_Module))
        self.RGB.clicked.connect(lambda:self.LedChange(self.RGB))
        self.checkBox_Led_Mode1.stateChanged.connect(lambda:self.LedChange(self.checkBox_Led_Mode1))
        self.checkBox_Led_Mode2.stateChanged.connect(lambda:self.LedChange(self.checkBox_Led_Mode2))
        self.checkBox_Led_Mode3.stateChanged.connect(lambda:self.LedChange(self.checkBox_Led_Mode3))
        self.checkBox_Led_Mode4.stateChanged.connect(lambda:self.LedChange(self.checkBox_Led_Mode4))
        self.checkBox_Led_Mode5.stateChanged.connect(lambda:self.LedChange(self.checkBox_Led_Mode5))

        self.checkBox_Matrix_Mode1.stateChanged.connect(lambda:self.MatrixChange(self.checkBox_Matrix_Mode1))
        self.checkBox_Matrix_Mode2.stateChanged.connect(lambda:self.MatrixChange(self.checkBox_Matrix_Mode2))
        self.checkBox_Matrix_Mode3.stateChanged.connect(lambda:self.MatrixChange(self.checkBox_Matrix_Mode3))
        self.checkBox_Matrix_Mode4.stateChanged.connect(lambda:self.MatrixChange(self.checkBox_Matrix_Mode4))
        self.checkBox_Matrix_Mode5.stateChanged.connect(lambda:self.MatrixChange(self.checkBox_Matrix_Mode5))
        self.Track.clicked.connect(self.on_btn_Track)
        self.Light.clicked.connect(self.on_btn_Light)
        self.Ultrasonic.clicked.connect(self.on_btn_Ultrasonic)
        self.Btn_ForWard.pressed.connect(self.on_btn_ForWard)
        self.Btn_ForWard.released.connect(self.on_btn_Stop)
        self.Btn_Turn_Left.pressed.connect(self.on_btn_Turn_Left)
        self.Btn_Turn_Left.released.connect(self.on_btn_Stop)
        self.Btn_BackWard.pressed.connect(self.on_btn_BackWard)
        self.Btn_BackWard.released.connect(self.on_btn_Stop)
        self.Btn_Turn_Right.pressed.connect(self.on_btn_Turn_Right)
        self.Btn_Turn_Right.released.connect(self.on_btn_Stop)
        self.Btn_Left.clicked.connect(self.on_btn_Left)
        self.Btn_Home.clicked.connect(self.on_btn_Home)
        self.Btn_Right.clicked.connect(self.on_btn_Right)
        self.Btn_Buzzer.pressed.connect(self.on_btn_Buzzer)
        self.Btn_Buzzer.released.connect(self.on_btn_Buzzer)
        self.Btn_Connect.clicked.connect(self.on_btn_Connect)
        self.Window_Min.clicked.connect(self.windowMinimumed)
        self.Window_Close.clicked.connect(self.close)
        self.Color_W.textChanged.connect(lambda:self.WS2812_Text_Change())
        self.L1.clicked.connect(self.WS2812_Calculate)
        self.L2.clicked.connect(self.WS2812_Calculate)
        self.L3.clicked.connect(self.WS2812_Calculate)
        self.L4.clicked.connect(self.WS2812_Calculate)
        self.L5.clicked.connect(self.WS2812_Calculate)
        self.L6.clicked.connect(self.WS2812_Calculate)
        self.L7.clicked.connect(self.WS2812_Calculate)
        self.L8.clicked.connect(self.WS2812_Calculate)
        self.W.clicked.connect(self.ALL_Click)
    def mousePressEvent(self, event):
        if event.button()==Qt.LeftButton:
            self.m_drag=True
            self.m_DragPosition=event.globalPos()-self.pos()
            event.accept()
    def mouseMoveEvent(self, QMouseEvent):
        if QMouseEvent.buttons() and Qt.LeftButton:
            self.move(QMouseEvent.globalPos()-self.m_DragPosition)
            QMouseEvent.accept()
    def mouseReleaseEvent(self, QMouseEvent):
        self.m_drag=False
    def keyPressEvent(self, event):
        if(event.key() == Qt.Key_Up):
            self.on_btn_Up()
        elif(event.key() == Qt.Key_Left):
            self.on_btn_Left()
        elif(event.key() == Qt.Key_Down):
            self.on_btn_Down()
        elif(event.key() == Qt.Key_Right):
            self.on_btn_Right()
        elif(event.key() == Qt.Key_Home):
            self.on_btn_Home()
        if(event.key() == Qt.Key_L):
            self.LED_Flag+=1
            if self.LED_Flag == 1:
                self.checkBox_Led_Mode1.setChecked(True)
            elif self.LED_Flag == 2:
                self.checkBox_Led_Mode2.setChecked(True)
            elif self.LED_Flag == 3:
                self.checkBox_Led_Mode3.setChecked(True)
            elif self.LED_Flag == 4:
                self.checkBox_Led_Mode4.setChecked(True)
            elif self.LED_Flag == 5:
                self.checkBox_Led_Mode5.setChecked(True)
            elif self.LED_Flag == 6:
                self.checkBox_Led_Mode5.setChecked(False)
                self.LED_Flag=0
        if(event.key() == Qt.Key_K):
            self.Matrix_Flag+=1
            if self.Matrix_Flag == 1:
                self.checkBox_Matrix_Mode1.setChecked(True)
            elif self.Matrix_Flag == 2:
                self.checkBox_Matrix_Mode2.setChecked(True)
            elif self.Matrix_Flag == 3:
                self.checkBox_Matrix_Mode3.setChecked(True)
            elif self.Matrix_Flag == 4:
                self.checkBox_Matrix_Mode4.setChecked(True)
            elif self.Matrix_Flag == 5:
                self.checkBox_Matrix_Mode5.setChecked(True)
            elif self.Matrix_Flag == 6:
                self.checkBox_Matrix_Mode5.setChecked(False)
                self.Matrix_Flag=0
        if (event.key() == Qt.Key_J):
            if self.commandFlag:
                self.TCP.sendData(cmd.CMD_MATRIX_MOD + self.intervalChar + '7' + self.endChar)
        if (event.key() == Qt.Key_R):
            self.on_btn_Light()
        if (event.key() == Qt.Key_T):
            self.on_btn_Track()
        if (event.key() == Qt.Key_Y):
            self.on_btn_Ultrasonic()
        if  (event.key() == Qt.Key_C):
            self.on_btn_Connect()
        if event.isAutoRepeat():
            pass
        else :
            if event.key() == Qt.Key_W:
                self.on_btn_ForWard()
                self.Key_W=True
            elif event.key() == Qt.Key_S:
                self.on_btn_BackWard()
                self.Key_S=True
            elif event.key() == Qt.Key_A:
                self.on_btn_Turn_Left()
                self.Key_A=True
            elif event.key() == Qt.Key_D:                  
                self.on_btn_Turn_Right()
                self.Key_D=True  
            elif event.key() == Qt.Key_Space:  
                self.on_btn_Buzzer()
                self.Key_Space=True
    def keyReleaseEvent(self, event):
        if(event.key() == Qt.Key_W):
            time.sleep(0.05)
            if(event.key() == Qt.Key_W):
                if not(event.isAutoRepeat()) and self.Key_W==True:
                    self.on_btn_Stop()
                    self.Key_W=False
        elif(event.key() == Qt.Key_A):
            if not(event.isAutoRepeat()) and self.Key_A==True:
                self.on_btn_Stop()
                self.Key_A=False
        elif(event.key() == Qt.Key_S):
            if not(event.isAutoRepeat()) and self.Key_S==True:
                self.on_btn_Stop()
                self.Key_S=False
        elif(event.key() == Qt.Key_D):
            if not(event.isAutoRepeat()) and self.Key_D==True:
                self.on_btn_Stop()
                self.Key_D=False
        if(event.key() == Qt.Key_Space):
            if not(event.isAutoRepeat()) and self.Key_Space==True:
                self.on_btn_Buzzer()
                self.Key_Space=False

    def on_btn_Connect(self):
        file = open('IP.txt', 'w')
        file.write(self.IP.text())
        file.close()
        if self.Btn_Connect.text() == "Connect":
            self.h=self.IP.text()
            if self.IP.text()!="IP Address":
                self.TCP.StartTcpClient(self.h,)
                try:
                    self.recv=Thread(target=self.recvmassage)
                    self.recv.start()
                except:
                    print ('recv error')
                self.Btn_Connect.setText( "Disconnect")
                print ('Server address:'+str(self.h)+'\n')
        elif self.Btn_Connect.text()=="Disconnect":
            self.Btn_Connect.setText( "Connect")
            self.lightFlag=0
            self.trackFlag=0
            self.UltrasonicFlag = 0
            self.Track.setText("Track off")
            self.Light.setText("Light off")
            self.Ultrasonic.setText("Ultrasonic off")
            self.commandFlag = 1
            self.label_Video.setPixmap(QPixmap('image/Pico_W_4WD_Car.png'))
            try:
                self.timer.stop()
                # stop_thread(self.power)
                stop_thread(self.recv)
            except:
                pass
            self.TCP.StopTcpcClient()

    def on_btn_ForWard(self):
        if self.commandFlag:
            self.trackFlag = 0
            self.Track.setText("Track off")
            self.lightFlag = 0
            self.Light.setText("Light off")
            self.UltrasonicFlag = 0
            self.Ultrasonic.setText("Ultrasonic off")
            ForWard=self.intervalChar+str(50)+self.intervalChar+str(50)+self.endChar
            self.TCP.sendData(cmd.CMD_MOTOR+ForWard)
    def on_btn_Turn_Left(self):
        if self.commandFlag:
            self.trackFlag = 0
            self.Track.setText("Track off")
            self.lightFlag = 0
            self.Light.setText("Light off")
            self.UltrasonicFlag = 0
            self.Ultrasonic.setText("Ultrasonic off")
            Turn_Left=self.intervalChar+str(50)+self.intervalChar+str(-50)+self.endChar
            self.TCP.sendData(cmd.CMD_MOTOR+ Turn_Left)

    def on_btn_BackWard(self):
        if self.commandFlag:
            self.trackFlag = 0
            self.Track.setText("Track off")
            self.lightFlag = 0
            self.Light.setText("Light off")
            self.UltrasonicFlag = 0
            self.Ultrasonic.setText("Ultrasonic off")
            BackWard=self.intervalChar+str(-50)+self.intervalChar+str(-50)+self.endChar
            self.TCP.sendData(cmd.CMD_MOTOR+BackWard)
    def on_btn_Turn_Right(self):
        if self.commandFlag:
            self.trackFlag = 0
            self.Track.setText("Track off")
            self.lightFlag = 0
            self.Light.setText("Light off")
            self.UltrasonicFlag = 0
            self.Ultrasonic.setText("Ultrasonic off")
            Turn_Right=self.intervalChar+str(50)+self.intervalChar+str(-50)+self.endChar
            self.TCP.sendData(cmd.CMD_MOTOR+Turn_Right)
    def on_btn_Stop(self):
        if self.commandFlag:
            Stop=self.intervalChar+str(0)+self.intervalChar+str(0)+self.endChar
            self.TCP.sendData(cmd.CMD_MOTOR+Stop)
    def on_btn_Buzzer(self):
        if self.commandFlag:
            if self.Btn_Buzzer.text()=='Buzzer':
                self.TCP.sendData(cmd.CMD_BUZZER+self.intervalChar+'2000'+self.endChar)
                self.Btn_Buzzer.setText('Noise')
            else:
                self.TCP.sendData(cmd.CMD_BUZZER+self.intervalChar+'0'+self.endChar)
                self.Btn_Buzzer.setText('Buzzer')

    def on_btn_Left(self):
        self.servo1=self.servo1-10
        if self.servo1<=30:
            self.servo1=30
        self.HSlider_Servo1.setValue(self.servo1)
    def on_btn_Right(self):
        self.servo1=self.servo1+10
        if self.servo1>=150:
            self.servo1=150
        self.HSlider_Servo1.setValue(self.servo1)
    def on_btn_Home(self):
        self.servo1=90
        self.HSlider_Servo1.setValue(self.servo1)

    def on_btn_Track(self):#Tracking car control
        if self.commandFlag:
            if self.trackFlag==0:
                self.trackFlag=1
                self.lightFlag=0
                self.UltrasonicFlag = 0
                self.Ultrasonic.setText("Ultrasonic off")
                self.Light.setText("Light off")
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'2'+self.endChar)
                self.Track.setText("Track on")
            else:
                self.trackFlag = 0
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'0'+self.endChar)
                self.Track.setText("Track off")
    def on_btn_Light(self):#Light seeking car control
        if self.commandFlag:
            if self.lightFlag==0:
                self.lightFlag=1
                self.trackFlag = 0
                self.UltrasonicFlag = 0
                self.Ultrasonic.setText("Ultrasonic off")
                self.Track.setText("Track off")
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'1'+self.endChar)
                self.Light.setText("Light on")
            else:
                self.lightFlag = 0
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'0'+self.endChar)
                self.Light.setText("Light off")
    def on_btn_Ultrasonic(self):#Ultrasonic seeking car control
        if self.commandFlag:
            if self.UltrasonicFlag==0:
                self.lightFlag=0
                self.trackFlag = 0
                self.UltrasonicFlag = 1
                self.Light.setText("Light off")
                self.Track.setText("Track off")
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'3'+self.endChar)
                self.Ultrasonic.setText("Ultrasonic on")
            else:
                self.UltrasonicFlag = 0
                self.TCP.sendData(cmd.CMD_CAR_MODE+self.intervalChar+'0'+self.endChar)
                self.Ultrasonic.setText("Ultrasonic off")
    def on_btn_Cam_Left(self):
        self.camera_angle-=90
        if self.camera_angle<=-360:
            self.camera_angle = 0
    def on_btn_Cam_Right(self):
        self.camera_angle += 90
        if self.camera_angle>=360:
            self.camera_angle = 0
    def on_btn_Cam_Origin(self):
        self.camera_angle = 0
    def Change_Left_Right(self):#Left or Right
        if self.commandFlag:
            self.TCP.sendData(cmd.CMD_SERVO+self.intervalChar+str(self.servo1)+self.endChar)
        self.servo1=self.HSlider_Servo1.value()
        self.label_Servo1.setText("%d"%self.servo1)

    def Fine_Tune_Left_Right(self):#fine tune Left or Right
        self.label_FineServo1.setText(str(self.HSlider_FineServo1.value()))
        if self.commandFlag:
            data=self.servo1+self.HSlider_FineServo1.value()
            self.TCP.sendData(cmd.CMD_SERVO+self.intervalChar+str(data)+self.endChar)

    def windowMinimumed(self):
        self.showMinimized()
    def WS2812_Text_Change(self):
        if self.Color_W.text()=='':
            self.Color_W.setText('0')
        ws2812_w = int(self.Color_W.text())
        if ws2812_w >= 256:
            ws2812_w=255
            self.Color_W.setText(str(ws2812_w))
        if ws2812_w & 0x001 == 0x001:
            self.L1.setChecked(True)
        else:
            self.L1.setChecked(False)
        if ws2812_w & 0x002 == 0x002:
            self.L2.setChecked(True)
        else:
            self.L2.setChecked(False)
        if ws2812_w & 0x004 == 0x004:
            self.L3.setChecked(True)
        else:
            self.L3.setChecked(False)
        if ws2812_w & 0x008 == 0x008:
            self.L4.setChecked(True)
        else:
            self.L4.setChecked(False)
        if ws2812_w & 0x010 == 0x010:
            self.L5.setChecked(True)
        else:
            self.L5.setChecked(False)
        if ws2812_w & 0x020 == 0x020:
            self.L6.setChecked(True)
        else:
            self.L6.setChecked(False)
        if ws2812_w & 0x040 == 0x040:
            self.L7.setChecked(True)
        else:
            self.L7.setChecked(False)
        if ws2812_w & 0x080 == 0x080:
            self.L8.setChecked(True)
        else:
            self.L8.setChecked(False)

    def ALL_Click(self):
        if self.W_flag==0:
            self.W_flag =1
            self.L1.setChecked(False)
            self.L2.setChecked(False)
            self.L3.setChecked(False)
            self.L4.setChecked(False)
            self.L5.setChecked(False)
            self.L6.setChecked(False)
            self.L7.setChecked(False)
            self.L8.setChecked(False)
            self.Color_W.setText("0")
        else:
            self.W_flag = 0
            self.L1.setChecked(True)
            self.L2.setChecked(True)
            self.L3.setChecked(True)
            self.L4.setChecked(True)
            self.L5.setChecked(True)
            self.L6.setChecked(True)
            self.L7.setChecked(True)
            self.L8.setChecked(True)
            self.Color_W.setText("255")

    def WS2812_Calculate(self):
        if self.L1.isChecked() == True:
            self.ws2812_number=self.ws2812_number|0x01
        else:
            self.ws2812_number = self.ws2812_number & 0xffe
        if self.L2.isChecked() == True:
            self.ws2812_number = self.ws2812_number | 0x02
        else:
            self.ws2812_number = self.ws2812_number & 0xffd
        if self.L3.isChecked() == True:
            self.ws2812_number=self.ws2812_number|0x04
        else:
            self.ws2812_number = self.ws2812_number & 0xffb
        if self.L4.isChecked() == True:
            self.ws2812_number=self.ws2812_number|0x08
        else:
            self.ws2812_number = self.ws2812_number & 0xff7
        if self.L5.isChecked() == True:
            self.ws2812_number = self.ws2812_number | 0x10
        else:
            self.ws2812_number = self.ws2812_number & 0xfef
        if self.L6.isChecked() == True:
            self.ws2812_number=self.ws2812_number|0x20
        else:
            self.ws2812_number = self.ws2812_number & 0xfdf
        if self.L7.isChecked() == True:
            self.ws2812_number=self.ws2812_number|0x40
        else:
            self.ws2812_number = self.ws2812_number & 0xfbf
        if self.L8.isChecked() == True:
            self.ws2812_number = self.ws2812_number | 0x80
        else:
            self.ws2812_number = self.ws2812_number & 0xf7f
        self.Color_W.setText(str(self.ws2812_number))
    def LedChange(self,b):
        if b.text() == "RGB":
            color_palette = QColorDialog.getColor().name()
            self.Color_R.setText(str(int(color_palette[1:3], 16)))
            self.Color_G.setText(str(int(color_palette[3:5], 16)))
            self.Color_B.setText(str(int(color_palette[5:7], 16)))
        if b.text() == "Led_Module":
            if self.commandFlag:
                color = self.Color_W.text() + self.intervalChar + self.Color_R.text() + self.intervalChar + self.Color_G.text() + self.intervalChar + self.Color_B.text() + self.endChar
                self.TCP.sendData(cmd.CMD_LED + self.intervalChar + color + self.endChar)
        if b.text() == "Led_Mode1":
           if b.isChecked() == True:
               self.checkBox_Led_Mode2.setChecked(False)
               self.checkBox_Led_Mode3.setChecked(False)
               self.checkBox_Led_Mode4.setChecked(False)
               self.checkBox_Led_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'1'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'0'+self.endChar)
        if b.text() == "Led_Mode2":
           if b.isChecked() == True:
               self.checkBox_Led_Mode1.setChecked(False)
               self.checkBox_Led_Mode3.setChecked(False)
               self.checkBox_Led_Mode4.setChecked(False)
               self.checkBox_Led_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'2'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'0'+self.endChar)
        if b.text() == "Led_Mode3":
           if b.isChecked() == True:
               self.checkBox_Led_Mode1.setChecked(False)
               self.checkBox_Led_Mode2.setChecked(False)
               self.checkBox_Led_Mode4.setChecked(False)
               self.checkBox_Led_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'3'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'0'+self.endChar)
        if b.text() == "Led_Mode4":
           if b.isChecked() == True:
               self.checkBox_Led_Mode1.setChecked(False)
               self.checkBox_Led_Mode2.setChecked(False)
               self.checkBox_Led_Mode3.setChecked(False)
               self.checkBox_Led_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'4'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'0'+self.endChar)
        if b.text() == "Led_Mode5":
           if b.isChecked() == True:
               self.checkBox_Led_Mode1.setChecked(False)
               self.checkBox_Led_Mode2.setChecked(False)
               self.checkBox_Led_Mode3.setChecked(False)
               self.checkBox_Led_Mode4.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'5'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_LED_MOD+self.intervalChar+'0'+self.endChar)
    def MatrixChange(self,matrix):
        if matrix.text() == "Matrix_Mode1":
           if matrix.isChecked() == True:
               self.checkBox_Matrix_Mode2.setChecked(False)
               self.checkBox_Matrix_Mode3.setChecked(False)
               self.checkBox_Matrix_Mode4.setChecked(False)
               self.checkBox_Matrix_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'1'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'0'+self.endChar)
        if matrix.text() == "Matrix_Mode2":
           if matrix.isChecked() == True:
               self.checkBox_Matrix_Mode1.setChecked(False)
               self.checkBox_Matrix_Mode3.setChecked(False)
               self.checkBox_Matrix_Mode4.setChecked(False)
               self.checkBox_Matrix_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'2'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'0'+self.endChar)
        if matrix.text() == "Matrix_Mode3":
           if matrix.isChecked() == True:
               self.checkBox_Matrix_Mode2.setChecked(False)
               self.checkBox_Matrix_Mode1.setChecked(False)
               self.checkBox_Matrix_Mode4.setChecked(False)
               self.checkBox_Matrix_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'3'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'0'+self.endChar)
        if matrix.text() == "Matrix_Mode4":
           if matrix.isChecked() == True:
               self.checkBox_Matrix_Mode2.setChecked(False)
               self.checkBox_Matrix_Mode3.setChecked(False)
               self.checkBox_Matrix_Mode1.setChecked(False)
               self.checkBox_Matrix_Mode5.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'6'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'0'+self.endChar)
        if matrix.text() == "Matrix_Mode5":
           if matrix.isChecked() == True:
               self.checkBox_Matrix_Mode1.setChecked(False)
               self.checkBox_Matrix_Mode2.setChecked(False)
               self.checkBox_Matrix_Mode3.setChecked(False)
               self.checkBox_Matrix_Mode4.setChecked(False)
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'4'+self.endChar)
           else:
               if self.commandFlag:
                   self.TCP.sendData(cmd.CMD_MATRIX_MOD+self.intervalChar+'0'+self.endChar)
    def close(self):
        self.timer.stop()
        try:
            # stop_thread(self.power)
            stop_thread(self.recv)
        except:
            pass
        self.TCP.StopTcpcClient()
        QCoreApplication.instance().quit()
        os._exit(0)
    def Power(self):
        while True:
            try:
                if self.Btn_Connect.text()=="Disconnect":
                    self.TCP.sendData(cmd.CMD_POWER+self.intervalChar+self.endChar)
                time.sleep(3)
            except:
                break
    def recvmassage(self):
            self.TCP.socket1_connect(self.h)
            # self.power=Thread(target=self.Power)
            # self.power.start()
            restCmd=""
            while True:
                Alldata=restCmd+str(self.TCP.recvData())
                restCmd=""
                if Alldata=="":
                    break
                else:
                    cmdArray=Alldata.split("\n")
                    if(cmdArray[-1] != ""):
                        restCmd=cmdArray[-1]
                        cmdArray=cmdArray[:-1]
                for oneCmd in cmdArray:
                    Massage=oneCmd.split("#")
                    if cmd. CMD_POWER in Massage:
                        if float(Massage[1]) >= 7.0:
                            percent_power=int((float(Massage[1])-7)/1.40*100)
                        else:
                            percent_power = 0
                        self.progress_Power.setValue(percent_power)

if __name__ == '__main__':
    QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QApplication(sys.argv)
    myshow=mywindow()
    myshow.show()
    sys.exit(app.exec_())
