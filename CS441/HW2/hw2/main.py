#!/usr/bin/python
import copy
import random
import time

import numpy as np

# TODO:
# Get data from file into a data structure X
# Implement a random (dumb) algorithm X
# Calculate the score X
# Loop for 60 seconds and output best score X
#   To standard output X
#   To file
# Fix scoring to include adjacent preference scores and +1/+2 for guest/host combos X
# Implement a more advanced algorithm (local search) X
# Clean up and back before submission X
# Add comments where needed X
# Submit


def main():
    print("Welcome to Homework 1!\n")

    print("Enter name of data file:")
    ans = get_input('')

    # Import data as matrix
    matrix = np.loadtxt(ans, dtype=int, skiprows=1)

    # Create set/list of people
    nppl = matrix.shape[0]
    print("\nNumber of people to seat: ", nppl)

    tblside = int(nppl/2)

    table = np.zeros((2, tblside), dtype=int)
    wintable = np.zeros((2, tblside), dtype=int)

    plist = []

    # Add each person to a list/set
    for i in range(nppl):
        plist.append(i)

    numit = 0
    winit = 0
    flips = [0]
    maxscore = -999

    print("\nCalculating max score...")
#    for y in range(1):
    t_end = time.time() + 60
    while time.time() < t_end:
        tlist = copy.deepcopy(plist)

        # Place each person at the table randomly
        randpop(table, tlist, tblside)

        # Place each person at the table by preference and positional score (draft)
#        draftpop(matrix, table, tlist, tblside)

        # Use local search to find best state starting from random state
        table = localsearch(matrix, table, tblside, flips)

        # Calculate the score of the returned table
        curscore = calcscore(table, tblside, matrix)

        if curscore > maxscore:
            maxscore = curscore
            wintable = table

    print("\nThe max score is:", maxscore)

    print("\nThe table of the max score is:")
    for i in range(2):
        for j in range(tblside):
            if i < 1:
                print(wintable[i, j], j + 1)
            else:
                print(wintable[i, j], j + 6)
    return 0


# Objective Function
def calcscore(table, tblside, matrix):
    # Calculate score for those sitting across from each other
    score = 0
    for i in range(tblside):
        p1 = table[0, i]
        p2 = table[1, i]
        p = 0
        p12 = 0
        p21 = 0
        p12 += pref(matrix, p1, p2)
        p21 += pref(matrix, p2, p1)
        if (ishost(p1, tblside) and not ishost(p2, tblside)) or (not ishost(p1, tblside) and ishost(p2, tblside)):
            p += 2

        # Calculate score for those sitting next to each other
        p13 = 0
        p31 = 0
        p24 = 0
        p42 = 0
        if i + 1 < tblside:
            p3 = table[0, i + 1]
            p4 = table[1, i + 1]
            p13 += pref(matrix, p1, p3)
            p31 += pref(matrix, p3, p1)
            p24 += pref(matrix, p2, p4)
            p42 += pref(matrix, p4, p2)
            if (ishost(p1, tblside) and not ishost(p3, tblside)) or (not ishost(p1, tblside) and ishost(p3, tblside)):
                p += 1
            if (ishost(p2, tblside) and not ishost(p4, tblside)) or (not ishost(p2, tblside) and ishost(p4, tblside)):
                p += 1
        p += p12 + p21 + p13 + p31 + p24 + p42
        score += p
    return score


def draftpop(matrix, table, tlist, tblside):
    p = random.sample(tlist, 1)[0]
    tlist.remove(p)
    table[0, 0] = p
    # Find best neighbor of remaining people
    best1 = -999
    best2 = -999
    neighbor1 = -999
    neighbor2 = -999
    for i in range(1):
        for j in range(tblside):
            p = table[i, j]
            # Find opposite match
            if j == 0:
                # First seat at table
                q = findbest(matrix, tlist, tblside, p, i + 1)
            else:
                # 2nd to n/2 seat at the table
                best = -999
                for k in tlist:
                    r = findbest(matrix, tlist, tblside, p, i + 1)
                    s = findbest(matrix, tlist, tblside, r, table[i + 1, j - 1])
                    if r + s > best:
                        best = r + s
                        pos = r
                q = pos
            table[i + 1, j] = q
            tlist.remove(q)
            # Find adjacent match
            if j + 1 < tblside:
                r = findbest(matrix, tlist, tblside, p, i)
                table[i, j + 1] = r
                tlist.remove(r)


# Find the best neighbor based on score of preference and combination of host/guest
def findbest(matrix, tlist, tblside, p, q):
    best = -999
    neighbor = -999
    for i in tlist:
        curr = pref(matrix, p, i) + pref(matrix, i, p)
        if(ishost(p, tblside) and not ishost(i, tblside)) or (not ishost(p, tblside) and ishost(i, tblside)):
            if p == 0:
                curr += 1
            else:
                curr += 2
        if curr > best:
            best = curr
            neighbor = i
    return neighbor


# Get user input for input file
def get_input(text):
    return input(text)


# Determine if a person is a host or not (guest)
def ishost(p, q):
    if p < q:
        return True
    else:
        return False


# Greedy local search algorithm using brute force instead of randomization
def localsearch(matrix, table, tblside, flips):
    # Calculate score of initial state
    iscore = calcscore(table, tblside, matrix)
    # Copy initial state
    ptable = copy.deepcopy(table)
    # 2 sides of table
    for i in range(2):
        # Number of people per side
        for j in range(tblside):
            # Start swap at same side of table
            for k in range(i, 2):
                # Start swap at next seat
                if k == i:
                    for l in range(j + 1, tblside):
                        # Make the swap
                        ntable = copy.deepcopy(ptable)
                        t = ntable[i, j]
                        ntable[i, j] = ntable[k, l]
                        ntable[k, l] = t
                        # Calculate and compare scores
                        nscore = calcscore(ntable, tblside, matrix)
                        if nscore > iscore:
                            iscore = nscore
                            ptable = copy.deepcopy(ntable)
                else:
                    for l in range(0, tblside):
                        # Make the swap
                        ntable = copy.deepcopy(ptable)
                        t = ntable[i, j]
                        ntable[i, j] = ntable[k, l]
                        ntable[k, l] = t
                        # Calculate and compare scores
                        nscore = calcscore(ntable, tblside, matrix)
                        if nscore > iscore:
                            iscore = nscore
                            ptable = copy.deepcopy(ntable)
    return ptable


# Return the preference score for a pair of people
def pref(a, p1, p2):
    return a[p1, p2]


# Randomly generate a table state
def randpop(table, tlist, tblside):
    # 2 sides of table
    for i in range(2):
        # Number of people per side
        for j in range(tblside):
            # Take random sample of remaining people to seat and remove once sat
            p = random.sample(tlist, 1)[0]
            table[i, j] = p
            tlist.remove(p)


main()