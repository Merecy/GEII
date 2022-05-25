function updateBtn(){
   //console.log("JE BOUTON");

   var dateDebut = document.getElementById("dd");
   var dateFin =  document.getElementById("df");

   //console.log(dateDebut.value);
   //console.log(dateFin.value);

   var tableau1 = document.getElementById("t1");
   var tableau2 = document.getElementById("t2");
   var tableau3 = document.getElementById("t3");
   //console.log(tableau1.getAttribute("src"));

   var test1 = tableau1.getAttribute("src")+"&start="+dateDebut.value+"&2000:00:00"+"&end="+dateFin.value+"&2000:00:00";
   var test2 = tableau2.getAttribute("src")+"&start="+dateDebut.value+"&2000:00:00"+"&end="+dateFin.value+"&2000:00:00";
   var test3 = tableau3.getAttribute("src")+"&start="+dateDebut.value+"&2000:00:00"+"&end="+dateFin.value+"&2000:00:00";
   //console.log(test1);

   tableau1.src=test1;
   tableau2.src=test2;
   tableau3.src=test3;
   //console.log(tableau1.getAttribute("src"));
}
