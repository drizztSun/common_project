import sys
import pygame
from pygame.locals import *
import os 
import math
import random
 
def loadPng(name):
    fullname = os.path.join('data',name)
    try:
        image = pygame.image.load(fullname)
        if image.get_alpha is None:
            image = image.convert()
        else:
            image = image.convert_alpha()
    except pygame.error as message:
        print("无法加载图片",fullname)
        raise SystemExit(message)
    return image,image.get_rect()
 
class Ball(pygame.sprite.Sprite):
 
    def __init__(self,xy,vector):
        pygame.sprite.Sprite.__init__(self)
        self.image,self.rect = loadPng('ball.png')
        screen = pygame.display.get_surface()
        self.area = screen.get_rect()
        self.vector = vector
        self.hit = 0
    
    def update(self):
        newpos = self.calcnewpos(self.rect,self.vector)
        self.rect = newpos
        (angle,z) = self.vector
 
        if not self.area.contains(newpos):
            tl = not self.area.collidepoint(newpos.topleft)
            tr = not self.area.collidepoint(newpos.topright)
            bl = not self.area.collidepoint(newpos.bottomleft)
            br = not self.area.collidepoint(newpos.bottomright)
            if tr and tl or (br and bl):
                angle = - angle
            if tl and bl:
                angle = math.pi - angle
            if tr and br:
                angle = math.pi - angle
        else:
            player1.rect.inflate(-3,-3)
            player2.rect.inflate(-3,-3)
 
            if self.rect.colliderect(player1.rect) == 1 and not self.hit:
                angle = math.pi - angle
                self.hit = not self.hit
            elif self.rect.colliderect(player2.rect) == 1 and not self.hit:
                angle = math.pi - angle
                self.hit = not self.hit
            elif self.hit:
                self.hit = not self.hit
        self.vector = (angle,z)
    
    def calcnewpos(self,rect,vector):
        (angle,z) = vector
        (dx,dy) = (z*math.cos(angle),z*math.sin(angle))
        return rect.move(dx,dy)
 
class Bat(pygame.sprite.Sprite):
 
    def __init__(self,side):
        pygame.sprite.Sprite.__init__(self)
        self.image,self.rect = loadPng('bat.png')
        screen = pygame.display.get_surface()
        self.area = screen.get_rect()
        self.side = side
        self.speed = 10
        self.state = "still"
        self.reinit()
    
    def reinit(self):
        self.state="still"
        self.movepos = [0,0]
        if self.side == 'left':
            self.rect.midleft = self.area.midleft
        elif self.side == "right":
            self.rect.midright = self.area.midright
 
    def update(self):
        newpos = self.rect.move(self.movepos)
        if self.area.contains(newpos):
            self.rect = newpos
        pygame.event.pump()
 
    def moveup(self):
        self.movepos[1] = self.movepos[1] - (self.speed)
        self.state = "moveup"
 
    def movedown(self):
        self.movepos[1] = self.movepos[1] + (self.speed)
        self.state = "movedown"
 
 
def main():
    pygame.init()
    screen = pygame.display.set_mode((640,480))
    pygame.display.set_caption('basic')
 
    #填充背景
    background = pygame.Surface(screen.get_size())
    background = background.convert()
    background.fill((0,0,0))
 
    #选择一些基本文字
    # font = pygame.font.Font(None,36)
    # text = font.render("hello there",3,(10,10,10))
    # textpos = text.get_rect()
    # textpos.centerx = background.get_rect().centerx
    # background.blit(text,textpos)
 
    # #画所有图
    # screen.blit(background,(0,0))
    # pygame.display.flip()
 
    global player1
    global player2
    player1 = Bat('left')
    player2 = Bat('right')
 
    speed = 5
    rand = ((0.1*(random.randint(5,8))))
    ball = Ball((0,0),(0.45,speed))
 
    playersprites = pygame.sprite.RenderPlain((player1,player2))
    ballsprite = pygame.sprite.RenderPlain(ball)
 
    screen.blit(background,(0,0))
    pygame.display.flip()
 
    clock = pygame.time.Clock()
 
    #事件
    while True:
        
        clock.tick(60)
 
        for event in pygame.event.get():
            if event.type == QUIT:
                return
            elif event.type == KEYDOWN:
                if event.key == K_w:
                    player1.moveup()
                if event.key == K_s:
                    player1.movedown()
                if event.key == K_UP:
                    player2.moveup()
                if event.key == K_DOWN:
                    player2.movedown()
 
            elif event.type == KEYUP:
                if event.key == K_w or event.key == K_s:
                    player1.movepos= [0,0]
                    player1.state = "still"
 
                if event.key == K_UP or event.key == K_DOWN:
                    player2.movepos = [0,0]
                    player2.state = "still"
 
        # screen.blit(background,(0,0))
        screen.blit(background,ball.rect,ball.rect)
        screen.blit(background,player1.rect,player1.rect)
        screen.blit(background,player2.rect,player2.rect)
        ballsprite.update()
        playersprites.update()
        ballsprite.draw(screen)
        playersprites.draw(screen)
        pygame.display.flip()
 
if __name__ == '__main__':
    main()
