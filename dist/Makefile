VERSION=0.1.4
DEBVER=1
FILES=usr/local/bin/raccoon

linux: debian-amd64 debian-i386

debian-amd64: raccoon-$(VERSION)_$(DEBVER)-amd64.deb
debian-i386: raccoon-$(VERSION)_$(DEBVER)-i386.deb

raccoon-$(VERSION)_$(DEBVER)-amd64.deb: debian-amd64/DEBIAN/control debian-amd64/copyright debian-amd64/compat debian-amd64/changelog $(addprefix debian-amd64/,$(FILES))
	dpkg-deb --build debian-amd64 raccoon-$(VERSION)_$(DEBVER)-amd64.deb

debian-amd64/usr/local/bin/raccoon: ../raccoon/bin/raccoon
	rm -rf debian-amd64/usr/local/bin/racooon
	mkdir -p debian-amd64/usr/local/bin
	cp ../raccoon/bin/raccoon debian-amd64/usr/local/bin/raccoon

debian-amd64/DEBIAN/control: debian-amd64/DEBIAN debian/control
	debian/arch.sh debian/control debian-amd64/DEBIAN/control amd64

debian-amd64/DEBIAN:
	mkdir -p debian-amd64/DEBIAN

debian-amd64/%: debian/%
	cp -f $< $@

../raccoon/bin/raccoon: 
	make -C ../raccoon -f ../raccoon/Makefile clean amd64

raccoon-$(VERSION)_$(DEBVER)-i386.deb: debian-i386/DEBIAN/control debian-i386/copyright debian-i386/compat debian-i386/changelog $(addprefix debian-i386/,$(FILES))
	dpkg-deb --build debian-i386 raccoon-$(VERSION)_$(DEBVER)-i386.deb
	rm -rf debian-i386/usr

debian-i386/usr/local/bin/raccoon: ../raccoon/bin/raccoon32
	rm -rf debian-i386/usr/local/bin/racooon
	mkdir -p debian-i386/usr/local/bin
	cp ../raccoon/bin/raccoon32 debian-i386/usr/local/bin/raccoon

debian-i386/DEBIAN/control: debian-i386/DEBIAN debian/control
	debian/arch.sh debian/control debian-i386/DEBIAN/control i386

debian-i386/DEBIAN:
	mkdir -p debian-i386/DEBIAN

debian-i386/%: debian/%
	cp $< $@

../raccoon/bin/raccoon32: 
	make -C ../raccoon -f ../raccoon/Makefile clean i386

clean:
	make -C ../raccoon -f ../raccoon/Makefile clean
	rm -rf *.deb
	rm -rf debian-amd64
	rm -rf debian-i386
