# Tekentafel_UGent
<i>UGent ingenieursproject 2</i>

<h2>git remote opzetten</h2>
open linux terminal in de juiste folder:

// maak .git folder aan
<br/><i>git init</i>

// connect de remote en test
<br/><i>git remote add origin https://github.com/ignacevau/Tekentafel_UGent</i>
<br/><i>git fetch origin</i>
<br/><i>git remote -v</i>

om te pullen type
<br/><i>git pull origin master</i>

of type
<br/><i>git branch --set-upstream-to=origin/master master</i>

en dan kan je gwn dit typen
<br/><i>git pull</i>

om je local files te vergelijken met de origin type
<br/><i>git status</i>

om te pushen naar origin voegt ge eerst u files toe
<br/><i>git add .</i>

dan committen
<br/><i>git commit -m "type hier u message bvb blabla error gefixt"</i>

dan u commits pushen naar origin
<br/><i>git push</i>

ait da is alles denkik gwn zorgen da ge eerst een pull doet voorda ge begint te coden

btwww als ge u credentials ng nie in global hebt gezet dan moet ge da eerst doen voorda ge kunt pushen
<br/><i>git config --global user.email "u email adres"</i>
<br/><i>git config --global user.name "u github naam"</i>