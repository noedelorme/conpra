#!/usr/bin/env python3

import sys
import math

readline = sys.stdin.readline

def read_integers():
    return list(map(int,readline().split()))

def read_floats():
    return list(map(float,readline().split()))

def spacesep(l):
    return " ".join(map(str,l))

def parse_input():
    n, m = read_integers()
    fc = read_integers()
    dc = [read_integers() for j in range(n)]
    return [n, m, fc, dc]

def cost(used, chosen, fc, dc):
    return sum([fc[f] for f in used]) + sum([dc[chosen[c]][c] for c in chosen])

def add_facility(used, chosen, f, fc, dc):
    res = {}
    delta = fc[f]
    for c in chosen:
        old = chosen[c]
        if dc[f][c] < dc[old][c]:
            res[c] = f
            delta += dc[f][c] - dc[old][c]
        else:
            res[c] = old
    return res, delta

def remove_facility(used, chosen, f, fc, dc):
    res = {}
    delta = - fc[f]
    for c in chosen:
        old = chosen[c]
        if old == f:
            res[c] = -1
            for alt in used:
                if alt != f:
                    if res[c] == -1 or dc[res[c]][c] > dc[alt][c]:
                        res[c] = alt
                        delta += dc[alt][c] - dc[old][c]
        else:
            res[c] = old
    return res, delta

def move_facility(used, chosen, old, new, fc, dc):
    chosen_a, delta_a = add_facility(used, chosen, new, fc, dc)
    new_used = {new: True}
    for f in used:
        new_used[f] = True
    chosen_r, delta_r = remove_facility(new_used, chosen_a, old, fc, dc)
    return chosen_r, delta_a + delta_r

def best_add(used, chosen, fc, dc, threshold):
    opt = (None, chosen, 0)
    opt_delta = threshold
    for f in range(len(fc)):
        if not f in used:
            new_choice, delta = add_facility(used, chosen, f, fc, dc)
            if delta < opt_delta:
                opt_delta = delta
                opt = (f, new_choice, opt_delta)
    return opt

def best_remove(used, chosen, fc, dc, threshold):
    opt = (None, chosen, 0)
    opt_delta = threshold
    if len(used)>1:
        for f in used:
            new_choice, delta = remove_facility(used, chosen, f, fc, dc)
            if delta < opt_delta:
                opt_delta = delta
                opt = (f, new_choice, opt_delta)
    return opt

def best_move(used, chosen, fc, dc, threshold):
    unused = {}
    for f in range(len(fc)):
        if not f in used:
            unused[f] = True
    opt = (None, None, chosen, 0)
    opt_delta = threshold
    for fnew in unused:
        for f in used:
            new_choice, delta = move_facility(used, chosen, f, fnew, fc, dc)
            if delta < opt_delta:
                opt_delta = delta
                opt = (f, fnew, new_choice, opt_delta)
    return opt

def improve(used, chosen, fc, dc, epsilon):
    c = cost(used, chosen, fc, dc)
    threshold = -epsilon * c
    f, new_choice, delta = best_add(used, chosen, fc, dc, threshold)
    if f:
        used[f] = True
        return used, new_choice, True
    f, new_choice, delta = best_remove(used, chosen, fc, dc, threshold)
    if f:
        del used[f]
        return used, new_choice, True
    f, fnew, new_choice, delta = best_move(used, chosen, fc, dc, threshold)
    if f:
        del used[f]
        used[fnew] = True
        return used, new_choice, True
    return used, chosen, False

def handle_case():
    n, m, fc, dc = parse_input()

    used = {0: True}
    chosen = {c: 0 for c in range(m)}
    improved = True
    epsilon = 1/(2*(m+n)**2)
    while improved:
        used, chosen, improved = improve(used, chosen, fc, dc, epsilon)
    res = [cost(used, chosen, fc, dc)]

    assignment = {}
    for f in used:
        assignment[f] = [f+1]
    for c in chosen:
        assignment[chosen[c]].append(c+1)
    for f in assignment:
        res.append(spacesep(assignment[f]))
    return res

if __name__ == '__main__':
    case_count = int(sys.stdin.readline())
    for case_number in range(1, case_count + 1):
        res = handle_case()
        if type(res) == list:
            res = "\n".join(map(str,res))
        print("Case #{}: {}".format(case_number, res))
        sys.stdin.readline()
