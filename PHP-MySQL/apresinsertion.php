<html>
    <body>
    <meta charset="utf-8">
    <?php
    $i=0;
    $bdd = new PDO('mysql:host=localhost;dbname=basemarine2022', 'root', '');
    $req=$bdd->query('SELECT idStation FROM stations');
    while($ligne = $req->fetch()){
        if($ligne['idStation']==$_POST['ID']){
            $i=1;
        }
    }

    if($_POST['ID']==''){
        $i=1;
    }


    if($i==1){
        echo "ajout impossible.";
    }
    else{
        if($_POST['Long']<>'' and $_POST['Lat']<>''){
            $req=$bdd->exec("INSERT INTO `stations`(`latitude`, `longitude`, `idStation`, `nom`) 
                VALUES ('".$_POST['Lat']."','".$_POST['Long']."','".$_POST['ID']."','".$_POST['Nom']."');");
                echo "ajout reussit";
            }

            else{
                $req=$bdd->exec("INSERT INTO `stations`(`latitude`, `longitude`, `idStation`, `nom`) 
                    VALUES (NULL,NULL,'".$_POST['ID']."','".$_POST['Nom']."');");
                    echo "ajout reussit";
                }
        }
        ?>
    </body>
</html>
