# uncomment for console version
#BUILD=CONSOLE

# uncomment for graphic version
BUILD=GRAPHIC -DX

# block for unix based make
PROJECT = casino
CC = g++
LINK = g++
LIBPATH =
CFLAGS = -Wall
LFLAGS = -L/usr/X11/lib -lm -lX11
O = o
INCPATH = -I. -I/usr/X11/include
RMCMD = rm
DEFS = -DUNIX -Dunix -D$(BUILD)


# block for borland c++ make
#PROJECT = casino.exe
#CC = bcc
#LINK = tlink
#LLINE=@linkcmds
#LIBPATH = -L\usr\lib
#CFLAGS = -k -mh
#LFLAGS = -lx
#O = obj
#INCPATH = -I\usr\include
#RMCMD = command /c erase
#DEFS = -Dmsdos -D$(BUILD)

OBJS = \
	mterm.$(O) \
	aruba.$(O) \
	bacc.$(O) \
	bahama.$(O) \
	bingo.$(O) \
	bj.$(O) \
	bonus6.$(O) \
	boston5.$(O) \
	card7.$(O) \
	cardgame.$(O) \
	carib.$(O) \
	chuck.$(O) \
	craps.$(O) \
	dstud.$(O) \
	faceup.$(O) \
	flop.$(O) \
	holdem.$(O) \
	keno.$(O) \
	lir.$(O) \
	p357.$(O) \
	paigow.$(O) \
	paigowtiles.$(O) \
	player.$(O) \
	poker.$(O) \
	reddog.$(O) \
	royal.$(O) \
	roul.$(O) \
	sicbo.$(O) \
	slotmach.$(O) \
	slotmenu.$(O) \
	spanish.$(O) \
	superfun.$(O) \
	support.$(O) \
	texas.$(O) \
	three.$(O) \
	videokeno.$(O) \
	wheel.$(O) \
	pkrmach.$(O) \
	wave.$(O) \
	war.$(O) \
	wildholdem.$(O) \
	main.$(O) \
	awlib.$(O) \
	card.$(O) \
	deck.$(O) \
        die.$(O) \
	hand.$(O) \
	bet.$(O) \
	paigowdeck.$(O) \
	paigowhand.$(O) \
	paigowtile.$(O) \
	random.$(O) \
	kernel.$(O) \
	mstring.$(O) \

# on unix system, next line needed
LLINE=$(OBJS) -o casino

.SUFFIXES = .cpp

$(PROJECT): $(OBJS)
	$(LINK) $(LIBPATH) $(LLINE) $(LFLAGS)

.cpp.o:
	$(CC) $(LIBPATH) $(INCPATH) $(CFLAGS) $(DEFS) -c $<

.c.o:
	gcc $(LIBPATH) $(INCPATH) $(CFLAGS) $(DEFS) -c $<

clean:
	$(RMCMD) *.$(O)
	$(RMCMD) $(PROJECT)

aruba.$(O): aruba.cpp header.h aruba.h cardgame.h card.h hand.h player.h deck.h
bacc.$(O): bacc.cpp header.h bacc.h cardgame.h card.h hand.h player.h deck.h
bahama.$(O): bahama.cpp header.h bahama.h cardgame.h card.h hand.h player.h deck.h
bingo.$(O): bingo.cpp header.h bingo.h player.h
bj.$(O): bj.cpp header.h bj.h cardgame.h card.h hand.h player.h deck.h
bonus6.$(O): bonus6.cpp header.h bonus6.h cardgame.h card.h hand.h player.h deck.h
boston5.$(O): boston5.cpp header.h boston5.h cardgame.h card.h hand.h player.h deck.h
card.$(O): card.cpp header.h card.h
card7.$(O): card7.cpp header.h card.h deck.h hand.h cardgame.h card7.h player.h poker.h
cardgame.$(O): cardgame.cpp header.h cardgame.h card.h deck.h player.h
carib.$(O): carib.cpp header.h carib.h cardgame.h card.h hand.h player.h deck.h
chuck.$(O): chuck.cpp header.h chuck.h player.h
craps.$(O): craps.cpp header.h craps.h player.h
deck.$(O): deck.cpp header.h card.h deck.h
dstud.$(O): dstud.cpp header.h card.h deck.h cardgame.h dstud.h player.h hand.h
faceup.$(O): faceup.cpp header.h card.h deck.h cardgame.h faceup.h player.h hand.h
flop.$(O): flop.cpp header.h card.h deck.h cardgame.h flop.h player.h hand.h
hand.$(O): hand.cpp header.h hand.h card.h
holdem.$(O): holdem.cpp header.h holdem.h cardgame.h card.h hand.h player.h deck.h
keno.$(O): keno.cpp header.h keno.h player.h
lir.$(O): lir.cpp header.h card.h deck.h cardgame.h lir.h player.h hand.h
main.$(O): main.cpp header.h
mterm.$(O): mterm.cpp header.h
p357.$(O): p357.cpp header.h card.h deck.h cardgame.h p357.h player.h hand.h
paigow.$(O): paigow.cpp header.h card.h hand.h deck.h player.h paigow.h cardgame.h
paigowtiles.$(O): paigowtiles.cpp header.h card.h hand.h deck.h player.h paigowtiles.h cardgame.h
pkrmach.$(O): pkrmach.cpp header.h pkrmach.h deck.h card.h hand.h player.h cardgame.h
pkrmach2.$(O): pkrmach2.cpp header.h
pkrmach3.$(O): pkrmach3.cpp header.h
pkrmach4.$(O): pkrmach4.cpp header.h
pkrmachp.$(O): pkrmachp.cpp header.h
player.$(O): player.cpp header.h player.h card.h hand.h
poker.$(O): poker.cpp header.h poker.h
reddog.$(O): reddog.cpp header.h card.h hand.h deck.h reddog.h player.h cardgame.h
royal.$(O): royal.cpp header.h royal.h cardgame.h card.h hand.h player.h deck.h
roul.$(O): roul.cpp header.h roul.h player.h
sicbo.$(O): sicbo.cpp header.h sicbo.h player.h
slotmach.$(O): slotmach.cpp header.h slotmach.h player.h images/slots.xpm
spanish.$(O): spanish.cpp header.h spanish.h cardgame.h card.h hand.h player.h deck.h
superfun.$(O): superfun.cpp header.h superfun.h cardgame.h card.h hand.h player.h deck.h
support.$(O): support.cpp header.h
texas.$(O): texas.cpp header.h card.h deck.h hand.h cardgame.h texas.h player.h poker.h
three.$(O): three.cpp header.h three.h deck.h card.h hand.h cardgame.h player.h
videokeno.$(O): videokeno.cpp header.h videokeno.h player.h
wheel.$(O): wheel.cpp header.h wheel.h player.h
slotmenu.$(O): slotmenu.cpp header.h images/slotmenu.xpm
wave.$(O): wave.cpp header.h wave.h cardgame.h card.h hand.h player.h deck.h
war.$(O): war.cpp header.h war.h cardgame.h card.h hand.h player.h deck.h
wildholdem.$(O): wildholdem.cpp header.h wildholdem.h cardgame.h card.h hand.h player.h deck.h
awlib.o:	awlib.c
