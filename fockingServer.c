#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs10.h"
int conn_sock;
char buff[1024];

typedef struct
{
    int flag;
    int x;
    int y;
}nuocdi;
nuocdi gogo;
char color[BOARD_SIZE]= {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 0, 7, 7, 7, 7, 7, 0, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        1, 7, 1, 7, 1, 7, 1, 7, 1,
        7, 1, 7, 7, 7, 7, 7, 1, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        1, 1, 1, 1, 1, 1, 1, 1, 1
};
char piece[BOARD_SIZE]= {
        5, 3, 2, 1, 6, 1, 2, 3, 5,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 4, 7, 7, 7, 7, 7, 4, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        0, 7, 0, 7, 0, 7, 0, 7, 0,
        7, 4, 7, 7, 7, 7, 7, 4, 7,
        7, 7, 7, 7, 7, 7, 7, 7, 7,
        5, 3, 2, 1, 6, 1, 2, 3, 5
};

unsigned long   nodecount, brandtotal = 0, gencount = 0;
char    ply, side, xside, computerside=0;
move    newmove;
gen_rec gen_dat[MOVE_STACK];
short   gen_begin[HIST_STACK], gen_end[HIST_STACK];
hist_rec hist_dat[HIST_STACK];
short   hdp;
void Gen(void);
 
short GetHumanMove(int from,int t)
{
    int revedBytes;
    static short x = 4, y = 5;
    long int i;
    int count = 0;
    short ch,selecting = 0;
    Gen();       /* for check legal move only */
    while(1){
    //nhan du lieu tu client
    revedBytes = recv(conn_sock,buff,1024,0);
    buff[revedBytes] = '\0';
    from = (int)buff[0];
    t = (int)buff[1];
    if(color[from]==side){
        newmove.from = from; newmove.dest = t;
        for (i=gen_begin[ply]; i<gen_end[ply]; i++)
        if (gen_dat[i].m.from==newmove.from && gen_dat[i].m.dest==newmove.dest){
            return 0;
            }
        }
    buff[0] = 0;
    buff[1] = '\0';
    send(conn_sock,buff,1024,0);//tra ve loi
    }
}

short offset[7][8] =
        {{-1, 1,13, 0, 0, 0, 0, 0},     /* PAWN {for DARK side} */
        {-12,-14,12,14,0,0,0,0},        /* BISHOP */
        {-28,-24,24,28, 0, 0, 0, 0 },   /* ELEPHAN */
        {-11,-15,-25,-27,11,15,25,27},  /* KNIGHT */
        {-1, 1,-13,13, 0, 0, 0, 0},     /* CANNON */
        {-1, 1,-13,13, 0, 0, 0, 0},     /* ROOK */
        {-1, 1,-13,13, 0, 0, 0, 0}};    /* KING */
 
