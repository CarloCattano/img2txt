Adapted from Daniel Shifmann image/video to ascii originally in p5.js
uses stb_image.h and stb_image_resize.h

to be used in (ft_ascii)[https://github.com/carlocattano/ft_ascii]

Written in c with stb headers only library.

### Usage:

Build the tool

```
./build.sh
```

Run

```
./img2txt <image.(png/jpg)> -s size -c 256
```

You can also pipe an image into the program:

```
cat image.jpg | ./img2txt
wget -O - <url_to_image> | ./img2txt
```

_img2txt_ picture.jpg, will default to your current terminal size

```

.. .'',-^'-^^^^^^-,.   .'   .'-''',-'.     ..         .'.  .          . .,
   .''',-'-^^^^^^,'    ''  .,''.              .       ..             ....'
   .''',,.^^^c^^^,.   ''.  .''           .'...,,.  '' ..             .'.',
   .''..'.-^^c^--'  ','  .'.,--   .   .'' -c''cc',^-'.   ...         ''..,
   ','..''^^^^-,'  ..,,.  ^-.,c^  ,^, 'co.,o ,o.,c',,,,'''',.        '. .'
  .',' .,,,''--,'......,, .cc..c^. ,o^ .o. ^  ^ .,.-,','''','     .'--.
 ..'''.',.    '--^-,^^-'^c  cc  -^  .^  .-  -  -..-,^'-,.'','.  .,-'...
.......',.     ,,cc^, c  c'  c'  -^  .^  ,,  -  c --^-^cc^-^--^c^'
....,-^^-', . 'c'o',' c. -^  'o   -^  .^  -, .o '^,^-c-??c^^^^-.
',,^^c,,,.^ - ,-.?.,, ^-  o'  ,^   ^,  -,  ^' ^-.^-^^cc^-,--.
,,-^'- ^'.^ ^ ', c  ^  c  'c   ^^  .o   o  '^ ^'^-^^^^----,c,
^.o -. c '- ^.., ^. c. ^.  o.  .?   o,  c, ,,.^-c^^^^----^,^^
 -, ^ ,- -' ^. - ^' ,^ '-  c-   o-  ^c  o' - -'^^-^^---,-^,.,.           '
 ^ -. c .-,.-. ^ '^  c,.^  ^c   ,?.  o  c -.,,-^^^^^-,-,^--^c'          .,
,--- -- ^.-.-'.-, --  ^-,  ,?.   ,?, .,-'^,'--^^^^---,-,,-^-o.          .,
.-o..o..c ^'-'-.-, ,-  c-   co.   o?  ^..?.^^occ^---,,,--^^c?,          .-
 c^ ,o -^.^,,-,^'--.-^ .o    ??   ?o  ^ -^'^ccoo^^,,--,',-,-?o          '^
 o, -c c',-'-'-'^-'^.^, c^   'O- .11  ^... .,^^cc^--,--,,^c-c?^        .,^
 o, ^^ c.^,-,,,-',-,^'o'.1'   ?- ,O1,         .-^-''----^--co?^        .-^
 o- ^-'^^-^-,,,'-,,--^,c -?   ', ,c'           .,,.-  '.,^^,co-        '^^
 cc -^'c^^^-,,,,,,,-,^--^ ^o,' ..             .'' '..,,-^^oocc^.      .-^^
 ^o c^^^cc-----,,-^-^,c'c, o11o^              ',.   . ,^^coo^^^'      ,^^^
 oo-?oooo^-----,,--^-^-^,o .^?c'             .,'     .,'  .,,,-'     .-^^^
^???1???oc^-------^^c-^c,?-. '               .'       --,, ,-,'    .',---^
?11111???o^^^-----^^,c-o^o?o-       .        .       .,^^-',,.    .',,,---
111111??ooc----^----^^oo?c-^.      ..        .      .''''.       ..--',,,-
????????ooc^---^--,-co???c'        ....               .           '^^'.',,

```

### Image:

zebra.jpg [Author](https://www.publicdomainpictures.net/en/view-image.php?image=455680&picture=zebra)
License: CC0 Public Domain
