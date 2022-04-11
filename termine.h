#define DPROG "termine"
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_pvirtfuehraus,
	T_Fuege_ein, //ω
	T_Kann_Termindatei,
	T_lstat_fehlgeschlagen,
	T_bei_Datei,
	T_einzulesen,
	T_Zeit_von,
	T_eindeutige_ID_Prim,
	T_Bezug_auf_terminakt,
	T_Pat_ID_aus_namen,
	T_Terminzeitpunkt,
	T_Raum,
	T_Zusatz,
	T_Zeitpunkt_der_Aktualisierung,
	T_UTC_Dateiaenderung,
	T_in_Klammern_angegebenes_Geburtsdatum,
	T_Termine,
	T_prueftbtab,
	T_frc_k,
	T_force_l,
	T_neu_Einlesen_erzwingen,
	T_MAX //α
}; // enum T_ //ω
void prueftbtab(DB *My, const string& tbtab, const int obverb, const int oblog, const uchar direkt=0);
//α
class hhcl:public dhcl
{
	private: 
		uchar anhl=0;    // <DPROG> anhalten
		uchar frc=0;    // Einlesen erzwigen
		string dszahl="30"; // Datensatzzahl fuer Tabellenausgaben
		//ω
		string quelldat{"/DATA/Patientendokumente/plz/TMFTools.pdf"};
		string datei{quelldat+".txt"};
		size_t aktc{0};
		string tbtab{"termine"};
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista{0};
		long listz{30}; //ω
	public: //α //ω
	private: //α //ω
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=nix);
		void pvirtvorrueckfragen();
		void neurf();
		void pvirtnachrueckfragen();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
}; // class hhcl //ω
