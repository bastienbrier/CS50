<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
        // check if the user entered a symbol
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        
        // check for the symbol
        $stock = lookup($_POST["symbol"]);
        
        // if it does not exist
        if ($stock === false)
        {
            apologize("This symbol does not exist.");
        }
        else
        {
            render("quote.php", ["stock" => $stock]);
        }
    }
?>
