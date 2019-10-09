#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "slotmach.h"


#define OFFS_X 101
#define OFFS_Y 303
#define SPACE_X 69
#define SPACE_Y 46

#ifdef GRAPHIC
#include "images/slots.xpm"
#include "images/slot_1.xpm"
#include "images/slot_2.xpm"
#include "images/slot_3.xpm"
#include "images/slot_4.xpm"
#include "images/slot_5.xpm"
#include "images/slot_6.xpm"
#include "images/slot_7.xpm"
#include "images/slot_red7.xpm"
#include "images/slot_blue7.xpm"
#include "images/slot_white7.xpm"
#include "images/slot_double7.xpm"
#include "images/slot_triple7.xpm"
#include "images/slot_8.xpm"
#include "images/slot_9.xpm"
#include "images/slot_0.xpm"
#include "images/slot_10.xpm"
#include "images/slot_bar.xpm"
#include "images/slot_dbar.xpm"
#include "images/slot_tbar.xpm"
#include "images/slot_wild_left.xpm"
#include "images/slot_wild_right.xpm"
#include "images/slot_wild_up.xpm"
#include "images/slot_wild_down.xpm"
#include "images/slot_wild.xpm"
#include "images/slot_bell.xpm"
#include "images/slot_orange.xpm"
#include "images/slot_plum.xpm"
#include "images/slot_star.xpm"
#include "images/slot_dollar.xpm"
#include "images/slot_diamond.xpm"
#include "images/slot_x2.xpm"
#include "images/slot_5x.xpm"
#include "images/slot_10x.xpm"
#include "images/slot_cherry.xpm"
#include "images/slot_horseshoe.xpm"
#include "images/slot_a.xpm"
#include "images/slot_b.xpm"
#include "images/slot_i.xpm"
#include "images/slot_j.xpm"
#include "images/slot_k.xpm"
#include "images/slot_l.xpm"
#include "images/slot_n.xpm"
#include "images/slot_o.xpm"
#include "images/slot_q.xpm"
#include "images/slot_s.xpm"
#include "images/slot_w.xpm"
#include "images/slot_y.xpm"
#include "images/slot_ruby.xpm"
#include "images/slot_emerald.xpm"
#include "images/slot_amethyst.xpm"
#include "images/slot_saphire.xpm"
#include "images/slot_star_red.xpm"
#include "images/slot_star_white.xpm"
#include "images/slot_star_blue.xpm"
#include "images/slot_car1.xpm"
#include "images/slot_car2.xpm"
#include "images/slot_car3.xpm"
#include "images/slot_plane.xpm"
#include "images/slot_train.xpm"
#include "images/slot_float.xpm"
#include "images/slot_boat1.xpm"
#include "images/slot_boat2.xpm"
#include "images/slot_boat3.xpm"
#include "images/slot_chip1.xpm"
#include "images/slot_chip5.xpm"
#include "images/slot_chip25.xpm"
#include "images/slot_chip100.xpm"
#include "images/slot_chip1k.xpm"
#include "images/slot_chip10k.xpm"
#include "images/slot_bill1.xpm"
#include "images/slot_jackpot.xpm"
#include "images/slot_sm_bar.xpm"
#include "images/slot_sm_dbar.xpm"
#include "images/slot_sm_tbar.xpm"
#include "images/slot_sm_abar.xpm"
#include "images/slot_sm_bell.xpm"
#include "images/slot_sm_any.xpm"
#include "images/slot_sm_dollar.xpm"
#include "images/slot_sm_orange.xpm"
#include "images/slot_sm_plum.xpm"
#include "images/slot_sm_cherry.xpm"
#include "images/slot_sm_x2.xpm"
#include "images/slot_sm_5x.xpm"
#include "images/slot_sm_10x.xpm"
#include "images/slot_sm_wild.xpm"
#include "images/slot_sm_7.xpm"
#include "images/slot_sm_red7.xpm"
#include "images/slot_sm_blue7.xpm"
#include "images/slot_sm_white7.xpm"
#include "images/slot_sm_any7.xpm"
#include "images/slot_sm_double7.xpm"
#include "images/slot_sm_triple7.xpm"
#include "images/slot_sm_star.xpm"
#include "images/slot_sm_horseshoe.xpm"
#include "images/slot_sm_diamond.xpm"
#include "images/slot_sm_emerald.xpm"
#include "images/slot_sm_ruby.xpm"
#include "images/slot_sm_saphire.xpm"
#include "images/slot_sm_amethyst.xpm"
#include "images/slot_sm_a.xpm"
#include "images/slot_sm_b.xpm"
#include "images/slot_sm_i.xpm"
#include "images/slot_sm_l.xpm"
#include "images/slot_sm_n.xpm"
#include "images/slot_sm_o.xpm"
#include "images/slot_sm_s.xpm"
#include "images/slot_sm_w.xpm"
#include "images/slot_sm_y.xpm"
#include "images/slot_sm_star_red.xpm"
#include "images/slot_sm_star_white.xpm"
#include "images/slot_sm_star_blue.xpm"
#include "images/slot_sm_car1.xpm"
#include "images/slot_sm_car2.xpm"
#include "images/slot_sm_car3.xpm"
#include "images/slot_sm_train.xpm"
#include "images/slot_sm_plane.xpm"
#include "images/slot_sm_boat1.xpm"
#include "images/slot_sm_boat2.xpm"
#include "images/slot_sm_boat3.xpm"
#include "images/slot_sm_float.xpm"
#include "images/slot_sm_chip1.xpm"
#include "images/slot_sm_chip5.xpm"
#include "images/slot_sm_chip25.xpm"
#include "images/slot_sm_chip100.xpm"
#include "images/slot_sm_chip1k.xpm"
#include "images/slot_sm_chip10k.xpm"
#include "images/slot_sm_bill1.xpm"
#include "images/slot_sm_jackpot.xpm"
#endif

