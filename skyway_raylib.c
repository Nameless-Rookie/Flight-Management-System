// SkyWay Flight Management - Raylib GUI
// Real Indian Airport Data | 40 Airports | 80 Routes
#include "raylib.h"
#include "flight_data.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RESULTS 20
#define PANELW 900
#define PANELH 620

typedef enum { TAB_SEARCH, TAB_RESULTS, TAB_AIRPORTS, TAB_ABOUT } Tab;

// State
static Tab tab = TAB_SEARCH;
static int selOrigin = -1, selDest = -1, selAirline = 0;
static int timeHour = 14, timeMin = 0;
static int results[MAX_RESULTS], resCnt = 0;
static int scroll = 0, apScroll = 0;
static bool darkMode = true;
static char searchMsg[128] = "";

// Colors
#define C_BG (darkMode ? (Color){15,14,23,255} : (Color){245,247,250,255})
#define C_CARD (darkMode ? (Color){26,25,50,255} : (Color){255,255,255,255})
#define C_TEXT (darkMode ? (Color){232,230,240,255} : (Color){26,26,46,255})
#define C_TEXT2 (darkMode ? (Color){154,151,176,255} : (Color){100,100,120,255})
#define C_PRIMARY (darkMode ? (Color){129,140,248,255} : (Color){37,99,235,255})
#define C_ACCENT (Color){167,139,250,255}
#define C_BORDER (darkMode ? (Color){40,38,70,255} : (Color){224,228,234,255})
#define C_BTNHOV (darkMode ? (Color){99,102,241,255} : (Color){29,78,216,255})
#define C_GREEN (Color){34,197,94,255}
#define C_RED (Color){239,68,68,255}

static const char *airlines[] = {"Browse All","Air India","IndiGo","SpiceJet","Vistara","GoFirst"};
#define NUM_AIRLINES 6

