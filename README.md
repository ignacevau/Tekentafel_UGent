# Tekentafel_UGent
UGent ingenieursproject 2

<h5>git remote opzetten</h5><br/>
open linux terminal in de juiste folder:

// maak .git folder aan
git init

// connect de remote en test
git remote add origin https://github.com/ignacevau/Tekentafel_UGent
git fetch origin
git remote -v

om te pullen type
git pull origin master

of type
git branch --set-upstream-to=origin/master master

en dan kan je gwn dit typen
git pull

om je local files te vergelijken met de origin type
git status

om te pushen naar origin voegt ge eerst u files toe
git add .

dan committen
git commit -m "type hier u message bvb blabla error gefixt"

dan u commits pushen naar origin
git push

ait da is alles denkik gwn zorgen da ge eerst een pull doet voorda ge begint te coden