SlotMachine::SlotMachine(int pl,Player* p,int m,int b) {
  int i;
  player=p;
  maxCoins=m;
  betSize=b;
  numReels=0;
  numPayouts=0;
  for (i=0;i<10;i++) pos[i]=0;
  payLines=pl;
  credits=0;
  coinsIn=0;
  for (i=0;i<255;i++) symbols[i]=0;
  }

SlotMachine::~SlotMachine() {
  int i;
  for (i=0;i<255;i++) 
    if (symbols[i] != 0) rcs_closePixmap(display,symbols[i]);
  }

void SlotMachine::loadSymbol(char s) {
  if (s<33 || symbols[(int)s]!=0) return;
  switch (s) {
    case '1':symbols['1']=rcs_xpmToPixmap(display,mainWindow,slot_1_xpm); break;
    case '2':symbols['2']=rcs_xpmToPixmap(display,mainWindow,slot_2_xpm); break;
    case '3':symbols['3']=rcs_xpmToPixmap(display,mainWindow,slot_3_xpm); break;
    case '4':symbols['4']=rcs_xpmToPixmap(display,mainWindow,slot_4_xpm); break;
    case '5':symbols['5']=rcs_xpmToPixmap(display,mainWindow,slot_5_xpm); break;
    case '6':symbols['6']=rcs_xpmToPixmap(display,mainWindow,slot_6_xpm); break;
    case '7':symbols['7']=rcs_xpmToPixmap(display,mainWindow,slot_7_xpm); break;
    case '8':symbols['8']=rcs_xpmToPixmap(display,mainWindow,slot_8_xpm); break;
    case '9':symbols['9']=rcs_xpmToPixmap(display,mainWindow,slot_9_xpm); break;
    case '0':symbols['0']=rcs_xpmToPixmap(display,mainWindow,slot_0_xpm); break;
    case '!':symbols['!']=rcs_xpmToPixmap(display,mainWindow,slot_chip1_xpm); break;
    case '@':symbols['@']=rcs_xpmToPixmap(display,mainWindow,slot_chip5_xpm); break;
    case '%':symbols['%']=rcs_xpmToPixmap(display,mainWindow,slot_chip25_xpm); break;
    case '&':symbols['&']=rcs_xpmToPixmap(display,mainWindow,slot_chip100_xpm); break;
    case '(':symbols['(']=rcs_xpmToPixmap(display,mainWindow,slot_chip1k_xpm); break;
    case ')':symbols[')']=rcs_xpmToPixmap(display,mainWindow,slot_chip10k_xpm); break;
    case '+':symbols['+']=rcs_xpmToPixmap(display,mainWindow,slot_10_xpm); break;
    case '~':symbols['~']=rcs_xpmToPixmap(display,mainWindow,slot_jackpot_xpm); break;
    case ',':symbols[',']=rcs_xpmToPixmap(display,mainWindow,slot_10x_xpm); break;
    case '[':symbols['[']=rcs_xpmToPixmap(display,mainWindow,slot_5x_xpm); break;
    case ']':symbols[']']=rcs_xpmToPixmap(display,mainWindow,slot_bill1_xpm); break;
    case '>':symbols['>']=rcs_xpmToPixmap(display,mainWindow,slot_wild_right_xpm); break;
    case '<':symbols['<']=rcs_xpmToPixmap(display,mainWindow,slot_wild_left_xpm); break;
    case '-':symbols['-']=rcs_xpmToPixmap(display,mainWindow,slot_bar_xpm); break;
    case '$':symbols['$']=rcs_xpmToPixmap(display,mainWindow,slot_dollar_xpm); break;
    case '=':symbols['=']=rcs_xpmToPixmap(display,mainWindow,slot_dbar_xpm); break;
    case '#':symbols['#']=rcs_xpmToPixmap(display,mainWindow,slot_tbar_xpm); break;
    case '*':symbols['*']=rcs_xpmToPixmap(display,mainWindow,slot_wild_xpm); break;
    case '^':symbols['^']=rcs_xpmToPixmap(display,mainWindow,slot_wild_up_xpm); break;
    case '{':symbols['{']=rcs_xpmToPixmap(display,mainWindow,slot_red7_xpm); break;
    case '}':symbols['}']=rcs_xpmToPixmap(display,mainWindow,slot_blue7_xpm); break;
    case '|':symbols['|']=rcs_xpmToPixmap(display,mainWindow,slot_white7_xpm); break;
    case ':':symbols[':']=rcs_xpmToPixmap(display,mainWindow,slot_double7_xpm); break;
    case ';':symbols[';']=rcs_xpmToPixmap(display,mainWindow,slot_triple7_xpm); break;
    case 'A':symbols['A']=rcs_xpmToPixmap(display,mainWindow,slot_amethyst_xpm); break;
    case 'B':symbols['B']=rcs_xpmToPixmap(display,mainWindow,slot_bell_xpm); break;
    case 'C':symbols['C']=rcs_xpmToPixmap(display,mainWindow,slot_cherry_xpm); break;
    case 'D':symbols['D']=rcs_xpmToPixmap(display,mainWindow,slot_diamond_xpm); break;
    case 'E':symbols['E']=rcs_xpmToPixmap(display,mainWindow,slot_emerald_xpm); break;
    case 'F':symbols['F']=rcs_xpmToPixmap(display,mainWindow,slot_car2_xpm); break;
    case 'G':symbols['G']=rcs_xpmToPixmap(display,mainWindow,slot_float_xpm); break;
    case 'H':symbols['H']=rcs_xpmToPixmap(display,mainWindow,slot_saphire_xpm); break;
    case 'I':symbols['I']=rcs_xpmToPixmap(display,mainWindow,slot_star_red_xpm); break;
    case 'J':symbols['J']=rcs_xpmToPixmap(display,mainWindow,slot_star_white_xpm); break;
    case 'K':symbols['K']=rcs_xpmToPixmap(display,mainWindow,slot_star_blue_xpm); break;
    case 'M':symbols['M']=rcs_xpmToPixmap(display,mainWindow,slot_boat1_xpm); break;
    case 'N':symbols['N']=rcs_xpmToPixmap(display,mainWindow,slot_boat2_xpm); break;
    case 'O':symbols['O']=rcs_xpmToPixmap(display,mainWindow,slot_orange_xpm); break;
    case 'P':symbols['P']=rcs_xpmToPixmap(display,mainWindow,slot_plum_xpm); break;
    case 'Q':symbols['Q']=rcs_xpmToPixmap(display,mainWindow,slot_plane_xpm); break;
    case 'R':symbols['R']=rcs_xpmToPixmap(display,mainWindow,slot_ruby_xpm); break;
    case 'S':symbols['S']=rcs_xpmToPixmap(display,mainWindow,slot_star_xpm); break;
    case 'T':symbols['T']=rcs_xpmToPixmap(display,mainWindow,slot_train_xpm); break;
    case 'U':symbols['U']=rcs_xpmToPixmap(display,mainWindow,slot_horseshoe_xpm); break;
    case 'V':symbols['V']=rcs_xpmToPixmap(display,mainWindow,slot_wild_down_xpm); break;
    case 'W':symbols['W']=rcs_xpmToPixmap(display,mainWindow,slot_car3_xpm); break;
    case 'X':symbols['X']=rcs_xpmToPixmap(display,mainWindow,slot_x2_xpm); break;
    case 'Y':symbols['Y']=rcs_xpmToPixmap(display,mainWindow,slot_boat3_xpm); break;
    case 'Z':symbols['Z']=rcs_xpmToPixmap(display,mainWindow,slot_car1_xpm); break;
    case 'a':symbols['a']=rcs_xpmToPixmap(display,mainWindow,slot_a_xpm); break;
    case 'b':symbols['b']=rcs_xpmToPixmap(display,mainWindow,slot_b_xpm); break;
    case 'i':symbols['i']=rcs_xpmToPixmap(display,mainWindow,slot_i_xpm); break;
    case 'j':symbols['j']=rcs_xpmToPixmap(display,mainWindow,slot_j_xpm); break;
    case 'k':symbols['k']=rcs_xpmToPixmap(display,mainWindow,slot_k_xpm); break;
    case 'l':symbols['l']=rcs_xpmToPixmap(display,mainWindow,slot_l_xpm); break;
    case 'n':symbols['n']=rcs_xpmToPixmap(display,mainWindow,slot_n_xpm); break;
    case 'o':symbols['o']=rcs_xpmToPixmap(display,mainWindow,slot_o_xpm); break;
    case 'q':symbols['q']=rcs_xpmToPixmap(display,mainWindow,slot_q_xpm); break;
    case 's':symbols['s']=rcs_xpmToPixmap(display,mainWindow,slot_s_xpm); break;
    case 'w':symbols['w']=rcs_xpmToPixmap(display,mainWindow,slot_w_xpm); break;
    case 'y':symbols['y']=rcs_xpmToPixmap(display,mainWindow,slot_y_xpm); break;
    }
  }