bool Btn(int x,int y,int w,int h,const char*txt,Color bg){
    Rectangle r={x,y,w,h}; bool hov=CheckCollisionPointRec(GetMousePosition(),r);
    DrawRectangleRounded(r,0.4,8,hov?C_BTNHOV:bg);
    int tw=MeasureText(txt,14); DrawText(txt,x+(w-tw)/2,y+(h-16)/2,14,WHITE);
    return hov&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void DrawCard(int x,int y,int w,int h){
    DrawRectangleRounded((Rectangle){x,y,w,h},0.03,8,C_CARD);
    DrawRectangleRoundedLines((Rectangle){x,y,w,h},0.03,8,C_BORDER);
}

int timeToMin(const char*t){int h=0,m=0;sscanf(t,"%d:%d",&h,&m);return h*60+m;}
int timeDiff(const char*ft,int ph,int pm){
    int f=timeToMin(ft),p=ph*60+pm,d=abs(f-p);
    if(d>720)d=1440-d; return d;
}

static int resDiffs[MAX_RESULTS]; // time diff in minutes for each result
static char searchTier[16] = "";  // "exact","window","sameday","none"

// Sort helper: bubble sort results by diff then price
void sortResults(){
    for(int i=0;i<resCnt-1;i++) for(int j=0;j<resCnt-1-i;j++){
        int da=resDiffs[j],db=resDiffs[j+1];
        int pa=routes[results[j]].price,pb=routes[results[j+1]].price;
        if(da>db||(da==db&&pa>pb)){
            int t=results[j];results[j]=results[j+1];results[j+1]=t;
            t=resDiffs[j];resDiffs[j]=resDiffs[j+1];resDiffs[j+1]=t;
        }
    }
}

void doSearch(){
    resCnt=0; searchMsg[0]=0; searchTier[0]=0;
    if(selOrigin<0||selDest<0){strcpy(searchMsg,"Select origin & destination");return;}
    if(selOrigin==selDest){strcpy(searchMsg,"Origin and destination must differ");return;}

    // Collect all route matches
    int allIdx[80],allDiff[80],allCnt=0;
    for(int i=0;i<NUM_ROUTES;i++){
        if(routes[i].originIdx!=selOrigin||routes[i].destIdx!=selDest)continue;
        if(selAirline>0&&strcmp(routes[i].airline,airlines[selAirline])!=0)continue;
        allIdx[allCnt]=i; allDiff[allCnt]=timeDiff(routes[i].depTime,timeHour,timeMin);
        allCnt++;
    }
    if(allCnt==0){sprintf(searchMsg,"No flights %s -> %s",airports[selOrigin].code,airports[selDest].code);return;}

    // Tier 1: Exact (<=15 min)
    for(int i=0;i<allCnt&&resCnt<MAX_RESULTS;i++) if(allDiff[i]<=15){results[resCnt]=allIdx[i];resDiffs[resCnt]=allDiff[i];resCnt++;}
    if(resCnt>0){strcpy(searchTier,"exact");sortResults();tab=TAB_RESULTS;scroll=0;return;}

    // Tier 2: ±3hr window
    for(int i=0;i<allCnt&&resCnt<MAX_RESULTS;i++) if(allDiff[i]<=180){results[resCnt]=allIdx[i];resDiffs[resCnt]=allDiff[i];resCnt++;}
    if(resCnt>0){strcpy(searchTier,"window");sortResults();tab=TAB_RESULTS;scroll=0;return;}

    // Tier 3: Same day — all, sorted by proximity
    for(int i=0;i<allCnt&&resCnt<MAX_RESULTS;i++){results[resCnt]=allIdx[i];resDiffs[resCnt]=allDiff[i];resCnt++;}
    strcpy(searchTier,"sameday");sortResults();tab=TAB_RESULTS;scroll=0;
}

void DrawDropdown(int x,int y,int w,const char*label,const char*items[],int cnt,int*sel,int id){
    DrawText(label,x,y,10,C_TEXT2);
    Rectangle r={x,y+14,w,32};
    DrawRectangleRounded(r,0.3,8,darkMode?(Color){30,28,55,255}:(Color){248,249,251,255});
    DrawRectangleRoundedLines(r,0.3,8,C_BORDER);
    const char*txt=(*sel>=0&&*sel<cnt)?items[*sel]:"-- Select --";
    DrawText(txt,x+8,y+22,13,C_TEXT);
    DrawText("v",x+w-16,y+22,13,C_TEXT2);
}

int main(void){
    SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_WINDOW_RESIZABLE);
    InitWindow(960,680,"SkyWay - Flight Management System");
    SetTargetFPS(60);

    // Build airport name list
    const char* apNames[NUM_AIRPORTS];
    char apBuf[NUM_AIRPORTS][64];
    for(int i=0;i<NUM_AIRPORTS;i++){sprintf(apBuf[i],"%s - %s",airports[i].code,airports[i].city);apNames[i]=apBuf[i];}

    bool showOriginDD=false,showDestDD=false,showAirlineDD=false;
    int originScr=0,destScr=0;

    while(!WindowShouldClose()){
        int W=GetScreenWidth(),H=GetScreenHeight();
        int px=(W-PANELW)/2, py=8;

        // Mouse
        Vector2 mp=GetMousePosition();
        bool clicked=IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        float wheel=GetMouseWheelMove();

        BeginDrawing();
        ClearBackground(C_BG);

        // === NAV BAR ===
        DrawRectangle(0,0,W,48,C_CARD);
        DrawLine(0,48,W,48,C_BORDER);
        DrawText("SkyWay",px+8,14,20,C_PRIMARY);
        // Nav buttons
        int tx=px+140;
        for(int i=0;i<4;i++){
            const char*labels[]={"Search","Results","Airports","About"};
            int tw=MeasureText(labels[i],14)+20;
            Rectangle nr={tx,8,tw,32};
            bool hov=CheckCollisionPointRec(mp,nr);
            if(tab==i)DrawRectangleRounded(nr,0.5,8,C_PRIMARY);
            else if(hov)DrawRectangleRounded(nr,0.5,8,(Color){C_PRIMARY.r,C_PRIMARY.g,C_PRIMARY.b,40});
            DrawText(labels[i],tx+10,16,14,tab==i?WHITE:C_TEXT2);
            if(hov&&clicked)tab=i;
            tx+=tw+6;
        }
        // Dark mode toggle
        Rectangle togR={W-px-70,12,56,24};
        DrawRectangleRounded(togR,0.5,8,darkMode?(Color){60,58,90,255}:(Color){200,205,215,255});
        int thumbX=darkMode?W-px-70+32:W-px-70+2;
        DrawCircle(thumbX+10,24,10,WHITE);
        DrawText(darkMode?"D":"L",thumbX+6,18,12,C_PRIMARY);
        if(CheckCollisionPointRec(mp,togR)&&clicked)darkMode=!darkMode;

        // === CONTENT AREA ===
        int cy=60;

        if(tab==TAB_SEARCH){
            // Hero
            DrawText("Plan your journey with ease",px+PANELW/2-MeasureText("Plan your journey with ease",22)/2,cy,22,C_TEXT);
            cy+=30;
            DrawText("Search, compare & book flights across 40 Indian airports",px+PANELW/2-MeasureText("Search, compare & book flights across 40 Indian airports",12)/2,cy,12,C_TEXT2);
            cy+=40;

            // Search card
            DrawCard(px,cy,PANELW,220);
            int cx=px+20,fy=cy+16;

            // Origin
            DrawText("FROM",cx,fy,10,C_TEXT2);
            Rectangle orR={cx,fy+14,200,32};
            DrawRectangleRounded(orR,0.3,8,darkMode?(Color){30,28,55,255}:(Color){248,249,251,255});
            DrawRectangleRoundedLines(orR,0.3,8,showOriginDD?C_PRIMARY:C_BORDER);
            DrawText(selOrigin>=0?apBuf[selOrigin]:"Select Origin",cx+8,fy+22,12,selOrigin>=0?C_TEXT:C_TEXT2);
            if(CheckCollisionPointRec(mp,orR)&&clicked){showOriginDD=!showOriginDD;showDestDD=false;showAirlineDD=false;}

            // Dest
            int dx=cx+220;
            DrawText("TO",dx,fy,10,C_TEXT2);
            Rectangle deR={dx,fy+14,200,32};
            DrawRectangleRounded(deR,0.3,8,darkMode?(Color){30,28,55,255}:(Color){248,249,251,255});
            DrawRectangleRoundedLines(deR,0.3,8,showDestDD?C_PRIMARY:C_BORDER);
            DrawText(selDest>=0?apBuf[selDest]:"Select Destination",dx+8,fy+22,12,selDest>=0?C_TEXT:C_TEXT2);
            if(CheckCollisionPointRec(mp,deR)&&clicked&&!showOriginDD){showDestDD=!showDestDD;showOriginDD=false;showAirlineDD=false;}

            // Time
            int ttx=dx+220;
            DrawText("PREFERRED TIME",ttx,fy,10,C_TEXT2);
            char timeBuf[16]; sprintf(timeBuf,"%02d:%02d",timeHour,timeMin);
            Rectangle tmR={ttx,fy+14,100,32};
            DrawRectangleRounded(tmR,0.3,8,darkMode?(Color){30,28,55,255}:(Color){248,249,251,255});
            DrawRectangleRoundedLines(tmR,0.3,8,C_BORDER);
            DrawText(timeBuf,ttx+8,fy+22,13,C_TEXT);
            // +/- buttons for time
            if(Btn(ttx+105,fy+14,28,15,"+",C_PRIMARY)){timeHour=(timeHour+1)%24;}
            if(Btn(ttx+105,fy+31,28,15,"-",C_PRIMARY)){timeHour=(timeHour+23)%24;}
            if(Btn(ttx+138,fy+14,28,15,"+",C_PRIMARY)){timeMin=(timeMin+30)%60;}
            if(Btn(ttx+138,fy+31,28,15,"-",C_PRIMARY)){timeMin=(timeMin+30)%60;}

            // Airline
            int ax=ttx+180;
            DrawText("AIRLINE",ax,fy,10,C_TEXT2);
            Rectangle alR={ax,fy+14,150,32};
            DrawRectangleRounded(alR,0.3,8,darkMode?(Color){30,28,55,255}:(Color){248,249,251,255});
            DrawRectangleRoundedLines(alR,0.3,8,showAirlineDD?C_PRIMARY:C_BORDER);
            DrawText(airlines[selAirline],ax+8,fy+22,12,C_TEXT);
            if(CheckCollisionPointRec(mp,alR)&&clicked&&!showOriginDD&&!showDestDD){showAirlineDD=!showAirlineDD;}

            // Search button
            fy+=60;
            if(Btn(px+PANELW/2-70,fy,140,36,"Search Flights",C_PRIMARY)) doSearch();
            fy+=44;
            DrawText("Smart search: exact -> +/-3hr -> closest on same day",px+PANELW/2-MeasureText("Smart search: exact -> +/-3hr -> closest on same day",11)/2,fy,11,C_TEXT2);

            if(searchMsg[0]){fy+=24;DrawText(searchMsg,px+PANELW/2-MeasureText(searchMsg,13)/2,fy,13,C_RED);}

            // Offer cards
            fy+=50;
            const char*offers[]={"Early Bird\nSave Rs.2000","Weekend Sale\n15% off","Business Class\nUpgrade deal","Student\n10% off"};
            Color ocols[]={{102,126,234,255},{240,147,251,255},{79,172,254,255},{67,233,123,255}};
            for(int i=0;i<4;i++){
                int ox=px+i*225;
                DrawRectangleRounded((Rectangle){ox,fy,210,70},0.15,8,ocols[i]);
                DrawText(offers[i],ox+12,fy+14,12,WHITE);
            }

            // === DROPDOWNS (drawn on top) ===
            if(showOriginDD){
                int ddy=fy-140; // positioned below origin field
                Rectangle ddR={cx,cy+62,200,200};
                DrawRectangleRounded(ddR,0.05,8,C_CARD);
                DrawRectangleRoundedLines(ddR,0.05,8,C_PRIMARY);
                if(CheckCollisionPointRec(mp,ddR))originScr-=(int)wheel*2;
                if(originScr<0)originScr=0; if(originScr>NUM_AIRPORTS-8)originScr=NUM_AIRPORTS-8;
                BeginScissorMode(cx,cy+62,200,200);
                for(int i=originScr;i<NUM_AIRPORTS&&i<originScr+10;i++){
                    int iy=cy+62+(i-originScr)*20;
                    Rectangle ir={cx,iy,200,20};
                    bool h=CheckCollisionPointRec(mp,ir);
                    if(h)DrawRectangleRec(ir,(Color){C_PRIMARY.r,C_PRIMARY.g,C_PRIMARY.b,40});
                    DrawText(apBuf[i],cx+6,iy+3,11,h?C_PRIMARY:C_TEXT);
                    if(h&&clicked){selOrigin=i;showOriginDD=false;}
                }
                EndScissorMode();
            }
            if(showDestDD){
                Rectangle ddR={cx+220,cy+62,200,200};
                DrawRectangleRounded(ddR,0.05,8,C_CARD);
                DrawRectangleRoundedLines(ddR,0.05,8,C_PRIMARY);
                if(CheckCollisionPointRec(mp,ddR))destScr-=(int)wheel*2;
                if(destScr<0)destScr=0; if(destScr>NUM_AIRPORTS-8)destScr=NUM_AIRPORTS-8;
                BeginScissorMode(cx+220,cy+62,200,200);
                for(int i=destScr;i<NUM_AIRPORTS&&i<destScr+10;i++){
                    int iy=cy+62+(i-destScr)*20;
                    Rectangle ir={cx+220,iy,200,20};
                    bool h=CheckCollisionPointRec(mp,ir);
                    if(h)DrawRectangleRec(ir,(Color){C_PRIMARY.r,C_PRIMARY.g,C_PRIMARY.b,40});
                    DrawText(apBuf[i],cx+226,iy+3,11,h?C_PRIMARY:C_TEXT);
                    if(h&&clicked){selDest=i;showDestDD=false;}
                }
                EndScissorMode();
            }
            if(showAirlineDD){
                int ax2=cx+620;
                Rectangle ddR={ax2,cy+62,150,NUM_AIRLINES*22+4};
                DrawRectangleRounded(ddR,0.05,8,C_CARD);
                DrawRectangleRoundedLines(ddR,0.05,8,C_PRIMARY);
                for(int i=0;i<NUM_AIRLINES;i++){
                    int iy=cy+64+i*22;
                    Rectangle ir={ax2,iy,150,22};
                    bool h=CheckCollisionPointRec(mp,ir);
                    if(h)DrawRectangleRec(ir,(Color){C_PRIMARY.r,C_PRIMARY.g,C_PRIMARY.b,40});
                    DrawText(airlines[i],ax2+8,iy+4,12,h?C_PRIMARY:C_TEXT);
                    if(h&&clicked){selAirline=i;showAirlineDD=false;}
                }
            }
        }
        else if(tab==TAB_RESULTS){
            // Tier status banner
            Color tierCol=C_GREEN; char tierMsg[128];
            if(strcmp(searchTier,"exact")==0){sprintf(tierMsg,"Exact match! %d flight(s) at %02d:%02d",resCnt,timeHour,timeMin);tierCol=C_GREEN;}
            else if(strcmp(searchTier,"window")==0){sprintf(tierMsg,"No exact match for %02d:%02d — %d flight(s) within +/-3hrs",timeHour,timeMin,resCnt);tierCol=C_PRIMARY;}
            else{sprintf(tierMsg,"No flights near %02d:%02d — showing %d closest option(s)",timeHour,timeMin,resCnt);tierCol=(Color){245,158,11,255};}
            DrawRectangleRounded((Rectangle){px,cy,PANELW,28},0.3,8,(Color){tierCol.r,tierCol.g,tierCol.b,30});
            DrawText(tierMsg,px+14,cy+7,12,tierCol);
            cy+=36;
            char hdr[64]; sprintf(hdr,"%d flights: %s -> %s",resCnt,airports[selOrigin].code,airports[selDest].code);
            DrawText(hdr,px,cy,16,C_TEXT); cy+=24;
            if(Btn(px+PANELW-120,cy-22,110,22,"< Back",C_PRIMARY)){tab=TAB_SEARCH;}

            scroll-=(int)wheel*40; if(scroll<0)scroll=0;
            BeginScissorMode(px,cy,PANELW,H-cy-10);
            for(int i=0;i<resCnt;i++){
                int ry=cy+i*90-scroll;
                if(ry<cy-90||ry>H)continue;
                FlightRoute f=routes[results[i]];
                DrawCard(px,ry,PANELW,80);
                // Airline
                DrawText(f.airline,px+16,ry+12,15,C_TEXT);
                DrawText(f.number,px+16,ry+30,11,C_TEXT2);
                // Time diff badge
                int dm=resDiffs[i]; char diffBuf[32];
                if(dm<=15)sprintf(diffBuf,"Exact match"); else{int dh=dm/60,dmm=dm%60;if(dh&&dmm)sprintf(diffBuf,"%dhr %dmin away",dh,dmm);else if(dh)sprintf(diffBuf,"%dhr away",dh);else sprintf(diffBuf,"%dmin away",dmm);}
                Color dc=dm<=15?C_GREEN:dm<=180?C_PRIMARY:(Color){245,158,11,255};
                DrawText(diffBuf,px+16,ry+48,9,dc);
                // Route
                int rx=px+180;
                DrawText(airports[f.originIdx].code,rx,ry+10,18,C_TEXT);
                DrawText(airports[f.originIdx].city,rx,ry+30,10,C_TEXT2);
                char dep[16]; sprintf(dep,"%s",f.depTime);
                DrawText(dep,rx,ry+48,11,C_PRIMARY);
                // Line
                DrawLine(rx+100,ry+25,rx+240,ry+25,C_BORDER);
                DrawText(">>>",rx+160,ry+18,12,C_TEXT2);
                // Dest
                DrawText(airports[f.destIdx].code,rx+260,ry+10,18,C_TEXT);
                DrawText(airports[f.destIdx].city,rx+260,ry+30,10,C_TEXT2);
                DrawText("Direct",rx+260,ry+48,11,C_TEXT2);
                // Price
                char price[32]; sprintf(price,"Rs.%d",f.price);
                int prx=px+PANELW-160;
                DrawText(price,prx,ry+14,20,C_PRIMARY);
                DrawText("per person",prx,ry+38,10,C_TEXT2);
                Btn(prx,ry+52,90,22,"Book",C_PRIMARY);
            }
            EndScissorMode();
        }
        else if(tab==TAB_AIRPORTS){
            DrawText("40 Indian Airports",px,cy,18,C_TEXT); cy+=8;
            char sub[64]; sprintf(sub,"Across %d+ states and union territories",20);
            DrawText(sub,px,cy+18,12,C_TEXT2); cy+=42;

            apScroll-=(int)wheel*30; if(apScroll<0)apScroll=0;
            BeginScissorMode(px,cy,PANELW,H-cy-10);
            // Table header
            int ty=cy-apScroll;
            DrawRectangleRounded((Rectangle){px,ty,PANELW,24},0.1,8,C_PRIMARY);
            DrawText("CODE",px+10,ty+5,11,WHITE);
            DrawText("CITY",px+70,ty+5,11,WHITE);
            DrawText("AIRPORT",px+220,ty+5,11,WHITE);
            DrawText("STATE",px+580,ty+5,11,WHITE);
            DrawText("ROUTES",px+PANELW-70,ty+5,11,WHITE);
            ty+=28;
            for(int i=0;i<NUM_AIRPORTS;i++){
                if(ty<cy-24||ty>H){ty+=22;continue;}
                if(i%2==0)DrawRectangle(px,ty,PANELW,22,(Color){C_PRIMARY.r,C_PRIMARY.g,C_PRIMARY.b,15});
                DrawText(airports[i].code,px+10,ty+4,12,C_PRIMARY);
                DrawText(airports[i].city,px+70,ty+4,12,C_TEXT);
                // Truncate airport name
                char apn[40]; strncpy(apn,airports[i].airport,35); apn[35]=0;
                DrawText(apn,px+220,ty+4,11,C_TEXT2);
                DrawText(airports[i].state,px+580,ty+4,11,C_TEXT);
                int rc=0; for(int j=0;j<NUM_ROUTES;j++) if(routes[j].originIdx==i||routes[j].destIdx==i)rc++;
                char rcb[8]; sprintf(rcb,"%d",rc);
                DrawText(rcb,px+PANELW-50,ty+4,12,C_ACCENT);
                ty+=22;
            }
            EndScissorMode();
        }
        else if(tab==TAB_ABOUT){
            DrawCard(px,cy,PANELW,280);
            DrawText("SkyWay Flight Management System",px+20,cy+20,20,C_PRIMARY);
            DrawText("Built with Raylib 5.5 | Real Indian Airport Data",px+20,cy+48,13,C_TEXT2);
            cy+=80;
            DrawText("STATISTICS",px+20,cy,12,C_ACCENT);
            char s1[64],s2[64],s3[64],s4[64];
            sprintf(s1,"Airports: %d",NUM_AIRPORTS);
            sprintf(s2,"Flight Routes: %d",NUM_ROUTES);
            sprintf(s3,"Airlines: 5 (Air India, IndiGo, SpiceJet, Vistara, GoFirst)");
            sprintf(s4,"States Covered: 20+");
            DrawText(s1,px+20,cy+20,14,C_TEXT); DrawText(s2,px+20,cy+40,14,C_TEXT);
            DrawText(s3,px+20,cy+60,14,C_TEXT); DrawText(s4,px+20,cy+80,14,C_TEXT);
            cy+=120;
            DrawText("OOP CONCEPTS",px+20,cy,12,C_ACCENT);
            DrawText("[CO1] Classes & Objects",px+20,cy+20,13,C_TEXT);
            DrawText("[CO2] Encapsulation",px+20,cy+38,13,C_TEXT);
            DrawText("[CO3] Arrays & Collections",px+20,cy+56,13,C_TEXT);
            DrawText("[CO4] Inheritance",px+20,cy+74,13,C_TEXT);
        }

        // Footer
        DrawText("SkyWay (c) 2025 | 40 Airports | 80 Routes | Raylib 5.5",px,H-18,10,C_TEXT2);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
