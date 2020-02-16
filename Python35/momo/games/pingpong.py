
import turtle as t  #create window.
wn = t.Screen()
wn.title('PING PONG')
wn.bgcolor('gray')
wn.setup(width=1000, height=600   )
wn.tracer(0)

score1 = 0
score2 = 0
#PAD1
pad1 = t.Turtle()
pad1.speed(0)
pad1.shape('square')
pad1.color('blue')
pad1.penup()
pad1.goto(-450 , 0)
pad1.shapesize(stretch_wid=5,stretch_len=1)



#PAD2
pad2 = t.Turtle()
pad2.speed(0)
pad2.shape('square')
pad2.color('red')
pad2.penup()
pad2.goto(450 , 0)
pad2.shapesize(stretch_wid=5,stretch_len=1)
#pen
pen = t.Turtle()
pen.speed(0)
pen.color('yellow')
pen.penup()
pen.hideturtle()
pen.goto(0,260)
pen.write('PLAYER 1 : 0 ,LAYER 2 : 0,ONE PLAER FAILS: 0' ,align='center', font=('Courier',24,'normal'))
#BALL
ball = t.Turtle()
ball.shape('circle')
ball.speed(0)
ball.color('orange')
ball.penup()
ball.goto(0,0)
ball.dx = 0.2
ball.dy = 0.2
#func
def pad1_up():
    y = pad1.ycor()
    y += 20
    pad1.sety(y)
def pad1_dwn():
    y = pad1.ycor()
    y -= 20
    pad1.sety(y)
        
wn.listen()
wn.onkeypress(pad1_up,'w')
wn.onkeypress(pad1_dwn,'s')
def pad2_up():
    y = pad2.ycor()
    y += 20
    pad2.sety(y)
def pad2_dwn():
    y = pad2.ycor()
    y -= 20
    pad2.sety(y)
        
wn.listen()
wn.onkeypress(pad2_up,'i')
wn.onkeypress(pad2_dwn,'k')
while True:
    wn.update()
    ball.setx(ball.xcor() + ball.dx)
    ball.sety(ball.ycor() + ball.dy)
    if ball.ycor() >260:  
        ball.sety(260)
        ball.dy *= -1
       
    if ball.ycor() <-290:  
        ball.sety(-290)
        ball.dy *= -1
    if ball.xcor() >490:  
        ball.goto(0,0)
        ball.dx *= -1
        score1 += 1
        pen.clear()
        pen.write('PLAYER 1 : {} , PLAYER 2 : {},ONE PLAER FAILS: {}'.format(score1,score2,score2+score1) ,align='center', font=('Courier',24,'normal'))
    if ball.xcor() <-490:  
        ball.goto(0,0)
        ball.dx *= -1
        score2 += 1
        pen.clear()
        pen.write('PLAYER 1 : {} , PLAYER 2 : {},ONE PLAYER FAILS: {}'.format(score1,score2,score1+score2) ,align='center', font=('Courier',24,'normal'))
    if (ball.xcor() > 440 and ball.xcor() < 450) and (ball.ycor() < pad2.ycor() + 50 and ball.ycor() > pad2.ycor() - 50):
        ball.setx(440)
        ball.dx *= -1
    if (ball.xcor() < -440 and ball.xcor() > -450) and (ball.ycor() < pad1.ycor() + 50 and ball.ycor() > pad1.ycor() - 50):
        ball.setx(-440)
        ball.dx *= -1