void SlotMachine::displayPayoutSymbol(int x,int y,char s) {
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  switch (s) {
    case '1':Output(" 1  "); break;
    case '2':Output(" 2  "); break;
    case '3':Output(" 3  "); break;
    case '4':Output(" 4  "); break;
    case '5':Output(" 5  "); break;
    case '6':Output(" 6  "); break;
    case '7':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_7_xpm); break;
    case '8':Output(" 8  "); break;
    case '9':Output(" 9  "); break;
    case '0':Output(" 0  "); break;
    case '+':Output(" 10 "); break;
    case '~':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_jackpot_xpm); break;
    case '[':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_5x_xpm); break;
    case ',':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_10x_xpm); break;
    case ']':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_bill1_xpm); break;
    case '!':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip1_xpm); break;
    case '@':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip5_xpm); break;
    case '%':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip25_xpm); break;
    case '&':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip100_xpm); break;
    case '(':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip1k_xpm); break;
    case ')':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_chip10k_xpm); break;
    case '$':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_dollar_xpm); break;
    case '-':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_bar_xpm); break;
    case '=':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_dbar_xpm); break;
    case '#':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_tbar_xpm); break;
    case '/':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_abar_xpm); break;
    case '.':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_any_xpm); break;
    case '*':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_wild_xpm); break;
    case '{':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_red7_xpm); break;
    case '}':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_blue7_xpm); break;
    case '|':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_white7_xpm); break;
    case '_':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_any7_xpm); break;
    case ':':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_double7_xpm); break;
    case ';':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_triple7_xpm); break;
    case 'X':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_x2_xpm); break;
    case 'A':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_amethyst_xpm); break;
    case 'B':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_bell_xpm); break;
    case 'C':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_cherry_xpm); break;
    case 'D':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_diamond_xpm); break;
    case 'E':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_emerald_xpm); break;
    case 'F':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_car2_xpm); break;
    case 'G':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_float_xpm); break;
    case 'H':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_saphire_xpm); break;
    case 'I':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_star_red_xpm); break;
    case 'J':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_star_white_xpm); break;
    case 'K':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_star_blue_xpm); break;
    case 'M':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_boat1_xpm); break;
    case 'N':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_boat2_xpm); break;
    case 'O':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_orange_xpm); break;
    case 'P':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_plum_xpm); break;
    case 'Q':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_plane_xpm); break;
    case 'R':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_ruby_xpm); break;
    case 'S':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_star_xpm); break;
    case 'T':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_train_xpm); break;
    case 'U':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_horseshoe_xpm); break;
    case 'W':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_car3_xpm); break;
    case 'Y':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_boat3_xpm); break;
    case 'Z':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_car1_xpm); break;
    case 'a':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_a_xpm); break;
    case 'b':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_b_xpm); break;
    case 'c':Output(" C  "); break;
    case 'd':Output(" D  "); break;
    case 'e':Output(" E  "); break;
    case 'f':Output(" F  "); break;
    case 'g':Output(" G  "); break;
    case 'h':Output(" H  "); break;
    case 'i':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_i_xpm); break;
    case 'j':Output(" J  "); break;
    case 'k':Output(" K  "); break;
    case 'l':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_l_xpm); break;
    case 'm':Output(" M  "); break;
    case 'n':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_n_xpm); break;
    case 'o':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_o_xpm); break;
    case 'p':Output(" P  "); break;
    case 'q':Output(" Q  "); break;
    case 'r':Output(" R  "); break;
    case 's':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_s_xpm); break;
    case 't':Output(" T  "); break;
    case 'u':Output(" U  "); break;
    case 'v':Output(" V  "); break;
    case 'w':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_w_xpm); break;
    case 'x':Output(" X  "); break;
    case 'y':rcs_drawPixmap(display,mainScreen,gc,x,y,slot_sm_y_xpm); break;
    case 'z':Output(" Z  "); break;
  rcs_closeGC(display,gc);
