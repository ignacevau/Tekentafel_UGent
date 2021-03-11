# Tekentafel_UGent
<i>UGent ingenieursproject 2</i>

<h2>git remote opzetten</h2>
open linux terminal in de juiste folder:

// maak .git folder aan
\n<i>git init</i>

// connect de remote en test
\n<i>git remote add origin https://github.com/ignacevau/Tekentafel_UGent</i>
\n<i>git fetch origin</i>
\n<i>git remote -v</i>

om te pullen type
\n<i>git pull origin master</i>

of type
\n<i>git branch --set-upstream-to=origin/master master</i>

en dan kan je gwn dit typen
\n<i>git pull</i>

om je local files te vergelijken met de origin type
\n<i>git status</i>

om te pushen naar origin voegt ge eerst u files toe
\n<i>git add .</i>

dan committen
\n<i>git commit -m "type hier u message bvb blabla error gefixt"</i>

dan u commits pushen naar origin
\n<i>git push</i>

ait da is alles denkik gwn zorgen da ge eerst een pull doet voorda ge begint te coden

btwww als ge u credentials ng nie in global hebt gezet dan moet ge da eerst doen voorda ge kunt pushen
\n<i>git config --global user.email "u email adres"</i>
\n<i>git config --global user.name "u github naam"</i>