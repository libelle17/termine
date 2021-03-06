// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "termine.h"
#include <list>
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]={
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_pvirtfuehraus,
	{"pvirtfuehraus()","pvirtexecute()"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_Kann_Termindatei,
	{"Kann Termindatei '","Cannot open file '"},
	// T_lstat_fehlgeschlagen,
	{"lstat fehlgeschlagen: ","lstat failed: "},
	// T_bei_Datei,
	{" bei Datei: "," for file: "},
	// T_einzulesen
	{"einzulesen: ","to load up: "},
	// T_Zeit_von
	{"Zeit von ","Time of "},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw;

using namespace std; //ω
hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
	dhcl::pvirtVorgbSpeziell(); //α
	hLog(violetts+Txk[T_Ende]+Tx[T_pvirtVorgbSpeziell]+schwarz);
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{ //ω
	opn<<new optcl(/*pptr*/&anhl,/*art*/puchar,T_st_k,T_stop_l,/*TxBp*/&Tx,/*Txi*/T_DPROG_anhalten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
} // void hhcl::pvirtmacherkl //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dhcl::virtMusterVorgb(); //α
	hLog(violetts+Txk[T_Ende]+Tx[T_virtMusterVorgb]+schwarz); //ω
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω
// wird aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=nix*/)
{
	dhcl::virtzeigversion(ltiffv);  //ω
} // void hhcl::virtzeigversion //α
//ω
//α
// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
} // void hhcl::pvirtvorrueckfragen //α


void hhcl::neurf()
{
	for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
		omit--;
		if (!(*omit)->Txtrf.empty()) {
			const char* const text=(*omit)->Txtrf.c_str();
			cout<<text<<endl;
		}
	}
} // void hhcl::neurf
 //ω

// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	fLog(violetts+Tx[T_virtpruefweiteres]+schwarz,obverb,oblog); //ω
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	hcl::virtpruefweiteres(); // z.Zt. leer //α
	//	DB My(MySQL,host,muser,mpwd,/*conz*/1,dbq);
		if (initDB()) {
			exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));
		}
		const string sql{"CREATE TABLE IF NOT EXISTS `"+tbtab+"`(id int(10) auto_increment key, pid int(10) comment 'Pat_Id aus namen',zp datetime comment 'Terminzeitpunkt', zusatz varchar(400) comment 'Beschreibung und Eintragender', abgerufen datetime comment 'UTC-Zeitpunkt der Dateiänderung TMFTools', `gebdat` DATETIME COMMENT 'in Klammern angegebenes Geburtsdatum', aktzeit datetime comment 'Zeitpunkt der aktualisierung', key zp (zp), key aktzeit(aktzeit),key pid (pid)) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_german2_ci ROW_FORMAT=DYNAMIC"}; //   , CONSTRAINT `pid_rel` FOREIGN KEY (`pid`) REFERENCES `namen` (`pat_id`) ON DELETE CASCADE ON UPDATE CASCADE

	RS rprueftm(My,tbtab);
	rprueftm.Abfrage(sql,aktc,obverb);
	if (rprueftm.obqueryfehler) { // wenn nicht Constraint-Name schon vergeben
		fLog(string("Fehler bei:")+sql+"': " +ltoan(rprueftm.obqueryfehler));
	}
} // void hhcl::virtpruefweiteres

// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	if (obverb) 
		hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
//α
// Parameter -st / --stop
// wird aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
} // void hhcl::anhalten() //α
//ω
//α
void hhcl::pvirtnachrueckfragen()
{
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
} // void hhcl::pvirtnachrueckfragen //α
//ω

