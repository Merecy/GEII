<html>
<body>
    <form method="post" action="affichagereleve.php">
        <p><select name="choixstation">
            <?php
            $bdd = new PDO('mysql:host=localhost;dbname=basemarine2022', 'root', '');
            $bdd->exec("set names utf8");
            $req=$bdd->query('SELECT nom FROM stations ORDER BY nom DESC;');
            while ($ligne = $req->fetch())
            {
                echo "<option value=".$ligne['nom'].">".$ligne['nom']."</option>";
                echo "\n";
            }
            ?>
        </select>
        <input type="submit" value="OK" /></p>
    </form>
</body>
</html>