#endif
    }
  }
void SlotMachine::displaySymbol(int x,int y,char s) {
#ifdef GRAPHIC
  rcs_GC gc;
  if (s<=32 || s>126) return;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,symbols[(int)s],mainScreen,gc,0,0,40,40,x,y);
  rcs_closeGC(display,gc);
  return;
#endif
  }

void SlotMachine::displaySymbol(char s) {
  switch (s) {
    case '1':Output(" 1  "); break;
    case '2':Output(" 2  "); break;
    case '3':Output(" 3  "); break;
    case '4':Output(" 4  "); break;
    case '5':Output(" 5  "); break;
    case '6':Output(" 6  "); break;
    case '7':Output(" 7  "); break;
    case '8':Output(" 8  "); break;
    case '9':Output(" 9  "); break;
    case '0':Output(" 0  "); break;
    case '+':Output(" 10 "); break;
    case '>':Output(">>>>"); break;
    case '<':Output("<<<<"); break;
    case '-':Output("----"); break;
    case '$':Output("$$$$"); break;
    case '=':Output("===="); break;
    case '#':Output("####"); break;
    case '*':Output("WILD"); break;
    case '^':Output("-^^-"); break;
    case 'B':Output("BELL"); break;
    case 'C':Output("CHRY"); break;
    case 'D':Output(" <> "); break;
    case 'O':Output("ORNG"); break;
    case 'P':Output("PLUM"); break;
    case 'S':Output(" *  "); break;
    case 'U':Output(" U  "); break;
    case 'V':Output("-VV-"); break;
    case 'X':Output(" X2 "); break;
    case 'a':Output(" A  "); break;
    case 'b':Output(" B  "); break;
    case 'c':Output(" C  "); break;
    case 'd':Output(" D  "); break;
    case 'e':Output(" E  "); break;
    case 'f':Output(" F  "); break;
    case 'g':Output(" G  "); break;
    case 'h':Output(" H  "); break;
    case 'i':Output(" I  "); break;
    case 'j':Output(" J  "); break;
    case 'k':Output(" K  "); break;
    case 'l':Output(" L  "); break;
    case 'm':Output(" M  "); break;
    case 'n':Output(" N  "); break;
    case 'o':Output(" O  "); break;
    case 'p':Output(" P  "); break;
    case 'q':Output(" Q  "); break;
    case 'r':Output(" R  "); break;
    case 's':Output(" S  "); break;
    case 't':Output(" T  "); break;
    case 'u':Output(" U  "); break;
    case 'v':Output(" V  "); break;
    case 'w':Output(" W  "); break;
    case 'x':Output(" X  "); break;
    case 'y':Output(" Y  "); break;
    case 'z':Output(" Z  "); break;
    default :Output("    "); break;
    }
  }

void SlotMachine::displayPayoutSymbol(char s) {
  switch (s) {
    case '1':Output(" 1  "); break;
    case '2':Output(" 2  "); break;
    case '3':Output(" 3  "); break;
    case '4':Output(" 4  "); break;
    case '5':Output(" 5  "); break;
    case '6':Output(" 6  "); break;
    case '7':Output(" 7  "); break;
    case '8':Output(" 8  "); break;
    case '9':Output(" 9  "); break;
    case '0':Output(" 0  "); break;
    case '+':Output(" 10 "); break;
    case '$':Output("$$$$"); break;
    case '-':Output("----"); break;
    case '=':Output("===="); break;
    case '#':Output("####"); break;
    case '/':Output("BAR "); break;
    case '.':Output("ANY "); break;
    case '*':Output("WILD"); break;
    case 'X':Output(" X2 "); break;
    case 'B':Output("BELL"); break;
    case 'C':Output("CHRY"); break;
    case 'D':Output(" <> "); break;
    case 'O':Output("ORNG"); break;
    case 'P':Output("PLUM"); break;
    case 'S':Output(" *  "); break;
    case 'U':Output(" U  "); break;
    case 'a':Output(" A  "); break;
    case 'b':Output(" B  "); break;
    case 'c':Output(" C  "); break;
    case 'd':Output(" D  "); break;
    case 'e':Output(" E  "); break;
    case 'f':Output(" F  "); break;
    case 'g':Output(" G  "); break;
    case 'h':Output(" H  "); break;
    case 'i':Output(" I  "); break;
    case 'j':Output(" J  "); break;
    case 'k':Output(" K  "); break;
    case 'l':Output(" L  "); break;
    case 'm':Output(" M  "); break;
    case 'n':Output(" N  "); break;
    case 'o':Output(" O  "); break;
    case 'p':Output(" P  "); break;
    case 'q':Output(" Q  "); break;
    case 'r':Output(" R  "); break;
    case 's':Output(" S  "); break;
    case 't':Output(" T  "); break;
    case 'u':Output(" U  "); break;
    case 'v':Output(" V  "); break;
    case 'w':Output(" W  "); break;
    case 'x':Output(" X  "); break;
    case 'y':Output(" Y  "); break;
    case 'z':Output(" Z  "); break;
    default :Output("    "); break;
    }
  }