void hhcl::pvirtfuehraus() //α
{ 
	hLog(violetts+Tx[T_pvirtfuehraus]+schwarz); //ω
	char cpt[MAXHOSTNAMELEN]; size_t cptlen{MAXHOSTNAMELEN};
	gethostname(cpt, cptlen);
	const string pdfzt{"test -f '"+datei+"' -a ! '"+datei+"' -ot '"+quelldat+"'||pdftotext -layout '"+quelldat+"' '"+datei+"'"}; //pdfzutext
	systemrueck(pdfzt.c_str(),obverb,oblog);
	struct stat s1{};
	if (obverb) cout<<Txk[T_datei]<<blau<<datei<<schwarz<<endl;
	if (lstat(datei.c_str(),&s1)) {
		fLog(string(Tx[T_lstat_fehlgeschlagen]) + strerror(errno) + Tx[T_bei_Datei]+drot+datei+schwarz,1,1);
		return;
	} // 	if (lstat(datei.c_str(),&s1))
	int einzulesen{0};
	struct tm ta{0}; // abgerufen
	memcpy(&ta,gmtime(&s1.st_mtime),sizeof ta); // hierbei Umwandlung in UTC
	char ***cerg;
	RS aktzmax(My,"SELECT MAX(abgerufen) FROM `"+tbtab+"`",aktc,ZDB); // dort als UTC gespeichert
	if (cerg=aktzmax.HolZeile(),cerg?*cerg:0) {
		struct tm tmj{0};
		strptime(cjj(cerg,0),"%Y-%m-%d %T",&tmj);
		time_t mktmj{mktime(&tmj)};
		if (obverb) cout<<"MAX(abgerufen) FROM "<<tbtab<<": "<<blau<<cjj(cerg,0)<<schwarz<<" = "<<blau<<mktmj<<schwarz<<endl;
		char buf[100];
		strftime(buf, sizeof(buf), "%Y-%m-%d %T (%z; %Z)", &ta);
		time_t tta{mktime(&ta)};
		if (obverb) cout<<Tx[T_Zeit_von]<<drot<<datei<<schwarz<<": "<<blau<<buf<<schwarz<<" (UTC)"<<" = "<<blau<<tta<<schwarz<<endl;
		if (mktmj<tta) einzulesen=1; // ta und tta sind UTC, s1.st_mtime nicht
		if (obverb) cout<<"=> "<<Tx[T_einzulesen]<<blau<<einzulesen<<schwarz<<endl;
	} else {
		einzulesen=1;
	} // 	if (cerg=aktzmax.HolZeile(),cerg?*cerg:0) else

	if (einzulesen) {
		FILE* const infile{fopen(datei.c_str(),"r")};
		if (!infile) {
			perror((string("\n")+Tx[T_Kann_Termindatei]+datei+Txk[T_nicht_zum_Lesen_oeffnen]).c_str());
			return;
		} // 		if (!infile)
		RS start(My,"START TRANSACTION",aktc,ZDB);
		char Zeile[256];
		vector<instyp> einf;
		//		list<string> zn{};
		struct uebt {
			string name;
			size_t p{0};
			size_t anf{0},len{0};
		} ue, uea[]{{"Nr."},{"PNr."},{"Tag"},{"Datum"},{"Uhr"},{"Patient"},{"Terminart"},{"Zusatz"}};
		uchar uefertig{0};
		//		size_t max{0};
		while (fgets(Zeile, sizeof Zeile, infile)) {
			string szn{Zeile};
			if (szn.find_first_not_of(" \r\n\f\t\v=")!=string::npos && (szn.find("Seite")==string::npos || szn.find(" vom ")==string::npos)) {
				if (obverb>1) cout<<":>"<<szn<<endl;
				char /*lfd[10],pids[11],*/wota[11],name[100],gebdat[21]/*,raum[21],zusatz[300]*/;
				/* *raum=0, *zusatz=0,*pids=0; */ 
				string lfd(10,0),pids(11,0),raum(21,0),zusatz(300,0);
				struct tm tzeit{0};
				if (szn.find("Terminart")!=string::npos && szn.find("Datum")!=string::npos) {
					if (!uefertig) {
						uefertig=1;
						uchar lbuch{0};
						for(size_t pos=0;pos<szn.length();pos++) {
							if ((szn[pos]==' '||pos==szn.length()-1) && lbuch) {
								for(size_t uep=0;uep<sizeof uea/sizeof *uea;uep++) {
									if (uea[uep].name.find(ue.name.substr(0,2))==0) {
										uea[uep].p=ue.p;
										break;
									} // 									if (uea[uep].name.find(ue.name.substr(0,2))==0)
								} // 								for(size_t uep=0;uep<sizeof uea/sizeof *uea;uep++)
								lbuch=0;
								ue.name.clear();
							} else if (szn[pos]!=' ') {
								if (!lbuch) {
									ue.p=pos;
									lbuch=1;
								} // 								if (!lbuch)
								ue.name+=szn[pos];
							} // if ((szn[pos] ...
						} // 				for(size_t pos=0;pos<szn.length();pos++)
						for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++) {
							if (uea[vnr].p) {
								if ((vnr && uea[vnr-1].p)||!vnr) uea[vnr].anf=uea[vnr].p-1;
								if (vnr<sizeof uea/sizeof *uea-1) {
									if (uea[vnr+1].p) uea[vnr].len=uea[vnr+1].p-uea[vnr].anf-1; 
								} 
								if (!uea[vnr].len) uea[vnr].len=(size_t)-1;
							} // 					if (uea[vnr].p)
						} // 				for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++)
						if (obverb) {
							for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++) {
								cout<<blau<<uea[vnr].p<<" "<<gruen<<uea[vnr].name<<schwarz<<" "<<uea[vnr].anf<<" "<<uea[vnr].len<<endl;
							} // 						for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++)
						}
					} // 				if (!uefertig)
				} else {
					for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++) {
						if ((uea[vnr].anf || uea[vnr].len) && uea[vnr].anf<szn.size()) {
							switch (vnr) {
								case 0: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%[^\1]",&lfd[0]); break;
								case 1: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%s",&pids[0]); break;
								case 2: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%s",&wota[0]); break;
								case 3: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%2d.%2d.%d",&tzeit.tm_mday,&tzeit.tm_mon,&tzeit.tm_year); break;
								case 4: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%2d:%2d",&tzeit.tm_hour,&tzeit.tm_min); break;
								case 5: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%[^\\(](%10[^\\)]",name,gebdat); break;
								case 6: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%s",&raum[0]); break;
								case 7: sscanf(szn.substr(uea[vnr].anf,uea[vnr].len).c_str(),"%[^\1]",&zusatz[0]); break;
							} // 						switch (vnr) 
						} // 					if ((uea[vnr].anf || uea[vnr].len) && uea[vnr].anf<szn.size())
					} // 				for(size_t vnr=0;vnr<sizeof uea/sizeof *uea;vnr++)
					if (tzeit.tm_year>2000) {
						tzeit.tm_mon--;
						tzeit.tm_year-=1900;
						if (obverb>1) {
							cout<<"lfdnr: '"<<blau<<lfd<<schwarz<<"', pids: '"<<blau<<pids<<schwarz<<"', wota: "<<blau<<wota<<schwarz<<", D: "<<blau<<put_time(&tzeit,"%Y-%m-%d %H:%M:%S")<<schwarz<<", name: "<<blau<<name<<schwarz<<", gebdat: "<<blau<<gebdat<<schwarz<<", raum: "<<blau<<raum<<schwarz<<", zusatz: "<<blau<<zusatz<<schwarz<<endl;
						} // 						if (obverb)
						string at1(asctime(&tzeit));
						at1 = at1.substr(0,at1.length()-1);
						if (isnumeric(pids.c_str())) {
							//							char buf[1000]{0};
							//							memset(buf,0,sizeof buf);
							time_t t{time(0)};
							struct tm *ts{gmtime(&t)};
							//caus<<"raum: '"<<raum<<"', gtrim(&raum): '"<<*gtrim(&raum)<<"', sqlft: '"<<sqlft(MySQL,gtrim(&raum))<<"'\n";
							//caus<<"zusatz: '"<<zusatz<<"', gtrim(&zusatz): '"<<*gtrim(&zusatz)<<"', sqlft: '"<<sqlft(MySQL,gtrim(&zusatz))<<"'\n";
							RS loe(My,"DELETE FROM `"+tbtab+"` WHERE zp="+sqlft(MySQL,&tzeit)+" AND raum="+sqlft(MySQL,raum)+" AND pid="+sqlft(MySQL,pids),aktc,ZDB);
							RS rins(My,tbtab); 
							einf.clear();
							einf.push_back(instyp(My->DBS,"pid",atol(pids.c_str())));
							einf.push_back(instyp(My->DBS,"zp",&tzeit));
							einf.push_back(instyp(My->DBS,"zusatz",gtrim(&zusatz)));
							einf.push_back(instyp(My->DBS,"raum",raum));
							einf.push_back(instyp(My->DBS,"aktzeit",ts));
							einf.push_back(instyp(My->DBS,"abgerufen",&ta));
							struct tm gtm{0};
							strptime(gebdat,"%d.%m.%Y",&gtm);
							einf.push_back(instyp(My->DBS,"gebdat",&gtm));
							rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0); 
							if (rins.fnr) {
								fLog(Txd[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
							} //         if (runde==1)
						} // if (isnumeric(pids)) 
					} // 					if (tzeit.tm_year>2000)
				} // 			if (szn.find("Terminart")!=string::npos)
				//				if (++max>100) break;
				//				zn.push_back(szn);
			} // if (szn.find_first_not_of(' ')!=string::npos)
		} // 		while (fgets(Zeile, sizeof Zeile, infile))
		RS commit(My,"COMMIT",aktc,ZDB);
		// My.insert(einf,&fehler,0,0);
		fclose(infile);
	} // 	if (einzulesen)
	// wait();
} // void hhcl::pvirtfuehraus  //α

// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{   //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige

// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
	// const int altobverb=obverb;
	// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
	// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
	const int altobverb=obverb;
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz);
	hcl::virtlieskonfein(); //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω
int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
} //ω
