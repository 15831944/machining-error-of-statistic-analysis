#!/usr/bin/env python
# -*- coding:utf-8-*-
import numpy as np
import  matplotlib.pyplot as plt

def draw_size_map(f):
    #各组尺寸分界点
    t = []
    #频数
    y = []
    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        t.append(float(i))

    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        y.append(int(i))

    temp = f.readline().strip('\n').strip(' ').split(' ')
    #工件尺寸平均值
    avg = float(temp[0])

    #画图用的x坐标，取各组中值
    x =[]
    for i in range(1, len(t)):
        x.append((t[i-1] + t[i]) / 2)
    plt.figure(figsize=(14, 8))
    plt.plot(x, y, marker='o')
    plt.xticks(np.arange(t[0], t[len(t)-1], 0.02))
    for a, b in zip(x, y):
        plt.text(a, b+0.3, (round(a, 4), b), ha='center')
    plt.vlines(avg, min(y), max(y), linestyles='dashed', colors='r')
    plt.text(avg, min(y), round(avg, 4))
    plt.show()

with open("size_map.txt") as f:
    draw_size_map(f)