<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
    
    // get parameters
    $parameter = array_map('trim', explode(",", urldecode($_GET["geo"])));    
    
    // SQL
    $sql = "SELECT * FROM places WHERE ";
    for ($i = 0, $count = count($parameter); $i < $count; $i++) {
        // if parameter is a number, it is the postal code
        if (is_numeric($parameter[$i])) {
            $sql .= 'postal_code LIKE "' . $parameter[$i] . '%"';
        } else {
            $sql .= 
                '(place_name  LIKE "' . $parameter[$i] . '%")';
        }
        
        if ($i < ($count - 1)) {
            $sql .= " AND ";
        }
    }
    // contact the database
    $places = query($sql);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
