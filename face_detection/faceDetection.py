#!/usr/bin/env python
# -*- coding: utf-8 -*-
""" Author: José Diôgo
    Based on: OpenCv faceDetection Tutorial
    Date: 22/10/2016 
"""
#bibliotecas necessárias
import numpy
import cv2
#carrega os classificadores
frontal_face_cascade = cv2.CascadeClassifier('cascade/haarcascade_frontalface_default.xml')
profile_face_cascade = cv2.CascadeClassifier('cascade/haarcascade_profileface.xml')
#carrega a imagem 
img = cv2.imread('img/family.jpeg')
#converte para escala de cinza
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
#encontre os rostos na imagem
faces = frontal_face_cascade.detectMultiScale(gray, 1.3, 5)
#se nao encontrou faces frontais, procure por faces em perfil
if len(faces) == 0:
	faces = profile_face_cascade.detectMultiScale(gray, 1.3, 5)
#se encontrou, desenhe um retangulo verde em cada rosto
for(x, y, w, h) in faces:
	cv2.rectangle(img, (x,y), (x+w, y+h), (0,255,0), 2)
#exiba a imagem	
cv2.imshow('family', img)
cv2.imwrite('img/familydetection.png', img)
#para sair pressione q
if cv2.waitKey(0) == 'q':
	cv2.destroyAllWindows()

