«Approximation Experimentation about Soup: Contest for Testcase Research»

(AES-CTR)

This is a directory with our solutions for Soup Delivery problem.

All solutions are written in Python3 (and share a lot of code…), they should
run fine with either PyPy3 or CPython3. The optimal solver requires GLPK (GNU
Linear Programmin Kit) installed and glpsol program in the executable search
path. It creates temporary files in the standard temporary file location.

solution_expected directory contains an implementation of the algorithm as
described in the slides. In many cases it obtains a very good approximation.

It starts with an arbitrary-chosen allocation, then does the best addition,
failing that the best removal, failing that the best replacement

solution_optimal directory contains a wrapper that uses GLPK to find the exact
optimal solutions using the input format of the problem.

solution_weak_warmup contains some solutions that implement a weakened version
of the algorithm. Some of these actually fail on the current test suite.

The solutions have the following limitations:

_0: handles facility 0 in a wrong way, cannot remove it, cannot remove
anything else when removing 0 is the optimal improvement.

_bestone: always uses a single facility (at least the best one)

_addfirst: starts with _bestone, then adds the first facility which improves
the situation

_removefirst: starts with all facilities in use, then removes the first
facility found which improves the situation

_nomove: never does the move, only adds or removes facilities (starts with
using a single facility 0)

solution_weak_graded directory contains the three solutions that provide
maximum bonus points for breaking them

_nomovefrombest: same, but can remove facilities when no addition improves
things and there is a useful removal

_remove: start by using all facilities, improve as much as possible at every
step by removing facilities (one per step)

_nomovefromall: starts by using all facilities, tries to find the best
addition first, in case of failure looks for the best removal

solution_broken directory contains a solution which is easier to break than
the graded ones but too hard to be among the warmup ones.

_add: start with _bestone, improve as much as possible at every step by adding
facilities (one per step)

AES-CTR scoring: 

For each graded solution:

* 2 points for breaking it (providing an example where it fails to be within
4x of the optimum)
* Half-points available! 1 point for a testcase where the half-broken solution
is not within 2x of the provided expected solution.
* +1 point for writing a generator which outputs diverse testcases with many
of them breaking the solution (10% is OK, but do describe what to expect if
less than half of testcases break the solution). The generator can ask for
parameters and random seed on the stdin (or just have something hardcoded),
and normally would output the testcases to stdout.
* +1 point for being the first to break a specific solution.

The warmup solutions are also graded: breaking the majority of them is 2
points, breaking or half-breaking majority is one point, breaking the majority
with a generator for each is 3 points (2 points for breaking + 1 for
generating), and +1 point for first-to-break is also available.

The intermediate-quality solution yields 1 point for breaking, 1 more point 
for a generator, and 1 more point for being first.

Submission via the course email, conpra@in.tum.de
