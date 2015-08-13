linux: debian-amd64 debian-i386

debian-amd64: raccoon-0.1.1_1-amd64.deb

debian-i386: raccoon-0.1.1_1-i386.deb

raccoon-0.1.1_1-amd64.deb: ../raccoon/bin/raccoon
	rm -rf debian-amd64/usr
	mkdir -p debian-amd64/usr/local/bin
	cp ../raccoon/bin/raccoon debian-amd64/usr/local/bin/raccoon
	dpkg-deb --build debian-amd64 raccoon-0.1.1_1-amd64.deb
	rm -rf debian-amd64/usr

../raccoon/bin/raccoon: 
	cd ../raccoon
	make clean amd64
	cd ../dist

raccoon-0.1.1_1-i386.deb: ../raccoon/bin/raccoon32
	rm -rf debian-i386/usr
	mkdir -p debian-i386/usr/local/bin
	cp ../raccoon/bin/raccoon32 debian-i386/usr/local/bin/raccoon
	dpkg-deb --build debian-i386 raccoon-0.1.1_1-i386.deb
	rm -rf debian-i386/usr

../raccoon/bin/raccoon32: 
	cd ../raccoon
	make clean i386
	cd ../dist

clean:
	rm -rf *.deb
	rm -rf debian-amd64/usr
	rm -rf debian-i386/usr
