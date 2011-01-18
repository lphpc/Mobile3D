
all:dummy

dummy:
	@echo "make mobile3d"

mobile3d:

	cp /usr/local/lib/*mobile3d*  mobile3d-1.0/usr/local/lib
	cp /usr/local/bin/3dclock  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/blending  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/caustics  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/flag  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/mii  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/model_am  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/rectangle  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/sea  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/texture  mobile3d-1.0/usr/local/bin
	cp /usr/local/bin/triangle  mobile3d-1.0/usr/local/bin
	cp -r /usr/local/share/mobile3d mobile3d-1.0/usr/local/share/
	fakeroot dpkg-deb --build mobile3d-1.0


clean:
	rm -rf mobile3d-1.0/usr/local/share/mobile3d
	rm -f mobile3d-1.0/usr/local/bin/*
	rm -f mobile3d-1.0/usr/local/lib/*mobile3d*
	rm -f *.deb

