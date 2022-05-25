var dateDebut = document.getElementById("dd");
var dateFin =  document.getElementById("df");

console.log(dateDebut.value)
console.log(dateFin.value)

var tableau1 = document.getElementById("t1");
console.log(tableau1.getAttribute("src"));
var test = tableau1.getAttribute("src")+"&start="+dateDebut.value+"&2000:00:00";
console.log(test);
tableau1.src=test
console.log(tableau1.getAttribute("src"));


    

function updateBtn(){
    console.log("JE BOUTON");
   

    // document.getElementsByTagName("h2")[0].style.color='red';

}

// function updateBtn() {
//   if (OkBtn.value === 'Ok') {
//     OkBtn.value = 'Arrêter la machine';
//     var Valeur1 = document.getElementsById("dd");
//     var Valeur2 = document.getElementsById("df");
//     var Url1 = document.getElementsById("T1");
//     var Url2 = document.getElementsById("T2");
//     var Url3 = document.getElementsById("T3");
// 	Url3.src ="https://thingspeak.com/channels/1566233/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=120&title=Debit+Instantane&type=line&xaxis=Date&yaxis=Litre%28s%29+par+seconde"+"&"+Valeur1.value+"&2000:00:00"
//   }
// }

// OkBtn.onclick = function(element) {
// var Valeur1 = document.getElementsById("dd");
// var Valeur2 = document.getElementsById("df");
// console.log(Valeur1);
// console.log(Valeur2);
// }
