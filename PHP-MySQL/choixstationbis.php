<html>
<body>
    <form method="post" action="affichagerelevebis.php">
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
        <select name="heure">
            <option value='01'>01h</option>
            <option value='02'>02h</option>
            <option value='03'>03h</option>
            <option value='04'>04h</option>
            <option value='05'>05h</option>
            <option value='06'>06h</option>
            <option value='07'>07h</option>
            <option value='08'>08h</option>
            <option value='09'>09h</option>
            <option value='10'>10h</option>
            <option value='11'>11h</option>
            <option value='12'>12h</option>
            <option value='13'>13h</option>
            <option value='14'>14h</option>
            <option value='15'>15h</option>
            <option value='16'>16h</option>
            <option value='17'>17h</option>
            <option value='18'>18h</option>
            <option value='19'>19h</option>
            <option value='20'>20h</option>
            <option value='21'>21h</option>
            <option value='22'>22h</option>
            <option value='23'>23h</option>
            <option value='24'>00h</option>
        </select>
        <input type="submit" value="OK" />
    </form></p>
</body>
</html>