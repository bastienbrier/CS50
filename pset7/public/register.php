<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO
        
        // check if username, password and confirmation exist
        if (empty($_POST["username"]))
        {
            apologize("You must provide a username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide a password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        
        // check if the password and the confirmation are equals
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("The password and the confirmation don't match.");
        }
        
        // insert the new user
        $newmember = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], crypt($_POST["password"]));
        
        // check if the username already exists
        if ($newmember === false)
        {
            apologize("Username already taken. Please select another one.");
        }
        
        // if it worked, log in automatically
        else
        {
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
            redirect("/");
        }
    }

?>
