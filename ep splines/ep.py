#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import splines

##############################################################################
# EP MAC0210 - 1s2018
# nome: Anderson Andrei da Silva, nusp: 8944025
##############################################################################

# Create an input file input.txt to test the getw().
def createInput():
    ref_arquivo = open("./input.txt","w")
    n = np.random.randint(0,50)
    t = np.arange(0,1,0.001)
    y = np.random.rand(50)
    ref_arquivo.write(str(n) + str("\n"))
    for i in range (0,50) :
        ref_arquivo.write(str(t[i]) + " " + str(y[i]) + str(" \n"))
    ref_arquivo.close()

# getw() get w for our aproximation. It reads a text file (input.txt) with the 
# format:
#
# n
# t0 y0
# t1 y1
#  ...
# tk yk    

def getw ():
    file = open("./input.txt","r")
    t = []
    y = []
    inp = file.readlines()
    size = len(inp)
    n = inp[0]
    lambida = 1
    for i in range (1,size) :
        alpha = inp[i].split()
        t.append(alpha[0])
        y.append(alpha[1])
    plt.plot(t,y)
    
    for i in range (len(t)):
        t[i] = float(t[i])
    for i in range (len(t)):
        y[i] = float(y[i])
        
    t = np.array(t)
    y = np.array(y)
    n = int(n)
    
    wtemp = np.random.rand(50)
    s = spline(wtemp, t[0], t[-1])
    B=[]
    for j in range(n) :
        B.append(s.beta_j(j,t))
    B = np.array(B)
    
    Bt = B.transpose()
    m1 = np.dot(B,Bt)
    b = np.dot(B,y)
    m2 = matrix_m2(n)
    m2 = np.dot(lambida,m2)
    m = m1+m2
    w = np.linalg.solve(m,b)
    
    s2 = spline(w, t[0], t[-1])
    plt.plot(t,s2(t))
        
    
    file.close()