# meca-research

This project aims to be a novel cryptosystem entirely reliant on cellular automata and boolean algebra.
To retain speed in software, all operations are bitwise; it is well studied that CAs are fast and can
be scaled in hardware. The end goal is a polymorphic cipher using easy to understand and novel means.

## Details

* A second-order CA is the primitive unit of the crypto system
    - All rules are 32-it instead of Wolfram's 8-bit rules
    - Rule/epoch selection is dependendent on the data being processed allowing polymorphism.
        - (See Stone Cipher 192 for inspiration)
    - In order for the first block to not remain mostly untouched as `t-1`, each 64-bit word may be swapped to execute over the other side or lapsed on the final block.
* A genetic algorithm will help reach optimal rules and epoch floor/ceilings
    - The fitness function consists of entropy score between intitial and end state in X epochs (both Shannon and Kolmogorav complexity) in a variety of configurations (zeroes, middle bit, half set, all set, cyclic, random), execution speed, bit-avalanche test passing between start and end, etc.
    - In the code, there is an in-memory SQLite DB that gets dumped to a file at the end of execution; this is where results will be stored.
* Key-material combination is still in development and testing

## Building/Running

```shell
$ make && ./bin/secondorder
```

## References

* TODO

## In-progress

See [TODO.txt](TODO.txt).
