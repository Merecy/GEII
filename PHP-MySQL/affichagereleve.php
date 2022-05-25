<html>
<body>
    <?php
    echo "Le nom est : ".$_POST['choixstation']."</br>";
    ?>


    <?php
    $bdd = new PDO('mysql:host=localhost;dbname=basemarine2022', 'root', '');
    $req=$bdd->query("SELECT nom, longitude, latitude FROM stations WHERE nom='".$_POST['choixstation']."';");
    $b=0;
    while($ligne = $req->fetch()){
        if(($ligne['longitude']==NULL) and ($ligne['latitude']==NULL)){
            echo "c'est un bateau !</br>";
            $b=1;
        }
        else{
            echo "c'est une boue !</br>";
            $b=2;
        }
    }
    ?>

    <?php
    if($b==2){
        $req=$bdd->query("SELECT nom, longitude, latitude FROM stations WHERE nom='".$_POST['choixstation']."';");
        while($ligne = $req->fetch()){
            echo "Sa longitude est : ".$ligne['longitude'].", sa latitude est : ".$ligne['latitude']."</br>";
        }
    }
    if($b==1){
       $req=$bdd->query("SELECT nom, AVG(releves.longitude) AS longitudemoy, AVG(releves.latitude) AS latitudemoy FROM releves INNER JOIN stations ON stations.idStation=releves.idStation WHERE nom='".$_POST['choixstation']."';");
       while($ligne = $req->fetch()){
        echo "Sa longitude moyenne est : ".$ligne['longitudemoy'].", sa latitude moyenne est : ".$ligne['latitudemoy']."</br>";
    }
}
?>

<?php
echo "</br>";
$req=$bdd->query("SELECT nom, dateheure, MAX(t) AS maxTemp, ff FROM releves INNER JOIN stations ON stations.idStation=releves.idStation WHERE nom='".$_POST['choixstation']."' ORDER BY dateheure DESC");
while($ligne = $req->fetch()){
    $max=$ligne['maxTemp'];
}



$req=$bdd->query("SELECT nom, dateheure, MIN(t) AS minTemp, ff FROM releves INNER JOIN stations ON stations.idStation=releves.idStation WHERE nom='".$_POST['choixstation']."' ORDER BY dateheure DESC");
while($ligne = $req->fetch()){
    $min=$ligne['minTemp'];
}


$req=$bdd->query("SELECT nom, dateheure, t, ff FROM releves INNER JOIN stations ON stations.idStation=releves.idStation WHERE nom='".$_POST['choixstation']."' ORDER BY dateheure DESC");
while($ligne = $req->fetch()){
    $str=$ligne['dateheure'];
    $annee=substr($str,0,-10);
    $mois=substr($str,4,-8);
    $jour=substr($str,6,-6);
    $heure=substr($str,8,-4);
    $min=substr($str,10,-2);

    if($ligne['t']==$min){
        echo "<span style='color:blue'>Date : ".$jour."/".$mois."/".$annee." a : ".$heure."h".$min.", temperature : ".($ligne['t']-273)."°C, vent : ".($ligne['ff']*3.6)." km/h</span></br>";
    }

    else if($ligne['t']==$max){
        echo "<span style='color:red'>Date : ".$jour."/".$mois."/".$annee." a : ".$heure."h".$min.", temperature : ".($ligne['t']-273)."°C, vent : ".($ligne['ff']*3.6)." km/h</span></br>";
    }

    else{
    echo "Date : ".$jour."/".$mois."/".$annee." a : ".$heure."h".$min.", temperature : ".($ligne['t']-273)."°C, vent : ".($ligne['ff']*3.6)." km/h</br>";
}
}
?>

<?php 
echo "</br>";
$req=$bdd->query("SELECT nom, AVG(t) AS moytemp, AVG(ff) AS moyvent FROM releves INNER JOIN stations ON stations.idStation=releves.idStation WHERE nom='".$_POST['choixstation']."'");
while($ligne = $req->fetch()){
    echo "La moyenne de temperature sur cette station est de : ".($ligne['moytemp']-273)."°C, et la moyenne de vent est de : ".($ligne['moyvent']*3.6)." km/h</br>";
}
?>
</body>
</html>