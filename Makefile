#top-level makefile
#by Yan Zhang, 2/2/2017

all:
	cd src; make
clean:
	cd src; make clean
tar:
	gtar cvzf Chess_V1.0.tar.gz bin --exclude 'CVS' doc --exclude 'CVS' --exclude 'Chess_SoftwareSpec.pdf' README INSTALL COPYRIGHT
tarsrc:
	gtar cvzf Chess_V1.0_src.tar.gz bin --exclude 'CVS' doc --exclude 'CVS' src --exclude 'CVS' --exclude '*.tar.gz' README Makefile INSTALL COPYRIGHT


