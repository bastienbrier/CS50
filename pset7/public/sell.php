<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("Enter a stock you want to sell.");
        }
        
        else
        {
            // find the stocks the user has and what he wants to sell
            $shares = query("SELECT shares FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            $stock = lookup($_POST["symbol"]);
            
            // update history
            $history = query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, 'SELL', CURRENT_TIMESTAMP, ?, ?, ?)",
            $_SESSION["id"], $_POST["symbol"], $shares[0]["shares"], $stock["price"]);
            
            // update the cash
            $sale = query("UPDATE users SET cash = cash + ? WHERE id = ?", $stock["price"] * $shares[0]["shares"], $_SESSION["id"]);
            
            // delete the stock
            $sell = query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            
            redirect('/');
        }
    }
    
    else
    {
        $rows = query("SELECT symbol FROM stocks WHERE id = ?", $_SESSION["id"]);
        render("sell.php", ["rows" => $rows, "title" => "Sell"]);
    }

?>
