#!/usr/bin/env python
# -*- coding:utf-8 -*-
import numpy as np
import  matplotlib.pyplot as plt

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

    plt.show()

with open("point_map.txt") as f:
    draw_point_map(f)