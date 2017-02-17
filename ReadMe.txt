
Cropto -- ReadMe

(Cropto vient d'une faute de frappe lors de la création du premier projet, je voulais mettre Crypto, mais je trouve l'erreur sympa du coup c'est resté ;) )



Le main est codé juste pour un fichier html (mais pour les autres types de fichier c'est sur le même principe)


Je n'ai pas encore codé CCroptoKey 
- je pense faire un algo qui déchiffre un ".txt" et garde la clef "en clair" en mémoire vive 
- et peut-être un système pour créer sa clef en entrant les valeurs numérique des "char" que l'on veut dans sa clef

Je voudrait aussi faire une classe CCroptoOdt, mais j'arrive pas à trouver de documentation claire pour comprendre le mécanisme de zippage des odt :'(

Lors de mes tests, j'ai utilisé des mot de passes et mes poèmes en .txt comme clef de chiffrement.


Le chiffrement se fait en mode aller-retour sur la clef, et somme le char à chiffrer avec le char de la clef (et ignore, le cas échéant le 9° bit)

ex : clef "abcd" ; et texte à chiffrer nommé t

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

Au début j'avais ajouté un compteur sur le nombre d'utilisation de la clef pour faire

 t[x] += c[x]*n;

mais au bout d'un certain nombre d'incrémentation ça devenait foireux :'(


Si vous avez des questions, n'hésitez pas ;)


