import random
import string
import sys
from shapely.geometry import box
import numpy as np

# 20 is randoly picked though, what would be a good number here?
def notSix():
	return str(random.randint(0,100))

def outOfRange():
	def getNum():
		min = -sys.maxsize -1
		num1 = random.randrange(min,0)
		num2 = random.randrange(101, sys.maxsize)
		return random.choice([num1,num2])
	return str(getNum())

def invalidChar():
	return random.choice(string.ascii_letters)

# Generate error1:
def error1(quadFile, output):
	for x in range(random.randint(0, 10)):
		charToWrite = random.choice([notSix, outOfRange, invalidChar])();
		quadFile.write(charToWrite + " ")
		output.write("error1\n")

def generatePair():
	return str(random.randint(0,100)), str(random.randint(0,100))

def twoSame():
	x,y = generatePair()
	a, b = generatePair()
	return x + " " + y + " "+ a + " " + b + " "+ x + " " + y

def threeSame():
	x,y = generatePair()
	return (x + " " + y + " "+ x + " " + y + " "+ x + " " + y)

# Generate error2:
def error2(quadFile, output):
	quadFile.write(random.choice([twoSame, threeSame])())
	output.write("error2\n")

#Generate error3:
def error3(quadFile, output):
	x = random.randint(0,100)
	y = random.randint(1,100)
	px = random.randint(0,x)
	py = random.randint(y,100)
	qx = random.randint(0,x)
	qy = random.randint(0,y)
	quadFile.write (str(x) + " " + str(y)+ " " + str(px) + " " + str(py) + " " + str(qx) + " " + str(qy))
	output.write("error3\n")

#Generate error4:
def error4(quadFile, output):
	# situation 1 is when three points colinear includes 0,0
	def situation1(quadFile):
		# px = random.randint(1,100)
		# py = random.randint(0,100)
		# qx = random.randint(0,px)
		# qy = py / px * qx
		# quadFile.write(str(px) + " " + str(py)+ " " + str(qx) + " " + str(qy) + " " + str(random.randint(0,100)) + " " + str(random.randint(0,100)))
		quadFile.write("1 1 2 2 5 75")
		
	# situation2 is when 0,0 is the outliner
	def situation2(quadFile):
		# px = random.randint(0,100)
		# py = random.randint(0,100)
		# qx = random.randint(0,100)
		# qy = random.randint(0,100)
		# coeff = np.polyfit([px,qx],[py,qy],1)
		# # y = ax + b
		# a = coeff[0]
		# b = coeff[1]
		# rx = random.randint(0,100)
		# ry = a*rx + b
		# quadFile.write(str(px) + " " + str(py)+ " " + str(qx) + " " + str(qy) + " " + str(rx) + " " + str(ry))
		quadFile.write("10 0 5 5 0 10")
	output.write("error4\n")
	random.choice([situation1, situation2])(quadFile)

def generateRectangle(quadFile, output):
	b = box(0,0,random.randint(0,100),random.randint(0,100))
	allPoints = list(b.exterior.coords)
	for x in range(3):
		quadFile.write(str(int(allPoints[x][0])) + " " + str(int(allPoints[x][1])) + " ")
	output.write("rectangle\n")

def generateSquare(quadFile, output):
	x = random.randint(0,100)
	quadFile.write(str(x) + " " + str(0)+ " " + str(x) + " " + str(x) + " " + str(0) + " " + str(x))
	output.write("square\n")

def generateRhombus(quadFile, output):
	# sitation1 is one point at x-axis:-> original point(5,0) (8,4) (3,4)
	def situation1(quadFile):
		time = random.randint(0,12)
		quadFile.write(str(5 * time) + " " + str(0)+ " " + str(8 * time) + " " + str(4 * time) + " " + str(3 * time) + " " + str(4 * time))
	# situation2 is no points at either axis -> original point(3,1) (4,4) (1,3)
	def situation2(quadFile):
		time = random.randint(0,25)
		quadFile.write(str(3 * time) + " " + str(1 * time)+ " " + str(4 * time) + " " + str(4 * time) + " " + str(1 * time) + " " + str(3 * time))
	output.write("rhombus\n")
	random.choice([situation1, situation2])(quadFile)

def generateParallelogram(quadFile, output):
	# situation1 is one point at x-axis: -> original (6 0) (9 4) (3 4)
	def situation1(quadFile):
		time = random.randint(0,12)
		quadFile.write(str(6 * time) + " " + str(0)+ " " + str(9 * time) + " " + str(4 * time) + " " + str(3 * time) + " " + str(4 * time))
	# situation2 is no point at x-axis -> original (3 1) (3 5) (0 4)
	def situation2(quadFile):
		time = random.randint(0,20)
		quadFile.write(str(3 * time) + " " + str(1 * time)+ " " + str(3 * time) + " " + str(5 * time) + " " + str(0 * time) + " " + str(4 * time))
	output.write("parallelogram\n")
	random.choice([situation1, situation2])(quadFile)

def generateKite(quadFile, output):
	# (5 0)(8 8 )(0 5)
	def situation1(quadFile):
		time = random.randint(0,12)
		quadFile.write(str(5 * time) + " " + str(0)+ " " + str(8 * time) + " " + str(8 * time) + " " + str(0 * time) + " " + str(5 * time))
	# (3 0) (4 4) (0 3)
	def situation2(quadFile):
		time = random.randint(0,20)
		quadFile.write(str(3 * time) + " " + str(0 * time)+ " " + str(4 * time) + " " + str(4 * time) + " " + str(0 * time) + " " + str(3 * time))
	output.write("kite\n")
	random.choice([situation1, situation2])(quadFile)

def generateQuad(quadFile,output):
	# (7 0)(2 2 )(1 1)
	def situation1(quadFile):
		time = random.randint(0,14)
		quadFile.write(str(7 * time) + " " + str(0)+ " " + str(2 * time) + " " + str(2 * time) + " " + str(1 * time) + " " + str(1 * time))
	# (4 4) (8 5) (2 6)
	def situation2(quadFile):
		time = random.randint(0,20)
		quadFile.write(str(4 * time) + " " + str(4 * time)+ " " + str(8 * time) + " " + str(5 * time) + " " + str(2 * time) + " " + str(6 * time))
	output.write("quadrilateral\n")
	random.choice([situation1, situation2])(quadFile)

def generateTrapezoid(quadFile, output):
	# 14 0 10 10 4 10 
	time = random.randint(0,7)
	output.write("trapezoid\n")
	quadFile.write(str(14 * time) + " " + str(0 * time)+ " " + str(10 * time) + " " + str(10 * time) + " " + str(4 * time) + " " + str(10 * time))



myList = [error1,error2,error3,error4,generateSquare,generateRhombus,generateKite,generateParallelogram,generateRectangle,generateQuad,generateTrapezoid]

for x in range(1000):
	quad = open('testCase/file%0.3d' %x + ".txt","w");
	output = open('output/file%0.3d' %x + ".txt","w");
	random.choice(myList)(quad,output)



	






	
