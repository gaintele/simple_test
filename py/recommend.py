#! /usr/bin/python
#coding:utf-8
import sys
from math import sqrt

users = {"Angelica": {"Blues Traveler": 3.5, "Broken Bells": 2.0, "Norah Jones": 4.5, "Phoenix": 5.0, "Slightly Stoopid": 1.5, "The Strokes": 2.5, "Vampire Weekend": 2.0},
    "Bill":{"Blues Traveler": 2.0, "Broken Bells": 3.5, "Deadmau5": 4.0, "Phoenix": 2.0, "Slightly Stoopid": 3.5, "Vampire Weekend": 3.0},
    "Chan": {"Blues Traveler": 5.0, "Broken Bells": 1.0, "Deadmau5": 1.0, "Norah Jones": 3.0, "Phoenix": 5, "Slightly Stoopid": 1.0},
    "Dan": {"Blues Traveler": 3.0, "Broken Bells": 4.0, "Deadmau5": 4.5, "Phoenix": 3.0, "Slightly Stoopid": 4.5, "The Strokes": 4.0, "Vampire Weekend": 2.0},
    "Hailey": {"Broken Bells": 4.0, "Deadmau5": 1.0, "Norah Jones": 4.0, "The Strokes": 4.0, "Vampire Weekend": 1.0},
    "Jordyn":  {"Broken Bells": 4.5, "Deadmau5": 4.0, "Norah Jones": 5.0, "Phoenix": 5.0, "Slightly Stoopid": 4.5, "The Strokes": 4.0, "Vampire Weekend": 4.0},
    "Sam": {"Blues Traveler": 5.0, "Broken Bells": 2.0, "Norah Jones": 3.0, "Phoenix": 5.0, "Slightly Stoopid": 4.0, "The Strokes": 5.0},
    "Veronica": {"Blues Traveler": 3.0, "Norah Jones": 5.0, "Phoenix": 4.0, "Slightly Stoopid": 2.5, "The Strokes": 3.0}
}

def printdb(users):
    for user in users:
        print user 
        ratings = users[user]
        for item in ratings:
            print "     %s:%s" % (item, ratings[item])

def manhattan(rating1, rating2):
    distance = 0
    for item in rating1:
        if item in rating2:
            distance += abs(rating1[item] - rating2[item])
    return distance

def minkowski(rating1, rating2, r):
    distance = 0
    for key in rating1:
        if key in rating2:
            distance += pow(abs(rating1[key] - rating2[key]), r)

    return pow(distance, 1.0 / r)

def pearson(rating1, rating2):
    sum_xy = 0
    sum_x = 0
    sum_y = 0
    sum_x2 = 0
    sum_y2 = 0
    n = 0
    for key in rating1:
        if key in rating2:
            n += 1
            x = rating1[key]
            y = rating2[key]
            sum_xy += x * y
            sum_x += x
            sum_y += y
            sum_x2 += pow(x, 2)
            sum_y2 += pow(y, 2)

    # 计算分母
    denominator = sqrt(sum_x2 - pow(sum_x, 2) / n) * sqrt(sum_y2 - pow(sum_y, 2) / n)
    if denominator == 0:
        return 0
    else:
        return (sum_xy - (sum_x * sum_y) / n) / denominator

def computeNearestNeighbor(username, users):
    """计算所有用户至username用户的距离，倒序排列并返回结果列表"""
    distance = []
    if username not in users:
        return distance

    for user in users:
        if user != username:
#            dis = manhattan(users[username], users[user])
#            dis = minkowski(users[username], users[user], 2)
            dis = pearson(users[username], users[user])
            distance.append((dis, user))

    distance.sort(reverse=True)
    for dis in distance:
        print dis
    return distance

def recommend(username, users):
    recos = []
    if username not in users:
        return recos

    reco_user = computeNearestNeighbor(username, users)[0][1]
    for item in users[reco_user]:
        if item not in users[username]:
            recos.append((users[reco_user][item], item))

    return sorted(recos, reverse=True)

def main(argv):
#    printdb(users)
#    distance = computeNearestNeighbor("Hailey", users)
    recos = recommend("Chan", users)
    for item in recos:
        print item

if __name__ == '__main__':
    main(sys.argv)