short mailbox182[182] =
        {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,-1,-1,
        -1,-1, 9,10,11,12,13,14,15,16,17,-1,-1,
        -1,-1,18,19,20,21,22,23,24,25,26,-1,-1,
        -1,-1,27,28,29,30,31,32,33,34,35,-1,-1,
        -1,-1,36,37,38,39,40,41,42,43,44,-1,-1,
        -1,-1,45,46,47,48,49,50,51,52,53,-1,-1,
        -1,-1,54,55,56,57,58,59,60,61,62,-1,-1,
        -1,-1,63,64,65,66,67,68,69,70,71,-1,-1,
        -1,-1,72,73,74,75,76,77,78,79,80,-1,-1,
        -1,-1,81,82,83,84,85,86,87,88,89,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
 
short mailbox90[90] =
        {28, 29, 30, 31, 32, 33, 34, 35, 36,
         41, 42, 43, 44, 45, 46, 47, 48, 49,
         54, 55, 56, 57, 58, 59, 60, 61, 62,
         67, 68, 69, 70, 71, 72, 73, 74, 75,
         80, 81, 82, 83, 84, 85, 86, 87, 88,
         93, 94, 95, 96, 97, 98, 99,100,101,
        106, 107,108,109,110,111,112,113,114,
        119, 120,121,122,123,124,125,126,127,
        132, 133,134,135,136,137,138,139,140,
        145, 146,147,148,149,150,151,152,153};
 
short legalposition[90] =
        {1, 1, 5, 3, 3, 3, 5, 1, 1,
        1, 1, 1, 3, 3, 3, 1, 1, 1,
        5, 1, 1, 3, 7, 3, 1, 1, 5,
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        9, 1,13, 1, 9, 1,13, 1, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9, 9, 9};
 
short maskpiece[7] = {8, 2, 4, 1, 1, 1, 2},
    knightcheck[8] = {1,-1,-9,-9,-1,1,9,9},
    elephancheck[8] = {-10,-8,8,10,0,0,0,0},
    kingpalace[9] = {3,4,5,12,13,14,21,22,23};
 
 
void InitGen(void)
{
    gen_begin[0] = 0; ply = 0; hdp = 0;
}
//Kiem tra doi mat tuong
short KingFace(short from, short dest)
{
    short i, k, t, r = 0;
    i = from % SIZE_X;
    if (i>=3 && i<=5 && piece[dest]!=KING) {
        t = piece[dest]; piece[dest] = piece[from]; piece[from] = EMPTY;
        i = 0;
        for (k=kingpalace[i]; piece[k]!=KING; k++) ;
        for (k += SIZE_X; k<BOARD_SIZE && piece[k]==EMPTY; k += SIZE_X);
        if (piece[k]==KING) r = 1;
        piece[from] = piece[dest]; piece[dest] = t;
    }
    return r;
}

void Gen_push(short from, short dest)
{
    if (!KingFace(from, dest)) {
        gen_dat[gen_end[ply]].m.from = from;
        gen_dat[gen_end[ply]].m.dest = dest;
        gen_end[ply]++;
    }
}

void Gen(void)
{
    short i, j, k, n, p, x, y, t, fcannon;
 
    gen_end[ply] = gen_begin[ply];
 
    for(i=0; i < BOARD_SIZE; i++)
        if (color[i]==side) {
            p = piece[i];
            for(j=0; j<8; j++) {
                if (!offset[p][j]) break;
                x = mailbox90[i]; fcannon = 0;
                if (p==ROOK || p==CANNON) n = 9; else n = 1;
                for (k=0; k<n; k++) {
                    if (p==PAWN && side==LIGHT) x -= offset[p][j]; else x += offset[p][j];
 
                    y = mailbox182[x];
                    if (side == DARK) t = y; else t = 89-y;
                    if (y==-1 || (legalposition[t] & maskpiece[p])==0) break;
                    if (!fcannon) {
                        if (color[y]!=side)
                            switch (p) {
                            case KNIGHT: if (color[i+knightcheck[j]]==EMPTY) Gen_push(i, y); break;
                            case ELEPHAN:if (color[i+elephancheck[j]]==EMPTY) Gen_push(i, y); break;
                            case CANNON: if (color[y]==EMPTY) Gen_push(i, y); break;
                            default: Gen_push(i, y);
                            }
                        if (color[y]!=EMPTY) { if (p==CANNON) fcannon++; else break; }
                    }
                    else {  /* CANNON switch */
                        if (color[y] != EMPTY) {
                            if (color[y]==xside) Gen_push(i, y);
                            break;
                        }
                    }
                } /* for k */
            } /* for j */
    }
 
    gen_end[ply+1] = gen_end[ply]; gen_begin[ply+1] = gen_end[ply];
    brandtotal += gen_end[ply] - gen_begin[ply]; gencount++;
}
short MakeMove(move m)
{
    short from, dest, p;
    nodecount++;
    from = m.from; dest = m.dest;
    hist_dat[hdp].m = m; hist_dat[hdp].capture = p = piece[dest];
    piece[dest] = piece[from]; piece[from] = EMPTY;
    color[dest] = color[from]; color[from] = EMPTY;
    hdp++; ply++; side = xside; xside = 1-xside;
    return p == KING;
}
 
 
void UnMakeMove(void)
{
    short from, dest;
    hdp--; ply--; side = xside; xside = 1-xside;
    from = hist_dat[hdp].m.from; dest = hist_dat[hdp].m.dest;
    piece[from] = piece[dest]; color[from] = color[dest];
    piece[dest] = hist_dat[hdp].capture;
    if (piece[dest] == EMPTY) color[dest] = EMPTY; else color[dest] = xside;
}
 
 
short UpdateNewMove(void)
{
    short from, dest, p;
    from = newmove.from; dest = newmove.dest; p = piece[dest];
    piece[dest] = piece[from]; piece[from] = EMPTY;
    color[dest] = color[from]; color[from] = EMPTY;
    return p == KING;
}
 
 
/***** EVALUATE *****/
short Eval(void)
{
    static short piecevalue[7] = {10, 20, 20, 40, 45, 90, 1000};
    short   i, s = 0;
    for (i=0; i<BOARD_SIZE; i++)
        if (color[i]==side) s += piecevalue[piece[i]];
        else if (color[i]==xside) s -= piecevalue[piece[i]];
    return s;
}

short AlphaBeta(short alpha, short beta, short depth)
{
    short i, value, best;
    if (!depth) return Eval();
    Gen();
    best = -INFINITY;
    for (i=gen_begin[ply]; i<gen_end[ply] && best<beta; i++) {
        if (best > alpha) alpha = best;
 
        if (MakeMove(gen_dat[i].m)) value = 1000-ply;
        else value = -AlphaBeta(-beta, -alpha, depth-1);
        UnMakeMove();
        if (value > best) {
            best = value; if (!ply) newmove = gen_dat[i].m;
        }
    }
 	
    return best;
}
void ComputerThink(void)
{
    short best;
    nodecount = 0;
    best = AlphaBeta(-INFINITY, INFINITY, MAX_PLY);
    //printf("%ld\n",nodecount);
}
void todo(){
	InitGen();
	if (side == computerside) ComputerThink();
        else if (GetHumanMove(0,1));
        side = xside; xside = 1-xside;
    printf("%d:%d\n",newmove.from,newmove.dest);
    UpdateNewMove();
}

void sig_chld(int signo)
{
pid_t pid;
int stat;
while((pid = waitpid(-1, &stat, WNOHANG))>0)
printf("child %d terminated\n", pid);
return;
}
int check_thang(){
    int i;
return 1;
}
int check_thua(){
return 0;
}



int main()
{
int listen_sock;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

listen_sock = socket(AF_INET, SOCK_STREAM, 0);
if (listen_sock == -1)
 {
    printf("khong tao duoc socket\n");
    return 0;
 }
 printf("Tao socket thanh cong\n");

server_address.sin_family = AF_INET;
inet_aton("127.0.0.1",&server_address.sin_addr);
server_address.sin_port = htons(5500);
server_len = sizeof(server_address);

if(bind(listen_sock, (struct sockaddr *)&server_address,server_len)<0)
{
	printf("bind failed.\n");
    return 0;
}
printf("bind done\n");
int check = listen(listen_sock, 10);
if (check == -1)
 {
 printf("error");
 return 0;
 }
printf("waiting connect ...\n");
while(1) {

client_len = sizeof(client_address);
conn_sock = accept(listen_sock,(struct sockaddr *)&client_address, &client_len);
if(conn_sock==-1){
	printf("error connect\n");
	return 0;
}else{
	printf("Accept new connection\n");
}
if(fork() == 0){
	close(listen_sock);
    //thiet lap truyen nhan giu lieu lien tuc
	int sentBytes,revedBytes,i;
    while(1){
        //nhan va kiem tra co bao
        revedBytes = recv(conn_sock,buff,1024,0);
        switch(buff[0]){
            case 0:
            /// dang nhap
            //lay du lieu
            //kiem tra dang nhap
            //gui ket qua cho client
            printf("Dang nhap\n");
            strcpy(buff,"Dang nhap");
            sentBytes = send(conn_sock,buff,1024,0);
            break;
            case 1: 
            //dang ky
            //lay du lieu
            //kiem tra dang nhap
            //gui ket qua cho client
            printf("Dang ky\n");
            strcpy(buff,"Dang ky");
            sentBytes = send(conn_sock,buff,1024,0);
            break;
            case 2:
                side = 1 ;xside = 0;
                InitGen();
                    while(1){
                            if(side == computerside){
                                ComputerThink();
                                printf("%d may choi\n",side);
                                UpdateNewMove();
                                buff[0] = newmove.from;
                                buff[1] = newmove.dest;
                                buff[2] = 0;
                                buff[3] = '\0';
                                //check thua tai day
                                send(conn_sock,buff,1024,0);
                            }
                            else 
                                if(GetHumanMove(0,1)==0){
                                    UpdateNewMove();                        
                                    buff[0] = 1;
                                    buff[2] = 1;
                                    buff[3] = '\0';
                                    //check thang tai day
                                    send(conn_sock,buff,1024,0);
                                    //tra ve neu di thanh cong
                                };

                            side = xside; xside = 1-xside;
                            printf("%d-%d-%d\n",side,newmove.from,newmove.dest);
            	    }
            break;
            default:
            break;
        	    
        }
    }
    close(conn_sock);
    exit(0);
}
signal(SIGCHLD,sig_chld);
close(conn_sock);
}
return 1;
}