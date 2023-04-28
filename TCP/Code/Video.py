#!/usr/bin/python 
# -*- coding: utf-8 -*-
import socket

class VideoStreaming:
    def __init__(self):
        self.connect_Flag=False
    def StartTcpClient(self,IP):
        self.client_socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    def StopTcpcClient(self):
        try:
            self.client_socket1.shutdown(2)
            self.client_socket1.close()
        except:
            pass
                  
    def sendData(self,s):
        try:
            if self.connect_Flag:
                self.client_socket1.send(s.encode('utf-8'))
        except:
            pass

    def recvData(self):
        data=""
        try:
            data=self.client_socket1.recv(1024).decode('utf-8')
        except:
            pass
        return data

    def socket1_connect(self,ip):
        try:
            self.client_socket1.connect((ip, 4002))
            self.connect_Flag=True
            print ("Connecttion Successful !")
        except Exception as e:
            print ("Connect to server Faild!: Server IP is right? Server is opend?")
            self.connect_Flag=False

if __name__ == '__main__':
    pass

