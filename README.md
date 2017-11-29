raccoon
=======

Raccoon is an experimental automated reasoner for OWL 2, which uses a connection-based approach for reasoning.

The reasoner is developed on C++ abiding to the C++11 standard.

It is currently under development. For now, it is able to to perform consistency checking on the ALC subset of OWL 2.

Download
======

Pre-compiled binaries are available for the following Operating Systems:

Version | Operating System | Platform
:------:|:----------------:|:--------:
0.1.9 | Debian<br>Ubuntu<br>Mint | [amd64](https://drive.google.com/file/d/1WpG0-3rOaCiWgqNBUt-zv_LILmxkgS2e)<br>[i386](https://drive.google.com/file/d/1D9g20EMDSF0KrOtchRDCChx5HFxy0z1K)

Author and Contributors
======
The reasoner was developed by Dimas Melo Filho, with inestimable help of the following contributors and researchers:

Name | Country | Organization
:---:|:-------:|:-----------:
Fred Freitas | Brazil | UFPE
Jens Otten | Germany | University of Potsdam
Diogo Espinhara | Brazil | UFPE
Renan Leandro Fernandes | Brazil | UFPE

Feel free to contribute.


How to Compile
======

Requirements:
* gcc (and g++) with C++11 standard support
* make

Instructions:
```shell
$ git clone https://github.com/dmfilho/raccoon.git
$ cd raccoon/raccoon
$ make
```

After compilation succeeds the binaries will be on the **bin** folder.

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
