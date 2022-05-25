<html>
<head>
	<title>Affichage nom stations + nb releve</title>
</head>
<body>
	<?php
	$bdd = new PDO('mysql:host=localhost;dbname=basemarine2022','root','');
	$bdd->exec("set names utf8"); ?>

	<?php

	$req=$bdd->query('SELECT nom, COUNT(*) AS nombredereleve FROM releves INNER JOIN stations ON releves.idStation=stations.idStation GROUP BY nom;');
	while ($ligne = $req->fetch())
	{
		echo $ligne['nom']." il y a ".$ligne['nombredereleve']." relevé(s) <br/>";
		echo "\n";
	}
	?>

	<?php
	$req=$bdd->query('SELECT MAX(t) AS tempmax FROM releves;');
	while ($ligne = $req->fetch())
	{
		echo "<br/><br/>La temperature max est de ".$ligne['tempmax']." Kelvin <br/>";
	}
	?>

	<?php
	$req=$bdd->query('SELECT nom, dateheure FROM releves INNER JOIN stations ON releves.idStation=stations.idStation HAVING MAX(t);');
	while ($ligne = $req->fetch())
	{
		echo "<br/><br/>La station avec la temperature max est ".$ligne['nom']." le ".$ligne['dateheure']." <br/><br/><br/>";
	}
	?>

	<?php
	$req=$bdd->query('SELECT nom, MIN(t) AS tempmin, MAX(t) AS tempmax FROM releves INNER JOIN stations ON releves.idStation=stations.idStation GROUP BY nom;');
	while ($ligne = $req->fetch())
	{
		echo "La station ".$ligne['nom']." a eu pour temperature min : ".$ligne['tempmin']." et pour temperature max : ".$ligne['tempmax']."</br>";
	}
	?>

</body>
</html>