# Laboratorio di Intelligenza Artificiale e Grafica Interattiva (A.Y. 2015/2016)

## Hardware
La piattaforma utilizzata è MARRtino. MARRtino è un prototipo di robot mobile per fini didattici e di ricerca.  

Si tratta di una piattaforma mobile semplice e completa su ruote di costo limitato, che può avere diverse forme. La piattaforma robotica è composta da:
* Ruote, due ruote con un diametro di 144 mm e una larghezza di 29 mm, le quali rendono possibile lo spostamento della piattaforma. È presente anche un caster, una ruota multi direzionale per creare il terzo punto d’appoggio al fine di stabilizzare l’andamento.
* Motori, due motori collegati alle due ruote anteriori attraverso mozzi inalluminio.  I motori utilizzati sono alimentati a 12 V, a tale voltaggio ilmotore fa 150 giri / min, e hanno un rapporto di riduzione 70:1.  Queste unità hanno un albero di uscita a forma di D di un diametro di 6 mm.
* Arduino Mega, è una scheda a microcontrollore basata sull’ATmega1280.È dotato di 54 pin di ingresso / uscita digitali (di cui 14 utilizzabili come uscite PWM), 16 ingressi analogici, 4 UART (porte seriali hardware), una connessione USB, una presa di potenza, un’intestazione ICSP e un pulsante di reset.  L’Arduino Mega può essere alimentato tramite la connessione USB o tramite un’alimentazione esterna, che può venire da una batteria.
3.2 Software9La scheda può funzionare su un’alimentazione esterna da 6 a 20 Volt, mal’intervallo consigliabile è da 7 a 12 Volt, al di spora dei 12 V il regolatore di tensione potrebbe surriscaldarsi e danneggiare la scheda. La sorgente di alimentazione viene selezionata automaticamente.
* Arduino Motor Shield, si basa sull’integrato L298, doppio driver a ponte-H progettato per pilotare carichi induttivi come relè, solenoidi, motori DC e motori passo-passo. Questa Shield abbinata ad una scheda di sviluppoArduino consente di pilotare due motori DC, controllando la velocità ela direzione di ciascun motore in modo indipendente.  Inoltre permette di misurare l’assorbimento di corrente di ciascun motore. È consigliabile,per evitare eventuali danneggiamenti, alimentare Arduino Motor Shieldattraverso un’alimentazione esterna e non attraverso connessione USB, in quanto spesso la corrente richiesta dai motori eccede il massimo valore supportato dalle porte USB.
* Kinect, posta nella parte alta della piattaforma viene utilizzato per la visione,quindi  per  la  ricerca  degli  oggetti,  e  per  la  localizzazione.   Il  Kinect  èdotato di telecamera RGB, doppio sensore di profondità a raggi infrarossicomposto da uno scanner laser a infrarossi e da una telecamera sensibilealla stessa banda. La telecamera RGB ha una risoluzione di 640×480 pixel,mentre quella a infrarossi usa una matrice di 320×240 pixel. Kinect disponeanche di un array di microfoni utilizzato dal sistema per la calibrazionedell’ambiente in cui ci si trova.
* Batteria, una batteria con una potenza di 12 V utilizzata per alimentare imotori, Arduino, Kinect e la webcam, che sono stati collegati alla batteria attraverso un mammut elettrico.


## Software
 ROS (Robot Operating System) è un framework flessibile per la scrittura disoftware  dedicato  ai  robot.   Si  tratta  di  una  raccolta  di  strumenti,  librerie  convenzioni che semplificano il compito di far realizzare complesse attività a unavasta gamma di piattaforme robotizzate. I package di ROS usati per il progettosono:
 *  freenect, permette a ROS di interfacciarsi con il Kinect.
 *  depthimage to laserscan, partendo da una depth image genera una scansione laser 2D in base ai parametri forniti.
 *  move base, fornisce un’interfaccia ROS per la configurazione, l’esecuzionee l’interazione con lo stack di navigazione di un robot. Se viene eseguito il nodo move base su un robot correttamente configurato, questo cercherà di raggiungere un obiettivo con una tolleranza di errore specificata dall’utente. Se il robot se percepisce come bloccato, quindi non trova un percorso percorribile, esegue comportamenti di recupero. In primo luogo, gli ostacoli esterni ad una regione specificata dall’utente verranno eliminati dalla mappa del robot. Successivamente, se possibile, il robot esegue una rotazione sulla sua posizione per cercare una traiettoria percorribile. Se anche questo fallisce, il robot agirà in modo più aggressivo sulla mappa, rimuovendo tutti gli ostacoli esterni alla regione rettangolare in cui può ruotare. Quindisarà eseguita una rotazione in loco.  Se tutto ciò fallisce, il robot considererà il suo obiettivo impossibile e notifica all’utente che l’azione è statainterrotta.
* Actionlib, il pacchetto fornisce strumenti per creare un server che esegueazioni e un client che interagisce con il server.  I ROS topic che server eclient si possono scambiare sono i seguenti:
  * goal, usato dal client per inviare nuovi obiettivi al server.
  * cancel, usato dal client per cancellare la richiesta precedentementeinviata al server.
  * status, inviato dal server per notificare al client lo stato corrente diogni goals nel sistema.
  * feedback, il server invia periodicamente al client informazioni ausiliare riguardanti il goal inviato.
  * result, inviato dal server un’unica volta per inviare informazione al client riguardanti il completamento del goal.
* roscpp, è un’implementazione del client ROS in c++.
* std msgs, contiene wrapper per i tipi primitivi ROS. Inoltre contiene iltipo vuoto, utile per inviare un messaggio vuoto. Tuttavia, questi tipi non trasmettono un significato semantico sul loro contenuto, ogni messaggioha semplicemente un campo chiamato “dati”. Questo pacchetto contieneanche i tipi Multy Array, che possono essere utili per memorizzare i dati di un sensore.
* message generation.
* tf, è un pacchetto che consente all’utente di tenere traccia di più frame di coordinate nel tempo. tf mantiene la relazione tra i frame di coordinate in una struttura ad albero e consente all’utente di trasformare punti, vettori,ecc. tra due frame di coordinate in qualsiasi momento desiderato.
* openCV,
* srrg orazio core, è il pacchetto utilizzato per configurare il robot, la configurazione avviene online e le modifiche vengono memorizzate direttamente su Arduino. Le sezioni per la configurazione sono quattro:
  * System
  * Joint
  * Kinematic
  * Joystick
  
  Ogni pacchetto offrirà funzioni e tipi necessari per lo sviluppo del codice


