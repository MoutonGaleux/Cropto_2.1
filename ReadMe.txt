
Cropto -- ReadMe

(Cropto vient d'une faute de frappe lors de la cr�ation du premier projet, je voulais mettre Crypto, mais je trouve l'erreur sympa du coup c'est rest� ;) )



Le main est cod� juste pour un fichier html (mais pour les autres types de fichier c'est sur le m�me principe)


Je n'ai pas encore cod� CCroptoKey 
- je pense faire un algo qui d�chiffre un ".txt" et garde la clef "en clair" en m�moire vive 
- et peut-�tre un syst�me pour cr�er sa clef en entrant les valeurs num�rique des "char" que l'on veut dans sa clef

Je voudrait aussi faire une classe CCroptoOdt, mais j'arrive pas � trouver de documentation claire pour comprendre le m�canisme de zippage des odt :'(

Lors de mes tests, j'ai utilis� des mot de passes et mes po�mes en .txt comme clef de chiffrement.


Le chiffrement se fait en mode aller-retour sur la clef, et somme le char � chiffrer avec le char de la clef (et ignore, le cas �ch�ant le 9� bit)

ex : clef "abcd" ; et texte � chiffrer nomm� t

t[0] += 'a';
t[1] += 'b';
t[2] += 'c';
t[3] += 'd';
t[4] += 'd';
t[5] += 'c';
t[6] += 'b';
t[7] += 'a';
t[8] += 'a';
t[9] += 'b';
...

Au d�but j'avais ajout� un compteur sur le nombre d'utilisation de la clef pour faire

 t[x] += c[x]*n;

mais au bout d'un certain nombre d'incr�mentation �a devenait foireux :'(


Si vous avez des questions, n'h�sitez pas ;)


