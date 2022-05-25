<html>
    <head>
        <title>Données par station et par heure</title>
    </head>
    <body>

    <p>Inserer une ville</p>
    
    <form method="post" action="choixstationbis5.php" id="chgstation">
        <p><b>Selectionnez une station</b></p>

    <?php
    $bdd = new PDO('mysql:host=localhost;dbname=basemarine2022','root','');
    ?>

    <select name="choixstation" onchange="document.forms['chgstation'].submit();">
    <option value="-1">--- Choix ---</option>
    <?php
    if(isset($_POST['choixstation']))
    {
        $nStatCh=$_POST['choixstation'];
    }
    else
    {
        $nStatCh=NULL;
    }


    echo "<p>la station est " . $nStatCh . "</p>";

    $req=$bdd->query("  SELECT nom,idStation
                        FROM stations");
    while($ligne = $req->fetch())
    {
        if($ligne['idStation']<>$nStatCh){
        echo "<option value=".$ligne['idStation'].">".$ligne['nom']."</option>";
        }
        else{
            echo"<option value=".$ligne['idStation']." selected>".$ligne['nom']."</option>";
        }
        echo "\n";
    }
    ?>

    </select>

    <select name="choixDateHeure">
        <?php
        if(isset($nStatCh) && $nStatCh != -1)
        {
            $req=$bdd->query("  SELECT dateheure
                                FROM releves
                                WHERE idStation='".$nStatCh."'
                                ORDER BY dateheure ASC");

            while($ligne = $req->fetch())
            {
                $str=$ligne['dateheure'];
                $annee=substr($str,0,-10);
                $mois=substr($str,4,-8);
                $jour=substr($str,6,-6);
                $heure=substr($str,8,-4);
                $min=substr($str,10,-2);
                echo "<option value=" .$ligne['dateheure'] . ">".$jour."/".$mois."/".$annee." a : ".$heure."h".$min.'</option>';
                echo "\n";
            }
        }
        ?>
        </select>
        <input type="submit" value="OK" formaction="affichagerelevebis5.php" />
    </form>
    </body>
</html>