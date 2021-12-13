#!/usr/bin/env python3

import sys
import math
import os
import subprocess
import tempfile

readline = sys.stdin.readline

glpk_solver_code = """
param n 'Number of facilties' integer, >0;
param m 'Number of customers' integer, >0;

param fc 'Facility cost' {i in 1..n} integer, >0;
param dc 'Delivery cost' {i in 1..n, j in 1..m} integer, >0;

var used 'Facility used' {i in 1..n} integer, >=0;
var chosen 'Facility chosen by customer' {i in 1..n, j in 1..m} integer, >=0;

var b integer;

minimize budget: b;

s.t. sufficient: (sum{i in 1..n} used[i]*fc[i]) + (sum{i in 1..n, j in 1..m} chosen[i,j]*dc[i,j]) <= b;
s.t. feasible{i in 1..n, j in 1..m}: chosen[i,j] <= used[i];
s.t. covered{j in 1..m}: sum{i in 1..n} chosen[i,j] >= 1;

solve;

printf "%d\\n", b;
for{i in 1..n} {
    printf (if used[i] then "%d" else ""), i;
    for{j in 1..m} {
      printf (if chosen[i,j] then " %d" else ""), j;
    }
    printf (if used[i] then "\\n" else "");
}
"""

def read_integers():
    return list(map(int,readline().split()))

def parse_input():
    n, m = read_integers()
    fc = read_integers()
    dc = [read_integers() for j in range(n)]
    return [n, m, fc, dc]

def glpk_1d_array(data):
    res = []
    for (i, x) in enumerate(data):
        res.append(f"{i+1} {x}")
    return "\n".join(res)

def glpk_2d_array(data):
    res = []
    for (i, x) in enumerate(data):
        for (j, y) in enumerate(x):
            res.append(f"{i+1} {j+1} {y}")
    return "\n".join(res)

def glpk_data(n, m, fc, dc):
    return f"""
    data;

    param n := {n};
    param m := {m};

    param fc :=
    {glpk_1d_array(fc)}
    ;

    param dc :=
    {glpk_2d_array(dc)}
    ;

    end;
    """

def handle_case(case_number):
    n, m, fc, dc = parse_input()
    glpk_text = glpk_data(n, m, fc, dc)
    glpk_solver = tempfile.mktemp()
    basename = tempfile.mktemp()
    with open(glpk_solver, "w") as f:
        f.write(glpk_solver_code)
    glpk_input = f"{basename}.{case_number}.dat"
    glpk_output = f"{basename}.{case_number}.sol"
    glpk_log = f"{basename}.{case_number}.log"
    with open(glpk_input, "w") as f:
        f.write(glpk_text)
    sys.stderr.write(f"Prepared case {case_number} for GLPK\n")
    with open(glpk_log, "w") as f:
        subprocess.run(["glpsol", "--model", glpk_solver, "--data", glpk_input, "--display", glpk_output], stdout=f)
    sys.stderr.write(f"Processed {case_number} by GLPK\n")
    with open(glpk_output, "r") as f:
        res = [s.strip() for s in f.readlines()]
    os.unlink(glpk_input)
    os.unlink(glpk_output)
    os.unlink(glpk_log)
    return res

if __name__ == '__main__':
    case_count = int(sys.stdin.readline())
    for case_number in range(1, case_count + 1):
        res = handle_case(case_number)
        if type(res) == list:
            res = "\n".join(res)
        print(f"Case #{case_number}: {res}")
        sys.stdin.readline()
