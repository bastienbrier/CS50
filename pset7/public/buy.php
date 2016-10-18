<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if the forms have been filled, and that it's a positive integer
        if (empty($_POST["symbol"]))
        {
            apologize("Enter a stock you want to buy.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("Enter the number of shares you want to buy.");
        }
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Enter a positive integer please.");
        }
        else
        {
            // check the cash and the value of the desired stock
            $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            $stock = lookup($_POST["symbol"]);
            
            // if the user does not have enough cash
            if ($cash[0]["cash"] < $stock["price"] * $_POST["shares"])
            {
                apologize("You don't have enough cash.");
            }
            
            else
            {
                // insert the new stocks in the tables
                $insert = query("INSERT INTO stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE
                KEY UPDATE shares = shares + ?", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], $_POST["shares"]);
                
                // update cash
                $newcash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $stock["price"] * $_POST["shares"], $_SESSION["id"]);
                
                // update history
                $history = query("INSERT INTO history (id, transaction, time, symbol, shares, price) VALUES (?, 'BUY', CURRENT_TIMESTAMP, ?, ?, ?)",
                $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
                
                // redirect
                redirect('/');
            }
        }
    }
    else
    {
        render("buy.php", ["title" => "Buy"]);
    }
?>
