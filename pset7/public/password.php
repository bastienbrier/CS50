<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("password_form.php", ["title" => "Password"]);
    }
    
    // if reached via POST
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // query database for user
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        
        // check if the boxes are filled
        if (empty($_POST["password"]))
        {
            apologize("You must type your password.");
        }
        else if (empty($_POST["new_password"]))
        {
            apologize("You must choose a new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
        else
        {
            // first row
            $row = $rows[0];
            
            // check if it is the good password
            if (crypt($_POST["password"], $row["hash"]) != $row["hash"])
            {
                apologize("Wrong password.");
            }
            else
            {
                // if the new password and confirmation don't match
                if ($_POST["new_password"] != $_POST["confirmation"])
                {
                    apologize("The new password and the confirmation don't match");
                }
                // change the password
                else
                {
                    $password = query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $SESSION["id"]);
                    redirect('/');
                }
            }
        }
    }

?>
