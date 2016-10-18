<?php

    // configuration
    require("../includes/config.php"); 

    $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
    $cash = query("SELECT cash FROM users where id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $stock["price"] * $row["shares"]
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);

?>