void SlotMachine::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  char     buffer[80];
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,725,228,150,150,725,228);
  font=rcs_openFont(display,VIDEO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,362+SPACE_X*(numReels-3),398,77,30,362+SPACE_X*(numReels-3),398);
  rcs_copyArea(display,table,mainScreen,gc,362+SPACE_X*(numReels-3),363,77,30,362+SPACE_X*(numReels-3),363);
/*
  rcs_drawFilledBox(display,mainScreen,gc,362+SPACE_X*(numReels-3),398,77,30);
  rcs_drawFilledBox(display,mainScreen,gc,362+SPACE_X*(numReels-3),363,77,20);
*/
  rcs_namedForeground(display,gc,"yellow");
  sprintf(buffer,"$%8.0f",player->money());
  rcs_drawString(display,mainScreen,gc,730,245,player->getName());
  rcs_drawString(display,mainScreen,gc,730,265,buffer);
  rcs_closeFont(display,font);
  rcs_namedForeground(display,gc,"red");
  font=rcs_openFont(display,SLOT_STAT_FONT);
  rcs_setFont(display,gc,font);
  sprintf(buffer,"%ld",credits);
  rcs_drawString(display,mainScreen,gc,370+SPACE_X*(numReels-3),376,buffer);
  sprintf(buffer,"%d",coinsIn);
  rcs_drawString(display,mainScreen,gc,370+SPACE_X*(numReels-3),408,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  }

long SlotMachine::checkWin(char* pl,char* sp) {
  int  i,j,k;
  int  mult;
  int  matched;
  byte counts[128];
  long ret;
  ret=0;
  for (i=0;i<numPayouts;i++) {
    matched=0;
    mult=1;
    if (strncmp(payouts[i],"|##",3)==0) {
      k=0; mult=1;
      for (j=0;j<numReels;j++) {
        if (pl[j]>='0' && pl[j]<='9') {
          k=k*10 + (pl[j]-'0');
          } else mult=0;
        }
      k*=mult;
      ret=k;
      }
    else if (strncmp(payouts[i],"|1",2)==0) {
      k=0;
      for (j=0;j<numReels;j++) {
        if (payouts[i][2]==pl[j]) k++;
        if (k==1) if (value[i]>ret) ret=value[i];
        }
      }
    else if (strncmp(payouts[i],"|2",2)==0) {
      k=0;
      for (j=0;j<numReels;j++) {
        if (payouts[i][2]==pl[j]) k++;
        if (k==2) if (value[i]>ret) ret=value[i];
        }
      }
    else if (strcmp(payouts[i],"|PAIR")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        if (counts[(int)pl[j]]>1 && pl[j]!=' ') if (value[i]>ret) ret=value[i];
        }
      }
    else if (strcmp(payouts[i],"|FULL")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        }
      k=0;
      for (j=0;j<128;j++) if (counts[j]==2 && j!=32) k|=1;
        else if (counts[j]==3 && j!=32) k|=2;
      if (k==3) if (value[i]>ret) ret=value[i];
      }
    else if (strcmp(payouts[i],"|TWOP")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        }
      k=0;
      for (j=0;j<128;j++) if (counts[j]>1 && j!=32) k++;
      if (k>1) if (value[i]>ret) ret=value[i];
      }
    else if (strcmp(payouts[i],"|FIVE")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        if (counts[(int)pl[j]]>4 && pl[j]!=' ') if (value[i]>ret) ret=value[i];
        }
      }
    else if (strcmp(payouts[i],"|FOUR")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        if (counts[(int)pl[j]]>3 && pl[j]!=' ') if (value[i]>ret) ret=value[i];
        }
      }
    else if (strcmp(payouts[i],"|THRE")==0) {
      for (j=0;j<128;j++) counts[j]=0;
      for (j=0;j<numReels;j++) {
        counts[(int)pl[j]]++;
        if (counts[(int)pl[j]]>2 && pl[j]!=' ') if (value[i]>ret) ret=value[i];
        }
      } else {
      for (j=0;j<numReels;j++) {
        if (sp[j] == '*') matched++;
        else if (sp[j] == '2') {
          matched++;
          mult *= 2;
          }
        else if (sp[j] == '5') {
          matched++;
          mult *= 5;
          }
        else if (sp[j] == '1') {
          matched++;
          mult *= 10;
          }
        else {
          switch (payouts[i][j]) {
            case '/':if (pl[j]=='-'||pl[j]=='='||pl[j]=='#') matched++;
                     break;
            case '_':if (pl[j]=='{'||pl[j]=='}'||pl[j]=='|' ||
                         pl[j]==':' || pl[j]==';') matched++;
                     break;
            case '?':matched++;
                     break;
            case '.':if (pl[j] != ' ') matched++;
                     break;
              default :if (pl[j] == payouts[i][j]) matched++;
            }
          }
        }
        if (matched == numReels) {
          if (value[i]*mult > ret) ret=value[i]*mult;
        }
      }
    }

  return ret;
  }

void SlotMachine::displayReels() {
  int i;
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,OFFS_X-20,OFFS_Y-20,SPACE_X*numReels+40,SPACE_Y*3+40,OFFS_X-20,OFFS_Y-20);
  rcs_closeGC(display,gc);
