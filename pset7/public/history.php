<?php

    // configuration
    require("../includes/config.php"); 
    
    // check history
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    
    // render
    render("history.php", ["rows" => $rows, "title" => "History"]);
    
?>
