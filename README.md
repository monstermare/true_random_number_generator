# True Random Number Generator with Intel Edison

## Overview
For any programming, when we need to use a random number, we use 'rand' function that is commonly provided by default. We often _do believe_ that a number generated by random functions is a true random number (at least I did until I faced the truth). Sadly, that is not true.

## Background
A random number generator is essentially under the category of _Deterministic Finite Automaton_ (or simply say DFA). You could learn more about DFA or further stuff on the [Wikipedia](https://en.wikipedia.org/wiki/Deterministic_finite_automaton), but it is out of the scope of this work. The only thing we need to know is the numbers generated by a random number generator can be predictable if we know what type of generator and input used! However, in reality, computer scientists invented awesome algorithms for the random number generator, and it is almost impossible to predict the numbers generated. How good those are? We will see what algorithms are commonly used today before we discuss the main topic.

## Algorithms for the random numbers
	- Middle-square method: X_