#endif
  for (i=0;i<numReels;i++) {
#ifdef GRAPHIC
    if (pos[i]+1<strlen(reels[i])) displaySymbol(i*SPACE_X+OFFS_X,OFFS_Y,reels[i][pos[i]+1]);
      else displaySymbol(i*SPACE_X+OFFS_X,OFFS_Y,reels[i][0]);
    displaySymbol(i*SPACE_X+OFFS_X,OFFS_Y+SPACE_Y,reels[i][pos[i]]);
    if (pos[i]>0) displaySymbol(i*SPACE_X+OFFS_X,OFFS_Y+SPACE_Y*2,reels[i][pos[i]-1]);
      else displaySymbol(i*SPACE_X+OFFS_X,OFFS_Y+SPACE_Y*2,reels[i][strlen(reels[i])-1]);
#endif
#ifdef CONSOLE
    GotoXY(5+i*5,numPayouts+3);
    if (pos[i]+1<strlen(reels[i])) displaySymbol(reels[i][pos[i]+1]);
      else displaySymbol(reels[i][0]);
    GotoXY(5+i*5,numPayouts+4);
    displaySymbol(reels[i][pos[i]]);
    GotoXY(5+i*5,numPayouts+5);
    if (pos[i]>0) displaySymbol(reels[i][pos[i]-1]);
      else displaySymbol(reels[i][strlen(reels[i])-1]);
#endif
    }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_drawLine(display,mainScreen,gc,83,371,297+SPACE_X*(numReels-3),371);
  if (payLines>1 && coinsIn>1) 
    rcs_drawLine(display,mainScreen,gc,83,325,297+SPACE_X*(numReels-3),325);
  if (payLines>2 && coinsIn>2) 
    rcs_drawLine(display,mainScreen,gc,83,417,297+SPACE_X*(numReels-3),417);
  if (payLines>3 && coinsIn>3) 
    rcs_drawLine(display,mainScreen,gc,83,290,297+SPACE_X*(numReels-3),450);
  if (payLines>4 && coinsIn>4) 
    rcs_drawLine(display,mainScreen,gc,83,450,297+SPACE_X*(numReels-3),290);
  rcs_closeGC(display,gc);
  gc=rcs_openGC(display,mainWindow);
  rcs_copyArea(display,mainScreen,mainWindow,gc,OFFS_X-20,OFFS_Y-20,SPACE_X*numReels+40,SPACE_Y*3+40,OFFS_X-20,OFFS_Y-20);
  rcs_closeGC(display,gc);
#endif
  }

void SlotMachine::addReel(const char* r,const char* sp,const char* st) {
  unsigned int i;
  strcpy(reels[numReels],r);
  strcpy(specials[numReels],sp);
  strcpy(stops[numReels++],st);
  for (i=0;i<strlen(r);i++) loadSymbol(r[i]);
  }

void SlotMachine::addPayout(const char* p,int n) {
  value[numPayouts]=n;
  strcpy(payouts[numPayouts++],p);
  }

void SlotMachine::spin() {
  int i,j;
  int extra;
  time_t start;
  for (i=0;i<numReels;i++) {
    j=Random(strlen(reels[i])*10);
    endPos[i]=0;
    j-=(10-(stops[i][endPos[i]]-0x30));
    extra=(stops[i][endPos[i]]-0x30);
    while (j>0) {
      endPos[i]++;
      j-=(10-(stops[i][endPos[i]]-0x30));
      j-=extra;
      extra=(stops[i][endPos[i]]-0x30);
      }
    if (endPos[i]>=strlen(reels[i])) endPos[i]--;
    }
  for (i=0;i<numReels;i++) {
    start=rcs_time()+((i==0)?1000:250);
    while (pos[i] != endPos[i] || rcs_time()<start) {
      for (j=i;j<numReels;j++) {
        pos[j]++;
        if (pos[j] >= strlen(reels[j])) pos[j]=0;
        }
      displayReels();
      }
    }
  displayReels();
  for (i=0; i<numReels; i++) {
    if (specials[i][pos[i]] == 'v') {
      Delay(1);
      pos[i]++;
      if (pos[i] >= strlen(reels[i])) pos[i]=0;
      displayReels();
      }
    if (specials[i][pos[i]] == '^') {
      Delay(1);
      pos[i]--;
      if (pos[i]<0) pos[i]=strlen(reels[i])-1;
      displayReels();
      }
    if (specials[i][pos[i]] == '>') {
      Delay(1);
      j=50;
      while (reels[i][pos[i]] != reels[i+1][pos[i+1]] && --j != 0) {
        pos[i]++;
        if (pos[i] >= strlen(reels[i])) pos[i]=0;
        displayReels();
        }
      }
    if (specials[i][pos[i]] == '<') {
      Delay(1);
      j=50;
      while (reels[i][pos[i]] != reels[i-1][pos[i-1]] && --j != 0) {
        pos[i]++;
        if (pos[i] >= strlen(reels[i])) pos[i]=0;
        displayReels();
        }
      }
    }
  }

