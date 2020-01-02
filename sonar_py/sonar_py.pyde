add_library('serial')
import time

angle = ""
distance = ""
data = ""
noObject = ""
pixsDistance = 0.0
iAngle = 0
iDistance = 0


def setup():
    size(1920, 1080)
    smooth()
    ser = Serial(this, "/dev/ttyACM0", 9600)


def draw():
    fill(98, 245, 31)
    textFont(loadFont("Courier-30.vlw"))
    # simulating motion blur and slow fade of the moving line
    noStroke()
    fill(0, 4)
    rect(0, 0, width, 1010)

    fill(98, 245, 31)  # green color
    # calls the functions for drawing the radar
    drawRadar()
    drawLine()
    drawObject()
    drawText()


def serialEvent(myPort):
    print("Serial event triggered")
    data = myPort.readline().decode("ASCII").split(",")
    if data[0] == "debug":
        print(data[1])

    elif data[0] == "data":
        iAngle = int(data[1])
        iDistance = int(data[2])


def drawRadar():
    pushMatrix()
    translate(960, 1000)  # moves the starting coordinats to new location
    noFill()
    strokeWeight(2)
    stroke(98, 245, 31)

    # draws the arc lines
    arc(0, 0, 1800, 1800, PI, TWO_PI)
    arc(0, 0, 1400, 1400, PI, TWO_PI)
    arc(0, 0, 1000, 1000, PI, TWO_PI)
    arc(0, 0, 600, 600, PI, TWO_PI)

    # draws the angle lines
    line(-960, 0, 960, 0)
    line(0, 0, -960 * cos(radians(30)), -960 * sin(radians(30)))
    line(0, 0, -960 * cos(radians(60)), -960 * sin(radians(60)))
    line(0, 0, -960 * cos(radians(90)), -960 * sin(radians(90)))
    line(0, 0, -960 * cos(radians(120)), -960 * sin(radians(120)))
    line(0, 0, -960 * cos(radians(150)), -960 * sin(radians(150)))
    line(-960 * cos(radians(30)), 0, 960, 0)
    popMatrix()


def drawObject():
    pushMatrix()
    translate(960, 1000)  # moves the starting coordinats to new location
    strokeWeight(9)
    stroke(255, 10, 10)  # red color
    pixsDistance = (iDistance * 22.5)  # converts the distance from the sensor from cm to pixels
    # limiting the range to 40 cm
    if iDistance < 40:
        # draws the object according to the angle and the distance
        line(
            pixsDistance * cos(radians(iAngle)),
            -pixsDistance * sin(radians(iAngle)),
            950 * cos(radians(iAngle)),
            -950 * sin(radians(iAngle))
        )

    popMatrix()


def drawLine():
    pushMatrix()
    strokeWeight(9)
    stroke(30, 250, 60)
    translate(960, 1000)  # moves the starting coordinates to new position
    line(0, 0, 950 * cos(radians(iAngle)), -950 * sin(radians(iAngle)))  # draws the line according to the angle
    popMatrix()


def drawText():
    pushMatrix()
    if iDistance > 40:
        noObject = "Out of Range"
    else:
        noObject = "In Range"

    fill(0, 0, 0)
    noStroke()
    rect(0, 1010, width, 1080)
    fill(98, 245, 31)
    textSize(25)
    text("10cm", 1180, 990)
    text("20cm", 1380, 990)
    text("30cm", 1580, 990)
    text("40cm", 1780, 990)
    textSize(40)
    text("Object: " + noObject, 240, 1050)
    text("Angle: " + str(iAngle) + " °", 1050, 1050)
    text("Distance: ", 1380, 1050)

    if iDistance < 40:
        text("        " + str(iDistance) + " cm", 1400, 1050)

    textSize(25)
    fill(98, 245, 60)

    translate(961 + 960 * cos(radians(30)), 982 - 960 * sin(radians(30)))
    rotate(-radians(-60))
    text("30°", 0, 0)
    resetMatrix()

    translate(954 + 960 * cos(radians(60)), 984 - 960 * sin(radians(60)))
    rotate(-radians(-30))
    text("60°", 0, 0)
    resetMatrix()

    translate(945 + 960 * cos(radians(90)), 990 - 960 * sin(radians(90)))
    rotate(radians(0))
    text("90°", 0, 0)
    resetMatrix()

    translate(935 + 960 * cos(radians(120)), 1003 - 960 * sin(radians(120)))
    rotate(radians(-30))
    text("120°", 0, 0)
    resetMatrix()

    translate(940 + 960 * cos(radians(150)), 1018 - 960 * sin(radians(150)))
    rotate(radians(-60))
    text("150°", 0, 0)
    popMatrix()
