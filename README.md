# Tekentafel_UGent
<i>UGent ingenieursproject 2</i>

<h2>git remote opzetten</h2>
open linux terminal in de juiste folder:

// maak .git folder aan
<i>git init</i>

// connect de remote en test
<i>git remote add origin https://github.com/ignacevau/Tekentafel_UGent</i>
<i>git fetch origin</i>
<i>git remote -v</i>

om te pullen type
<i>git pull origin master</i>

of type
<i>git branch --set-upstream-to=origin/master master</i>

en dan kan je gwn dit typen
<i>git pull</i>

om je local files te vergelijken met de origin type
<i>git status</i>

om te pushen naar origin voegt ge eerst u files toe
<i>git add .</i>

dan committen
<i>git commit -m "type hier u message bvb blabla error gefixt"</i>

dan u commits pushen naar origin
<i>git push</i>

ait da is alles denkik gwn zorgen da ge eerst een pull doet voorda ge begint te coden

btwww als ge u credentials ng nie in global hebt gezet dan moet ge da eerst doen voorda ge kunt pushen
<i>git config --global user.email "u email adres"</i>
<i>git config --global user.name "u github naam"</i>