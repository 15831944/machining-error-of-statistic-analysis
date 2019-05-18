#!/usr/bin/env python
# -*- coding:utf-8-*-
import numpy as np
import  matplotlib.pyplot as plt
import os

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

    plt.savefig('size_map.png')

def draw_point_map(f):
    #各组尺寸平均值
    avg = []
    #各组极差
    sub = []
    #上、下控制限及均值
    other_par_of_avg = []
    other_par_of_sub = []
    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        avg.append(float(i))

    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        sub.append(float(i))

    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        other_par_of_avg.append(float(i))

    temp = f.readline().strip('\n').strip(' ').split(' ')
    for i in temp:
        other_par_of_sub.append(float(i))

    #工件均值图
    x = range(1, len(avg)+1)
    plt.figure(figsize=(14, 8))
    plt.subplot(2, 1, 1)
    plt.plot(x, avg, marker='.')
    plt.xticks(np.arange(1, len(avg)+1, 1))
    for a, b in zip(x, avg):
        plt.text(a, b+0.0001, round(b, 4), fontsize=10, ha='center')
    for i in other_par_of_avg:
        plt.hlines(i, min(x), max(x), linestyles='dashed', colors='r')
        plt.text(max(x)+1, i, round(i, 4))

    #极差图
    plt.subplot(2, 1, 2)
    plt.plot(x, sub, marker='o')
    plt.xticks(np.arange(1, len(avg) + 1, 1))
    for a, b in zip(x, sub):
        plt.text(a, b+0.0001, round(b, 4), ha='center')
    for i in other_par_of_sub:
        plt.hlines(i, min(x), max(x), linestyles='dashed', colors='r')
        plt.text(max(x)+1, i, round(i, 4))

    plt.savefig('point_map.png')

if (os.path.isfile('size_map.txt')):
    with open("size_map.txt") as f:
        draw_size_map(f)
if (os.path.isfile('point_map.txt')):
    with open("point_map.txt") as f:
        draw_point_map(f)