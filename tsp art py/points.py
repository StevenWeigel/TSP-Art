#import serial
pointsFile = 'C:/Projects/tsp-art-python-master/images/smiley points.txt'    #modify
pathFile = 'C:/Projects/tsp-art-python-master/images/smiley path.txt'        #modify



def readPoints(pointsFile):
        pointsFile = open(pointsFile, 'r')
        points = pointsFile.read().splitlines() #puts the file into an array
        pointsFile.close()
        return points
    
def readPath(pathFile):
        pathFile = open(pathFile, 'r')
        path = pathFile.read().splitlines() #puts the file into an array
        pathFile.close()
        return path

points0 = readPoints(pointsFile)
path = readPath(pathFile)
points = []

for rows in points0:
    x = rows.split()
    y = x[1] + ' ' + x[2]
    points += [y]

mX = 0
mY = 0

for rows in points0:
    x = rows.split()
    mX = max(mX, int(float(x[1])))
    mY = max(mY, int(float(x[2])))

print("max x: ", mX, "\nmax y: ", mY)

delta = []

i = 0
s0 = ''
for rows in path:
    s1 = points[int(float(rows))].split()
    if len(s0) == 0:
        s0 = s1
        continue
    dx = int(float(s1[0])) - int(float(s0[0]))
    dy = int(float(s1[1])) - int(float(s0[1]))
    if (dx > 127 or dx < -127 or dy > 127 or dy < -127):
        print("Overflow char limit at position: " +  rows)
    s0 = s1
    delta += ['{' + str(dx) + ', ' + str(dy) + '}, ']

file = open ('C:/Projects/tsp-art-python-master/images/smiley route.txt', 'w')     #modify
for row in delta:
    file.write(row)
file.close()
    
    