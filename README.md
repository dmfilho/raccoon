raccoon
=======

Raccoon is an experimental automated reasoner for OWL 2, which uses a connection-based approach for reasoning.

The reasoner is developed on C++ abiding to the C++11 standard.

It is currently udner development. For now, it is able to to perform consistency checking on the ALC subset of OWL 2.


How to Compile
======

Requirements:
	* gcc (and g++) with C++11 standard support
	* make

Instructions:
	1. Using a terminal, change to raccoon subdirectory and type 'make'.
	2. Two binaries will be built (raccoon and raccoon_dbg). raccoon_dbg outputs debugging information during the parsing.


Windows and osx are supported, however there are no automated building scripts for those platforms yet, building has to
be done manually.

Usage Examples
======

Currently raccoon only provides support to consistency checking.
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