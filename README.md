raccoon
=======

Raccoon is an experimental automated reasoner for OWL 2, which uses a connection-based approach for reasoning.

The reasoner is developed on C++ abiding to the C++11 standard.

It is currently under development. For now, it is able to to perform consistency checking on the ALC subset of OWL 2.

Download
======

Compiled binaries are available for the following Operating Systems:

Version | Operating System | Platform
:-------:---------------:|:--------:
0.1.2|Debian<br>Ubuntu<br>Mint|[amd64](https://drive.google.com/file/d/0B4CJaYm24URxMU9XSjJfUjVXRms/view?usp=sharing)<br>[i386](https://drive.google.com/file/d/0B4CJaYm24URxWXUzNllub0pYRlU/view?usp=sharing)

How to Compile
======

Requirements:
* gcc (and g++) with C++11 standard support
* make

Instructions:
* Using a terminal, change to the raccoon subdirectory and type 'make amd64' or 'make i386' depending on your target platform.
* Two binaries will be built (raccoon and raccoon_dbg). raccoon_dbg outputs debugging information during the parsing.


Windows and osx are supported, however there are no automated building scripts for those platforms yet, building has to
be done manually.

Usage Examples
======

Currently raccoon only supports consistency checking.
To perform consistency checking use:
```
raccoon -c consistency -i ontology.owl
```

To display the normalized matrix of an ontology use:
```
raccoon -c matrix -i ontology.owl
```

For more information type:
```
raccoon -h
```