void SlotMachine::play() {
  int i,j;
  int bet;
  long won;
//  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char     flag;
#endif
  char buffer[80];
  char spec[10];
  credits=0;
#ifdef GRAPHIC
  table=rcs_xpmToPixmap(display,mainWindow,slots_xpm);
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  if (numReels>3) {
    for (i=0;i<(numReels-3);i++) {
      rcs_copyArea(display,table,mainScreen,gc,OFFS_X-12+SPACE_X,0,SPACE_X,600,OFFS_X+SPACE_X*(2+i)-12,0);
      }
  rcs_copyArea(display,table,mainScreen,gc,OFFS_X-12+SPACE_X*2,0,800-OFFS_X-12+SPACE_X*numReels,600,OFFS_X+SPACE_X*(numReels-1)-12,0);
    }
  if (payLines>1) {
    rcs_copyArea(display,mainScreen,mainScreen,gc,299+SPACE_X*(numReels-3),358,41,30,299+SPACE_X*(numReels-3),358-SPACE_Y);
    rcs_copyArea(display,mainScreen,mainScreen,gc,299+SPACE_X*(numReels-3),358,41,30,299+SPACE_X*(numReels-3),358+SPACE_Y);
    rcs_copyArea(display,mainScreen,mainScreen,gc,40,358,41,30,40,358-SPACE_Y);
    rcs_copyArea(display,mainScreen,mainScreen,gc,40,358,41,30,40,358+SPACE_Y);
    if (payLines>3) {
      rcs_copyArea(display,mainScreen,mainScreen,gc,40,358,41,30,40,358-82);
      rcs_copyArea(display,mainScreen,mainScreen,gc,40,358,41,30,40,358+82);
      rcs_copyArea(display,mainScreen,mainScreen,gc,299+SPACE_X*(numReels-3),358,41,30,299+SPACE_X*(numReels-3),358-82);
      rcs_copyArea(display,mainScreen,mainScreen,gc,299+SPACE_X*(numReels-3),358,41,30,299+SPACE_X*(numReels-3),358+82);
      }
    }
  rcs_copyArea(display,mainScreen,table,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  ClearScreen();
#endif
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,SLOT_FONT);
  rcs_setFont(display,gc,font);
#endif
  for (i=0;i<numPayouts;i++) {
#ifdef GRAPHIC
    if (strcmp(payouts[i],"|PAIR")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any Pair");
      else if (strcmp(payouts[i],"|TWOP")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 2 Pair");
      else if (strcmp(payouts[i],"|THRE")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 3 of a kind");
      else if (strcmp(payouts[i],"|FULL")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any Fullhouse");
      else if (strcmp(payouts[i],"|FOUR")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 4 of a kind");
      else if (strcmp(payouts[i],"|FIVE")==0) rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 5 of a kind");
      else if (strncmp(payouts[i],"|1",2)==0) {
        rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 1");
        displayPayoutSymbol(100,20+i*20,payouts[i][2]);
        }
      else if (strncmp(payouts[i],"|2",2)==0) {
        rcs_drawString(display,mainScreen,gc,40,35+i*20,"Any 2");
        displayPayoutSymbol(100,20+i*20,payouts[i][2]);
        }
      else if (strncmp(payouts[i],"|##",3)==0) {
        rcs_drawString(display,mainScreen,gc,40,35+i*20,"Pays lined up amount");
        continue;
        }
      else for (j=0;j<(int)strlen(payouts[i]);j++) {
        displayPayoutSymbol(40+j*22,20+i*20,payouts[i][j]);
      }
    for (j=0;j<((payLines == 1) ? maxCoins : 1);j++) {
      sprintf(buffer,"%7ld",(j+1)*value[i]);
      rcs_drawString(display,mainScreen,gc,22*numReels+(j*75)+82,35+i*20,buffer);
      }
#endif
#ifdef CONSOLE
    GotoXY(1,i+1);
    if (strcmp(payouts[i],"|PAIR")==0) Output("Any Pair");
      else if (strcmp(payouts[i],"|TWOP")==0) Output("Any 2 Pair");
      else if (strcmp(payouts[i],"|THRE")==0) Output("Any 3 of a kind");
      else if (strcmp(payouts[i],"|FULL")==0) Output("Any Fullhouse");
      else if (strcmp(payouts[i],"|FOUR")==0) Output("Any 4 of a kind");
      else if (strcmp(payouts[i],"|FIVE")==0) Output("Any 5 of a kind");
      else for (j=0;j<strlen(payouts[i]);j++) {
        GotoXY(j*5+1,i+1); displayPayoutSymbol(payouts[i][j]);
        }

    for (j=0;j<((payLines == 1) ? maxCoins : 1);j++) {
      sprintf(buffer,"%7ld",(j+1)*value[i]);
      GotoXY(numReels*6+j*8,i+1);
      Output(buffer);
      }
#endif
    }
#ifdef GRAPHIC
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  for (i=0;i<numReels;i++) pos[i]=Random(strlen(reels[i]));
  displayReels();
  bet=1;
#ifdef CONSOLE
  GotoXY(numReels*5+10,numPayouts+3);
  Output("Credits");
  GotoXY(numReels*5+10,numPayouts+6);
  Output("Won");
  GotoXY(1,numPayouts+4); Output("-->");
  GotoXY(numReels*5+5,numPayouts+4); Output("<--");
#endif
  while (bet != 0) {
    showPlayer();
    coinsIn=0;
#ifdef GRAPHIC
    flag=' ';
    while (flag == ' ') {
      event=getEvent(display);
      if (event.type==EVENT_BUTTON_PRESS && event.d1 == 1) {
        if (event.d2>=52 && event.d2<=110 &&
            event.d3>=497 && event.d3<=532 && coinsIn==0) {
            flag='P';
            bet=0;
            }
        if (event.d2>=235+(numReels-3)*SPACE_X &&
            event.d2<=293+(numReels-3)*SPACE_X &&
            event.d3>=497 && event.d3<=532 && coinsIn>0) {
            flag='P';
            bet=coinsIn;
            }
        if (event.d2>=490+(numReels-3)*SPACE_X &&
            event.d2<=554+(numReels-3)*SPACE_X &&
            event.d3>=425 && event.d3<=462 && coinsIn<maxCoins) {
          coinsIn++;
          showPlayer();
          }
        if (event.d2>=371+(numReels-3)*SPACE_X &&
            event.d2<=429+(numReels-3)*SPACE_X &&
            event.d3>=497 && event.d3<=532 && coinsIn<maxCoins) {
          coinsIn++;
          showPlayer();
          }
        if (event.d2>=303+(numReels-3)*SPACE_X &&
            event.d2<=360+(numReels-3)*SPACE_X &&
            event.d3>=497 && event.d3<=532 && coinsIn<maxCoins) {
          coinsIn=maxCoins;
          showPlayer();
          flag='P';
          bet=coinsIn;
          }
        }
      }
#endif

#ifdef CONSOLE
    sprintf(buffer,"Money $%12.2f",player->money());
    GotoXY(5,19); Output(buffer);
    GotoXY(numReels*5+10,numPayouts+4);
    sprintf(buffer,"%6ld",credits);
    Output(buffer);
    GotoXY(5,20); Output("Coins ? ");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
#endif
    if (bet != 0) {
      if (bet > 0 && bet>maxCoins) bet=maxCoins;
      player->addPaidIn(abs(bet*betSize));
      if (bet < 0) {
        bet=-bet;
        if (bet>maxCoins) bet=maxCoins;
        player->placeBet((bet-credits)*betSize,0,1,1);
player->loseHandBets(0);
        }
      else if (credits >= bet) credits -= bet;
        else {
          player->placeBet((bet-credits)*betSize,0,1,1);
player->loseHandBets(0);
          credits=0;
        }
      showPlayer();
#ifdef CONSOLE
      if (payLines>1 && bet>1) {
        GotoXY(1,numPayouts+3); Output("-->");
        GotoXY(numReels*5+5,numPayouts+3); Output("<--");
        } else {
        GotoXY(1,numPayouts+3); Output("   ");
        GotoXY(numReels*5+5,numPayouts+3); Output("   ");
        }
      if (payLines>2 && bet>2) {
        GotoXY(1,numPayouts+5); Output("-->");
        GotoXY(numReels*5+5,numPayouts+5); Output("<--");
        } else {
        GotoXY(1,numPayouts+5); Output("   ");
        GotoXY(numReels*5+5,numPayouts+5); Output("   ");
        }
      if (payLines>3 && bet>3) {
        GotoXY(1,numPayouts+2); Output("--\\");
        GotoXY(numReels*5+5,numPayouts+6); Output("\\--");
        } else {
        GotoXY(1,numPayouts+2); Output("   ");
        GotoXY(numReels*5+5,numPayouts+6); Output("   ");
        }
      if (payLines>4 && bet>4) {
        GotoXY(1,numPayouts+6); Output("--/");
        GotoXY(numReels*5+5,numPayouts+2); Output("/--");
        } else {
        GotoXY(1,numPayouts+6); Output("   ");
        GotoXY(numReels*5+5,numPayouts+2); Output("   ");
        }
      GotoXY(numReels*5+10,numPayouts+4);
      sprintf(buffer,"%6ld",credits);
      Output(buffer);
      sprintf(buffer,"Money $%12.2f",player->money());
      GotoXY(5,19); Output(buffer);
      GotoXY(5,20); Output("             ");
#endif
      spin();
      for (i=0;i<numReels;i++) buffer[i]=reels[i][pos[i]];
      for (i=0;i<numReels;i++) spec[i]=specials[i][pos[i]];
      buffer[numReels]=0;
      spec[numReels]=0;
      won=checkWin(buffer,spec);
      if (payLines == 1) won *= bet;
      if (payLines>1 && bet>1) {
        for (i=0;i<numReels;i++)
          buffer[i]=(pos[i]<strlen(reels[i])-1)?reels[i][pos[i]+1]:reels[i][0];
        for (i=0;i<numReels;i++)
          spec[i]=(pos[i]<strlen(reels[i])-1)?specials[i][pos[i]+1]:specials[i][0];
        buffer[numReels]=0;
        spec[numReels]=0;
        won+=checkWin(buffer,spec);
        }
      if (payLines>2 && bet>2) {
        for (i=0;i<numReels;i++)
          buffer[i]=(pos[i]>0)?reels[i][pos[i]-1]:reels[i][strlen(reels[i])-1];
        for (i=0;i<numReels;i++)
          spec[i]=(pos[i]>0)?specials[i][pos[i]-1]:specials[i][strlen(specials[i])-1];
        buffer[numReels]=0;
        spec[numReels]=0;
        won+=checkWin(buffer,spec);
        }
      if (payLines>3 && bet>3) {
        buffer[0]=(pos[0]<strlen(reels[0])-1)?reels[0][pos[0]+1]:reels[0][0];
        spec[0]=(pos[0]<strlen(reels[0])-1)?specials[0][pos[0]+1]:specials[0][0];
        buffer[1]=reels[1][pos[1]];
        buffer[2]=(pos[2]>0)?reels[2][pos[2]-1]:reels[2][strlen(reels[2])-1];
        spec[2]=(pos[2]>0)?specials[2][pos[2]-1]:specials[2][strlen(specials[2])-1];
        buffer[numReels]=0;
        spec[numReels]=0;
        won+=checkWin(buffer,spec);
        }
      if (payLines>4 && bet>4) {
        buffer[0]=(pos[0]>0)?reels[0][pos[0]-1]:reels[0][strlen(reels[0])-1];
        spec[0]=(pos[0]>0)?specials[0][pos[0]-1]:specials[0][strlen(specials[0])-1];
        buffer[1]=reels[1][pos[1]];
        buffer[2]=(pos[2]<strlen(reels[2])-1)?reels[2][pos[2]+1]:reels[2][0];
        spec[0]=(pos[2]<strlen(reels[2])-1)?specials[2][pos[2]+1]:specials[2][0];
        buffer[numReels]=0;
        spec[numReels]=0;
        won+=checkWin(buffer,spec);
        }
#ifdef CONSOLE
      GotoXY(numReels*5+10,numPayouts+7);
      sprintf(buffer,"%6ld",won);
      Output(buffer);
#endif
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,362+SPACE_X*(numReels-3),331,77,20,362+SPACE_X*(numReels-3),331);
//  rcs_drawFilledBox(display,mainScreen,gc,362+SPACE_X*(numReels-3),331,77,20);
  rcs_namedForeground(display,gc,"red");
  font=rcs_openFont(display,SLOT_STAT_FONT);
  rcs_setFont(display,gc,font);
  sprintf(buffer,"%ld",won);
  rcs_drawString(display,mainScreen,gc,370+SPACE_X*(numReels-3),344,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
#endif
      credits+=won;
      player->addPaidOut(won*betSize);
    }
    }
  if (credits > 0) player->winMoney(credits*betSize);
  }

