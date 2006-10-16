#include "aktionen.h"


using namespace std;

extern pthread_mutex_t  mutexAktionsliste;
extern Aktionsliste* lAktionsliste;

void *AktionenSammeln( void *ptr)
{
pthread_mutex_lock(&mutexAktionsliste);
Aktionsliste* lLetzterEintrag=0;
pthread_mutex_unlock(&mutexAktionsliste);

// Nach Start des Kontrollprogramms (zum Beispiel über ein Init-Script) setzt man dann DTR auf High - die LED wird grün und die Eingänge können geschaltet werden. Die vier Eingänge CD, DSR, CTS und RI werden über fünf Taster und einen gemeinsamen Vorwiderstand von 10 kOhm mit dem Ausgang DTR verbunden

int fd=0;
Aktionsliste* lNeu=0;
int currstat=0;
//int tmp=0;
ptr=0;

 if((fd = open("/dev/ttyS0", O_RDWR | O_NDELAY)) < 0)
 {
 	cout << "Fehler beim Öffnen der seriellen Schnittstelle! " << fd << endl;
 } 
 else
 {
	/* Panel initialisieren*/
	currstat = TIOCM_DTR;
        ioctl(fd, TIOCMSET, &currstat);

	for(;;)
	{
		delete lNeu;
		lNeu = 0;
		ioctl(fd, TIOCMGET, &currstat);       /* Schnittstellenstatus lesen */
		//Wer weiß ob wir das brauchen
		currstat &= ~(TIOCM_DTR | TIOCM_RTS); /* LED-Status abschneiden */ 
//		cout << "Aktueller Status: " << currstat << endl;
		switch(currstat)
		{
			case TIOCM_CD: //64
 				lNeu = new Aktionsliste(Hoch);
 			break;
			case TIOCM_DSR: //256
 				lNeu = new Aktionsliste(Runter);
 			break;
			case TIOCM_CTS: //32
 				lNeu = new Aktionsliste(Rechts);
 			break;
			case TIOCM_RI: //128
 				lNeu = new Aktionsliste(Links);
 			break;
// 			case 66:
// 				lNeu = new Aktionsliste(Runter);
// 				break;
		// Ungenutze Kombinationen
		// 	case TIOCM_DTS:
		// 		return tVor;
		// 	break;
		// 	case (TIOCM_DSR | TIOCM_CAR) :
		// 		return tPlayliste_loeschen;
		// 	break;
		// 	case (TIOCM_DSR | TIOCM_CTS) :
		// 		return tStop;
		// 	break;	
		}
/*		cout << "Ihr Eingabe bitte: ";
		cin >> tmp; 
		switch(tmp)
		{
			case 8:
			lNeu = new Aktionsliste(Hoch);
			break;
		
			case 2:
			lNeu = new Aktionsliste(Runter);
			break;
		
			case 6:
			lNeu = new Aktionsliste(Rechts);
			break;
		
			case 4:
			lNeu = new Aktionsliste(Links);
			break;
		}*/
// 		if (lNeu!=0)
// 		{
// 		cout << lNeu->GetAktion() << endl;
// 		}
		pthread_mutex_lock(&mutexAktionsliste);
//		cout << "aliste: "<<lAktionsliste<< "lneu: " << lNeu << endl;
		if ((lAktionsliste==0) && (lNeu != 0))  //Erster Eintrag oder abgearbeitete Liste
		{
			lAktionsliste = lNeu;
		}
		else if ((lAktionsliste!=0) && (lNeu != 0))  //Kleiner Rückstau in der Aktionsliste. Wird schon abgearbeitet
		{
			lLetzterEintrag = lAktionsliste;
			while (lLetzterEintrag->Naechster!= 0)
				lLetzterEintrag = lLetzterEintrag->Naechster;
			lAktionsliste->Naechster = lNeu;
		}
		pthread_mutex_unlock(&mutexAktionsliste);

		usleep(350000);                        /* 250ms Delay */
		//Willkürlich, kürzer= mehr last aber reaktisonschneller
	}
}
}
